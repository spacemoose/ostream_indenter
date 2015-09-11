#pragma once

#include <locale>
#include <algorithm>
#include <iostream>
#include <iomanip>



/// Create the indenter facet which is constant, and knows its indentation level.
template <int ind_lev>
class indent_facet : public std::codecvt<char, char, std::mbstate_t> {
public:
	explicit indent_facet( int indent_level, size_t ref = 0)
		: std::codecvt<char, char, std::mbstate_t>(ref){}
	typedef std::codecvt_base::result result;
	typedef std::codecvt<char, char, std::mbstate_t> parent;
	typedef parent::intern_type intern_type;
	typedef parent::extern_type extern_type;
	typedef parent::state_type  state_type;

	int &state(state_type &s) const { return *reinterpret_cast<int *>(&s); }

protected:

	// Override so the do_out() virtual function is called.
	virtual bool do_always_noconv() const throw() override {
		return ind_lev==0;
	}


	/// The override of do_out, which uses the indentation level.
	/// Unfortunately, the debugger shows me that m_indentation_level is zero
	/// no matter how often I have called push.
	virtual result do_out(state_type &need_indentation,
		const intern_type *from, const intern_type *from_end, const intern_type *&from_next,
		extern_type *to, extern_type *to_end, extern_type *&to_next
		) const
	{
		result res = std::codecvt_base::noconv;
		for (; (from < from_end) && (to < to_end); ++from, ++to) {
			// 0 indicates that the last character seen was a newline.
			// thus we will print a tab before it. Ignore it the next
			// character is also a newline
			if ((state(need_indentation) == 0) && (*from != '\n')) {
				res = std::codecvt_base::ok;
				state(need_indentation) = 1;
				for(int i=0; i<ind_lev; ++i){
					*to = '\t'; ++to;
				}
				if (to == to_end) {
					res = std::codecvt_base::partial;
					break;
				}
			}
			*to = *from; // Copy the next character.

			// If the character copied was a '\n' mark that state
			if (*from == '\n') {
				state(need_indentation) = 0;
			}
		}

		if (from != from_end) {
			res = std::codecvt_base::partial;
		}
		from_next = from;
		to_next = to;

		return res;
	};

};




namespace indent_manip{

static const int index {  std::ios_base::xalloc()};

/// Here I create a new instance of the indent_facet class.  The
/// contructor is called, but but the imbued locale doesn't seem to
/// use the new instance.
static std::ostream & push(std::ostream& os)
{
	auto ilevel = ++os.iword(index);
	std::ios_base::sync_with_stdio(false);
	auto t = new indent_facet<2>;
	os.imbue(std::locale(os.getloc(), t));
	return os;
}

std::ostream& pop(std::ostream& os)
{
	auto ilevel = (os.iword(index)>0) ? --os.iword(index) : 0;
	os.imbue(std::locale(os.getloc(), new indent_facet(ilevel)));
	return os;
}

std::ostream& clear(std::ostream& os)
{
	os.iword(index)=0;
	os.imbue(std::locale(os.getloc(), new indent_facet(0)));
	return os;
}

/// Provides a RAII guard around your manipulation.
class guard
{
public:
	guard(std::ostream& os):m_oref(os){};
	~guard(){clear(m_oref);}
private:
	std::ostream& m_oref;
};
}

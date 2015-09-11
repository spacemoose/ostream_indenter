#include <locale>
#include <iostream>
#include <fstream>
#include <locale>
#include <iostream>

#include "indent_facet.hpp"


void call_me()
{
	std::cout << "- Maybe you have output in a function somehwere, but the indentation\n"
		"level is actually determined by the calling function.\n";
}

// For why this is necessary, see:
// http://stackoverflow.com/questions/26387054/how-can-i-use-stdimbue-to-set-the-locale-for-stdwcout
int main()
{
	std::ios_base::sync_with_stdio(false);
    std::cout.imbue(std::locale(std::cout.getloc(),new indent_facet(0)));
	indent_manip::guard img(std::cout);	// This is a RAII gaurd to ensure
										// clear() is called even if exceptio
										// is called.
	std::cout << "Why would you want to use indent manipulator?\n"
			  << indent_manip::push;

	call_me();
	std::cout << "- Okay, the single \t case is only a small saving, but...\n"
			  << indent_manip::push
			  << "+ imagine the benefits\n"
			  << "for nested indents!\n" << indent_manip::clear;
	std::cout<<"Note the indent_manipulator class uses RAII to guarentee that when this \n"
			 <<"functions exits, the indent level is cleared\n";

}

class indenting_streambuf : public std::streambuf
{

	std::streambuf* m_dest;
	int m_iLevel;


};

/// Here's a pretty good tutorial on custom buffers.
/// http://www.mr-edd.co.uk/blog/beginners_guide_streambuf
class caps_buffer : public std::streambuf
{
public:
	explicit caps_buffer(std::ostream& sink, std::size_t buff_sz = 256);
	bool do_caps_and_flush();

private:
	int_type overflow(int_type ch);
	int sync();

	// copying not allowed.
	caps_buffer(const caps_buffer&) = delete;

	caps_buffer& operator= (const caps_buffer &);


	bool m_cap_next;
	std::ostream& m_sink;
	std::vector<char> m_buffer;
};

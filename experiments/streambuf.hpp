#include <iostream>
#include <streambuf>
#include <iomanip>

class indenting_buf : public std::streambuf
{
public:
  indenting_buf( std::streambuf* s)(sbufs)

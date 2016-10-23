#include <locale>
#include <iostream>
#include <fstream>
#include <locale>
#include <iostream>

#include "indent_facet.hpp"


void demo1()
{
  indent_manip::raii_guard rg(std::cout);
  std::cout << "<DEMO START>\n"
	    << indent_manip::push <<  "This is after a push... "
	    << indent_manip::push <<"that last push\n"
	    <<"only affects me on a new line of course."
	    << indent_manip::pop << "\nPop has the expected effect.\n";
  rg.reset();
  std::cout << "raii_guard.reset()  brings me back to the original raii_guard state.\n"
	    << "<DEMO STOP>\n";
}

void rai_demo()
{
  indent_manip::raii_guard rg(std::cout);
  std::cout << "The safe indenter object just provides a RAII guard around identation.\n"
	    << indent_manip::push
	    << "If I forget to call reset, or an exception is thrown...\n";
  throw std::runtime_error("oops");
  std::cout << "The pop never gets called:" << indent_manip::pop;
}



void trivial()
{
  /// This probably has to be called once for every program:
  // http://stackoverflow.com/questions/26387054/how-can-i-use-stdimbue-to-set-the-locale-for-stdwcout
  std::ios_base::sync_with_stdio(false);

  std::cout << "I want to push indentation levels:\n" << indent_manip::push
	    << "To arbitrary depths\n" << indent_manip::push
	    << "and pop them\n" << indent_manip::pop
	    << "back down\n" << indent_manip::pop
	    << "like this.\n" << indent_manip::pop;
}

void indent_demo()
{
  indent_manip::raii_guard rg (std::cout);
  std::cout << "Here I call demo starting at zero indentation level:\n\n";
  demo1();
  std::cout << indent_manip::push
	    << "\n\nNow within an indent level:\n";
  demo1();

  std::cout << "Demo left the indentation level where it found it.\n"
	    << indent_manip::clear << "Clear pust me at zero.\n";

  try
    {
      std::cout << indent_manip::push << indent_manip::push
		<< "\n\nThe rai guard, resets, it doesn't clear:\n";
      rai_demo();
    }
  catch(std::runtime_error& e)
    {
      std::cerr << "\n=Cerr of course has its own indentation level=\n\n";
      std::cout << "But for instructional purposes we see that the RAII guard retored\n"
		<< "the original indent level.\n";

    }
  std::cout << indent_manip::clear
	    << "I can also call clear to make sure I'm at zero at any particular point.\n";
}


int main()
{
  trivial();
  indent_demo();

}

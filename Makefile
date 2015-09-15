all : indenter wrapper

indenter: indent_test.cpp
	g++ -Wall -o indenter  -ggdb --std=c++14 indent_test.cpp

wrapper: word_wrapping.cpp
	g++ -Wall -o wrapper -ggdb --std=c++14 word_wrapping.cpp

#include <unordered_set>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
//#include <random>

#include "terminal_info.hpp"

std::vector<std::string> read_some_words(const std::string& fname)
{
	std::ifstream inf(fname);
	std::string word;
	std::unordered_set<std::string> some_words;
	while(inf >> word)
		some_words.insert(word);
	std::vector<std::string> retval;
	std::copy(some_words.begin(), some_words.end(), std::back_inserter(retval));
	return retval;
}

int main()
{
	namespace   ti=terminal_info;
	std::cout << "termina cols: " << ti::cols() << ", lines: " << ti::lines() << "\n";
	auto words = read_some_words("LICENSE");
//	auto unidist = std::uniform_int_distribution<unsigned int>(0,words.size());
	std::random_shuffle(words.begin(), words.end());
	for (auto w : words)
		std::cout << w << " ";
	std::cout << "\n";

	return 0;
}

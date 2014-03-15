#pragma once

#include "LevenshteinDestination.h"
#include <iostream>
#include <string>
#include "time.h"
#include <fstream>


size_t LevenshteinDestinationByWagnerFischer(const std::string& str1, const std::string& str2)
{
	if (str1.size() == 0) return str2.size();
	if (str2.size() == 0) return str1.size();
	std::vector<size_t> last_column;
	std::string str1_ = AddFirstUnimportantSymbol(str1);
	std::string str2_ = AddFirstUnimportantSymbol(str2);
	LeftColumnOfMedian(str1_, str2_, last_column, 1, str1.size(), 1, str2.size());
	return last_column[last_column.size() - 1];
}


void TestRandom()
{
	const size_t MAX_LENGTH = 1000;
	srand(time(NULL));
	size_t str1_length = rand() % MAX_LENGTH,
		   str2_length = rand() % MAX_LENGTH;
	std::string str1, str2;
	char alphabet[] = "abc";
	for (size_t i = 0; i < str1_length; i++)
		str1.push_back( alphabet[rand()%3] );
	for (size_t i = 0; i < str2_length; i++)
		str2.push_back( alphabet[rand()%3] );
	size_t result = LevenshteinDestination(str1, str2);
	size_t check = LevenshteinDestinationByWagnerFischer(str1, str2);
	std::cout << "Destination = " << result << std::endl;
	if (result != check) 
		throw std::logic_error("TestRandom: FAIL");
}


void TestText()
{
	std::ifstream f_text1("text1.txt");
	std::ifstream f_text2("text2.txt");
	std::string str1, str2, temp_str;
	if (!f_text1) 
		throw std::logic_error("File 'Text1' does not exsist");
	if (!f_text2) 
		throw std::logic_error("File 'Text2' does not exsist");
	while (!f_text1.eof())
	{
		std::getline(f_text1, temp_str);
		str1.append(temp_str);
		str1.push_back('\n');
	}
	f_text1.close();
	while (!f_text2.eof())
	{
		std::getline(f_text2, temp_str);
		str2.append(temp_str);
		str2.push_back('\n');
	}
	f_text2.close();
	size_t result = LevenshteinDestination(str1, str2);
	std::cout << "Destination = " << result << std::endl;
}


void TestLevenshteinDestination()
{
	TestRandom();
	std::cout.clear();
	TestText();
}

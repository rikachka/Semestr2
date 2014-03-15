#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "conio.h"


void CreateTable(std::vector<std::vector<size_t>>& table, size_t str_size)
{
	std::vector<size_t> table_line;
	for (size_t i = 0; i < str_size; i++)
		table_line.push_back(0);
	for (size_t i = 0; i < str_size; i++)
		table.push_back(table_line);
}


void FillInTable(std::vector<std::vector<size_t>>& table, const std::string& str)
{
	for (size_t str_begin = str.size(); str_begin > 0; ) 
	{
		str_begin--;
		for (size_t str_end = str_begin; str_end < str.size(); str_end++)
		{
			if (str_begin == str_end && str[str_begin] == str[str_end])
				table[str_begin][str_end] = 1;
			else 
			{
				if (str[str_begin] == str[str_end])
					table[str_begin][str_end] = table[str_begin + 1][str_end - 1] + 2;
				else table[str_begin][str_end] = std::max(table[str_begin + 1][str_end], table[str_begin][str_end - 1]);
			}
		}
	}
}


void RestorePalindrome(const std::vector<std::vector<size_t>>& table, const std::string& str)
{
	size_t str_begin = 0,
		   str_end = str.size() - 1;

	std::string HalfOfPalindrome;

	while (str_begin < str_end)
	{
		if (str[str_begin] == str[str_end])
		{
			HalfOfPalindrome.push_back(str[str_begin]);
			str_begin++;
			str_end--;
		}
		else
		{
			if (table[str_begin + 1][str_end] > table[str_begin][str_end - 1])
				str_begin++;
			else str_end--;
		}
	}

	std::cout << HalfOfPalindrome;
	if (str_begin == str_end && str[str_begin] == str[str_end])
		std::cout << str[str_begin];
	for (size_t i = HalfOfPalindrome.size(); i > 0; )
	{
		i--;
		std::cout << HalfOfPalindrome[i];
	}
}


void Palindrome(const std::string& str)
{
	std::vector<std::vector<size_t>> table;
	CreateTable(table, str.size());
	FillInTable(table, str);
	RestorePalindrome(table, str);
}



int main()
{
	std::string str;
	std::cin >> str;
	Palindrome(str);
	getch();
	return 0;
}

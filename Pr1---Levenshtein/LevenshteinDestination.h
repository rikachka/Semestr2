#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>



std::string AddFirstUnimportantSymbol(const std::string& str)
{
	std::string str_ = " ";
	str_.append(str);
	return str_;
}



void DecreaseTheSizeOfString(const std::string& str1, const std::string& str2, 
	size_t& str1_begin, size_t& str1_end, size_t& str2_begin, size_t& str2_end)
{
	do
	{
		if ((str1_begin > str1_end) || (str2_begin > str2_end) || !(str1[str1_begin]==str2[str2_begin])) break;
		str1_begin++;
		str2_begin++;
	}
	while (true);
	if ((str1_begin <= str1_end) && (str2_begin <= str2_end))
	{
		do
		{
			if ((str1_begin > str1_end) || (str2_begin > str2_end) || !(str1[str1_end]==str2[str2_end])) break;
			str1_end--;
			str2_end--;
		}
		while (true);
	}
}



size_t ChangeElement(const std::string& str1, const std::string& str2, 
	size_t str1_begin, size_t str1_end, size_t str2_begin, size_t str2_end) 
{
	if (str1[str1_begin] == str2[str2_begin]) 
			return 0;
		else 
		{
			std::cout << "# v pozicii " << str1_begin << " : " << str1[str1_begin] << "->" << str2[str2_begin] << std::endl;
			return 1;
		}
}

size_t AddElements(const std::string& str1, const std::string& str2, 
	size_t str1_begin, size_t str1_end, size_t str2_begin, size_t str2_end)
{
	for (size_t str2_index = str2_begin; str2_index <= str2_end; str2_index++)
		std::cout << "+ k posicii " << str1_end  << " : " << str2[str2_index] << std::endl;
	return str2_end - str2_begin + 1;
}

size_t DeleteElements(const std::string& str1, const std::string& str2, 
	size_t str1_begin, size_t str1_end, size_t str2_begin, size_t str2_end)
{
	for (size_t str1_index = str1_begin; str1_index <= str1_end; str1_index++)
		std::cout << "- posicii " << str1_index << " : " << str1[str1_index] << std::endl;
	return str1_end - str1_begin + 1;
}

int CheckCriticalSituations(const std::string& str1, const std::string& str2, 
	size_t str1_begin, size_t str1_end, size_t str2_begin, size_t str2_end)
{
	if (str1_begin > str1_end && str2_begin > str2_end) return 0;

	if ((str1_begin == str1_end) && (str2_begin == str2_end))
		return ChangeElement(str1, str2, str1_begin, str1_end, str2_begin, str2_end);

	if (str1_begin > str1_end)
		return AddElements(str1, str2, str1_begin, str1_end, str2_begin, str2_end);

	if (str2_begin > str2_end)
		return DeleteElements(str1, str2, str1_begin, str1_end, str2_begin, str2_end);
	
	if (str1_begin == str1_end)
	{
		size_t destination_counter = 0;
		while (str2_begin != str2_end)
		{
			if (str1[str1_begin] == str2[str2_begin]) 
				return AddElements(str1, str2, str1_begin + 1, str1_end, str2_begin + 1, str2_end) + destination_counter;
			AddElements(str1, str2, str1_begin, str1_end - 1, str2_begin, str2_begin);
			destination_counter++;
			str2_begin++;
		}
		return ChangeElement(str1, str2, str1_begin, str1_end, str2_begin, str2_end) + destination_counter;
	}

	if (str2_begin == str2_end)
	{
		size_t destination_counter = 0;
		while (str1_begin != str1_end)
		{
			if (str1[str1_begin] == str2[str2_begin]) 
				return DeleteElements(str1, str2, str1_begin + 1, str1_end, str2_begin + 1, str2_end) + destination_counter;
			DeleteElements(str1, str2, str1_begin, str1_begin, str2_begin, str2_begin - 1);
			destination_counter++;
			str1_begin++;
		}
		return ChangeElement(str1, str2, str1_begin, str1_end, str2_begin, str2_end) + destination_counter;
	}

	return -1;
}



size_t StringLength(size_t str_begin, size_t str_end)
{
	return abs(int(str_begin - str_end)) + 1;
}

void FillNullColumn(std::vector<size_t>& column, size_t column_size)
{
	for (size_t i = 0; i <= column_size; i++)
	{
		column.push_back(i);
	}
}

void RenewOneDiagElement(char bukva1, char bukva2, std::vector<size_t>& column,
	size_t column_index, size_t& diag_element)
{
	size_t new_element;
	if (bukva1 == bukva2) 
		new_element = diag_element;
	else
		new_element = std::min(diag_element, std::min(column[column_index - 1], column[column_index])) + 1;
	diag_element = column[column_index];
	column[column_index] = new_element;
}



void ColumnOfDestinationTable(const std::string& str1, const std::string& str2, std::vector<size_t>& column, 
	size_t str1_begin, size_t str1_end, size_t str2_begin, size_t str2_end, int order)
{
	FillNullColumn(column, StringLength(str2_begin, str2_end));

	size_t str1_index = str1_begin - order;
	do
	{
		str1_index += order;
		size_t diag_element = column[0];
		column[0] = StringLength(str1_begin, str1_index);
		size_t str2_index = str2_begin - order;
		do
		{
			str2_index += order;
			size_t column_index = StringLength(str2_begin, str2_index);
			RenewOneDiagElement(str1[str1_index], str2[str2_index], column, column_index, diag_element);
		}
		while (str2_index != str2_end);
	}
	while (str1_index != str1_end);
}

void LeftColumnOfMedian(const std::string& str1, const std::string& str2, std::vector<size_t>& column, 
	size_t str1_begin, size_t str1_end, size_t str2_begin, size_t str2_end)
{
	ColumnOfDestinationTable(str1, str2, column, str1_begin, str1_end, str2_begin, str2_end, 1);
}

void RightColumnOfMedian(const std::string& str1, const std::string& str2, std::vector<size_t>& column, 
	size_t str1_begin, size_t str1_end, size_t str2_begin, size_t str2_end)
{
	ColumnOfDestinationTable(str1, str2, column, str1_end, str1_begin, str2_end, str2_begin, -1);
}



size_t MinSummaOfTwoColumns(const std::vector<size_t>& left_column, const std::vector<size_t>& right_column)
{
	size_t column_size = left_column.size() - 1;
	size_t min = left_column[0] + right_column[column_size];
	size_t median = 0;
	for (size_t i = 1; i <= column_size; i++)
	{
		size_t sum = left_column[i] + right_column[column_size - i];
		if (sum < min)
		{
			min = sum;
			median = i;
		}
	}
	return median;
}



size_t FindMedian(const std::string& str1, const std::string& str2, 
	size_t str1_begin, size_t median1, size_t str1_end, size_t str2_begin, size_t str2_end)
{
	
	std::vector<size_t> left_column, right_column;
	LeftColumnOfMedian(str1, str2, left_column, str1_begin, median1, str2_begin, str2_end);
	RightColumnOfMedian(str1, str2, right_column, median1 + 1, str1_end, str2_begin, str2_end);
	size_t median = MinSummaOfTwoColumns(left_column, right_column);
	return median + str2_begin - 1;
}



size_t LevenshteinDestination(const std::string& str1, const std::string& str2, 
	size_t str1_begin, size_t str1_end, size_t str2_begin, size_t str2_end)
{
	DecreaseTheSizeOfString(str1, str2, str1_begin, str1_end, str2_begin, str2_end);

	int critical_result = CheckCriticalSituations(str1, str2, str1_begin, str1_end, str2_begin, str2_end);
	if (critical_result >= 0) return critical_result;

	size_t median1 = (str1_begin + str1_end)/2;
	size_t median2 = FindMedian(str1, str2, str1_begin, median1, str1_end, str2_begin, str2_end);

	size_t left_destination = LevenshteinDestination(str1, str2, str1_begin, median1, str2_begin, median2);
	
	size_t right_destination = LevenshteinDestination(str1, str2, median1 + 1, str1_end, median2 + 1, str2_end);

	return left_destination + right_destination;
}



size_t LevenshteinDestination(const std::string& str1, const std::string& str2)
{
	std::string str1_ = AddFirstUnimportantSymbol(str1);
	std::string str2_ = AddFirstUnimportantSymbol(str2);
	return LevenshteinDestination(str1_, str2_, 1, str1.size(), 1, str2.size()); 
}

// Pr2 - LIS - 1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include "conio.h"



int binsearch(const int element, const std::vector<int>& vector, size_t begin, size_t end) // [begin, end]
{
	size_t median = (begin + end) / 2;
	if (vector[median] > element)
	{
		if (median == begin) return begin;
		else return binsearch(element, vector, begin, median);
	}
	else if (vector[median] < element)
	{
		if (median + 1 >= vector.size() || vector[median + 1] > element)
			return median + 1;
		else return binsearch(element, vector, median + 1, end);
	}
	else if (vector[median] == element)
	{
		return median;
	}
}



int binsearch(const int element, const std::vector<int>& vector)
{
	if (vector.size() == 0) return -1;
	else return binsearch(element, vector, 0, vector.size() - 1);
}

void lis(const std::vector<int>& vector)
{
	if (vector.size() == 0)
		return 0;

	std::vector<int> vector_lis;

	for (size_t index = 0; index < vector.size(); index++)
	{
		int element = vector[index];
		int element_place = binsearch(element, vector_lis);
		if (element_place < vector_lis.size())
			vector_lis[element_place] = element;
		else vector_lis.push_back(element);
	}
	for (size_t i = 0; i < vector_lis.size(); i++)
		std::cout << vector_lis[i] << " ";
	std::cout << std::endl;
}

int main()
{
	std::vector<int> vector;
	size_t vector_size;
	std::cin >> vector_size;
	for (size_t i = 0; i < vector_size; i++)
	{
		int element;
		std::cin >> element;
		vector.push_back(element);
	}
	
	getch();

	return 0;
}


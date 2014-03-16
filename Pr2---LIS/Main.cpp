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
		return;

	std::vector<int> vector_value;
	std::vector<size_t> vector_index;
	std::vector<int> previous_index;

	for (size_t index = 0; index < vector.size(); index++)
	{
		int element = vector[index];
		int element_place = binsearch(element, vector_value);
		// обновляем первый, который не меньше
		if (element_place < vector_value.size())
		{
			vector_value[element_place] = element;
			vector_index[element_place] = index;
			if (element_place > 0)
				previous_index.push_back(vector_index[element_place - 1]);
			else previous_index.push_back(-1);
		}
		else 
		{
			vector_value.push_back(element);
			vector_index.push_back(index);
			if (element_place > 0)
				previous_index.push_back(vector_index[element_place - 1]);
			else previous_index.push_back(-1);
		}
	}

	std::vector<int> result;
	int index = vector_index[vector_index.size() - 1];
	do
	{
		result.push_back(vector[index]);
		index = previous_index[index];
	}
	while (previous_index[index] != -1);
	result.push_back(vector[index]);

	for (size_t i = 1; i <= result.size(); i++)
		std::cout << result[result.size() - i] << " ";
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

	lis(vector);

	getch();
	return 0;
}


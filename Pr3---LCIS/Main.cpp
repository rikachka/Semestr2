#include "stdafx.h"
#include <vector>
#include <iostream>
#include "conio.h"



size_t lcis(const std::vector<int>& vector1, const std::vector<int>& vector2)
{
	std::vector<size_t> line;
	for (size_t j = 0; j < vector2.size(); j++)
		line.push_back(0);

	size_t best_result_in_line;
	for (size_t vector1_index = 0; vector1_index < vector1.size(); vector1_index++)
	{
		best_result_in_line = 0;
		for (size_t vector2_index = 0; vector2_index < vector2.size(); vector2_index++)
		{
			if (vector1[vector1_index] == vector2[vector2_index]) 
				line[vector2_index] = best_result_in_line + 1;

			if (best_result_in_line < line[vector2_index] && vector1[vector1_index] > vector2[vector2_index])
				best_result_in_line = line[vector2_index];
		}
	}
	
	size_t result = 0;
	for (size_t i = 0; i < line.size(); i++)
		if (line[i] > result) 
			result = line[i];

	return result;
}


void CreateNewVector(std::vector<int>& vector)
{
	size_t vector_size;
	std::cin >> vector_size;
	for (size_t i = 0; i < vector_size; i++)
	{
		int element;
		std::cin >> element;
		vector.push_back(element);
	}
}


int main()
{
	std::vector<int> vector1, vector2;
	CreateNewVector(vector1);
	CreateNewVector(vector2);
	
	std::cout << lcis(vector1, vector2);
	getch();

	return 0;
}

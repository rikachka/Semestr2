#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include "conio.h"



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
		int element_place = std::lower_bound(vector_value.begin(), vector_value.end(), element) - vector_value.begin();
		// обновляем первый, который не меньше
		if (element_place < vector_value.size())
		{
			vector_value[element_place] = element;
			vector_index[element_place] = index;
		}
		else 
		{
			vector_value.push_back(element);
			vector_index.push_back(index);
		}
		if (element_place > 0)
			previous_index.push_back(vector_index[element_place - 1]);
		else previous_index.push_back(-1);
	}

	std::vector<int> result;
	int index = vector_index[vector_index.size() - 1];
	while (previous_index[index] != -1)
	{
		result.push_back(vector[index]);
		index = previous_index[index];
	}
	result.push_back(vector[index]);

	for (size_t i = 1; i <= result.size(); i++)
		std::cout << result[result.size() - i] << " ";
}


void CreateYourVector(std::vector<int>& vector)
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

// http://informatics.mccme.ru/mod/statements/view3.php?id=766&chapterid=1794#1
void CreateTestVector(std::vector<int>& vector)
{
	size_t vector_size, a, k, b, m;
	std::cin >> vector_size >> a >> k >> b >> m;
	for (size_t i = 0; i < vector_size; i++)
	{
		vector.push_back(a);
		a = (k*a + b) % m;
	}
}


int main()
{
	std::vector<int> vector;
	CreateTestVector(vector);

	lis(vector);

	getch();
	return 0;
}


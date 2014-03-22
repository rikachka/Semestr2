#pragma once

#include <string>
#include <vector>
#include <list>
#include <stdexcept>


class HashIterator
{
public:
	HashIterator(std::vector< std::list<std::string> >& init_vector)
	{
		vector = init_vector;
		vector_index = 0;
		if (!NextNotEmptyList(vector_index)) 
		{
			throw std::logic_error("HashIterator: Vector is empty!");
			return;
		}
		iterator = vector[vector_index].begin();
	}


	void operator++()
	{
		if (!NextIterator(vector_index, iterator))
			throw std::logic_error("HashIterator: ++: There is no next iterator!");
	}

	bool End()
	{
		size_t current_index = vector_index;
		std::list<std::string>::iterator current_iterator = iterator;
		return !NextIterator(current_index, current_iterator);
	}


	void operator--()
	{
		if (!PreviousIterator(vector_index, iterator))
			throw std::logic_error("HashIterator: --: There is no previous iterator!");
	}

	bool Begin()
	{
		size_t current_index = vector_index;
		std::list<std::string>::iterator current_iterator = iterator;
		return !PreviousIterator(current_index, current_iterator);
	}


	std::string operator*()
	{
		return *iterator;
	}


private:
	std::vector< std::list<std::string> > vector;
	size_t vector_index;
	std::list<std::string>::iterator iterator;


	bool NextNotEmptyList(size_t& current_index)
	{
		if (current_index >= vector.size()) return false;
		while (vector[current_index].empty())
		{
			current_index++;
			if (current_index == vector.size()) return false;
		}
		return true;
	}

	bool NextIterator(size_t& current_index, std::list<std::string>::iterator& current_iterator)
	{
		current_iterator++;
		if (current_iterator == vector[current_index].end()) 
		{
			current_index++;
			if (!NextNotEmptyList(current_index))
			{
				return false;
			}
			current_iterator = vector[current_index].begin();
		}
		return true;
	}


	bool PreviousNotEmptyList(size_t& current_index)
	{
		if (current_index == 0) return false;
		current_index--;
		while (vector[current_index].empty())
		{
			if (current_index == 0) return false;
			current_index--;
		}
		return true;
	}

	bool PreviousIterator(size_t& current_index, std::list<std::string>::iterator& current_iterator)
	{
		if (current_iterator == vector[current_index].begin()) 
		{
			if (!PreviousNotEmptyList(current_index))
			{
				throw std::logic_error("HashIterator: --: There is no previous iterator!");
				return false;
			}
			current_iterator = vector[current_index].end();
		}
		current_iterator--;
		return true;
	}
};

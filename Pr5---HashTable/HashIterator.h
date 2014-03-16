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
		NextIterator(vector_index, iterator);
	}

	bool End()
	{
		try
		{
			size_t current_index = vector_index;
			std::list<std::string>::iterator current_iterator = iterator;
			NextIterator(current_index, current_iterator);
			return false;
		}
		catch (const std::exception& ex) 
		{
			return true;
		}
	}


	void operator--()
	{
		PreviousIterator(vector_index, iterator);
	}

	bool Begin()
	{
		try
		{
			size_t current_index = vector_index;
			std::list<std::string>::iterator current_iterator = iterator;
			PreviousIterator(current_index, current_iterator);
			return false;
		}
		catch (const std::exception& ex) 
		{
			return true;
		}
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

	void NextIterator(size_t& current_index, std::list<std::string>::iterator& current_iterator)
	{
		current_iterator++;
		if (current_iterator == vector[current_index].end()) 
		{
			current_index++;
			if (!NextNotEmptyList(current_index))
			{
				throw std::logic_error("HashIterator: ++: There is no next iterator!");
				return;
			}
			current_iterator = vector[current_index].begin();
		}
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

	void PreviousIterator(size_t& current_index, std::list<std::string>::iterator& current_iterator)
	{
		if (iterator == vector[vector_index].begin()) 
		{
			if (!PreviousNotEmptyList(vector_index))
			{
				throw std::logic_error("HashIterator: --: There is no previous iterator!");
				return;
			}
			iterator = vector[vector_index].end();
		}
		iterator--;
	}
};

#include "HashIterator.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>



#define INITIAL_TABLE_SIZE 1000


class HashTable
{
public:
	HashTable()
		: table_size_(INITIAL_TABLE_SIZE), number_of_elements_(0)
	{
		std::list<std::string> list;
		vector_.resize(table_size_);
	}


	void Add(const std::string& str)
	{
		size_t hash_value = HashFunction(str);
		if (!Find(str, hash_value))
		{
			vector_[hash_value].push_back(str);
			number_of_elements_++;
		}
		if (number_of_elements_ > 4*table_size_)
			Reallocate();
	}


	bool Find(const std::string& str)
	{
		size_t hash_value = HashFunction(str);
		return Find(str, hash_value);
	}


	void Delete(const std::string& str)
	{
		size_t hash_value = HashFunction(str);
		vector_[hash_value].remove(str);
	}


	void EnumerateElements()
	{
		HashIterator it(vector_);
		std::cout << *it << " ";
		while (!it.End())
		{
			std::cout << NextElement(it) << " ";
		}
	}


private:
	size_t HashFunction(const std::string& str)
	{
		size_t sum = 0;
		for (size_t i = 0; i < str.length(); i++)
			sum+=int(str[i]);
		return sum % table_size_;
	}


	bool Find(const std::string& str, size_t hash_value)
	{
		std::list<std::string> list = vector_[hash_value];
		if (list.empty()) return false;
		for (std::list<std::string>::iterator it = list.begin(); it != list.end(); it++)
			if (*it == str) return true;
		return false;
	}


	std::string NextElement(HashIterator& it)
	{
		it++;
		return *it;
	}


	void Reallocate()
	{
		std::vector< std::list<std::string> > new_vector;
		table_size_ = 4*table_size_;
		new_vector.resize(table_size_);

		HashIterator it(vector_);
		size_t hash_value = HashFunction(*it);
		new_vector[hash_value].push_back(*it);
		while (!it.End())
		{
			std::string str = NextElement(it);
			hash_value = HashFunction(str);
			new_vector[hash_value].push_back(str);
		}

		vector_ = new_vector;
	}


	size_t table_size_;
	size_t number_of_elements_;
	std::vector< std::list<std::string> > vector_;
};

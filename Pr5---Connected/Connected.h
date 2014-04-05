#include "stdafx.h"
#include <vector>
#include <ctime>
#include <iostream>



class Graph
{
public:
	Graph(size_t number_of_nodes)
	{
		parent_.resize(number_of_nodes, -1);
	}

	void AddEdge(size_t edge_begin, size_t edge_end)
	{
		if (edge_begin >= parent_.size() || edge_end >= parent_.size())
			throw std::runtime_error("Graph.AddEdge: There is no such node here");
		UnionSets(edge_begin, edge_end);
	}

	bool IsThereEdge(size_t edge_begin, size_t edge_end)
	{
		if (edge_begin >= parent_.size() || edge_end >= parent_.size())
			throw std::runtime_error("Graph.AddEdge: There is no such node here");
		return (FindLeader(edge_begin) == FindLeader(edge_end));
	}

private:
	size_t FindLeader(size_t elem)
	{
		if (parent_[elem] == -1)
			return elem;
		else 
		{
			size_t leader = FindLeader(parent_[elem]);
			parent_[elem] = leader;
			return leader;
		}
	}

	void UnionSets(size_t elem1, size_t elem2)
	{
		size_t leader1 = FindLeader(elem1);
		size_t leader2 = FindLeader(elem2);
		if (leader1 != leader2)
		{
			srand(time(NULL));
			if (rand()%2)
				parent_[leader1] = leader2;
			else 
				parent_[leader2] = leader1;
		}
	}


	std::vector<int> parent_;
};

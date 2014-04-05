#include "stdafx.h"
#include <vector>
#include <list>
#include <stack>
#include <iostream>
#include "conio.h"

class Graph
{
public:
	Graph()
	{
		size_t number_of_nodes;
		std::cout << "The number of nodes: ";
		std::cin >> number_of_nodes;
		std::list<size_t> list;
		edges_.resize(number_of_nodes, list);
		edges_copy_.resize(number_of_nodes, list);

		size_t number_of_edges;
		std::cout << "The number of edges: ";
		std::cin >> number_of_edges;
		degree_.resize(number_of_edges, 0);
		for (size_t i = 0; i < number_of_edges; i++)
		{
			std::cout << "Edge " << i+1 << ": ";
			size_t edge_begin, edge_end;
			std::cin >> edge_begin >> edge_end;
			edges_[edge_begin].push_back(edge_end);
			degree_[edge_begin]++;
			degree_[edge_end]++;
		}
	}


	void EulerianCycle()
	{
		CopyGraph();
		edges_order_.resize(0);

		for (size_t i = 0; i < edges_copy_.size(); i++) // проверим, что кратность всех вершин чётна
		{
			if (degree_[i] % 2 != 0)
			{
				std::cout << "There is no Eulerian cycle here." << std::endl;
				return;
			}
		}

		size_t node = 0;
		while (node < edges_copy_.size() && edges_copy_[node].empty()) // изолированные вершины нам не интересны
			node++;
		if (node == edges_copy_.size())
		{
			return;
		}
		FindEulerianCycle(node);

		for (size_t i = 0; i < edges_copy_.size(); i++) // проверим, что граф был связный
		{
			if (!edges_copy_[i].empty())
			{
				std::cout << "There is no Eulerian cycle here." << std::endl;
				return;
			}
		}

		size_t number_of_edges = edges_order_.size();
		for (size_t i = 0; i < number_of_edges; i++)
			std::cout << edges_order_[number_of_edges - i - 1].first << "-" << edges_order_[number_of_edges - i - 1].second << " ";
		std::cout << std::endl;
	}


private:
	void CopyGraph()
	{
		for (size_t i = 0; i < edges_.size(); i++)
			for (std::list<size_t>::iterator it = edges_[i].begin(); it != edges_[i].end(); it++)
				edges_copy_[i].push_back(*it);
	}


	void FindEulerianCycle(size_t node)
	{
		while (!edges_copy_[node].empty())
		{
			size_t child = edges_copy_[node].front();
			edges_copy_[node].pop_front();
			FindEulerianCycle(child);
			edges_order_.push_back(std::pair<size_t, size_t>(node, child));
		}
	}


	std::vector< std::list<size_t> > edges_;
	std::vector< std::list<size_t> > edges_copy_;
	std::vector< std::pair<size_t, size_t> > edges_order_;
	std::vector<size_t> degree_;
};

int main()
{
	Graph graph;
	graph.EulerianCycle();
	getch();
	return 0;
}

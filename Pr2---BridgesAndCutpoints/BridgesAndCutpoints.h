#include "stdafx.h"
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <stack>


#define FIND_BRIDGES 0
#define FIND_CUTPOINTS 1
#define FIND_POINT_COMPONENTS 2
#define FIND_EDGE_COMPONENTS 3


class Graph
{
public:
	Graph()
	{
		size_t number_of_nodes;
		std::cout << "The number of nodes: ";
		std::cin >> number_of_nodes;
		std::vector<size_t> node;
		for (size_t i = 0; i < number_of_nodes; i++)
		{
			edges_.push_back(node);
			used_.push_back(false);
			time_in_.push_back(0);
			time_of_node_component_.push_back(0);
		}

		size_t number_of_edges;
		std::cout << "The number of edges: ";
		std::cin >> number_of_edges;
		for (size_t i = 0; i < number_of_edges; i++)
		{
			std::cout << "Edge " << i+1 << ": ";
			size_t edge_begin, edge_end;
			std::cin >> edge_begin >> edge_end;
			edges_[edge_begin].push_back(edge_end);
			edges_[edge_end].push_back(edge_begin);
		}
	}

	void FindBridges()
	{
		std::cout << "Bridges:\n";
		Do(FIND_BRIDGES);
	}

	void FindCutpoints()
	{
		std::cout << "Cutpoints:\n";
		Do(FIND_CUTPOINTS);
	}

	void FindPointComponents()
	{
		std::cout << "Point components:\n";
		Do(FIND_POINT_COMPONENTS);
	}

	void FindEdgeComponents()
	{
		std::cout << "Edge components:\n";
		Do(FIND_EDGE_COMPONENTS);
	}


private:
	void Clear()
	{
		for (size_t i = 0; i < edges_.size(); i++)
			used_[i] = false;
		timer_ = 0;

		std::stack< std::pair<size_t, size_t> > edges_empty_stack;
		edges_stack_.swap(edges_empty_stack);
		std::stack<int> points_empty_stack;
		points_stack_.swap(points_empty_stack);
	}


	void DoKeyAction(size_t key, size_t node, size_t child, int parent)
	{
		switch(key)
		{
		case FIND_BRIDGES:
			if (time_in_[node] < time_of_node_component_[child])
				std::cout << node << "-" << child << " ";
			break;

		case FIND_CUTPOINTS:
			if (time_in_[node] <= time_of_node_component_[child] && parent != -1)
					std::cout << node << " ";
			break;

		case FIND_POINT_COMPONENTS:
			if (time_in_[node] <= time_of_node_component_[child])
			{
				while (!edges_stack_.empty() && edges_stack_.top().first != node)
				{
					std::cout << edges_stack_.top().first << "-" << edges_stack_.top().second << " ";
					edges_stack_.pop();
				}
				if (!edges_stack_.empty())
				{
					std::cout << edges_stack_.top().first << "-" << edges_stack_.top().second << " ";
					edges_stack_.pop();
				}
				std::cout << std::endl;
			}
			break;

		case FIND_EDGE_COMPONENTS:
			if (time_in_[node] < time_of_node_component_[child])
			{
				if (points_stack_.top() != -1) std::cout << points_stack_.top() << " ";
				while (edges_stack_.top() != std::pair<size_t, size_t>(node, child))
				{
					points_stack_.pop();
					if (points_stack_.top() != -1) std::cout << points_stack_.top() << " ";
					edges_stack_.pop();
				}
				points_stack_.pop();
				edges_stack_.pop();
				std::cout << std::endl;
			}
			break;
		}
	}

	void DoKeyActionInTheEnd(size_t key, size_t node, int parent, size_t number_of_children)
	{
		switch(key)
		{
		case FIND_BRIDGES:
			break;

		case FIND_CUTPOINTS:
			if (parent == - 1 && number_of_children > 1)
				std::cout << node << " ";
			break;

		case FIND_POINT_COMPONENTS:
			break;

		case FIND_EDGE_COMPONENTS:
			if (!points_stack_.empty() && parent == -1)
			{
				while (!points_stack_.empty())
				{
					if (points_stack_.top() != -1) std::cout << points_stack_.top() << " ";
					points_stack_.pop();
				}
				std::cout << std::endl;
			}
		}
	}


	void DFS(size_t key, size_t node, int parent = -1)
	{
		used_[node] = true;
		size_t number_of_children = 0;

		time_in_[node] = timer_;
		time_of_node_component_[node] = timer_;
		timer_++;

		points_stack_.push(node);

		for (size_t i = 0; i < edges_[node].size(); i++)
		{
			size_t child = edges_[node][i];
			if (child == parent) continue;
			if (used_[child])
			{
				if (time_in_[child] < time_in_[node])                             // чтобы не добавлялись рёбра по второму разу
				{
					edges_stack_.push(std::pair<size_t, size_t>(node, child));
					points_stack_.push(-1);
				}
				time_of_node_component_[node] = std::min(time_of_node_component_[node], time_in_[child]);
			}
			else
			{
				edges_stack_.push(std::pair<size_t, size_t>(node, child));
				DFS(key, child, node);
				time_of_node_component_[node] = std::min(time_of_node_component_[node], time_of_node_component_[child]);
				DoKeyAction(key, node, child, parent);
				number_of_children++;
			}
		}
		DoKeyActionInTheEnd(key, node, parent, number_of_children);
	}


	void Do(size_t key)
	{
		Clear();
		for (size_t i = 0; i < edges_.size(); i++)
			if (!used_[i])
				DFS(key, i);
		std::cout << std::endl;
	}


	std::vector< std::vector<size_t> > edges_;
	std::vector<bool> used_;
	std::vector<size_t> time_in_;
	std::vector<size_t> time_of_node_component_;
	size_t timer_;
	std::stack< std::pair<size_t, size_t> > edges_stack_;
	std::stack<int> points_stack_;
};

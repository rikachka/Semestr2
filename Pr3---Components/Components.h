#include "stdafx.h"
#include <list>
#include <vector>
#include <stack>
#include <iostream>



class GraphKosaraju
{
public:
	GraphKosaraju()
	{
		size_t number_of_nodes;
		std::cout << "The number of nodes: ";
		std::cin >> number_of_nodes;
		std::list<size_t> list;
		edges_.resize(number_of_nodes, list);
		transposed_edges_.resize(number_of_nodes, list);

		size_t number_of_edges;
		std::cout << "The number of edges: ";
		std::cin >> number_of_edges;
		for (size_t i = 0; i < number_of_edges; i++)
		{
			std::cout << "Edge " << i+1 << ": ";
			size_t edge_begin, edge_end;
			std::cin >> edge_begin >> edge_end;
			edges_[edge_begin].push_back(edge_end);
			transposed_edges_[edge_end].push_back(edge_begin);
		}

		used_.resize(number_of_nodes);
	}


	void StronglyConnectedComponentsKosaraju()
	{
		ClearUse();
		for (size_t i = 0; i < edges_.size(); i++)
			if (!used_[i])
				DFS(i);
		ClearUse();
		while (!time_out_stack_.empty())
		{
			size_t node = time_out_stack_.top();
			if (!used_[node])
			{
				TransposedDFS(node);
				std::cout << std::endl;
			}
			time_out_stack_.pop();
		}
	}

private:
	void DFS(size_t node)
	{
		used_[node] = true;
		for (std::list<size_t>::iterator it = edges_[node].begin(); it != edges_[node].end(); it++)
		{
			size_t child = *it;
			if (!used_[child]) 
				DFS(child);
		}
		time_out_stack_.push(node);
	}

	void TransposedDFS(size_t node)
	{
		used_[node] = true;
		for (std::list<size_t>::iterator it = transposed_edges_[node].begin(); it != transposed_edges_[node].end(); it++)
		{
			size_t child = *it;
			if (!used_[child])
				TransposedDFS(child);
		}
		std::cout << node << " ";
	}


	void ClearUse()
	{
		for(size_t i = 0; i < used_.size(); i++)
			used_[i] = false;
	}


	std::vector< std::list<size_t> > edges_;
	std::vector< std::list<size_t> > transposed_edges_;
	std::vector<bool> used_;
	std::stack<size_t> time_out_stack_;
};



class GraphTarjan
{
public:
	GraphTarjan()
	{
		size_t number_of_nodes;
		std::cout << "The number of nodes: ";
		std::cin >> number_of_nodes;
		std::list<size_t> list;
		edges_.resize(number_of_nodes, list);

		size_t number_of_edges;
		std::cout << "The number of edges: ";
		std::cin >> number_of_edges;
		for (size_t i = 0; i < number_of_edges; i++)
		{
			std::cout << "Edge " << i+1 << ": ";
			size_t edge_begin, edge_end;
			std::cin >> edge_begin >> edge_end;
			edges_[edge_begin].push_back(edge_end);
		}

		time_in_.resize(number_of_nodes);
		colour_.resize(number_of_nodes);
	}


	void StronglyConnectedComponentsTarjan()
	{
		Clear();
		for (size_t i = 0; i < edges_.size(); i++)
			if (colour_[i] != BLACK)
				DFS(i);
	}

private:
	void DFS(size_t node)
	{
		colour_[node] = GREY;
		coloured_nodes_stack_.push(node);
		available_nodes_stack_.push(node);
		time_in_[node] = timer_;
		timer_++;

		for (std::list<size_t>::iterator it = edges_[node].begin(); it != edges_[node].end(); it++)
		{
			size_t child = *it;
			if (colour_[child] == WHITE) DFS(child);
			else
			if (colour_[child] == GREY) 
			{
				while (time_in_[available_nodes_stack_.top()] > time_in_[child])
					available_nodes_stack_.pop();
			}
		}

		if (available_nodes_stack_.top() == node)
		{
			while (coloured_nodes_stack_.top() != node)
			{
				std::cout << coloured_nodes_stack_.top() << " ";
				coloured_nodes_stack_.pop();
			}
			std::cout << coloured_nodes_stack_.top() << std::endl;
			coloured_nodes_stack_.pop();
			available_nodes_stack_.pop();
		}
		colour_[node] = BLACK;
	}


	void Clear()
	{
		for(size_t i = 0; i < colour_.size(); i++)
			colour_[i] = WHITE;
		timer_ = 0;
	}


	std::vector< std::list<size_t> > edges_;
	std::vector<size_t> time_in_;
	size_t timer_;
	std::stack<size_t> coloured_nodes_stack_; // складываем сюда все пройденные вершины; достаём, когда пишем компоненту
	std::stack<size_t> available_nodes_stack_; // верхняя вершина - с наим номером та, про которую мы знаем, что она достижима из текущей
	enum colour {WHITE, GREY, BLACK};
	std::vector<colour> colour_;
};

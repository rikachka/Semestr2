#include "stdafx.h"
#include <vector>
#include <list>
#include <iostream>
#include <stack>
#include "conio.h"


class Graph
{
public:
	Graph()
	{
		size_t number_of_nodes;
		std::cout << "The number of nodes: ";
		std::cin >> number_of_nodes;
		Node node;
		vector_.resize(number_of_nodes, node);

		size_t number_of_edges;
		std::cout << "The number of edges: ";
		std::cin >> number_of_edges;
		for (size_t i = 0; i < number_of_edges; i++)
		{
			std::cout << "Edge " << i+1 << ": ";
			size_t edge_begin, edge_end;
			std::cin >> edge_begin >> edge_end;
			vector_[edge_begin].adj_list.push_back(edge_end);
		}

		for (size_t i = 0; i < number_of_nodes; i++)
		{
			vector_[i].it_next_node = vector_[i].adj_list.begin();
			vector_[i].parent = i;
			vector_[i].colour = Node::WHITE;
		}
	}


	void WriteNodesInTopologicalOrder()
	{
		if (DFS())
		{
			while (!stack_time_out_.empty())
			{
				std::cout << stack_time_out_.top() << " ";
				stack_time_out_.pop();
			}
		}
		else 
			std::cout << "It's impossible to write nodes in topological order. There is a cycle in the graph";
	}


private:
	bool ThereIsNextChild(size_t cur_node)
	{
		return !(vector_[cur_node].it_next_node == vector_[cur_node].adj_list.end());
	}

	size_t NextNode(size_t cur_node)
	{
		vector_[cur_node].it_next_node++;
		if (ThereIsNextChild(cur_node))
			return *vector_[cur_node].it_next_node;
		else return 0;
	}


	bool DFS()
	{
		bool flag_cycle_absence = true; 
		for (size_t index = 0; index < vector_.size(); index++)
		{
			if (vector_[index].colour != Node::BLACK)
			{
				size_t cur_node = index;
				while (true)
				{
					vector_[cur_node].colour = Node::GREY;

					size_t next_child;
					if (ThereIsNextChild(cur_node))
						next_child = *vector_[cur_node].it_next_node;
					while ( (ThereIsNextChild(cur_node)) && (vector_[next_child].colour != Node::WHITE) )
					{
						if (vector_[next_child].colour == Node::GREY)
							flag_cycle_absence = false; 
						next_child = NextNode(cur_node);
					}

					if (ThereIsNextChild(cur_node))
					{
						vector_[next_child].parent = cur_node;
						NextNode(cur_node);
						cur_node = next_child;
					}
					else
					{
						vector_[cur_node].colour = Node::BLACK;
						stack_time_out_.push(cur_node);
						if (cur_node != vector_[cur_node].parent)
							cur_node = vector_[cur_node].parent;
						else break;
					}
				}
			}
		}
		return flag_cycle_absence;			
	}


	struct Node
	{
		std::list<size_t> adj_list; //adjacency_list - список смежности
		std::list<size_t>::iterator it_next_node;
		size_t parent;
		enum {WHITE, GREY, BLACK} colour;
	};

	std::vector<Node> vector_;
	std::stack<size_t> stack_time_out_;
};



int main()
{
	Graph graph;
	graph.WriteNodesInTopologicalOrder();
	getch();
	return 0;
}

#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stack>


class ReturnGraphAlgorithms
{
public:
	ReturnGraphAlgorithms()
	{

	}

	explicit ReturnGraphAlgorithms(int numberOfNodes, int saturation = 70)
	{
		this->numberOfNodes = numberOfNodes;
		this->saturation = saturation;
		initGraph();
		countNumberOfEdges();
		randGraph();
	}

	virtual ~ReturnGraphAlgorithms()
	{

	}

	void newGraph(int numberOfNodes, int saturation)
	{
		this->numberOfNodes = numberOfNodes;
		this->saturation = saturation;
		initGraph();
		countNumberOfEdges();
		randGraph();
	}

	void print()
	{
		for (int i = 0; i < this->numberOfNodes; i++)
		{
			for (int j = 0; j < this->numberOfNodes; j++)
			{
				std::cout << graphMatrix[i][j] << "\t";
			}
			std::cout << std::endl;
		}
	}

	void printCycle()
	{
		for each (int i in solution)
		{
			std::cout << i << "\t";
		}
	}

	void eulerCycle(int node)
	{
		temp.push(node);
		for (int i = 0; i < this->numberOfNodes; i++)
		{
			if (graphMatrix[node][i] == true)
			{
				graphMatrix[node][i] = graphMatrix[i][node] = false;
				eulerCycle(i);
			}
		}
		solution.push_back(node);
		temp.pop();
	}

	void hamiltonCycle(int node)
	{
		visited[node] = true;
		solution.push_back(node);
		if (solution.size() == this->numberOfNodes)
		{
			if (graphMatrix[solution[0]][node] == true)
			{
				this->isFinished = true;
				solution.push_back(solution[0]);
				return;
			}
		}
		for (int i = 0; i < this->numberOfNodes; i++)
		{
			if (graphMatrix[node][i] == true)
			{
				if (visited[i] == false)
				{
					hamiltonCycle(i);
					if (this->isFinished)
					{
						return;
					}
				}
			}
		}
		visited[node] = false;
		solution.pop_back();
	}

	void removeHamiltonCycle()
	{
		int node = rand() % this->numberOfNodes;
		for (int i = 0; i < this->numberOfNodes; i++)
		{
			graphMatrix[node][i] = graphMatrix[i][node] = false;
		}
		int newConnection = rand() % this->numberOfNodes;
		while (newConnection == node)
		{
			int newConnection = rand() % this->numberOfNodes;
		}
		graphMatrix[node][newConnection] = graphMatrix[newConnection][node] = true;
	}

	void clearGraph()
	{
		delete[] visited;
		for (int i = 0; i < this->numberOfNodes; i++)
		{
			delete[] graphMatrix[i];
		}
		solution.clear();
		while (!temp.empty())
		{
			temp.pop();
		}
		this->isFinished = false;
	}

private:
	int numberOfNodes;
	int saturation;
	int numberOfEdges;
	bool isFinished = false;
	bool **graphMatrix;
	std::vector<int> solution;
	std::stack<int> temp;
	bool *visited;

	void createMatrix()
	{
		graphMatrix = new bool *[this->numberOfNodes];
		for (int i = 0; i < this->numberOfNodes; i++)
		{
			graphMatrix[i] = new bool[this->numberOfNodes];
		}
		for (int i = 0; i < this->numberOfNodes; i++)
		{
			for (int j = 0; j < this->numberOfNodes; j++)
			{
				graphMatrix[i][j] = false;
			}
		}
	}

	void countNumberOfEdges()
	{
		numberOfEdges = (((numberOfNodes * (numberOfNodes - 1)) / 2) * saturation) / 100;
	}

	void randGraph()
	{
		std::vector<int> nodes;
		std::vector<int> cycle;
		int tmp;
		int nodeA, nodeB, nodeC;
		for (int i = 0; i < this->numberOfNodes; i++)
		{
			nodes.push_back(i);
		}
		for (int i = 0; i < this->numberOfNodes; i++)
		{
			tmp = rand() % nodes.size();
			cycle.push_back(nodes[tmp]);
			nodes.erase(nodes.begin() + tmp);
		}
		for (int i = 0; i < this->numberOfNodes - 1; i++)
		{
			graphMatrix[cycle[i]][cycle[i + 1]] = graphMatrix[cycle[i + 1]][cycle[i]] = true;
		}
		graphMatrix[cycle[0]][cycle[cycle.size() - 1]] = graphMatrix[cycle[cycle.size() - 1]][cycle[0]] = true;
		this->numberOfEdges -= this->numberOfNodes;
		for (int i = 0; i < this->numberOfEdges; i += 3)
		{
			do
			{
				nodeA = rand() % this->numberOfNodes;
				nodeB = rand() % this->numberOfNodes;
				nodeC = rand() % this->numberOfNodes;
			} while (nodeA == nodeB || nodeA == nodeC || nodeB == nodeC ||
				graphMatrix[nodeA][nodeB] == true || graphMatrix[nodeA][nodeC] == true || graphMatrix[nodeB][nodeC] == true);

			graphMatrix[nodeA][nodeB] = graphMatrix[nodeB][nodeA] = true;
			graphMatrix[nodeA][nodeC] = graphMatrix[nodeC][nodeA] = true;
			graphMatrix[nodeB][nodeC] = graphMatrix[nodeC][nodeB] = true;
		}
	}

	void initGraph()
	{
		createMatrix();
		visited = new bool[this->numberOfNodes];
		for (int i = 0; i < this->numberOfNodes; i++)
		{
			visited[i] = false;
		}
	}
};

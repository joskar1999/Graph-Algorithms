#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stack>


class Graph
{
private:
public:

	Graph()
	{

	}

	Graph(int numberOfNodes)
	{
		this->numberOfNodes = numberOfNodes;
		initGraph();
		randDAG();
	}

	~Graph()
	{

	}

	void print()
	{
		for (int i = 0; i < numberOfNodes; i++)
		{
			for (int j = 0; j < numberOfNodes; j++)
			{
				std::cout << graphMatrix[i][j] << "\t";
			}
			std::cout << std::endl;
		}
	}

	void newGraph(int numberOfNodes)
	{
		deleteMatrix();
		this->numberOfNodes = numberOfNodes;
		initGraph();
		randDAG();
	}

	void BFSTopologicalSort();

	void DFSTopologicalSort();

protected:

	int numberOfNodes;
	bool **graphMatrix;

	void deleteMatrix()
	{
		for (int i = 0; i < numberOfNodes; i++)
		{
			delete[] graphMatrix[i];
		}
		delete[] graphMatrix;
	}

	void initGraph()
	{
		graphMatrix = new bool *[numberOfNodes];

		for (int i = 0; i < numberOfNodes; i++)
		{
			graphMatrix[i] = new bool[numberOfNodes];
		}

		for (int i = 0; i < numberOfNodes; i++)
		{
			for (int j = 0; j < numberOfNodes; j++)
			{
				graphMatrix[i][j] = false;
			}
		}
	}

	void randDAG()
	{
		int numberOfEdges = (this->numberOfNodes *(this->numberOfNodes - 1)) / 4;
		int row, col;

		for (int i = 1; i < this->numberOfNodes; i++)
		{
			row = rand() % (this->numberOfNodes);
			while (row >= i)
			{
				row = rand() % (this->numberOfNodes);
			}
			graphMatrix[row][i] = true;
			numberOfEdges--;
		}

		while (numberOfEdges > 0)
		{
			row = rand() % (this->numberOfNodes);
			col = rand() % (this->numberOfNodes);
			if (col > row && row < this->numberOfNodes && graphMatrix[row][col] != true)
			{
				graphMatrix[row][col] = true;
				numberOfEdges--;
			}
		}
	}
};

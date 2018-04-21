#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stack>


class GraphMON
{
private:
	int numberOfNodes;
	bool **graphMatrix;

	void randDAG()
	{
		int numberOfEdges = (this->numberOfNodes *(this->numberOfNodes - 1)) / 4;
		int row, col;
		while (numberOfEdges > 0)
		{
			row = rand() % (this->numberOfNodes - 1);
			col = rand() % (this->numberOfNodes - 1);
			if (col > row && row < this->numberOfNodes - 1 && graphMatrix[row][col] != true)
			{
				graphMatrix[row][col] = true;
				numberOfEdges--;
			}
		}
	}

	void deleteMatrix()
	{
		for (int i = 0; i < numberOfNodes; i++)
		{
			delete[] graphMatrix[i];
		}
		delete[] graphMatrix;
	}

public:

	GraphMON()
	{

	}

	GraphMON(int numberOfNodes)
	{
		this->numberOfNodes = numberOfNodes;

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
		randDAG();
	}

	~GraphMON()
	{
		for (int i = 0; i < numberOfNodes; i++)
		{
			delete[] graphMatrix[i];
		}
		delete[] graphMatrix;
	}

	void newGraph(int numberOfNodes)
	{
		deleteMatrix();
		this->numberOfNodes = numberOfNodes;
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
		randDAG();
	}

	void printMON()
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

	void BFSTopologicalSort()
	{
		int *numberOfPredecessors = new int[this->numberOfNodes];
		std::vector<int> sorted;
		bool *isInSorted = new bool[this->numberOfNodes];

		for (int i = 0; i < this->numberOfNodes; i++)
		{
			numberOfPredecessors[i] = 0;
			isInSorted[i] = false;
		}

		for (int i = 0; i < this->numberOfNodes; i++)
		{
			for (int j = 0; j < this->numberOfNodes; j++)
			{
				if (graphMatrix[j][i] == true)
				{
					numberOfPredecessors[i]++;
				}
			}
		}

		for (int i = 0; i < this->numberOfNodes; i++)
		{
			if (numberOfPredecessors[i] == 0 && isInSorted[i] == false)
			{
				sorted.push_back(i);
				isInSorted[i] = true;
				for (int j = 0; j < this->numberOfNodes; j++)
				{
					if (graphMatrix[i][j] == true)
					{
						numberOfPredecessors[j]--;
					}
				}
				i = 0; 
			}
		}
		for (int i = 0; i < this->numberOfNodes; i++)
		{
			std::cout << sorted[i] << "\t";
		}

	}

	void DFSTopologicalSort()
	{
		std::stack<int> graphStack;
		bool *visited = new bool[this->numberOfNodes];
		int **prePostNumeration = new int *[this->numberOfNodes];
		int *sorted = new int[this->numberOfNodes];
		int prePostCounter = 1;
		int i = 0, j;

		for (int i = 0; i < this->numberOfNodes; i++)
		{
			visited[i] = false;
			prePostNumeration[i] = new int[2];
			prePostNumeration[i][0] = prePostNumeration[i][1] = 0;
			sorted[i] = i;
		}

		while (i < this->numberOfNodes)
		{
			if ((graphStack.empty() || graphStack.top() != i) && visited[i] == false)
			{
				graphStack.push(i);
				prePostNumeration[i][0] = prePostCounter++;
				visited[i] = true;
				j = 0;
				while (!(graphMatrix[i][j] == true && visited[j] == false))
				{
					j++;
					if (j == this->numberOfNodes)
					{
						break;
					}
				}
				if (j < this->numberOfNodes)
				{
					i = j;
				}
				else
				{
					prePostNumeration[i][1] = prePostCounter++;
					graphStack.pop();
					if (!graphStack.empty())
					{
						i = graphStack.top();
					}
					else
					{
						i = 0;
						j = 0;
						while (visited[j] == true)
						{
							j++;
							if (j == this->numberOfNodes)
							{
								break;
							}
						}
						i = j;
					}
				}
			}
			else
			{
				j = 0;
				while (!(graphMatrix[i][j] == true && visited[j] == false))
				{
					j++;
					if (j == this->numberOfNodes)
					{
						break;
					}
				}
				if (j < this->numberOfNodes)
				{
					i = j;
				}
				else
				{
					prePostNumeration[i][1] = prePostCounter++;
					graphStack.pop();
					if (!graphStack.empty())
					{
						i = graphStack.top();
					}
					else
					{
						i = 0;
						j = 0;
						while (visited[j] == true)
						{
							j++;
							if (j == this->numberOfNodes)
							{
								break;
							}
						}
						i = j;
					}
				}
			}
		}

		for (int i = 0; i < this->numberOfNodes; i++)
		{
			for (int j = 0; j < this->numberOfNodes - 1; j++)
			{
				if (prePostNumeration[j][1] < prePostNumeration[j + 1][1])
				{
					std::swap(prePostNumeration[j], prePostNumeration[j + 1]);
					std::swap(sorted[j], sorted[j + 1]);
				}
			}
		}

		for (int i = 0; i < this->numberOfNodes; i++)
		{
			std::cout << sorted[i] << "\t";
		}
	}

protected:
};

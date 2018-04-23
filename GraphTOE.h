#pragma once
#include "Graph.h"


class GraphTOE : public Graph
{
private:
	std::vector<std::vector<int>> tableOfEdges;

	void transformMatrixToTable()
	{
		std::vector<int> edge;
		for (int i = 0; i < this->numberOfNodes; i++)
		{
			for (int j = 0; j < this->numberOfNodes; j++)
			{
				if (graphMatrix[i][j] == true)
				{
					edge.clear();
					edge.push_back(i);
					edge.push_back(j);
					tableOfEdges.push_back(edge);
				}
			}
		}
	}

public:

	GraphTOE()
	{

	}

	GraphTOE(int numberOfNodes)
	{
		newGraph(numberOfNodes);
		transformMatrixToTable();
	}

	~GraphTOE()
	{
		tableOfEdges.clear();
	}

	void printTOE()
	{
		for (int i = 0; i < tableOfEdges.size(); i++)
		{
			std::cout << tableOfEdges[i][0] << "\t" << tableOfEdges[i][1] << std::endl;
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

		for (int i = 0; i < tableOfEdges.size(); i++)
		{
			numberOfPredecessors[tableOfEdges[i][1]]++;
		}

		for (int i = 0; i < this->numberOfNodes; i++)
		{
			if (numberOfPredecessors[i] == 0 && isInSorted[i] == false)
			{
				sorted.push_back(i);
				isInSorted[i] = true;
				for (int j = 0; j < tableOfEdges.size(); j++)
				{
					if (tableOfEdges[j][0] == i)
					{
						numberOfPredecessors[tableOfEdges[j][1]]--;
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
				while (!(tableOfEdges[j][0] == i && visited[tableOfEdges[j][1]] == false))
				{
					j++;
					if (j == tableOfEdges.size())
					{
						break;
					}
				}
				if (j < tableOfEdges.size())
				{
					i = tableOfEdges[j][1];
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
				while (!(tableOfEdges[j][0] == i && visited[tableOfEdges[j][1]] == false))
				{
					j++;
					if (j == tableOfEdges.size())
					{
						break;
					}
				}
				if (j < tableOfEdges.size())
				{
					i = tableOfEdges[j][1];
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
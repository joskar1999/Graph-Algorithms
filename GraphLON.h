#pragma once
#include "Graph.h"


class GraphLON : public Graph
{
private:
	std::vector<std::vector<int>> graphList;
	std::vector<int> tmpList;

	void transformMatrixToList()
	{
		for (int i = 0; i < this->numberOfNodes; i++)
		{
			tmpList.clear();
			for (int j = 0; j < this->numberOfNodes; j++)
			{
				if (graphMatrix[i][j] == true)
				{
					tmpList.push_back(j);
				}
			}
			graphList.push_back(tmpList);
		}
	}

public:

	GraphLON()
	{

	}

	GraphLON(int numberOfNodes)
	{
		newGraph(numberOfNodes);
		transformMatrixToList();
	}

	~GraphLON()
	{
		graphList.clear();
	}

	void printLON()
	{
		for (int i = 0; i < graphList.size(); i++)
		{
			for (int j = 0; j < graphList[i].size(); j++)
			{
				std::cout << graphList[i][j] << "->";
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

		for (int i = 0; i < graphList.size(); i++)
		{
			for (int j = 0; j < graphList[i].size(); j++)
			{
				numberOfPredecessors[graphList[i][j]]++;
			}
		}

		for (int i = 0; i < this->numberOfNodes; i++)
		{
			if (numberOfPredecessors[i] == 0 && isInSorted[i] == false)
			{
				sorted.push_back(i);
				isInSorted[i] = true;
				for (int j = 0; j < graphList[i].size(); j++)
				{
					numberOfPredecessors[graphList[i][j]]--;
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
				if (j < graphList[i].size())
				{
					while (visited[graphList[i][j]] == true)
					{
						j++;
						if (j == graphList[i].size())
						{
							break;
						}
					}
				}
				if (j < graphList[i].size())
				{
					i = graphList[i][j];
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
				if (j < graphList[i].size())
				{
					while (visited[graphList[i][j]] == true)
					{
						j++;
						if (j == graphList[i].size())
						{
							break;
						}
					}
				}
				if (j < graphList[i].size())
				{
					i = graphList[i][j];
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
				if (prePostNumeration[j][1] < prePostNumeration[j+1][1])
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
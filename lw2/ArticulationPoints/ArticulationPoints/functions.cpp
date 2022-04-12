#include <iostream>
#include "functions.h"

void PrintGraph(std::vector<std::vector<int>> graph)
{
	int size = graph.size();
    for (int i = 1; i < size; ++i)
    {
        for (int j = 1; j < size; ++j)
        {
            std::cout << graph[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void PrintStack(std::stack<int> stack)
{
    if (stack.empty())
        return;
    int x = stack.top();
    stack.pop();
    PrintStack(stack);
    std::cout << x << " ";
    stack.push(x);
}

std::vector<std::vector<int>> ReadAdjacencyMatrixFromStream(std::ifstream& input)
{
    int countVertices;
    int countEdges;
    input >> countVertices >> countEdges;

    std::vector<std::vector<int>> matrix(countVertices + 1,
        std::vector<int>(countVertices + 1, 0));

    int num1, num2;
    while (input >> num1 >> num2)
    {
        matrix[num1][num2] = 1;
        matrix[num2][num1] = 1;
    }
    return matrix;
}

std::set<int> SearchCutVertices(std::vector<std::vector<int>> graph)
{
	int root = 1;
	int graphSize = graph.size();
	std::vector<int> tin(graphSize, 0);
	std::vector<int> tout(graphSize, 0);
	std::vector<Edge> reverseEdges;

	DFS(graph, root, tin, tout, reverseEdges);

	std::set<int> cutVertices = GetCutVertices(graph, root, tin, tout, reverseEdges);

	return cutVertices;
}

void DFS(const std::vector<std::vector<int>> graph, int root, std::vector<int>& tin,
	std::vector<int>& tout, std::vector<Edge>& reverseEdges)
{
	int graphSize = graph.size();
	int timer = 0;
	std::vector<bool> visited(graphSize, false);
	Edge edge;
	int parent = 0;
	int vertex = root;
	std::stack<int> stack;
	stack.push(vertex);
	bool isPath = true;

	while (!stack.empty())
	{
		int vertex = stack.top();
		visited[vertex] = true;

		if (isPath)	tin[vertex] = ++timer;

		isPath = false;
		for (int i = 1; i < graphSize; ++i)
		{
			if (graph[vertex][i] == 1)
			{
				if (!visited[i])
				{
					parent = stack.top();
					stack.push(i);
					isPath = true;
					break;
				}
				if (visited[i] && tin[vertex] - tin[i] > 1 && !tout[parent] && i != parent)
				{
					edge.min = (i < vertex) ? i : vertex;
					edge.max = (i > vertex) ? i : vertex;
					reverseEdges.push_back(edge);
				}
			}
		}

		if (!isPath)
		{
			parent = stack.top();
			stack.pop();
			tout[vertex] = ++timer;
		}
	}
}

std::set<int> GetCutVertices(std::vector<std::vector<int>> graph, int root, std::vector<int> tin,
	std::vector<int> tout, std::vector<Edge> reverseEdges)
{
	int graphSize = graph.size();
	std::set<int> cutVertices;

	for (int i = 1; i < graphSize; ++i)
	{
		bool isCutVertice = true;
		bool hasChild = false;
		int countChild = 0;
		int parentOfHangingVertice;
		for (int j = 1; j < graphSize; ++j)
		{
			if (graph[i][j] == 1)
			{
				countChild = ++countChild;
				parentOfHangingVertice = j;
			}
			if (tin[i] < tin[j] && tout[i] > tout[j])
			{
				hasChild = true;
				for (auto x : reverseEdges)
				{
					if (x.max == j)
					{
						if (x.min < i) isCutVertice = false;
					}
				}
			}
		}

		if (i == root)
		{
			bool isRootCutVertice = false;
			for (int k = 1; k < graphSize; ++k)
			{
				if (graph[i][k] == 1)
				{
					if (tin[k] - 1 == tin[i] && tout[k] + 1 == tout[i])
					{
						isRootCutVertice = true;
					}
				}
			}
			if (!isRootCutVertice) cutVertices.insert(i);

			continue;
		}

		if (countChild == 1) cutVertices.insert(parentOfHangingVertice);
		if (!hasChild) continue;
		if (isCutVertice) cutVertices.insert(i);
	}
	return cutVertices;
}
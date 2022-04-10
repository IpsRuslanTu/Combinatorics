#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <set>
#include <iterator>

using namespace std;

struct Edge
{
	int min;
	int max;
};

void PrintStack(stack<int> s);
void PrintGraph(vector<vector<int>> graph, int size);

int main(int argc, char* argv[])
{
	int countVertices;
	int countEdges;

	ifstream input(argv[1]);
	if (!input.is_open())
	{
		return 1;
	}

	input >> countVertices >> countEdges;

	vector<vector<int>> graph(countVertices + 1,
		vector<int>(countVertices + 1, 0));

	int num1, num2;
	while (input >> num1 >> num2)
	{
		graph[num1][num2] = 1;
		graph[num2][num1] = 1;
	}

	// ----------------------------------------------------------------------

	int timer = 0;
	vector<int> tin(countVertices + 1, 0);
	vector<int> tout(countVertices + 1, 0);
	vector<bool> visited(countVertices + 1, false);
	Edge edge;
	vector<Edge> reverseEdges;
	int parent = 0;
	int vertex = 1;
	stack<int> stack;
	stack.push(vertex);

	bool isPath = true;

	while (!stack.empty())
	{
		int vertex = stack.top();
		visited[vertex] = true;

		if (isPath)
		{
			tin[vertex] = ++timer;
		}

		isPath = false;
		for (int i = 1; i <= countVertices; ++i)
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
					if (i < vertex)
					{
						edge.min = i;
						edge.max = vertex;
					}
					else
					{
						edge.min = vertex;
						edge.max = i;
					}
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

	set<int> point;
	int root = 1;

	for (int i = 1; i <= countVertices; ++i)
	{
		bool isArt = true;
		bool hasChild = false;
		for (int j = 1; j <= countVertices; ++j)
		{
			if (tin[i] < tin[j] && tout[i] > tout[j])
			{
				hasChild = true;
				for (auto x : reverseEdges)
				{
					if (x.max == j)
					{
						if (x.min < i)
						{
							isArt = false;
						}
					}
				}
			}
		}
		if (i == root)
		{
			bool test = false;
			for (int k = 1; k <= countVertices; ++k)
			{
				if (graph[i][k] == 1)
				{
					if (tin[k] - 1 == tin[i] && tout[k] + 1 == tout[i])
					{
						test = true;
					}
				}
			}
			if (!test)
			{
				point.insert(i);
			}
			continue;
		}
		if (!hasChild)
		{
			continue;
		}
		if (isArt)
		{
			point.insert(i);
		}
	}

	// Печать обратных ребер
	for (auto& i : point)
	{
		cout << i << endl;
	}
}

 void PrintGraph(vector<vector<int>> graph, int size)
 {
     for (int i = 1; i <= size; ++i)
     {
         for (int j = 1; j <= size; ++j)
         {
             cout << graph[i][j] << " ";
         }
         cout << endl;
     }
 }
 void PrintStack(stack<int> s)
 {
	 if (s.empty())
		 return;
	 int x = s.top();
	 s.pop();
	 PrintStack(s);
	 cout << x << " ";
	 s.push(x);
 }
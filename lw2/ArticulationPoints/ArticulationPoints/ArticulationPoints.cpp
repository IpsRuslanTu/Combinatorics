#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <set>
#include <iterator>

using namespace std;

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

	int vertex = 1;

	stack<int> stack;
	stack.push(vertex);

	bool isPath = true;

	while (!stack.empty())
	{
		PrintStack(stack);
		cout << endl;

		int vertex = stack.top();
		visited[vertex] = true;

		if (isPath)
		{
			tin[vertex] = ++timer;
		}

		for (int i = 1; i <= countVertices; ++i)
		{
			if (graph[vertex][i] == 1 && !visited[i])
			{
				stack.push(i);
				isPath = true;
				break;
			}
			else
			{
				isPath = false;
			}
		}

		if (!isPath)
		{
			stack.pop();
			tout[vertex] = ++timer;
		}
	}

	//Печать времени входа
	copy(tin.begin() + 1, tin.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	//Печать времени выхода
	copy(tout.begin() + 1, tout.end(), ostream_iterator<int>(cout, " "));














	//Печать обратных ребер
	//for (auto& i : reverseEdges)
	//{
	//	cout << i.u << " " << i.v << endl;
	//}
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
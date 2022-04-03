#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <set>
#include <iterator>

using namespace std;

set<int> pointsConnectebility;
vector<bool> visited;

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

// void PrintGraph(vector<vector<int>> graph, int size);

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

    visited.resize(countVertices + 1, false);
    int timer = 0;
    vector<int> tin(countVertices + 1, 0);
    vector<int> tout(countVertices + 1, 0);

    stack<int> stack;
    int v = 1;
    bool isPath = false;

    stack.push(v);
    visited.at(v) = true;
    tin[v] = ++timer;
    int children = 0;

    while (!stack.empty())
    {
        v = stack.top();
        isPath = false;

        for (int i = 1; i < graph[v].size(); ++i)
        {
            if (graph[v][i] == 1 && !visited[i])
            {
                visited.at(i) = true;
                tin[i] = ++timer;
                stack.push(i);
                isPath = true;
            }
        }
        if (!isPath)
        {
            stack.pop();
            tout[v] = ++timer;
        }
    }


    copy(tin.begin(), tin.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    copy(tout.begin(), tout.end(), ostream_iterator<int>(cout, " "));
}

void DFS(vector<vector<int>>& matrix)
{
}

// void PrintGraph(vector<vector<int>> graph, int size)
// {
//     for (int i = 1; i <= size; ++i)
//     {
//         for (int j = 1; j <= size; ++j)
//         {
//             cout << graph[i][j] << " ";
//         }
//         cout << endl;
//     }
// }

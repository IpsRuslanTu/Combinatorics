#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "functions.h"

using namespace std;

int main(int argc, char* argv[])
{
	ifstream input(argv[1]);
	if (!input.is_open())
	{
		return 1;
	}

	vector<vector<int>> adjacencyMatrix = ReadAdjacencyMatrixFromStream(input);

	set<int> cutVertices = SearchCutVertices(adjacencyMatrix);

	copy(cutVertices.begin(), cutVertices.end(), ostream_iterator<int>(cout, " "));
}
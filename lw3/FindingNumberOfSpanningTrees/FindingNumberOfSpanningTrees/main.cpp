#include "functions.h"

using namespace std;

int main(int argc, char* argv[])
{
	auto name = ParseArgs(argc, argv);
	if (!name)
	{
		return 1;
	}

	auto input = OpenFile(*name);
	if (!input)
	{
		return 1;
	}

	int size;
	*input >> size;

	if (size > 100 && size < 1)
	{
		cout << "Number of vertices of graph should be from 1 to 100\n";
		return 1;
	}

	vector<vector<int>> matrix = ReadMatrixFromStream(*input, size);

	vector<vector<float>> matrixKirchhoff = CreateKirchhoffMatrix(matrix, size);

	cout << "Number of spanning trees: " << GetDeterminant(matrixKirchhoff, size) << endl;
}
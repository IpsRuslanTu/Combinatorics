#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>
#include <algorithm>

using namespace std;

optional<string> ParseArgs(int argc, char* argv[]);
optional<ifstream> OpenFile(string fileIn);
vector<vector<int>> ReadMatrixFromStream(ifstream& input, int size);
vector<vector<float>> CreateKirchhoffMatrix(const vector<vector<int>>& arr, int size);
void PrintMatrix(const vector<vector<float>>& arr, int size);
int GetDeterminant(vector<vector<float>>& arr, int size);

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

	vector<vector<int>> matrix = ReadMatrixFromStream(*input, size);

	vector<vector<float>> matrixKirchhoff = CreateKirchhoffMatrix(matrix, size);

	vector<vector<float>> test = {
		{2, -1, -1, 0},
		{-1, 3, -1, -1},
		{-1, -1, 3, -1},
		{0, -1, -1 ,2},
	};

	GetDeterminant(test, 4);
}

optional<string> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: main.exe <input file with graph>\n";
		return nullopt;
	}
	return argv[1];
}

optional<ifstream> OpenFile(string fileIn)
{
	ifstream input;
	input.open(fileIn);
	if (!input.is_open())
	{
		cout << "Failed to open '" << fileIn << "' for reading\n";
		return nullopt;
	}
	return input;
}

vector<vector<int>> ReadMatrixFromStream(ifstream& input, int size)
{
	vector<vector<int>> arr(size, vector<int>(size, 0));

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			input >> arr[i][j];
		}
	}
	return arr;
}

void PrintMatrix(const vector<vector<float>>& arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

vector<vector<float>> CreateKirchhoffMatrix(const vector<vector<int>>& arr, int size)
{
	vector<vector<float>> matrixKirchhoff(size, vector<float>(size, 0));

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (arr[i][j] == 1)
			{
				matrixKirchhoff[i][j] = -1.0f;
				matrixKirchhoff[i][i] += 1.0f;
			}
		}
	}

	return matrixKirchhoff;
}

int GetDeterminant(vector<vector<float>>& arr, int size)
{
	for (int column = 0; column < size - 1; ++column)
	{
		for (int line = column + 1; line < size; ++line)
		{
			if (arr[line][column] != 0)
			{
				float k = arr[line][column] / arr[column][column];
				for (int i = 0; i < size; ++i)
				{
					arr[line][i] = arr[line][i] - k * arr[column][i];
				}
			}
		}
	}

	cout << endl;
	PrintMatrix(arr, size);
	return 5;
}
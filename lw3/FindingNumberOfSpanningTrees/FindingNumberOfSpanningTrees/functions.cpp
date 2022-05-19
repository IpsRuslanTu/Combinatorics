#include "functions.h"

using namespace std;

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

vector<vector<int>> ReadMatrixFromStream(ifstream& input, const int size)
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
	int sizeOfAlgebraic—omplement = size - 1;
	vector<vector<float>> algebraic—omplement(sizeOfAlgebraic—omplement,
		vector<float>(sizeOfAlgebraic—omplement));

	for (int i = 0; i < sizeOfAlgebraic—omplement; ++i)
	{
		for (int j = 0; j < sizeOfAlgebraic—omplement; ++j)
		{
			float buf = arr[i][j];
			algebraic—omplement[i][j] = buf;
		}
	}

	for (int column = 0; column < sizeOfAlgebraic—omplement - 1; ++column)
	{
		for (int line = column + 1; line < sizeOfAlgebraic—omplement; ++line)
		{
			if (algebraic—omplement[line][column] != 0)
			{
				float k = algebraic—omplement[line][column] / algebraic—omplement[column][column];
				for (int i = 0; i < sizeOfAlgebraic—omplement; ++i)
				{
					algebraic—omplement[line][i] = round((algebraic—omplement[line][i]
						- k * algebraic—omplement[column][i]) * 1000) / 1000;
				}
			}
		}
	}

	int determinant = CalcDeterminant(algebraic—omplement, sizeOfAlgebraic—omplement);

	return determinant;
}

int CalcDeterminant(vector<vector<float>>& arr, int size)
{
	float det = 1;
	for (int i = 0; i < size; ++i)
	{
		det *= arr[i][i];
	}

	return det;
}
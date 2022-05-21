#include <iostream>
#include <optional>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

optional<string> ParseArgs(int argc, char* argv[]);
optional<ifstream> OpenFile(string fileIn);
vector<vector<int>> ReadMatrixFromStream(ifstream& input, const int size);
void PrintMatrix(const vector<vector<int>>& arr, int size);
bool HungarianAlgorithm(const vector<vector<int>>& arr, int size);

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

	cout << HungarianAlgorithm(matrix, size) << endl;
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

vector<vector<int>> ReadMatrixFromStream(ifstream& input, const int size)
{
	vector<vector<int>> arr(size, vector<int>(size, 0));
	int temp;

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			input >> temp;
			arr[i][j] = temp == 0 ? INT_MAX : temp;
		}
	}
	return arr;
}

void PrintMatrix(const vector<vector<int>>& arr, int size)
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

bool HungarianAlgorithm(const vector<vector<int>>& arr, int size)
{
	vector<vector<int>> tempArr(arr);

	// Преборазую хотя бы одно ребро в каждой строке и столбце к 0.
	for (int i = 0; i < size; ++i)
	{
		// Использую i как строку

		int minInLine = *min_element(tempArr[i].begin(), tempArr[i].end());

		for_each(tempArr[i].begin(), tempArr[i].end(), 
			[minInLine](int& d) { d == INT_MAX ? d : d -= minInLine; });

		// Использую i как столбец

		int minINColumn = INT_MAX;

		for (int j = 0; j < size; ++j)
		{
			minINColumn = tempArr[j][i] < minINColumn ? tempArr[j][i] : minINColumn;
		}

		if (minINColumn != 0)
		{
			for (int k = 0; k < size; ++k)
			{
				tempArr[k][i] = tempArr[k][i] == INT_MAX 
					? tempArr[k][i] 
					: tempArr[k][i] - minINColumn;
			}
		}

	}

	// -----------------------------------------------------------------
	vector<int> pare(size, -1);

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (tempArr[i][j] == 0 
				&& find(pare.begin(), pare.end(), j) == pare.end())
			{
				pare[i] = j;
			}
		}

		if (count(pare.begin(), pare.end(), -1) == 0) return true;
	}

	copy(pare.begin(), pare.end(), ostream_iterator<int>(cout, " "));

	return false;
}
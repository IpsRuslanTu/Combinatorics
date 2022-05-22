#include <iostream>
#include <optional>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

optional<string> ParseArgs(int argc, char* argv[]);
optional<ifstream> OpenFile(string fileIn);
vector<vector<int>> ReadMatrixFromStream(ifstream& input, const int size);
void PrintMatrix(const vector<vector<int>>& arr, int size);
bool HungarianAlgorithm(const vector<vector<int>>& arr, int size);
bool IsValueInVector(vector<int>& arr, int value);
int GetIndexOfValueInVector(vector<int>& arr, int value);
int GetMinWithoutZeroInVector(vector<int>& arr);
bool Try_kuhn(int v, vector<bool>& used, vector<int>& mt, vector<vector<int>>& BZero);

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

	HungarianAlgorithm(matrix, size);
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

	// Преобразую хотя бы одно ребро в каждой строке к 0.
	for (int i = 0; i < size; ++i)
	{
		// Использую i как строку

		int minInLine = *min_element(tempArr[i].begin(), tempArr[i].end());

		for_each(tempArr[i].begin(), tempArr[i].end(), 
			[minInLine](int& d) { d == INT_MAX ? d : d -= minInLine; });
	}

	// Преобразую хотя бы одно ребро в каждом столбце к 0.
	for (int j = 0; j < size; ++j)
	{
		int minINColumn = INT_MAX;

		for (int i = 0; i < size; ++i)
		{
			minINColumn = tempArr[i][j] < minINColumn ? tempArr[i][j] : minINColumn;
		}

		if (minINColumn != 0)
		{
			for (int k = 0; k < size; ++k)
			{
				tempArr[k][j] = tempArr[k][j] == INT_MAX
					? tempArr[k][j]
					: tempArr[k][j] - minINColumn;
			}
		}
	}
	
	vector<vector<int>> BZero(size);
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (tempArr[i][j] == 0)
			{
				BZero[i].push_back(j);
			}
		}
	}

	vector<int> mt(size, -1);
	vector<bool> used;

	for (int v = 0; v < size; ++v) {
		used.assign(size, false);
		Try_kuhn(v, used, mt, BZero);
	}

	for (int i = 0; i < size; ++i)
	{
		cout << mt[i] << ", " << i << endl;
	}

	for (int i = 0; i < size; ++i)
	{
		cout << used[i] << ", " << i << endl;
	}
	
	if (std::find(mt.begin(), mt.end(), -1) != mt.end())
	{
		int index = GetIndexOfValueInVector(mt, -1);

		for (int j = 0; j < size; ++j)
		{
			int column;
			if (tempArr[index][j] == 0)
			{
				column = j;
			}
		}
	}
	else
	{
		cout << "Task completed" << endl;
		return true;
	}
}

bool IsValueInVector(vector<int>& arr, int value)
{
	bool IsValue = false;

	if (find(arr.begin(), arr.end(), value) != arr.end()) IsValue = true;

	return IsValue;
}

int GetIndexOfValueInVector(vector<int>& arr, int value)
{
	int index = -1;

	for (int i = 0; i < arr.size(); ++i)
	{
		if (arr[i] == value)
		{
			index = i;
		}
	}

	return index;
}

int GetMinWithoutZeroInVector(vector<int>& arr)
{
	int min = INT_MAX;

	for (int i = 0; i < arr.size(); ++i)
	{
		if (arr[i] != 0)
		{
			min = arr[i] < min ? arr[i] : min;
		}
	}

	return min;
}

bool Try_kuhn(int v, vector<bool>& used, vector<int>& mt, vector<vector<int>>& BZero) {
	if (used[v])  return false;
	used[v] = true;
	for (size_t i = 0; i < BZero[v].size(); ++i) {
		int to = BZero[v][i];
		if (mt[to] == -1 || Try_kuhn(mt[to], used, mt, BZero)) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}

//void NewTransformation(vector<vector<int>>)
//{
//
//}
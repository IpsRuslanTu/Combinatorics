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
void HungarianAlgorithm(const vector<vector<int>>& arr, int size);
bool IsValueInVector(vector<int>& arr, int value);
int GetIndexOfValueInVector(vector<int>& arr, int value);
int GetMinWithoutZeroInVector(vector<int>& arr);

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

void HungarianAlgorithm(const vector<vector<int>>& arr, int size)
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
	
	vector<int> pare(size, -1);

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (tempArr[i][j] != 0) continue;
				
			if (!IsValueInVector(pare, j))
			{
				pare[i] = j;
			}
			else
			{
				int line1 = i;
				int line2 = GetIndexOfValueInVector(pare, j);
				int column = j;

				int min1 = GetMinWithoutZeroInVector(tempArr[line1]);
				int min2 = GetMinWithoutZeroInVector(tempArr[line2]);

				int min = min1 < min2 ? min1 : min2;

				for_each(tempArr[line1].begin(), tempArr[line1].end(),
					[min](int& d) { (d == INT_MAX || d == 0) ? d : d -= min; });

				for_each(tempArr[line2].begin(), tempArr[line2].end(),
					[min](int& d) {  (d == INT_MAX || d == 0) ? d : d -= min; });
			}
		}
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

//copy(arr.begin(), arr.end(), ostream_iterator<int>(cout, " "));
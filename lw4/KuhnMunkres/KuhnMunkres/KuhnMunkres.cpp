#include <iostream>
#include <optional>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

const int NO_MATCH = -1;

optional<string> ParseArgs(int argc, char* argv[]);
optional<ifstream> OpenFile(string fileIn);
vector<vector<int>> ReadMatrixFromStream(ifstream& input, const int size);
void PrintMatrix(const vector<vector<int>>& arr, int size);
vector<int> FindCompleteMatch(vector<vector<int>>& arr, int size);
bool KuhnMunkres(int v, vector<bool>& used, vector<int>& result, vector<vector<int>>& arrOfEdges);

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

	vector<int> result = FindCompleteMatch(matrix, size);

	if (std::find(result.begin(), result.end(), NO_MATCH) != result.end()) {
		cout << "No\n";
	}
	else {
		cout << "Yes\n";
		for (int i = 0; i < size; ++i)
		{
			cout << result[i] << " , " << i << endl;
		}
	}
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
	vector<vector<int>> arr(size, vector<int>(size));

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			input >> arr[i][j];
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

vector<int> FindCompleteMatch(vector<vector<int>>& arr, int size)
{
	vector<vector<int>> arrOfEdges(size);
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (arr[i][j] == 1)
			{
				arrOfEdges[i].push_back(j);
			}
		}
	}

	vector<int> result(size, NO_MATCH);
	vector<bool> used;

	for (int v = 0; v < size; ++v) {
		used.assign(size, false);
		KuhnMunkres(v, used, result, arrOfEdges);
	}

	return result;
}

bool KuhnMunkres(int v, vector<bool>& used, vector<int>& result, vector<vector<int>>& arrOfEdges) 
{
	if (used[v])  return false;
	used[v] = true;
	for (int i = 0; i < arrOfEdges[v].size(); ++i) {
		int to = arrOfEdges[v][i];
		if (result[to] == NO_MATCH || KuhnMunkres(result[to], used, result, arrOfEdges)) {
			result[to] = v;
			return true;
		}
	}
	return false;
}
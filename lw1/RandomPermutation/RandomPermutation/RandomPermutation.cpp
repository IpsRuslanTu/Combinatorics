#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

void PrintArr(vector<int> &inputArray)
{
	for (int i = 0; i < inputArray.size(); ++i)
		cout << inputArray[i] << " ";
	cout << "\n";
}

void MixIndexOfArray(vector<int>& inputArray)
{
	int randomNum;
	for (int i = 0; i < inputArray.size(); ++i)
	{
		randomNum = rand() % inputArray.size();
		swap(inputArray[i], inputArray[randomNum]);
	}
	cout << "\n";
}

int main()
{
	srand(time(0));
	vector<int> arr = {1, 2, 3, 4, 5};

	cout << "Source array:\n";
	PrintArr(arr);

	char repeat = 121;
	do
	{
		MixIndexOfArray(arr);
		cout << "Array after mixing:\n";
		PrintArr(arr);

		cout << "\nShuffle again? y/n : ";
		cin >> repeat;
	} while (repeat == 121);
}
#include <iostream>
#include <vector>
#include <boost/timer.hpp>

using namespace std;

void PrintArr(vector<int>& inputArr)
{
    for (int i = inputArr.size() - 2; i >= 0; --i)
        cout << inputArr[i] << " ";
    cout << endl;
}

int main()
{
    int N;
    cout << "Input number of elements: ";
    cin >> N;
    cout << "\n";

    int k;
    cout << "Input number of placements: ";
    cin >> k;
    cout << "\n";

    // ----------------------------------------------------------

	boost::timer t;
	t.restart();

    vector<int> arr(k + 1);

    for (int i = 0; i <= k; ++i)
    {
        arr[i] = 0;
    }

    while (arr[k] != 1)
    {
        PrintArr(arr);
        int i = 0;
        while (arr[i] == N - 1)
        {
            arr[i] = 0;
            ++i;
        }
        ++arr[i];
    }

    // --------------------------------------------------------------

    double duration = t.elapsed();
    cout << duration << endl;
}
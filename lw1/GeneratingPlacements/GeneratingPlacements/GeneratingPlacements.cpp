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

    vector<int> b(k + 1);

    for (int i = 0; i <= k; ++i)
    {
        b[i] = 0;
    }

    int count = 0;

    while (b[k] != 1)
    {
        ++count;
        PrintArr(b);
        int i = 0;
        while (b[i] == N - 1)
        {
            b[i] = 0;
            ++i;
        }
        b[i] = b[i] + 1;
    }

    // --------------------------------------------------------------

    double duration = t.elapsed();
    cout << duration << endl;
    cout << count;
}
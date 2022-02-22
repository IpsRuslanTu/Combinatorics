#include <iostream>
#include <vector>
#include <boost/timer.hpp>

using namespace std;

void PrintArr(vector<int>& inputArr)
{
    for (int i = 1; i < inputArr.size(); ++i)
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
    cout << "Input number of combinations: ";
    cin >> k;
    cout << "\n";

    boost::timer t;
    t.restart();

    vector<int> comb(k + 1);
    comb[0] = -1;
    for (int i = 1; i <= k; ++i)
        comb[i] = i;

    int maxIndex = 1;

    while (maxIndex != 0)
    {
        PrintArr(comb);
        maxIndex = k;

        while (comb[maxIndex] == N - k + maxIndex)
        {
            maxIndex = maxIndex - 1;
        }
        comb[maxIndex] = comb[maxIndex] + 1;

        for (int i = maxIndex + 1; i <= k; ++i)
            comb[i] = comb[i - 1] + 1;
    }

    double duration = t.elapsed();
    cout << duration << endl;
}
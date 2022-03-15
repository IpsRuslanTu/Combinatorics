#include <iostream>
#include <vector>
#include <boost/timer.hpp>

using namespace std;

void PrintArr(vector<int>& inputArr)
{
    for (int i = inputArr.size() - 1; i >= 0; --i)
        cout << inputArr[i] << " ";
    cout << endl;
}

int main()
{
    int N;
    cout << "Input number of elements: ";
    cin >> N;
    cout << "\n";

    boost::timer t;
    t.restart();

    vector<int> b(N);
    for (int i = 0; i < N; ++i)
        b[i] = 0;

    int count = 0;
    while (b[b.size() - 1] != 1)
    {
        ++count;
        //PrintArr(b);
        int i = 0;
        while (b[i] == 1)
        {
            b[i] = 0;
            i = i + 1;
        }
        b[i] = 1;
    }

    double duration = t.elapsed();
    cout << duration << endl;
    cout << count << endl;
}
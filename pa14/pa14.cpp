#include <iostream>
#include <iomanip>
#include <ctime>
#include <thread>
#include <vector>
#include <future>
#include <atomic>

using namespace std;

class ThreadData
{
public:
    time_t startTime;
    time_t endTime;
};

unsigned long long int fibonacci(unsigned int n);
void startFibonacci(unsigned int n, ThreadData& data);

int main()
{
    cout << fixed << setprecision(6);
    cout << "Enter three numbers: ";

    unsigned int num1, num2, num3;
    cin >> num1 >> num2 >> num3;

    vector<ThreadData> results(3);

    vector<thread> threads;
    atomic<int> completedCount(0);

    threads.emplace_back([&num1, &results, &completedCount]() {
        startFibonacci(num1, results[0]);
        completedCount++;
    });

    threads.emplace_back([&num2, &results, &completedCount]() {
        startFibonacci(num2, results[1]);
        completedCount++;
    });

    threads.emplace_back([&num3, &results, &completedCount]() {
        startFibonacci(num3, results[2]);
        completedCount++;
    });

    while (completedCount < 3)
    {
        // Wait for all calculations to finish
        this_thread::yield();
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    time_t seqStartTime = results[0].startTime;
    time_t seqEndTime = results[0].endTime;

    for (const auto& result : results)
    {
        if (result.startTime < seqStartTime)
            seqStartTime = result.startTime;
        if (result.endTime > seqEndTime)
            seqEndTime = result.endTime;
    }

    cout << "Sequential Calculation Time = " << difftime(seqEndTime, seqStartTime) / 60.0 << " minutes" << endl;
}

void startFibonacci(unsigned int n, ThreadData& data)
{
    cout << "Thread ID: " << this_thread::get_id() << " Calculating fibonacci(" << n << ")" << endl;
    data.startTime = time(nullptr);
    auto fibonacciValue = fibonacci(n);
    data.endTime = time(nullptr);

    cout << "Thread ID: " << this_thread::get_id() << " fibonacci(" << n << ") = " << fibonacciValue << endl;
    cout << "Thread ID: " << this_thread::get_id() << " Calculation Time = " << difftime(data.endTime, data.startTime) / 60.0 << " minutes" << endl;
}

unsigned long long int fibonacci(unsigned int n)
{
    if (0 == n || 1 == n)
    {
        return n;
    }
    else
    {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}


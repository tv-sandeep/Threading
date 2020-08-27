// Threading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

typedef unsigned long long ull;

ull findEvenSum(int start, int end)
{
	ull sum = 0;
	for (int i = 0; i < end; i=i+2)
	{
		sum += i;
	}
	return sum;
}

ull findOddSum(int start, int end)
{
	ull sum = 0;
	for (int i = 1; i < end; i = i + 2)
	{
		sum += i;
	}
	return sum;
}

int main()
{
    ull start = 0, end = 1900000000, oddSum = 0, evenSum = 0;

	auto st = high_resolution_clock::now();
	evenSum = findEvenSum(start, end);
	oddSum = findOddSum(start, end);
	auto et = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(st - et);
	std::cout << "Even sum: " <<  evenSum<< std::endl;
	std::cout << "Odd sum: " <<  oddSum<< std::endl;
	cout << "duration: " << duration.count()/1000000 << endl;
}
// Threading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

typedef unsigned long long ull;

 ull oddSum = 0, evenSum = 0;

void findEvenSum(ull start, ull end)
{
	for (int i = 0; i < end; i=i+2)
		evenSum += i;
}

void findOddSum(ull start, ull end)
{
	for (int i = 1; i < end; i = i + 2)
		oddSum += i;
}

void fun(int x)
{
	printf("Value: %d\n", x);
	this_thread::sleep_for(chrono::seconds(3));
}
int main()
{
	//Either join or detachable should be called on thread object,
	//otherwise during thread object's destructor, it will terminate the program.
	//Because inside the destructor it checks if thread is still joinable.
	//if yes it terminate the program.
	if (0)
	{
		//Before threading
		ull start = 0, end = 1900000000;
		auto st = high_resolution_clock::now();
		findEvenSum(start, end);
		findOddSum(start, end);
		auto et = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(st - et);
		std::cout << "Even sum: " << evenSum << std::endl;
		std::cout << "Odd sum: " << oddSum << std::endl;
		cout << "duration: " << duration.count() / 1000000 << endl;
	}
	if (0)
	{
		ull start = 0, end = 1900000000;

		auto st = high_resolution_clock::now();

		thread t1(findEvenSum, start, end);
		// Now  t1 thread will be started and comback to next statemnt, mean while
		//findEvenSum() running in background
		thread t2(findOddSum, start, end);

		//These threads need to join the main thread
		//If we dont  join main thread may complete before these two thread, then 
		// there is no chance to get the results

		t1.join();
		//Now we will wait untill this thread is over
		t2.join();
		//Now we will wait untill this thread is over

		auto et = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(st - et);
		std::cout << "Even sum: " << evenSum << std::endl;
		std::cout << "Odd sum: " << oddSum << std::endl;
		cout << "duration: " << duration.count() / 1000000 << endl;
	}
	if (0)
	{
		thread t3(fun, 10);
		cout << "After thread start" << endl;
		//OS will take some time to create thread
		t3.join();
		cout << "After join" << endl;
		//Here main will wait untill thread is finished
		//Calling join multiple times program ill be terminated.
		if (t3.joinable())
			t3.join();
	}

	if (1)
	{
		thread t4(fun, 10);
		//OS will take some time to create thread
		t4.detach();
		//main thread wont wait here to finish because it is detached
		//Although it is detached, it will be executed but we wont get the result
		// because we detachd it from main thread
		cout << "After Detach" << endl;
		t4.join(); //Just to check
		if (t4.joinable())
			t4.detach();//Double detach will end up termination
	}
	return 1;
}
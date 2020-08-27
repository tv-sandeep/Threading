#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

std::condition_variable cv;
std::mutex m;

long balance = 0;

void addMoney(int money)
{
	//This thread will be started after releasing the lock by 
	//cv.wait() in withdrawMoney(...)
	std::lock_guard<mutex> lg(m);
	balance += money;
	cout << "Amount added: " << money << endl;
	cv.notify_one();
	//Who ever using this 'cv' will be notified to awake.
	//using notify_one because only one thread is waiting y using this condition.
}

void withdrawMoney(int money)
{
	std::unique_lock<mutex> ul(m);

				   //predicate or condition
	cv.wait(ul, [] {return (balance != 0) ? true : false; });
	//If this condition returns false then this thread will wait by 
	//releasing this mutex 'm'. It will wait here until this condition is true.
	//unlock is internal in cv.wait(...) statement.
	
	//After got notification from cv.notify_one(); in addMoney()
	//then it will try_lock the mutex m. and check the condition.

	//This statement not go further untill balance is not zero
	if (balance >= money)
	{
		balance -= money;
		cout << "Amount Deducted: " << money << endl;
	}
	else
	{
		cout << "Amount cant be Deducted: " << money << endl;
	}
	cout << "curent balance: " << balance << endl;
}


int main()
{
	std::thread t1(withdrawMoney, 500);
	std::thread t2(addMoney, 500);

	t1.join();
	t2.join();
}
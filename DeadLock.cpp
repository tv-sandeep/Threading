#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex m1;
mutex m2;

void thread1()
{
	m1.lock();
	//this_thread::sleep_for(chrono::seconds(1));	
	//If it sleeps here, then it will wait untill m2 will be unlocked
	//but in thread2(), it will be wait untill m1 unlocked 
	//So it is a dead lock situation.
	m2.lock();
	cout << "Thread1\n";
	m1.unlock();
	m2.unlock();
}

void thread2()
{
	m2.lock();
	//this_thread::sleep_for(chrono::seconds(1));	
	m1.lock();
	cout << "Thread2\n";
	m2.unlock();
	m1.unlock();
}

int main()
{
	//If we doesnt include sleep, then before starting the other thread 
	//Our computer will execut first two or three statements very fast.

	thread t1(thread1);
	thread t2(thread2);

	t1.join();
	t2.join();
}



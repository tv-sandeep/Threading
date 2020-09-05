#include <iostream>
#include <Queue>
#include <mutex>
#include <thread>
#include <condition_variable>
using namespace std;

condition_variable cv;

struct Semaphore
{
	int m_Value;
	queue<thread> m_qThreads;
	Semaphore(int nThreads)
	{
		m_Value = nThreads;
	}
};

Semaphore s(3);

void PassThread(int val)
{
	s.m_qThreads.push()
}

int main()
{
	thread t1
}
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
int x = 0;

mutex m;
void Add()
{
	//If t1 gets the lock and enter, t2 cant enter here 
	//and it will be blocked here so t2 will wait at this line
	//untill it gets lock.
	m.lock();
	x++;
	m.unlock();
}


void Inc()
{
	for (int i = 0; i < 100000; i++)
	{
		//If t1 gets the lock and enter, t2 cant enter if loop
		//but it doesnt block here it will continue the for loop
		//untill it gets lock. so actually it will skips some increments
		if (m.try_lock())
		{
			++x;
			m.unlock();
		}
	}
}

void main()
{
	thread t1(Add);
	thread t2(Add);

	t1.join();
	t2.join();
	cout << "x: " << x << endl;
	return;
}

//std::try_lock;
//std::mutex::try_lock;
//std::timed_mutex::try_lock;
//std::shared_lock::try_lock;
//std::unique_lock::try_lock;
//std:shared_mutex::try_lock;
//std:recursive_mutex::try_lock;
//std:shared_timed_mutex::try_lock;
//std:recursive_timed_mutex::try_lock;

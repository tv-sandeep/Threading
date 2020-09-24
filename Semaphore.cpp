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


//Semaphores are not available in C++ as of now, but can easily be implemented with a mutexand a condition variable.

//#include <mutex>
//#include <condition_variable>
//
//class Semaphore {
//public:
//    Semaphore(int count_ = 0)
//        : count(count_)
//    {
//    }
//
//    inline void notify(int tid) {
//        std::unique_lock<std::mutex> lock(mtx);
//        count++;
//        cout << "thread " << tid << " notify" << endl;
//        //notify the waiting thread
//        cv.notify_one();
//    }
//    inline void wait(int tid) {
//        std::unique_lock<std::mutex> lock(mtx);
//        while (count == 0) {
//            cout << "thread " << tid << " wait" << endl;
//            //wait on the mutex until notify is called
//            cv.wait(lock);
//            cout << "thread " << tid << " run" << endl;
//        }
//        count--;
//    }
//private:
//    std::mutex mtx;
//    std::condition_variable cv;
//    int count;
//};


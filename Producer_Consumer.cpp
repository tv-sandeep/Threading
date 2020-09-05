#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>

std::mutex m;
std::condition_variable cv;
std::deque<int> buffer;
const unsigned int Max_Buffer = 50;

void Producer(int Val)
{
	while (Val)
	{
		std::unique_lock<std::mutex> ul(m);
		cv.wait(ul, []() {return buffer.size() < Max_Buffer; });
		buffer.push_back(Val);
		Val--;
		std::cout << "Produced: " << Val <<std::endl;
		ul.unlock();
		cv.notify_one();
	}
}


void consumer()
{
	while (true)
	{
		std::unique_lock<std::mutex> ul(m);
		cv.wait(ul, []() {return buffer.size() > 0; });
		int Val = buffer.back();
		buffer.pop_back();
		std::cout << "Consumed: " << Val << std::endl;
		ul.unlock();
		cv.notify_one();
	}
}

int main()
{
	std::thread t1(Producer, 100);
	std::thread t2(consumer);

	t1.join();
	t2.join();

	return 0;
}
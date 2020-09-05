#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

unsigned int Buffer[100];

unsigned int BufferLength = 0;

condition_variable cv;
mutex m;

void WriteData(int val)
{
	while (val)
	{
		unique_lock<mutex> ul(m);
		cv.wait(ul, [&]() {
			return (BufferLength < 50);	});
		Buffer[BufferLength++] = val--;
		printf("Produced: %d\n", Buffer[BufferLength]);
		ul.unlock();
		cv.notify_all();
	}
}

void ReadData(int val)
{
	while (true)
	{
		unique_lock<mutex> ul(m);
		cv.wait(ul, [&]() {
			return (BufferLength > 0);	});
		printf("consumed: %d\n", Buffer[BufferLength--]);
		ul.unlock();
		cv.notify_all();
	}
}

class A
{
	int i = 5;
	int a = 10;
	char c = 'a';
	bool b = true;
};
int main()
{
	A a;
	cout << sizeof(a) << endl;
	//int* p = reinterpret_cast<int*>(&a);
	int* p = (int*)(&a);
	cout << *p << endl;
	p++;
	cout << *p << endl;
	p++;
	cout << *p << endl;

	printf("");
	thread t1(WriteData, 100);
	thread t2(ReadData, 1);
	//thread t3(ReadData, 2);

	t1.join();
	t2.join();
	//t3.join();
}
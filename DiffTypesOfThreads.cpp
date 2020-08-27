#include <iostream>
#include <thread>


////1. Function pointers
//
//void fun(int x)
//{
//	printf("%d\n", x);
//}
//
//int main()
//{
//	std::thread t(fun, 10);
//	t.join();
//	return 0;
//}



//2. Lambda function

//int main()
//{
//	auto fun = [](int x)
//	{
//		printf("%d\n", x);
//	};
//	std::thread t(fun, 10);
//	t.join();
//
//	//Directly injecting lambda
//	std::thread t1([](int x)
//		{
//			printf("%d\n", x);
//		}, 10);
//	t1.join();
//	return 0;
//}


//3. Functors

//class A
//{
//public:
//	void operator()(int x)
//	{
//		printf("%d\n", x);
//	}
//};
//
//int main()
//{
//	std::thread t((A()), 10);
//	t.join();
//}


//4. Non static member function of class

//class A
//{
//public:
//	void print(int x)
//	{
//		printf("%d\n", x);
//	}
//};
//
//int main()
//{
//	A a;
//	std::thread t(&A::print, &a, 10);
//	t.join();
//	return 0;
//}


//5. Static member function of a class
class A
{
public:
	static void print(int x)
	{
		printf("%d\n", x);
	}
};

int main()
{
	std::thread t(&A::print, 10);
	t.join();
	return 0;
}
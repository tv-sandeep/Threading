#include <iostream>
#include <thread>
#include <future>

void findSum(std::promise<int>&& Sum, int Start, int End)
{
	int iSum = 0;
	for (int i = Start; i < End; i++)
	{
		iSum += i;
	}
	Sum.set_value(iSum);
}

int main()
{
	int iSt = 0, iEnd = 1000;
	std::promise<int> iSumPromise;
	std::future<int> iSumRes = iSumPromise.get_future();
	std::thread t(findSum, std::move(iSumPromise), iSt, iEnd);

	std::cout << "Waiting for result\n";
	std::cout << "Sum: " << iSumRes.get() << std::endl;//You will wait here 
									//untill you get value
	//It will be executed after 'Sum.set_value(iSum);' statement executed

	t.join();
	return 0;

}
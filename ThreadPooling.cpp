#include <iostream>
#include <functional>
#include <vector>
#include <thread>
#include <condition_variable>
#include <queue>

class ThreadPool
{
public:
	using Task = std::function<void()>;

	explicit ThreadPool(std::size_t numThreads)
	{
		printf("ThreadPool constructor\n");
		start(numThreads);
	}
	~ThreadPool()
	{
		printf("ThreadPool destructor\n");
		stop();
	}

	void enqueue(Task task)
	{
		printf("Enqueue\n");
		{
			std::unique_lock<std::mutex> lock(m_EventMutex);
			m_QueueTasks.emplace(std::move(task));
		}
		m_EventVar.notify_one();
	}

private:
	std::vector<std::thread> m_VectThreads;
	std::condition_variable m_EventVar;

	std::mutex m_EventMutex;
	bool m_Stopping = false;

	std::queue<Task> m_QueueTasks;
	void start(std::size_t numThreads)
	{
		printf("Start\n");
		m_VectThreads.emplace_back([=]{
			while (true)
			{
				Task task;
				{
					std::unique_lock<std::mutex> lock(m_EventMutex);
					m_EventVar.wait(lock, [=] { return m_Stopping || !m_QueueTasks.empty(); });
				
					printf("Task\n");
					if (m_Stopping && m_QueueTasks.empty())
						break;
					printf("Task\n");

					task = std::move(m_QueueTasks.front());
					m_QueueTasks.pop();
				}
				printf("task()\n");
				task();
			}
		});
	}
	void stop() noexcept
	{
		printf("Stop\n");
		{
			std::unique_lock<std::mutex> lock(m_EventMutex);
			m_Stopping = true;
		}
		m_EventVar.notify_all();

		printf("After notify all\n");
		for (auto& thread : m_VectThreads)
			thread.join();
	}
};

int main()
{
	{
		ThreadPool pool(5);

		pool.enqueue([] {
			std::cout << "1\n";
			});

		pool.enqueue([] {
			std::cout << "2\n";
			});

		pool.enqueue([] {
			std::cout << "3\n";
			});

		pool.enqueue([] {
			std::cout << "4\n";
			});

		pool.enqueue([] {
			std::cout << "5\n";
			});

		pool.enqueue([] {
			std::cout << "6\n";
			});

		pool.enqueue([] {
			std::cout << "7\n";
			});
	}
	return 0;
}
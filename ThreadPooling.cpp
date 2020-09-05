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
		start(numThreads);
	}
	~ThreadPool()
	{
		stop();
	}

	void enqueue(Task task)
	{
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
		m_VectThreads.emplace_back([=]{
			while (true)
			{
				Task task;
				{
					std::unique_lock<std::mutex> lock(m_EventMutex);
					m_EventVar.wait(lock, [=] { return m_Stopping || !m_QueueTasks.empty(); });
				
					if (m_Stopping && m_QueueTasks.empty())
						break;

					task = std::move(m_QueueTasks.front());
					m_QueueTasks.pop();
				}
				task();
			}
		});
	}
	void stop() noexcept
	{
		{
			std::unique_lock<std::mutex> lock(m_EventMutex);
			m_Stopping = true;
		}
		m_EventVar.notify_all();

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
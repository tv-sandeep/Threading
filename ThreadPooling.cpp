#include <functional>
#include <vector>
#include <thread>
#include <condition_variable>

class ThreadPool
{
public:
	explicit ThreadPool(std::size_t numThreads)
	{
		start(numThreads);
	}
	~ThreadPool()
	{
		stop();
	}

private:
	std::vector<std::thread> m_VectThreads;
	std::condition_variable m_EventVar;
	std::mutex m_EventMutex;
	bool m_Stopping = false;
	void start(std::size_t numThreads)
	{
		m_VectThreads.emplace_back([=]{
			while (true)
			{
				std::unique_lock<std::mutex> lock(m_EventMutex);
				m_EventVar.wait(lock, [=] {return m_Stopping; });
				if (m_Stopping)
					break;
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
	ThreadPool pool(36);
	return 0;
}
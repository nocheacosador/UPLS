#ifndef TSQUEUE_H_
#define TSQUEUE_H_

#include <deque>
#include <mutex>

template<class T>
class tsqueue
{
public:
	tsqueue() = default;
	tsqueue(const tsqueue<T>&) = delete;

public:
	typedef typename std::deque<T> deque_type;
	typedef typename deque_type::iterator iterator;
	typedef typename deque_type::const_iterator const_iterator;
	
	const T& front()
	{
		std::scoped_lock lock(m_mux);
		return m_queue.front();
	}

	const T& back()
	{
		std::scoped_lock lock(m_mux);
		return m_queue.back();
	}

	bool empty()
	{
		std::scoped_lock lock(m_mux);
		return m_queue.empty();
	}

	size_t size() const
	{
		std::scoped_lock lock(m_mux);
		return m_queue.size();
	}

	T pop()
	{
		std::scoped_lock lock(m_mux);
		auto t = std::move(m_queue.front());
		m_queue.pop_front();
		return t;
	}

	void push(const T& item)
	{
		std::scoped_lock lock(m_mux);
		m_queue.push_back(std::move(item));
	}

	void clear()
	{
		std::scoped_lock lock(m_mux);
		m_queue.clear();
	}

	inline iterator begin() noexcept
	{
		std::scoped_lock lock(m_mux);
		return m_queue.begin();
	}

	inline iterator end() noexcept
	{
		std::scoped_lock lock(m_mux);
		return m_queue.end();
	}

	inline const_iterator cbegin() const noexcept
	{
		std::scoped_lock lock(m_mux);
		return m_queue.cbegin();
	}

	inline const_iterator cend() const noexcept
	{
		std::scoped_lock lock(m_mux);
		return m_queue.cend();
	}

protected:
	std::deque<T> m_queue;
	std::mutex 	  m_mux;
};

#endif // TSQUEUE_H_
#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <mutex>
#include <iostream>
#include "logger.h"


// Thread-safe ring buffer
template<class T, size_t buffer_size = 30>
class RingBuffer
{
public:
	// Constructor
	RingBuffer();
	
	// Destructor
	~RingBuffer();
	
	// Write function. Adds an item to the queue.
	void push(T& item);
	
	// Access function. Pops item from the queue.
	T pop();
	
	// Access function. Peeks to the item in the queue.
	T& peek();
	
	// Utility function. Checks if buffer is empty.
	bool empty() const;
	
	// Utility function. Checks if buffer is full.
	bool full() const;
	
	// Utility function. Returns buffer size.
	size_t size() const;

	// Utility function. Returns item count.
	size_t count() const;

	// Utility function. Clears buffer.
	void clear();

private:
	T m_data[buffer_size];
	size_t m_itemCount;
	size_t m_size;
	size_t m_head;
	size_t m_tail;

protected:
	mutable std::mutex m_mux;
};



template<class T, size_t buffer_size>
RingBuffer<T, buffer_size>::RingBuffer() : m_size(buffer_size), m_head(0), m_tail(0), m_itemCount(0)
{ ; }

template<class T, size_t buffer_size>
RingBuffer<T, buffer_size>::~RingBuffer() { ; }

template<class T, size_t buffer_size>
void RingBuffer<T, buffer_size>::push(T& item)
{
	if (!full())
	{
		std::scoped_lock lock(m_mux);
		m_data[m_head] = item;
		m_head++;
		m_head %= m_size;
		m_itemCount++;
	}
	else
		na::log.error("Error in template<class T> void RingBuffer<T>::push(T&): buffer overflow. Increase buffer size.");
}

template<class T, size_t buffer_size>
T RingBuffer<T, buffer_size>::pop()
{
	T result = 0;
	if (!empty())
	{
		std::scoped_lock lock(m_mux);
		m_itemCount--;
		result = m_data[m_tail];
		m_tail++;
		m_tail %= m_size;
	}
	return result;
}

template<class T, size_t buffer_size>
T& RingBuffer<T, buffer_size>::peek()
{
	char result = 0;
	if (!empty())
	{
		std::scoped_lock lock(m_mux);
		result = m_data[m_tail];
	}
	return result;
}

template<class T, size_t buffer_size>
inline bool RingBuffer<T, buffer_size>::empty() const
{
	std::scoped_lock lock(m_mux);
	return m_tail == m_head;
}

template<class T, size_t buffer_size>
inline bool RingBuffer<T, buffer_size>::full() const
{
	std::scoped_lock lock(m_mux);
	return m_itemCount == m_size;
}

template<class T, size_t buffer_size>
inline size_t RingBuffer<T, buffer_size>::size() const
{
	std::scoped_lock lock(m_mux);
	return m_size;
}

template<class T, size_t buffer_size>
inline size_t RingBuffer<T, buffer_size>::count() const
{
	std::scoped_lock lock(m_mux);
	return m_itemCount;
}

template<class T, size_t buffer_size>
void RingBuffer<T, buffer_size>::clear()
{
	std::scoped_lock lock(m_mux);
	memset(m_data, 0, m_size * sizeof(T));
	m_head = 0;
	m_tail = 0;
	m_itemCount = 0;
}

#endif // RINGBUFFER_H_
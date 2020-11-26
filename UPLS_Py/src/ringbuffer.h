#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <mutex>
#include <iostream>
#include "console_formating.h"

#define RING_BUFFER_DEFAULT_SIZE 	50

// Thread-safe ring buffer
template<class T>
class RingBuffer
{
public:
	// Constructor
	RingBuffer(size_t size = RING_BUFFER_DEFAULT_SIZE);
	
	// Destructor
	~RingBuffer();
	
	// Write function. Adds an item to the queue.
	void push(T& item);
	
	// Access function. Pops item from the queue.
	T pop();
	
	// Access function. Pops item from the queue.
	T peek();
	
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
	T* m_data;
	size_t m_itemCount;
	size_t m_size;
	size_t m_head;
	size_t m_tail;

protected:
	mutable std::mutex m_mux;
};



template<class T>
RingBuffer<T>::RingBuffer(size_t size) : m_size(size), m_head(0), m_tail(0), m_itemCount(0)
{
	m_data = new T[m_size];
}

template<class T>
RingBuffer<T>::~RingBuffer()
{
	if (m_data) delete[] m_data;
}

template<class T>
void RingBuffer<T>::push(T& item)
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
		std::cerr << "[" << Format("Error").color(Color::Red).bold() << "] " << "in template<class T> void RingBuffer<T>::push(T&): buffer overflow. "
			"Increase buffer size.\n";
}

template<class T>
T RingBuffer<T>::pop()
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

template<class T>
T RingBuffer<T>::peek()
{
	char result = 0;
	if (!empty())
	{
		std::scoped_lock lock(m_mux);
		result = m_data[m_tail];
	}
	return result;
}

template<class T>
inline bool RingBuffer<T>::empty() const
{
	std::scoped_lock lock(m_mux);
	return m_tail == m_head;
}

template<class T>
inline bool RingBuffer<T>::full() const
{
	std::scoped_lock lock(m_mux);
	return m_itemCount == m_size;
}

template<class T>
inline size_t RingBuffer<T>::size() const
{
	std::scoped_lock lock(m_mux);
	return m_size;
}

template<class T>
inline size_t RingBuffer<T>::count() const
{
	std::scoped_lock lock(m_mux);
	return m_itemCount;
}

template<class T>
void RingBuffer<T>::clear()
{
	std::scoped_lock lock(m_mux);
	memset(m_data, 0, m_size * sizeof(T));
	m_head = 0;
	m_tail = 0;
	m_itemCount = 0;
}

#endif // RINGBUFFER_H_
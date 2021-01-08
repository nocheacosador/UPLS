#ifndef MYQUEUE_H_
#define MYQUEUE_H_

#include <cstddef>
#include <iostream>

namespace na
{
	template<class T>
	struct __queue_node
	{
		__queue_node() : next(nullptr) 
		{ 
			std::cout << "New node created at 0x" << std::hex << this << std::endl;
		}
		
		__queue_node(const T& obj) : next(nullptr), data(obj) 
		{ 
			std::cout << "New node created at 0x" << std::hex << this << std::endl;
		}

		~__queue_node()
		{
			std::cout << "Node deleted at 0x" << std::hex << this << std::endl;
		}

		__queue_node* next = nullptr;
		T data;
	};
	
	template<class T, bool iterable = false>
	class queue;

	template<class T, false>
	class queue
	{
	public:
		queue();
		queue(const queue&) = delete;
		queue& operator = (const queue&) = delete;

		~queue();

		void push(T& data);
		void push(T data);
		T pop();
		T& peek();
		
		T& front() { return m_first->data; }
		T& back() { return m_last->data; }

		size_t size() { return m_size; }
		bool empty() { return m_size == 0; }
	
	private:
		size_t m_size;
		__queue_node<T>* m_first;
		__queue_node<T>* m_last;
	};

	template<class T, true>
	class queue
	{
	public:
		queue();
		queue(const queue&) = delete;
		queue& operator = (const queue&) = delete;

		~queue();

		void push(T& data);
		void push(T data);
		T pop();
		T& peek();
		
		T& front() { return m_first->data; }
		T& back() { return m_last->data; }

		size_t size() { return m_size; }
		bool empty() { return m_size == 0; }
	
	private:
		size_t m_size;
		__queue_node<T>* m_first;
		__queue_node<T>* m_last;
	};
};


// implementation
namespace na
{	
	template<class T>
	queue<T>::queue() : m_size(0), m_first(nullptr), m_last(nullptr) { ; }

	template<class T>
	queue<T>::~queue()
	{
		while (!empty()) pop();
	}

	template<class T>
	void queue<T>::push(T& data)
	{
		__queue_node<T>* p = new __queue_node<T>(data);

		if (p)
		{
			if (!m_first) 			// first member added
				m_first = p;
			else 					// it's not first member, that is added
				m_last->next = p;
			
			m_last = p;

			m_size++;
		}
	}

	template<class T>
	void queue<T>::push(T data)
	{
		__queue_node<T>* p = new __queue_node<T>(data);

		if (p)
		{
			if (!m_first) 			// first member added
				m_first = p;
			else 					// it's not first member, that is added
				m_last->next = p;
			
			m_last = p;

			m_size++;
		}
	}

	template<class T>
	T queue<T>::pop()
	{
		T result;
		if (m_first)
		{
			result = m_first->data;
			__queue_node<T>* p = m_first;
			m_first = m_first->next;
			delete p;
			m_size--;
		}
		return result;
	}

	template<class T>
	T& queue<T>::peek()
	{
		return m_first->data;
	}
};

#endif // MYQUEUE_H_
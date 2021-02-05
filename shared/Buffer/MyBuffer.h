#ifndef MYBUFFER_H
#define MYBUFFER_H
 
#include <stdint.h>
#include <string.h>

template <typename T, size_t N = 256>
class MyBuffer
{
private:
    T _buf[N];
    volatile size_t   _wloc;
    volatile size_t   _rloc;
    size_t            _size;
	size_t			  _count;
 
public:
	/** Initialize buffer
	 */
	MyBuffer();

	/** Get the size of the ring buffer
	 * @return the size of the ring buffer
	 */
	size_t getSize();

	/** Add a data element into the buffer
	 *  @param data Something to add to the buffer
	 */
	void put(const T& data);

	/** Remove a data element from the buffer
	 *  @return Pull the oldest element from the buffer
	 */
	T get(void);

	/** Get the address to the head of the buffer
	 *  @return The address of element 0 in the buffer
	 */
	T *head(void);

	/** Reset the buffer to 0. Useful if using head() to parse packeted data
	 */
	void clear(void);

	/** Determine if anything is readable in the buffer
	 *  @return 1 if something can be read, 0 otherwise
	 */
	bool available(void);
};
 
template <typename T, size_t N>
inline void MyBuffer<T,N>::put(const T& data)
{
    _buf[_wloc++] = data;
    _wloc %= _size;
	if (_count < _size) _count++;
    return;
}
 
template <typename T, size_t N>
inline T MyBuffer<T, N>::get(void)
{
    T data_pos = T();
	if (_count)
	{
		data_pos = _buf[_rloc++];
		_rloc %= (_size);
		_count--;
	}
    return data_pos;
}
 
template <typename T, size_t N>
inline T *MyBuffer<T, N>::head(void)
{
    T *data_pos = &_buf[0];
    
    return data_pos;
}
 
template <typename T, size_t N>
inline bool MyBuffer<T, N>::available(void)
{
    return _count != 0;
}
 
#endif
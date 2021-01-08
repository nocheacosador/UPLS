
/**
 * @file    Buffer.cpp
 * @brief   Software Buffer - Templated Ring Buffer for most data types
 * @author  sam grove
 * @version 1.0
 * @see     
 *
 * Copyright (c) 2013
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "MyBuffer.h"
 
template <typename T, size_t N>
MyBuffer<T, N>::MyBuffer() : _size(N), _count(0)
{
    clear();
    
    return;
}
 
template <typename T, size_t N>
size_t MyBuffer<T, N>::getSize() 
{ 
    return this->_size; 
}
 
template <typename T, size_t N>
void MyBuffer<T, N>::clear(void)
{
    _wloc = 0;
    _rloc = 0;
	_count = 0;
    memset(_buf, 0, _size);
    
    return;
}
 
// make the linker aware of some possible types
template class MyBuffer<uint8_t>;
template class MyBuffer<int8_t>;
template class MyBuffer<uint16_t>;
template class MyBuffer<int16_t>;
template class MyBuffer<uint32_t>;
template class MyBuffer<int32_t>;
template class MyBuffer<uint64_t>;
template class MyBuffer<int64_t>;
template class MyBuffer<char>;
template class MyBuffer<wchar_t>;
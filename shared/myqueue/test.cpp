#include "naqueue.h"

int main()
{
	na::queue<int> q;
	
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	while (!q.empty())
	{
		std::cout << q.pop() << std::endl;
	}

	return 0;
}
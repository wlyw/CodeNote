#include <iostream>
#include <string>

#include "FunTest.h"

using std::string;
using std::cout;
using std::endl;

//6.7
size_t CountCalls()
{
	static size_t ctr = 0;
	return ctr++;
}

//6.10
void ValChange(int *val1, int *val2)
{
	int temp = *val1;
	*val1 = *val2;
	*val2 = temp;
}

//6.12
void ValChange(int &val1, int &val2)
{
	int temp = val1;
	val1 = val2;
	val2 = temp;
}

//6.17
bool HaveCapLet(const string &s)
{
	for (auto c : s)
	{
		if (c >= 'A' && c <= 'Z')
		{
			return true;
		}
	}
	return false;
}

void TransCapLet(string &s)
{
	for (auto &c : s)
	{
		if (c >= 'A' && c <= 'Z')
			c = 'a' + (c - 'A');
	}
}
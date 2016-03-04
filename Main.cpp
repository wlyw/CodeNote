#include<iostream>
#include<cassert>

#include "StrTest.h"
#include "FunTest.h"
#include "leetcode.h"

#define NDEBUG

using namespace std;

int main()
{
	conststr("LiuyaWei");

	//6.7
	for (size_t i = 0; i != 2; ++i)
	{
		cout << CountCalls() << endl;
	}

	//6.10
	int val1 = 5, val2 = 10;
	ValChange(&val1, &val2);
	cout << val1 << " " << val2 << endl;

	//6.12
	ValChange(val1, val2);
	cout << val1 << " " << val2 << endl;

	//6.17
	if (HaveCapLet("helloworld!"))
	{
		cout << "HaveCapLet!" << endl;
	}
	else
	{
		cout << "Have no CapLet!" << endl;
	}

	string totrans("HelloWorld");
	TransCapLet(totrans);
	cout << totrans << endl;

	//leetcode test
	vector<int> nums = { 1,2,3,4,5,6 };
	int temp = findMin(nums);
	cout << temp << endl;

	//6.43
	string s1("s1isshort");
	string s2("s2isnotshort");
	if (isShorter(s1, s2))
		cout << "s1isshort" << endl;
	else
		cout << "s1isnotshort" << endl;

#ifndef NDEBUG
	cout << "NDEBUG" << __LINE__ << endl;
	assert(isShorter(s2, s1));
#endif

	return 0;
}
#include <iostream>
#include <string>
#include <stdexcept>

#include "StrTest.h"

using std::string;
using std::cout;
using std::endl;
using std::runtime_error;

string conststr(string s)
{
	try
	{
		for (auto &c : s)
		{
			c = toupper(c);
		}
		cout << s << endl;
	}
	catch (runtime_error err)
	{
		string err_info = "Error";
		return err_info;
	}
	return s;
}
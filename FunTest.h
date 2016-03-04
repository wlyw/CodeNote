#include <string>

using std::string;

#ifndef FUNTEST_H
#define FUNTEST_H

size_t CountCalls();

void ValChange(int *val1, int *val2);
void ValChange(int &val1, int &val2);

bool HaveCapLet(const string &s);
void TransCapLet(string &s);

inline bool isShorter(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}

#endif // !FUNTEST_H


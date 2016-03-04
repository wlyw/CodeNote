#include "leetcode.h"

using namespace std;

int findMin(vector<int>& nums)
{
	if (nums.size() == 1)
		return *nums.begin();
	auto begin = nums.begin();
	auto end = nums.end()-1;
	int fuck = *begin;
	int temp = *begin;

	if (*begin < *end)
		return *begin;

	while (begin <= end)
	{
		auto mid = begin + (end - begin) / 2;
		if (mid == begin) 
		{ 
			temp = *begin < *end ? *begin : *end;
			break;
		}
		if (*mid < *begin )
		{ 
			end = mid; 
		}
		else if (*mid > *begin)
		{ 
			if(*mid > fuck)
				begin = mid + 1;
			else end = mid;
		}
	}
	return temp;
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

void iteratively(vector<int>& temp, TreeNode* root) {
	if (root == NULL)
		return;
	temp.push_back((*root).val);
	iteratively(temp, (*root).left);
	iteratively(temp, (*root).right);
}

vector<int> preorderTraversal(TreeNode* root) {
	vector<int> temp;
	if (root == NULL)
		return temp;
	iteratively(temp, root);
	return temp;
}
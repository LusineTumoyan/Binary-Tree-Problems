#include "pch.h"
#include <iostream>
#include <queue>
#include <list>
#include <stack>
using namespace std;

struct node {
	double data;
	node *left;
	node *right;

	node(int d, node *l = nullptr, node *r = nullptr) : data(d), left(l), right(r) {}
};

void print(node *root, int space = 0)
{
	if (root == NULL)
		return;
	space += 13;

	print(root->right, space);

	cout << endl;
	for (int i = 13; i < space; i++)
		cout<<" ";
	cout << root->data;

	print(root->left, space);
}

//1. Get the height of each subtree. Set the data of each node to it's subtree's height.
int SetDataHeightRecursive(node *r) {
	if (!r) return -1;
	int heightLeft = SetDataHeightRecursive(r->left);
	int heightRight = SetDataHeightRecursive(r->right);
	r->data = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
	return r->data;
}
int GetHeightRecursive(node *r) {
	if (!r) return 0;
	int heightLeft = GetHeightRecursive(r->left);
	int heightRight = GetHeightRecursive(r->right);
	return (heightLeft > heightRight ? heightLeft : heightRight) + 1;
}
int GetHeight(node *r) {
	queue<node*> q;
	q.push(r);

	node *first = nullptr;
	int height = -1;

	while (!q.empty()) {
		int size = q.size();

		while (size--) {
			first = q.front();
			q.pop();
			if (first->left) q.push(first->left);
			if (first->right) q.push(first->right);
		}
		height++;
	}
	return height;
}
void SetDataHeightIterative(node *r) {
	if (!r) return;
	queue<node *> q;
	q.push(r);
	node *first = nullptr;

	while (!q.empty()) {
		first = q.front();
		first->data = GetHeight(first);
		q.pop();
		if (first->left) q.push(first->left);
		if (first->right) q.push(first->right);
	}
}
int GetHeightPreorderIterative(node *r) {
	if (!r) return 0;
	stack<node *> s;
	int height = 0;
	node *first = r;
	while (true) {
		if (s.size() > height)
			height = s.size();
		if (first) {
			s.push(first);
			first = first->left;
		}
		else if (s.empty())
			break;
		else {
			first = s.top()->right;
			s.pop();
		}
	}
	return height + 1;
}

//2. Get the average of each subtrees' data. Set the data of each node to it's subtree's average data.
double SetDataAverageRecursive(node *r) {
	if (!r) {
		cout << "oops";
		exit(1);
	}
	double k = r->data;
	if (!r->right && !r->left) {
		r->data = 0;
		return k;
	}
	if (!r->right) {
		r->data = SetDataAverageRecursive(r->left);
		return (k + r->data) / 2;
	}
	else if (!r->left) {
		r->data = SetDataAverageRecursive(r->right);
		return (k + r->data) / 2;
	}
	else {
		double heightLeft = SetDataAverageRecursive(r->left);
		double heightRight = SetDataAverageRecursive(r->right);
		r->data = (heightLeft + heightRight) / 2;
		return r->data;
	}
}
double GetAverage(node *r) {
	queue<node*> q;
	q.push(r);

	node *first = nullptr;
	double average = -r->data;
	int count = -1;

	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			first = q.front();
			average += first->data;
			q.pop();
			count++;
			if (first->left) q.push(first->left);
			if (first->right) q.push(first->right);
		}
	}
	if (!count) return 0;
	return average / count;
}
void SetDataAverageIterative(node *r) {
	if (!r) return;
	queue<node *> q;
	q.push(r);
	node *first = nullptr;

	while (!q.empty()) {
		first = q.front();
		first->data = GetAverage(first);
		q.pop();
		if (first->left) q.push(first->left);
		if (first->right) q.push(first->right);
	}
}

//3. Get the number of nodes with minimum childs.
int GetMinimumNodesIterative(node *r) {
	if (!r) return -1;

	queue<node *> q;
	q.push(r);

	int count = 0;
	node *first = nullptr;

	while (!q.empty()) {
		int t = 0;
		int size = q.size();
		while (size--) {
			first = q.front();
			q.pop();
			if (first->left) {
				q.push(first->left);
				t++;
			}
			if (first->right) {
				q.push(first->right);
				t++;
			}
			if (t == 1) count++;
		}
	}
	return count;
}
int GetMinimumNodesRecursive(node *r) {
	if (!r) return -1;
	if (!r->right && !r->left) return 0;
	if (!r->left) return GetMinimumNodesRecursive(r->right) + 1;
	if (!r->right) return GetMinimumNodesRecursive(r->left) + 1;
	return GetMinimumNodesRecursive(r->right) + GetMinimumNodesRecursive(r->left);
}

//4. Get the levels with minimum number of nodes.
list<int> GetMinimumLevelsIterative(node *r) {
	if (!r) nullptr;

	queue<node *> q;
	q.push(r);

	list<int> result;
	int minCount = 2;
	int level = 0;
	node *first = nullptr;

	while (!q.empty()) {
		int size = q.size();

		if (minCount > size && level) {
			minCount = size;
			result.clear();
			result.push_back(level);
		}
		else if (minCount == size && level)
			result.push_back(level);

		while (size--) {
			first = q.front();
			q.pop();
			if (first->left) {
				q.push(first->left);
			}
			if (first->right) {
				q.push(first->right);
			}
		}
		level++;
	}
	return result;
}
int arr[100] = { 0 };
void GetMinimumLevelsRecursive(node *r, int level = 0) {
	if (!r) return;
	arr[level]++;
	GetMinimumLevelsRecursive(r->left, level + 1);
	GetMinimumLevelsRecursive(r->right, level + 1);
}

//5. Get nodes with only one child.
int GetNodesWithOneChildRecursive(node *r) {
	if (!r || (!r->right && !r->left)) return 0;
	if (!r->right) return GetNodesWithOneChildRecursive(r->left) + 1;
	if (!r->left) return GetNodesWithOneChildRecursive(r->right) + 1;
	return GetNodesWithOneChildRecursive(r->left) + GetNodesWithOneChildRecursive(r->right);
}
int GetNodesWithOneChildIterative(node *r) {
	if (!r) return -1;
	queue<node *> q;
	q.push(r);

	node *first = nullptr;
	int size = 0;
	int count = 0, t;
	while (!q.empty()) {
		size = q.size();
		while (size--) {
			t = 0;
			first = q.front();
			q.pop();
			if (first->left) {
				t++;
				q.push(first->left);
			}
			if (first->right) {
				t++;
				q.push(first->right);
			}
			if (t == 1) count++;
		}
	}
	return count;
}

//6. Get the number of leaves in a subtree. Set the data of a node to it's subtree's leaf count.
int SetDataSubtreeLeafCountRecursive(node *r) {
	if (!r) return 0;
	if (!r->right && !r->left) {
		r->data = -1;
		return 0;
	}
	if (!r->right) {
		r->data = SetDataSubtreeLeafCountRecursive(r->left);
		return r->data + 1;
	}
	if (!r->left) {
		r->data = SetDataSubtreeLeafCountRecursive(r->right);
		return r->data + 1;
	}
	r->data = SetDataSubtreeLeafCountRecursive(r->left) + SetDataSubtreeLeafCountRecursive(r->right);
	return r->data + 1;
}
int GetSubtreeLeafCount(node *r) {
	queue<node *> q;
	q.push(r);

	node *first = nullptr;
	int size = 0;
	int count = -1, t;
	while (!q.empty()) {
		size = q.size();
		while (size--) {
			t = 0;
			first = q.front();
			q.pop();
			if (first->left) {
				t++;
				q.push(first->left);
			}
			if (first->right) {
				t++;
				q.push(first->right);
			}
			if (t != 0) count++;
		}
	}
	return count;
}
void SetDataSubtreeLeafCountIterative(node *r) {
	if (!r) return;
	queue<node *> q;
	q.push(r);
	node *first = nullptr;

	while (!q.empty()) {
		first = q.front();
		first->data = GetSubtreeLeafCount(first);
		q.pop();
		if (first->left) q.push(first->left);
		if (first->right) q.push(first->right);
	}
}

//7. Check 2 trees on identical structure.
bool CheckTreesOnStructureRecursive(node *r1, node *r2) {
	if (!r1 && !r2) return true;
	if (!r1 || !r2) return false;
	return CheckTreesOnStructureRecursive(r1->left, r2->left) && CheckTreesOnStructureRecursive(r1->right, r2->right);
}
bool CheckTreesOnStructureIterative(node *r1, node *r2) {
	if (!r1 && !r2) return true;
	if (!r1 || !r2) return false;

	queue<node *> q1, q2;
	q1.push(r1);
	q2.push(r2);
	node *first1 = nullptr;
	node *first2 = nullptr;

	while (!q1.empty() && !q2.empty()) {
		first1 = q1.front();
		first2 = q2.front();

		q1.pop();
		q2.pop();

		if (first1->left && first2->left) {
			q1.push(first1->left);
			q2.push(first2->left);
		}
		else if (first1->left || first2->left)
			return false;

		if (first1->right && first2->right) {
			q1.push(first1->right);
			q2.push(first2->right);
		}
		else if (first1->right || first2->right)
			return false;
	}
	return true;
}

//8. Get the number of missed nodes in a subtree. Set the data of a node to it's subtree's missed nodes count.
int SetDataMissedNodesRecursive(node *r) {
	if (!r) return -1;
	if (!r->right && !r->left) return r->data = 0;
	if (!r->right) return r->data = SetDataMissedNodesRecursive(r->left) + 1;
	if (!r->left) return r->data = SetDataMissedNodesRecursive(r->right) + 1;
	return r->data = SetDataMissedNodesRecursive(r->left) + SetDataMissedNodesRecursive(r->right);
}
int GetDataMissedNodes(node *r) {
	if (!r) return -1;
	queue<node *> q;
	q.push(r);
	node *first = nullptr;
	int count = 0;

	while (!q.empty()) {
		first = q.front();
		q.pop();
		if (!first->left && first->right || first->left && !first->right) count++;
		if (first->left) q.push(first->left);
		if (first->right) q.push(first->right);
	}
	return count;
}
void SetDataMissedNodesIterative(node *r) {
	if (!r) return;
	queue<node *> q;
	q.push(r);
	node *first = nullptr;

	while (!q.empty()) {
		first = q.front();
		first->data = GetDataMissedNodes(first);
		q.pop();
		if (first->left) q.push(first->left);
		if (first->right) q.push(first->right);
	}
}

//9. Get the number of nodes after a particular level.
int GetNodesAfterLevelRecursive(node *r, int level) {
	if (!r) return 0;
	if (level >= 0)
		return GetNodesAfterLevelRecursive(r->left, level - 1) + GetNodesAfterLevelRecursive(r->right, level - 1);

	if (!r->right) return GetNodesAfterLevelRecursive(r->left, level - 1) + 1;
	if (!r->left) return GetNodesAfterLevelRecursive(r->right, level - 1) + 1;
	return GetNodesAfterLevelRecursive(r->left, level - 1) + GetNodesAfterLevelRecursive(r->right, level - 1) + 1;
}
int GetNodesAfterLevelIterative(node *r, int level) {
	if (!r) return 0;

	queue<node *> q;
	q.push(r);

	int count = 0;
	node *first = nullptr;
	int lvl = 0, t;

	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			t = 0;
			first = q.front();
			q.pop();
			if (first->left) {
				q.push(first->left);
				t++;
			}
			if (first->right) {
				q.push(first->right);
				t++;
			}
		}
		if (lvl > level) count += t;
		lvl++;
	}
	return count;
}

//10. Set the node data to the count of missed nodes in it's level / until the node from the root.
void SetDataMissedNodeCountIterative(node *r) {
	if (!r) return;

	queue<node *> q;
	q.push(r);

	node *first = nullptr;
	int lvl = 0;

	while (!q.empty()) {
		int size = q.size();
		int count = size;
		while (size--) {
			q.front()->data = pow(2, lvl) - count;
			first = q.front();
			q.pop();
			if (first->left) q.push(first->left);
			if (first->right) q.push(first->right);
		}
		lvl++;
	}
}
void SetDataMissedNodeUntilCountIterative(node *r) {
	if (!r) return;
	r->data = 0;
	queue<node *> q;
	q.push(r);

	node *first = nullptr;
	int lvl = 0, count;

	while (!q.empty()) {
		int size = q.size();
		int count = 0;
		while (size--) {
			first = q.front();
			q.pop();
			if (first->left) {
				q.push(first->left);
				first->left->data = count;
			}
			else count++;
			if (first->right) {
				q.push(first->right);
				first->right->data = count;
			}
			else count++;
		}
		lvl++;
	}
}
int levels[100] = { 0 };
void SetDataMissedNodeUntilRecursive(node *r, int level = 1) {
	if (!r) return;
	if (!r->left && !r->right) {
		levels[level] += 2;
		return;
	}
	if (!r->left) {
		levels[level]++;
		r->right->data = levels[level];
		SetDataMissedNodeUntilRecursive(r->right, level + 1);
	}
	else if (!r->right) {
		r->left->data = levels[level];
		levels[level]++;
		SetDataMissedNodeUntilRecursive(r->left, level + 1);
	}
	else {
		r->left->data = levels[level];
		SetDataMissedNodeUntilRecursive(r->left, level + 1);
		r->right->data = levels[level];
		SetDataMissedNodeUntilRecursive(r->right, level + 1);
	}
}
void SetDataMissedNodeIterative(node *r) {
	if (!r) return;
	r->data = 0;
	queue<node *> q;
	q.push(r);

	node *first = nullptr;
	int lvl = 0, count = 0;

	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			first = q.front();
			q.pop();
			if (first->left) {
				q.push(first->left);
				first->left->data = count;
			}
			else count++;
			if (first->right) {
				q.push(first->right);
				first->right->data = count;
			}
			else count++;
		}
		lvl++;
	}
}
int lvls[100] = { 0 };
int GetSum(int level) {
	int i = 0, sum = 0;
	while (i++ < level)
		sum += lvls[i];
	return sum;
}
void SetDataMissedNodeRecursive(node *r, int level = 1) {
	if (!r) return;
	if (!r->left && !r->right) {
		lvls[level] += 2;
		return;
	}
	if (!r->left) {
		lvls[level]++;
		r->right->data = GetSum(level);
		SetDataMissedNodeRecursive(r->right, level + 1);
	}
	else if (!r->right) {
		r->left->data = GetSum(level);
		lvls[level]++;
		SetDataMissedNodeRecursive(r->left, level + 1);
	}
	else {
		r->left->data = GetSum(level);
		SetDataMissedNodeRecursive(r->left, level + 1);
		r->right->data = GetSum(level);
		SetDataMissedNodeRecursive(r->right, level + 1);
	}
}

//11. Get the sum of nodes' data until a particular level.
int GetSumUntilLevelRecursive(node *r, int level) {
	if (!r) {
		cout << "error";
		exit(1);
	}
	if (level > 0) {
		if (!r->left && !r->right) return r->data;
		if (!r->left) return r->data + GetSumUntilLevelRecursive(r->right, level - 1);
		if (!r->right) return r->data + GetSumUntilLevelRecursive(r->left, level - 1);
		return r->data + GetSumUntilLevelRecursive(r->right, level - 1) + GetSumUntilLevelRecursive(r->left, level - 1);
	}
	else return 0;
}
int GetSumUntilLevelIterative(node *r, int level) {
	if (!r) {
		cout << "error";
		exit(1);
	}
	queue<node *> q;
	q.push(r);
	node *first = nullptr;
	int size = 0, sum = 0;

	while (!q.empty() && level) {
		size = q.size();
		while (size--) {
			first = q.front();
			sum += first->data;
			q.pop();
			if (first->left) q.push(first->left);
			if (first->right) q.push(first->right);
		}
		level--;
	}
	return sum;
}

//12. Get the node with minimum data in a level.
int GetMinInLevelIterative(node *r, int level) {
	if (!r) {
		cout << "error";
		exit(1);
	}
	queue<node *> q;
	q.push(r);
	node *first = r;
	int size = 0, min;
	bool t = true;

	while (!q.empty() && level >= 0) {
		size = q.size();
		while (size--) {
			if (t) {
				min = first->data; t = false;
			}
			first = q.front();
			q.pop();
			if (first->left) q.push(first->left);
			if (first->right) q.push(first->right);
			if (!level)
				min = min < first->data ? min : first->data;
		}
		level--;
	}
	return min;
}
int min1 = 0;
bool t = true;
void GetMinInLevelRecursive(node *r, int level) {
	if (!r) return;
	if (level == 0) {
		if (t) {
			min1 = r->data; t = false;
		}
		min1 = min1 < r->data ? min1 : r->data;
	}
	else {
		GetMinInLevelRecursive(r->right, level - 1);
		GetMinInLevelRecursive(r->left, level - 1);
	}
}

//13. Copy a tree.
void CopyTreeIterative(node *src, node *&dest) {
	if (!src) {
		dest = nullptr;
		return;
	}
	dest = new node(src->data);
	queue<node *> q1;
	queue<node *> q2;
	q1.push(src);
	q2.push(dest);
	node *first1 = nullptr;
	node *first2 = nullptr;

	while (!q1.empty()) {
		int size = q1.size();
		while (size--) {
			first1 = q1.front();
			first2 = q2.front();
			q1.pop();
			q2.pop();
			if (first1->left) {
				q1.push(first1->left);
				first2->left = new node(first1->left->data);
				q2.push(first2->left);
			}
			if (first1->right) {
				q1.push(first1->right);
				first2->right = new node(first1->right->data);
				q2.push(first2->right);
			}
		}
	}
}
node * CopyTreeRecursive(node *src, node *&dest) {
	if (!src) {
		dest = nullptr;
		return nullptr;
	}
	dest = new node(src->data);
	dest->left = CopyTreeRecursive(src->left, dest->left),
		dest->right = CopyTreeRecursive(src->right, dest->right);
	return dest;
}


int main()
{
    std::cout << "Hello World!\n"; 
}
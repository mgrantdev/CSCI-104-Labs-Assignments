#include "bst.h"

#include <stack>
#include <queue>
#include <set>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <climits>

using namespace std;

int rangeSum(Node *root, int L, int R) {
	
	//Base case - called on a null node -> return 0!
	if (root == nullptr) return 0;	
	
	//Otherwise get the value of the left and right trees under you (recursive call)
	//Sum em
	//Should add node->key to the sum?
	//Return the sum!
	if (root->key < L) return rangeSum(root->right, L, R); // Too small, go to the right subtree
	if (root->key > R) return rangeSum(root->left, L, R); // Too big, go to the left subtree
	return root->key + rangeSum(root->left, L, R) + rangeSum(root->right, L, R);
}

int maxHeight(Node* root)
{
	if (root == nullptr) return 0;
	int maxLeftHeight = maxHeight(root->left);
	int maxRightHeight = maxHeight(root->right);
	return 1 + max(maxLeftHeight, maxRightHeight); // max because the height of a tree is determined by the level of the lowest leaf node
}
    
bool isBalanced(Node *root) {
	//Get the heights of the left and right subtrees - helper func?
	//Determine if this node is balanced! If not ret false!
	if (root == nullptr) return true;
	int leftHeight = maxHeight(root->left);
	int rightHeight = maxHeight(root->right);

	//Check if there are subtrees under us
	//Are they balanced?
	if (abs(leftHeight - rightHeight) > 1) return false;
	return isBalanced(root->left) && isBalanced(root->right);

	//If all nodes are balanced return true!
}

/*

Given a binary tree, return the level order traversal of its nodes' values. (i.e. from left to right, level by level).


If you're given this binary tree as input:

    3
   / \
  9  20
    /  \
   15   7

return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]

*/
vector<vector<int>> levelOrder(Node* root) {
	vector<vector<int>> results;
	if (root == nullptr) return results;
	// BFS
	queue<Node*> q;
	q.push(root);
	while (!q.empty())
	{
		vector<int> curLevel;
		int curLevelNum = q.size(); // Each time the size of queue is the number of nodes at a level because FIFO
		for (int i = 0; i < curLevelNum; i++)
		{
			Node* node = q.front();
			q.pop();
			curLevel.push_back(node->key);
			if (node->left != nullptr) q.push(node->left);
			if (node->right != nullptr) q.push(node->right);
		}
		results.push_back(curLevel);
	}
	return results;
}


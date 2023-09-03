#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int x) {
		val = x;
		left = right = nullptr;
	}
};


class DFS_Approch_Problems {
public:

	static bool hasPathSum(TreeNode* root, int sum) {
		if (root == nullptr) {
			return false;
		}
		if (root->left == nullptr && root->right == nullptr && sum == root->val) {
			return true;
		}
		else return (hasPathSum(root->left,  sum - (root->val)) ||
			         hasPathSum(root->right, sum - (root->val)) );
	}

	static void allPathSum(TreeNode* root, int sum,
		vector<int>& currentPath, vector<vector<int>>& allPath) {

		if (root == nullptr) { return; }

		currentPath.push_back(root->val);

		if (root->left == nullptr && root->right == nullptr && sum == root->val) {
			allPath.push_back(currentPath);
		}

		else {
			allPathSum(root->left, sum - root->val, currentPath, allPath);
			allPathSum(root->right, sum - root->val, currentPath, allPath);
		}
		currentPath.pop_back();
	}

	static void allPathToLeaf(TreeNode* root, vector<int>& currentPath,
		vector<vector<int>>& allPath) {

		if (root == nullptr) { return; }

		currentPath.push_back(root->val);

		if (root->left == nullptr && root->right == nullptr) {
			allPath.push_back(currentPath);
		}

		else {
			allPathToLeaf(root->left,  currentPath, allPath);
			allPathToLeaf(root->right,  currentPath, allPath);
		}
		currentPath.pop_back();			
	}

	static bool isPathExist(TreeNode* root, vector<int> seq, int n) 
	{
		// Either root reach to the leaf or 
		// seq.size() > hight of tree. 
		if (root == nullptr || n >= seq.size() ) {		
			return false;
		}
		if (root->left == nullptr && root->right == nullptr && n == seq.size() - 1) {
			return true;
		}
		else {
			if (root->val == seq.at(n)) {
				return (isPathExist(root->left, seq, n+1) ||
					isPathExist(root->right, seq, n+1));
			}
			else return false;
		}
	}
	
	static int height(struct TreeNode* node)
	{
		// base case tree is empty
		if (node == NULL)
			return 0;

		// If tree is not empty then height = 1 + max of left
		// height and right heights
		return 1 + max(height(node->left), height(node->right));
	}

	static int treeDiameter(TreeNode* root) {
		
		if (root == nullptr) {
			return 0;
		}
		int cHeight  = height(root->left) + height(root->right) + 1;
		int diameter = treeDiameter(root->left) + treeDiameter(root->right);

		return max(cHeight, diameter);
	}

	static int findSumAllNode(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}
		return (root->val + findSumAllNode(root->left) + findSumAllNode(root->right));		
	}

	static int findMaxsum(TreeNode* root) {

		if (root == nullptr) {
			return 0;
		}
		int currentSum = findSumAllNode(root->left) + findSumAllNode(root->right);
		int allsum = findMaxsum(root->left) + findMaxsum(root->right);

		return max(currentSum, allsum);
	}

	static int checkBST(TreeNode* root, int LB, int UB) {
		if (root == nullptr) {
			return true;
		}
		if (root->val < LB || root->val >= UB) {
			return false;
		}
		else {
			return (
				checkBST(root->left, LB, root->val) &&
				checkBST(root->right, root->val, UB)
				);
		}
	}

};


TreeNode* createTree1() {
	TreeNode* root = new TreeNode(10);
	root->left = new TreeNode(100);
	root->right = new TreeNode(8);
	root->left->left = new TreeNode(3);
	root->left->right = new TreeNode(50);
	root->right->left = new TreeNode(2);
	root->right->right = new TreeNode(11);
	root->right->right->left = new TreeNode(20);
	return root;
}

TreeNode* createTree2() {
	TreeNode* root = new TreeNode(4);
	root->left = new TreeNode(2);
	root->right = new TreeNode(5);
	root->left->left = new TreeNode(1);
	root->left->right = new TreeNode(3);

	/*   	4
		   / \	
		  2   5
         / \
        1   3
	*/

	return root;
}

int main() {
	/* Constructed binary tree is
		   10
		 /   \
	   8      100
	 /  \    / \
   3     50 2   11
               / 
	         20
	 */

	TreeNode* root1 = createTree1();
	//cout<< DFS_Approch_Problems::hasPathSum(root1, 22);

	vector<vector<int>> allpaths;
	vector<int> currentPath;	
	//DFS_Approch_Problems::allPathSum(root1, 23, currentPath, allpaths);
	//DFS_Approch_Problems::allPathToLeaf(root1, currentPath, allpaths);

	//cout << DFS_Approch_Problems::isPathExist(root1, { 10,2,2,1 }, 0);

	//cout << DFS_Approch_Problems::treeDiameter(root1);
	//cout << DFS_Approch_Problems::findMaxsum(root1);

	
	cout << DFS_Approch_Problems::checkBST(createTree2(), INT_MIN, INT_MAX);

	return 0;
	
}






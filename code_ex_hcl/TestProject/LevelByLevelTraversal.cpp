#include<iostream>
#include<vector>
#include<deque>

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

class LevelOrder {
public:
	static vector<vector<int>>  traverse(TreeNode* root){

		vector<vector<int>> result;
		if (root == nullptr) {
			return result;
		}
		
		deque<TreeNode*> queue;
		queue.push_back(root);
		while (!queue.empty()) {
			vector<int> currentLevel;
			int size = queue.size();

			while (size-- > 0) {
				TreeNode* node = queue.front();
				queue.pop_front();
				if (node->left) queue.push_back(node->left);
				if (node->right) queue.push_back(node->right);

				currentLevel.push_back(node->val);
			}
			result.push_back(currentLevel);
		}
		return result;
	}

	static void print_Level_by_Lebel(vector<vector<int>> result) {

		cout << "print_Level_by_Lebel" << endl;
		for (auto collection : result) {
			for (auto item : collection) {
				cout << item << " ";
			}
			cout << endl;
		}
		cout << "\n------------------------------\n";
	}

	static void print_Rev_Level_by_Lebel(vector<vector<int>> result) {

		cout << "print_Rev_Level_by_Lebel" << endl;
		int size = result.size();
		for (int i = size - 1; i >= 0; i--) {
			vector<int> level = result[i];
			for (auto item : level) {
				cout << item << " ";
			}
			cout << "\n";
		}
		cout << "\n------------------------------\n";
	}

	static void print_zig_zag_traversal(vector<vector<int>> result) {

		bool leftToRight = true;

		cout << "print_zig_zag_traversal" << endl;

		for (auto collection : result) {
			if (leftToRight) {
				for (auto item : collection) {
					cout << item << " ";
				}
			}
			else {
				int size = collection.size();
				for (int i = size - 1; i >= 0; i--) {
					cout << collection[i] << " ";
				}
			}

			if (leftToRight) leftToRight = false;
			else leftToRight = true;
			
			cout << endl;
		}
		cout << "\n------------------------------\n";
	}

	static void right_view_of_tree(vector<vector<int>> result) {

		cout << "right_view_of_tree" << endl;

		for (auto collection : result) {
			cout << collection[collection.size() - 1] << " ";
			
		}
		cout << "\n------------------------------\n";
	}

	static void left_view_of_tree(vector<vector<int>> result) {

		cout << "left_view_of_tree" << endl;

		for (auto collection : result) {
			cout << collection[0] << " ";
		}
		cout << "\n------------------------------\n";
	}

	static void level_order_successor(vector < vector<int>> result, int num) {
		//Logic:: if num match then, print immideate next node of the current level.
		//        if num if last element of the level then print first node of the next level;  
	}

	static void find_min_depth(vector < vector<int>> result) {
		//Logic:: each level has max pow(2,hight) node,
		//        if any node has less then this number, means having
		//        leaf node at this level, so min depth is that level -1;

		int hight=0;
		for (auto collection : result) {
			int max_node = pow(2, hight);
			if (collection.size() == max_node) {
				hight++;
			}
			else
			{
				break;
			}
		}
		cout << "Min_Depth = " << hight  << endl;
		cout << "\n------------------------------\n";


	}

	static void connect_all_siblings(vector<vector<TreeNode>>* result) {
		//Logic:: This is bit diffrent, this required vector<vector<TreeNode*>> for all level
		//        instead of only data (vector<vector<int>>). once we get dont need left pointer.
		//        connect all right pointer to the next of node in level.
		          
	}


};



int main() {
	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);

	root->left->left = new TreeNode(4);
	root->left->right = new TreeNode(5);

	root->right->left = new TreeNode(6);
	root->right->right = new TreeNode(7);

	root->left->left->left = new TreeNode(8);
	root->left->left->right = new TreeNode(9);

	vector<vector<int>> result = LevelOrder::traverse(root);

	LevelOrder::print_Level_by_Lebel(result);
	LevelOrder::print_Rev_Level_by_Lebel(result);
	LevelOrder::print_zig_zag_traversal(result);
	LevelOrder::right_view_of_tree(result);
	LevelOrder::left_view_of_tree(result);

	LevelOrder::find_min_depth(result);
	LevelOrder::level_order_successor(result, 4);

	return 0;
}
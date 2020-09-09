#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;

struct node {
	int val;
	node *left;
	node *right;
	node(int v = 0, node *l = nullptr, node *r = nullptr): val(v), left(l), right(r) { ; }
};

struct item {
	node *parent;
	int begin;
	int end;
	item(node *p, int b, int e): parent(p), begin(b), end(e) { ; }
};

void show_sequence(int a[], int len) {
	for(int i = 0; i < len; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void preorder_traversal(node *root) {
	if(root == nullptr) { return; }
	cout << root->val << " ";
	preorder_traversal(root->left);
	preorder_traversal(root->right);
	return;
}

void inorder_traversal(node *root) {
	if(root == nullptr) { return; }
	inorder_traversal(root->left);
	cout << root->val << " ";
	inorder_traversal(root->right);
	return;
}

node *build_up_tree(int preorder[], int inorder[], int len) {
	node *root(nullptr);
	stack<item> state;
	int pre_loc(0), in_loc(0);
	int begin(0), end(len - 1);
	item condition(root, begin, end);
	node **sub_root = &root;
	while(pre_loc < len) {
		// whenever we enter this loop, we default that
		// the parameters, sub_root, begin, end, etc. are all ready
		// in this case, we can judge the begin and end
		if(begin > end || begin < 0 || begin > len || end < 0 || end > len) {
			condition = state.top(); state.pop();
			assert(condition.parent != nullptr);
			sub_root = &(condition.parent->right);
			begin = condition.begin; end = condition.end;
		}
		else {
			assert(sub_root != nullptr);
			// find the location of sub-root
			for(in_loc = begin; in_loc <= end; ++in_loc) {
				if(preorder[pre_loc] == inorder[in_loc]) { break; }
			}
			// get a new node
			node *temp = new node(preorder[pre_loc], nullptr, nullptr);	assert(temp != nullptr);
			// write into parent node
			*sub_root = temp;
			// push the sub-root, and the part of inorder sequence into the stack
			state.push(item(temp, in_loc + 1, end));
			// prepare the parameters
			sub_root = &(temp->left);
			begin = begin;	end = in_loc - 1;
			++pre_loc;
		}
	}
	return root;
}

node *get_tree() {
	// get the sum of nodes
	int len(0);
	cin >> len;

	// get preorder sequence
	int *preorder = new int[len];	assert(preorder != nullptr);
	for(int i = 0; i < len; ++i) {
		cin >> preorder[i];
	}
	//show_sequence(preorder, len);

	// get inorder sequence
	int *inorder = new int[len];	assert(inorder != nullptr);
	for(int i = 0; i < len; ++i) {
		cin >> inorder[i];
	}
	//show_sequence(inorder, len);

	// build up the binary tree using these two sequnces
	node *root = build_up_tree(preorder, inorder, len);

	// test
	assert(root != nullptr);
	//preorder_traversal(root);	cout << endl;
	//inorder_traversal(root);	cout << endl;

	// return memory
	delete[]preorder;	delete[]inorder;
	return root;
}

int get_depth(node *root, int present_depth) {
	if(root == nullptr) {
		return present_depth - 1;
	}
	int left_depth = get_depth(root->left, present_depth + 1);
	int right_depth = get_depth(root->right, present_depth + 1);
	return (left_depth > right_depth ? left_depth : right_depth);
}

int get_depth(node *root) {
	return get_depth(root, 0);
}

int get_diameter(node *root, int &max_dia) {
	if(root == nullptr) {
		max_dia = 0;
		return 0;
	}
	int temp_left(0), temp_right(0);
	int left_path = get_diameter(root->left, temp_left);
	int right_path = get_diameter(root->right, temp_right);
	max_dia = ((temp_left > temp_right) ? temp_left : temp_right);
	int temp = left_path + right_path + 1;
	max_dia = ((temp > max_dia) ? temp : max_dia);
	return ((left_path > right_path) ? (left_path + 1) : (right_path + 1));
}

int get_diameter(node *root) {
	int result(0);
	//int temp = 0;
	get_diameter(root, result);
	return result - 1;
}

void clear_tree(node *root) {
	if(root == nullptr) { return; }
	clear_tree(root->left);
	clear_tree(root->right);
	delete root;
	return;
}

int main() {
	// build up a binary tree using the sequences
	node *root = get_tree();
	//cout << "the depth is: ";
	cout << get_depth(root) << endl;
	//cout << "the diameter is: ";
	cout << get_diameter(root) << endl;
	clear_tree(root);
	return 0;
}

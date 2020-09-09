#include<iostream>
#include<assert.h>
using namespace std;

struct node {
	int val;
	node *leftChild;
	node *rightChild;
	node(int v = 0, node *l = nullptr, node *r = nullptr): val(v), leftChild(l), rightChild(r) { ; }
};

void preorderTraversal(node *root) {
	if(root == nullptr) { return; }
	cout << root->val << " ";
	preorderTraversal(root->leftChild);
	preorderTraversal(root->rightChild);
	return;
}

void inorderTraversal(node *root) {
	if(root == nullptr) { return; }
	inorderTraversal(root->leftChild);
	cout << root->val << " ";
	inorderTraversal(root->rightChild);
	return;
}

void buildUpTree(node *(&root), int preorder[], int inorder[], int len,
		int &pre_loc, int first, int last) {
	//printf("pre_loc = %d, first = %d, last = %d\n", pre_loc, first, last);
	if(last >= len || last < 0 || first < 0 || first >= len || first > last) {
		pre_loc -= 1;
		return;
	}
	// the preorder divide the inorder into two parts
	int sub_root(-1);
	for(int i = first; i <= last; ++i) {
		if(inorder[i] == preorder[pre_loc]) {
			sub_root = i;
			break;
		}
	}
	if(sub_root < 0) { assert(0); return; }
	// apply nodes for the root
	root  = new node(preorder[pre_loc], nullptr, nullptr);	assert(root != nullptr);
	// the first part belongs to left child
	pre_loc += 1;
	buildUpTree(root->leftChild, preorder, inorder, len, pre_loc, first, sub_root - 1);
	// the right part belongs to right child
	pre_loc += 1;
	buildUpTree(root->rightChild, preorder, inorder, len, pre_loc, sub_root + 1, last);
	// finish
	return;
}

node *getTree() {
	// get sum of the nodes
	int sum(0);
	cin >> sum;
	// get preorder sequence
	int *preorder = new int[sum];	assert(preorder != nullptr);
	for(int i = 0; i < sum; ++i) {
		cin >> preorder[i];
	}
	// get inorder sequence
	int *inorder = new int[sum];	assert(inorder != nullptr);
	for(int i = 0; i < sum; ++i) {
		cin >> inorder[i];
	}

	// construct a tree using the sequences

	// apply nodes for the root
	node *root(nullptr);
	// build up a tree, from two parts
	int pre_loc(0);
	buildUpTree(root, preorder, inorder, sum, pre_loc, 0, sum - 1);
	// return memory
	delete[]preorder;	delete[]inorder;

	return root;
}

int getDepth(node *root, int depth) {
	if(root == nullptr) {
		return depth - 1;
	}
	int result = getDepth(root->leftChild, depth + 1);
	int temp = getDepth(root->rightChild, depth + 1);
	result = (result > temp) ? result : temp;
	return result;
}

int getDepth(node *root) {
	return getDepth(root, 0);
}

int getDiameter(node *root, int &present_max) {
	if(root == nullptr) {
		present_max = 0;
		return 0;
	}
	int maxLeft(0), maxRight(0);
	int leftVal = getDiameter(root->leftChild, maxLeft);
	int rightVal = getDiameter(root->rightChild, maxRight);
	present_max = (maxLeft > maxRight) ? maxLeft : maxRight;
	int temp = leftVal + rightVal + 1;
	present_max = temp > present_max ? temp : present_max;
	return (leftVal > rightVal) ? (leftVal + 1) : (rightVal + 1);
}

int getDiameter(node *root) {
	int result(0);
	getDiameter(root, result);
	return result;
}

void clearTree(node *root) {
	if(root == nullptr) { return; }
	clearTree(root->leftChild);
	clearTree(root->rightChild);
	delete root;
	return;
}

int main() {
	node *root = getTree();
	//preorderTraversal(root);	cout << endl;
	//inorderTraversal(root);	cout << endl;
	//cout << "the depth is: ";
	cout << getDepth(root) << endl;
	//cout << "the diameter is: ";
	cout << getDiameter(root) - 1 << endl;
	clearTree(root);
	return 0;
}

#ifndef _DEFINISION_MAP_HPP_
#define _DEFINISION_MAP_HPP_

#include "declaration_map.hpp"

using namespace stl;

template <typename KEY, typename VAL>
void  map<KEY, VAL>::insertFix(map<KEY, VAL>::Node*& node)
{
	Node* uncle = nullptr;

	if (node->parent->parent != nullptr) {
		Node* P = node->parent;
		Node* GP = node->parent->parent;
		uncle = DefineUncle(node);
		if (P->color == RED && uncle != nullptr && 
		    uncle->color == RED) {
			RedDumpDown(GP);
		} else if (uncle == nullptr) {
			marginRotate(node);
		} else if (node->color == RED && P->color == RED && 
			   uncle->color == BLACK) {
			node->left->parent = node; 
			node->right->parent = node; 
			globalRotate(node);
		}	
	}
	root->color = BLACK;
	root->parent = nullptr;

} 

template <typename KEY, typename VAL>
void map<KEY, VAL>::marginRotate(Node*& node)
{
	Node* P = node->parent;
	Node* GP = node->parent->parent;

	if (node == P->right && P == GP->left) { 
		UncleNullNodeRightchildParentLeftchild(node);
	} else if (node == P->left && P == GP->left) {
		UncleNullNodeLeftchildParentLeftchild(node);
	} else if (node == P->left && P == GP->right) {
		UncleNullNodeLeftchildParentRightchild(node);
	} else if (node == P->right && P == GP->right) { 
		UncleNullNodeRightchildParentRightchild(node);
	}
}

template <typename KEY, typename VAL>
void map<KEY, VAL>::globalRotate(map<KEY, VAL>::Node*& node)
{
	Node* P = node->parent;
	Node* GP = node->parent->parent;

	if (P->right == node && P == GP->right) {
		UncleBlackNodeREDRightchildParentRedRightchild(node);
	} else if (node == P->left && P == GP->left) {
		UncleBlackNodeREDLeftchildParentRedLeftchild(node);
	} else if (node == P->left && P == GP->right) {
		UncleBlackNodeREDLeftchildParentRedRightchild(node);
	} else if (node == P->right && P == GP->left) {
		UncleBlackNodeREDRightchildParentRedLeftchild(node);
	}
}
template <typename KEY, typename VAL>
typename map<KEY, VAL>::Node* map<KEY, VAL>::DefineUncle(Node* node)
{
	Node* uncle = nullptr;
	Node* gp = node->parent->parent;
	Node* p = node->parent;
	if (gp->right != nullptr  &&
		gp->left == node->parent
	) {
		uncle = gp->right;
	} else  if (gp->left != nullptr &&
		    gp->right == node->parent
			) {
		uncle = gp->left;
	}
	return uncle;
}

template <typename KEY, typename VAL>
void map<KEY, VAL>::RedDumpDown(map<KEY, VAL>::Node* arg_node)
 {
	arg_node->left->color = BLACK;
	arg_node->right->color = BLACK;
	if (arg_node == root) {
		arg_node->color = BLACK;
		return;
	}
	arg_node->color = RED;
	insertFix(arg_node);
}

// case 1 uncle is null node is rightchild parent is leftchild
template <typename KEY, typename VAL>
void map<KEY, VAL>::
UncleNullNodeRightchildParentLeftchild(map<KEY, VAL>::Node* node)
{
	map<KEY, VAL>::Node* gp = node->parent->parent;
	if(gp->parent != nullptr) {
		if (gp == gp->parent->left) {
			gp->parent->left = node;
		} else if (gp == gp->parent->right) {
			gp->parent->right = node;
		}
	}
	Node* node_parent_parent = node->parent->parent;
	Node* node_parent = node->parent;
	Node* gp_parent = gp->parent;
	node->right = node_parent->parent;
	node->left  = node_parent;
	node->parent = gp_parent;
	node->right->parent = node;
	node->left->parent = node;
	if (node_parent_parent == root) {
		root = node;
	}
	root->color = BLACK;
	MakeNull(node->left);
	return;
}

// case 2 uncle is null node is leftchild parent is rightchild
template <typename KEY, typename VAL>
void map<KEY, VAL>::
UncleNullNodeLeftchildParentRightchild(map<KEY, VAL>::Node* node)
{
	Node* gp = node->parent->parent;
	if(gp->parent != nullptr) {
		if (gp == gp->parent->left) {
			gp->parent->left = node;
		} else if (gp == gp->parent->right) {
			gp->parent->right = node;
		}
	}
	Node* node_parent = node->parent;
	Node* node_parent_parent = node->parent->parent;
	Node* gp_parent = gp->parent;
	node->right = node_parent;
	node->left = node_parent_parent;
	node->parent = gp_parent;
	node->left->parent = node;
	node->right->parent = node;
	if (root == node_parent_parent) {
		root = node;
	}
	root->color = BLACK;
	MakeNull(node->right);
	return ;
}

// case 3 uncle is null node is leftchild parent is leftchild
template <typename KEY, typename VAL>
void map<KEY, VAL>::
UncleNullNodeLeftchildParentLeftchild(map<KEY,VAL>::Node* node)
 {
	Node* gp = node->parent->parent;
	if(gp->parent != nullptr) {
		if (gp == gp->parent->left) {
			gp->parent->left = node->parent;
		} else if (gp == gp->parent->right) {
			gp->parent->right = node->parent;
		}
	}
	node->parent->right = node->parent->parent;
	node->parent->parent = node->parent->parent->parent;
	node->parent->right->parent = node->parent;
	if (gp == root) {
		root = node->parent;
	}
	root->color = BLACK;
	MakeNull(node);
	return ;
}

// case 4 uncle is null node is rightchild parent is rightchild
template <typename KEY, typename VAL>
void map<KEY, VAL>::
UncleNullNodeRightchildParentRightchild(map<KEY, VAL>::Node* node)
 {
	Node* gp = node->parent->parent;
	if(gp->parent != nullptr) {
		if (gp == gp->parent->left) {
			gp->parent->left = node->parent;
		} else if (gp == gp->parent->right) {
			gp->parent->right = node->parent;
		}
	}
	node->parent->parent = gp->parent;
	node->parent->left = gp;
	gp->parent = node->parent;
	if(root == gp) {
		root = node->parent;
	}
	root->color = BLACK;
	MakeNull(node);
	return ;
}

// case 5 uncle is BLACK node is RED and rightchild parent is RED and rightchild  
template <typename KEY, typename VAL>
void map<KEY, VAL>::
UncleBlackNodeREDRightchildParentRedRightchild(map<KEY, VAL>::Node* node)
{
	Node* gp = node->parent->parent;
	if (gp!=root) {
		if (gp == gp->parent->right) {
			gp->parent->right = node->parent;
		} else {
			gp->parent->left = node->parent;
		}
	}
	Node* tmp_node = gp->parent;
	gp->parent = node->parent;
	gp->right = node->parent->left;
	node->parent->left->parent = gp;
	node->parent->left = gp;
	node->parent->parent = tmp_node;
	if (gp == root) {
		root = node->parent;
	}
	ColorFix(node);
	root->color = BLACK;
	return;
}

// case 6 uncle is BLACK node is RED and leftchild parent is RED and leftchild
template <typename KEY, typename VAL>
void map<KEY, VAL>::
UncleBlackNodeREDLeftchildParentRedLeftchild(map<KEY, VAL>::Node* node)
{
	map<KEY, VAL>::Node* gp = node->parent->parent;
	if (gp!=root) {
		if (gp == gp->parent->right) {
			gp->parent->right = node->parent;
		} else {
			gp->parent->left = node->parent;
		}
	}
	map<KEY, VAL>::Node* tmp_node = gp->parent;
	gp->parent = node->parent;
	gp->left = node->parent->right;
	node->parent->right->parent = gp;
	node->parent->right = gp;
	node->parent->parent = tmp_node;
	ColorFix(node);
	if (gp == root) {
		root = node->parent;
	}
	root->color = BLACK;
	return;
}

// case 7 uncle is BLACK node is RED and leftchild parent is RED and rightchild
template <typename KEY, typename VAL>
void map<KEY, VAL>::
UncleBlackNodeREDLeftchildParentRedRightchild(map<KEY, VAL>::Node* node)
{

	Node* gp = node->parent->parent;
	Node *gp_right = gp->right;
	Node *node_parent_left = node->parent->left;
	Node *node_parent_parent = node->parent->parent;
	Node *node_right_parent = node->right->parent;
	Node *node_right = node->right;
	Node *node_parent = node->parent;
	node->parent->left = node_right;
	node->parent->left->parent = node; // there is issue in this line but after  " fixing "
	gp->right = node;
	node->right = node_parent;
	node->right->parent = node;
	node->parent = gp;
	insertFix(node->right);
	root->color = BLACK;
}

// case 8 uncle is BLACK node is RED and leftchild parent is RED and rightchild
template <typename KEY, typename VAL>
void map<KEY, VAL>::
UncleBlackNodeREDRightchildParentRedLeftchild(map<KEY, VAL>::Node* node)
{
        Node *gp = node->parent->parent;
        Node *gp_left = gp->left;
        Node *node_parent_right = node->parent->right;
        Node *node_parent_parent = node->parent->parent;
        Node *node_left_parent = node->left->parent;
        Node *node_left = node->left;
        Node *node_parent = node->parent;
	node->parent->right = node_left;
	node->parent->right->parent = node;
	gp->left = node;
	node->left = node_parent;
	node->left->parent = node;
	node->parent = gp;
	insertFix(node->left);
	root->color = BLACK;
}

template <typename KEY, typename VAL>
void map<KEY, VAL>::MakeNull(map<KEY, VAL>::Node*& node)
{
	Node* sibling = nullptr;
	node->left = nullptr;
	node->right = nullptr;
	if (node->parent->left == node) {
		sibling = node->parent->right;
	} else {
		sibling = node->parent->left;
	}
	sibling->left = nullptr;
	sibling->right = nullptr;
	ColorFix(node);
}

template <typename KEY, typename VAL>
void map<KEY, VAL>::ColorFix(map<KEY, VAL>::Node*& node)
{
	map<KEY, VAL>::Node* sibling = nullptr;
	if (node->parent->left == node) {
		sibling = node->parent->right;
	} else {
		sibling = node->parent->left;
	}
	sibling->color = RED;
	node->color = RED;
	node->parent->color = BLACK;
}

template <typename KEY, typename VAL>
typename map<KEY, VAL>::Node*
map<KEY, VAL>::InOrder (map<KEY, VAL>::Node* ptr)
{
	if (ptr != nullptr) {
		InOrder(ptr->left);
		std::cout<< ptr->data<< "   " << ptr->color << std::endl;
		InOrder(ptr->right);
	}
	return ptr;
}

template <typename KEY, typename VAL>
typename map<KEY, VAL>::Node* 
map<KEY, VAL>::find_right_more_node(map<KEY, VAL>::Node* node)
{
	if (node->right == nullptr) {
		return node;
	} else {
		return find_right_more_node(node->right);
	}
}

template <typename KEY, typename VAL>
typename map<KEY, VAL>::Node*
map<KEY, VAL>::find_left_more_node(map<KEY, VAL>::Node* node)
{
	if (node->left == nullptr) {
		return node;
	} else {
		return find_left_more_node(node->left);
	}
}

// new node insertion with checking if the member data is unique or not
template <typename KEY, typename VAL>
void map<KEY, VAL>::InsertFromGivenNode(map<KEY, VAL>::Node* node,
		             map<KEY, VAL>::Node* current, bool& isEqual)
{
	if (node->data == current->data) {
		isEqual = false;
		delete node;
		return;
	} else if (node->data < current->data && current->left != nullptr) {
		InsertFromGivenNode(node, current->left, isEqual);
	} else if (node->data > current->data && current->right != nullptr) {
		InsertFromGivenNode(node, current->right, isEqual);
	} else if (node->data < current->data && current->left == nullptr) {
		current->left = node;
		node->parent = current;
		return;
	} else if (node->data > current->data && current->right == nullptr) {
		current->right = node;
		node->parent = current;
		return;
	}
}

template <typename KEY, typename VAL>
void map<KEY, VAL>::
DeleteTheGivenVal (map<KEY, VAL>::Node* current, map& arg_ob, KEY& arg_int)
{
	if (current != nullptr) {
		DeleteTheGivenVal(current->left, arg_ob, arg_int);
		if(current->data.first != arg_int){
			  arg_ob.insert(current->data.first, current->data.second);
		}
		DeleteTheGivenVal(current->right, arg_ob, arg_int);
	}
}

template <typename KEY, typename VAL>
void  map<KEY, VAL>::FreeSpace(map<KEY, VAL>::Node* ptr)
{
	if (ptr != nullptr) {
		FreeSpace(ptr->left);
		FreeSpace(ptr->right);
		delete ptr;
	}
}

template <typename KEY, typename VAL>
std::pair<KEY, VAL>  map<KEY, VAL>::PairCreater(KEY key, VAL val)
{
	return std::make_pair(key, val);
}

template <typename KEY, typename VAL>
void  map<KEY, VAL>::insert(KEY key, VAL value)
{
	auto arg_int = map<KEY, VAL>::PairCreater(key, value);
	if (root != nullptr) {
		bool isEqual = true;
		Node* new_node = new Node;
		new_node->data.first = arg_int.first;
		new_node->data.second = arg_int.second;
		new_node->color = RED;
		InsertFromGivenNode(new_node, root, isEqual);
		if (isEqual) {
			insertFix(new_node);
		}
	} else {	
		root = new Node;
		root->data.first = arg_int.first;
		root->data.second= arg_int.second;
		root->color = BLACK;
		root->parent = nullptr;
	}	 
}

template <typename KEY, typename VAL>
void map<KEY, VAL>::Delete(KEY key)
{
	map<KEY, VAL>  new_ob;
	DeleteTheGivenVal(root, new_ob, key);
	shutFreeSpace = true;
	Node* tmp_node;
	tmp_node = this->root;
	this->root = new_ob.root;
	new_ob.root = tmp_node;
}

#endif // _DEFINISION_MAP_HPP_

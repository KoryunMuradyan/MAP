#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include "declaration_map.hpp"

using namespace stl;

template <typename KEY, typename VAL>
typename map<KEY, VAL>::iterator& map<KEY, VAL>::iterator::operator++ ()
{
	if (current->right == nullptr) {
		Node* tmp_node = return_to_left_path(current);
		if (tmp_node->parent == nullptr) {
			current = current->right;
			return *this;
		}
		current = tmp_node->parent;
		return *this;
	} else {
		current = find_left_more_node(current->right);
	}
	return *this;
}

template <typename KEY, typename VAL>
typename map<KEY, VAL>::value_type map<KEY, VAL>::iterator::operator* ()
{
	assert(current != 0);
	return current->data;
}

template <typename KEY, typename VAL>
bool map<KEY, VAL>::iterator::operator== (const map<KEY, VAL>::iterator& o) 
{
	return current == o.current;
}

template <typename KEY, typename VAL>
bool map<KEY, VAL>::iterator::operator!= (const map<KEY, VAL>::iterator& o) 
{
	return this->current != o.current;
}

template <typename KEY, typename VAL>
typename map<KEY, VAL>::Node* 
map<KEY, VAL>::iterator::find_left_more_node(Node* arg_node)
{
	if (arg_node->left == nullptr) {
		return arg_node;
	} else {
		return find_left_more_node(arg_node->left);
	}
}

template <typename KEY, typename VAL>
typename map<KEY, VAL>::Node*
map<KEY, VAL>::iterator::return_to_left_path(Node* arg_node)
{
	if (arg_node->parent == nullptr) {
		return arg_node;
	}
	if (arg_node == arg_node->parent->right) {
		return return_to_left_path(arg_node->parent);
	} else {
		return arg_node;
	}
}		

template <typename KEY, typename VAL>
typename map<KEY, VAL>::iterator
map<KEY, VAL>::begin() 
{
	Node * tmp = find_left_more_node(root);
	return iterator(find_left_more_node(root));
 }

template <typename KEY, typename VAL>
typename map<KEY, VAL>::iterator map<KEY, VAL>::end() 
{
	return iterator(nullptr);
}

#endif  // _ITERATOR_HPP_ 

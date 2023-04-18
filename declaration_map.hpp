#ifndef _DECLARATION_MAP__HPP__
#define _DECLARATION_MAP__HPP__

#include <iostream>
#include <cassert>
#include <initializer_list>
#include "map.hpp"

namespace stl
{
	template <typename KEY, typename VAL>
	class map
	{
		public:
			using value_type = std::pair<const KEY, VAL>;
			using size_type = std::size_t;
		private:
			enum Colour { RED, BLACK };
			struct Node
			{
				Colour color = RED; // RED->0 BLACK ->1	
				std::pair<KEY, VAL> data ; 
				Node* left = nullptr;
				Node* right = nullptr;
				Node* parent =  nullptr;
			};
			void FreeSpace(Node*);
			void DeleteTheGivenVal (Node*, map&, KEY&);
			void InsertFromGivenNode(Node*, Node*, bool&);
			void RedDumpDown(Node*);
			void UncleNullNodeRightchildParentLeftchild(Node*);
			void UncleNullNodeLeftchildParentLeftchild(Node*);
			void UncleNullNodeLeftchildParentRightchild(Node*);
			void UncleNullNodeRightchildParentRightchild(Node*);
			void UncleBlackNodeREDRightchildParentRedRightchild(Node*);
			void UncleBlackNodeREDLeftchildParentRedLeftchild(Node*);
			void UncleBlackNodeREDLeftchildParentRedRightchild(Node*);
			void UncleBlackNodeREDRightchildParentRedLeftchild(Node*);
			Node* DefineUncle(Node*);
			void marginRotate(Node*&);
			void globalRotate(Node*&);
			void insertFix(Node*&);
			void MakeNull(Node*&);
			void ColorFix(Node*&);
			Node*  InOrder (Node*);
			Node* find_right_more_node(Node*);
			Node* find_left_more_node(Node*);
		public:
			Node *root = nullptr;
			bool shutFreeSpace = false;
			map()
			{
			}
			~map()
			{	
				FreeSpace(root);
			}
			std::pair<KEY, VAL> PairCreater(KEY, VAL);
			void insert(KEY, VAL);
			void Delete(KEY arg);
			class iterator
			{
				private:
					friend class map<KEY, VAL>;
					Node* current;
					iterator (Node* c)
						: current(c)
					{}
				public:
					value_type operator* ();
					iterator& operator++ ();
					bool operator== (const iterator& o);
					bool operator!= (const iterator& o);
					Node* find_left_more_node(Node*);
					Node* return_to_left_path(Node*);
			}; // Iterator end

			iterator begin();
			iterator end();
	}; // Class end 
} // Namespace end

#endif // _DECLARATION_MAP__HPP__

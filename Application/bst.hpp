/**
 * @file bst.hpp
 * @author Muhammad Musa Khan
 * @description BST Tree implementation in C++
*/
#pragma once
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<iomanip>
#include<math.h>
#include<queue>
#include<vector>
#include<tuple>
#include<type_traits>

using namespace std;
template <typename T1, typename T2>
class Node
{
	private:
		T1 key;					//city name
		vector<T2> value;		//vector of hotel pointers in the city
		Node<T1,T2>* left;		//left child
		Node<T1,T2>* right;		//right child
		Node<T1,T2>* parent;	//pointer to the parent node
	public:
		Node(T1 key) : key(key),left(nullptr),right(nullptr), parent(nullptr) {}
		void print(string stars="")	//print all or only those hotels with specific stars.
		{
			int counter=0;
			cout<<std::left<<setw(50)<<"Name"<<" "<<setw(10)<<"City"<<" "<<setw(6)<<"Stars"<<" "<<setw(10)<<"Price"<<" "<<setw(20)<<"Country"<<" "<<"Address"<<endl;
			cout<<"------------------------------------------------------------------------------------------------------------"<<endl;

			for(auto it:value)
				if(stars=="" or stars==it->getStars())
				{
					it->print2();
					counter++;
				}
			
			cout<<"------------------------------------------------------------------------------------------------------------"<<endl;
			cout<<counter<<" records found."<<endl;
		}

		// helper methods 
		bool isFullInternal(); // returns true if both child != nullptr

		template<typename,typename> friend class BST;
};
//=============================================================================
template <typename T1, typename T2>
class BST
{
	private:
		Node<T1,T2> *root;
	public:
		BST();									//constructor
		~BST();									//destructor
		Node<T1,T2>* getRoot();						//returns the root of the Tree
		void insert(Node<T1,T2>* ptr, T1 key, T2 val);			//Insert key into tree/subtree with root ptr
		int height(Node<T1,T2>* ptr);				    //Find the height of a tree/subtree with root ptr
		tuple<Node<T1,T2>*, bool> findNode(Node<T1,T2>* ptr, T1 key);		//Find and returns the node with key
		Node<T1,T2>* findMin(Node<T1,T2>* ptr);				//Find and return the Node<T1,T2> with minimum key value from a tree/subtree with root ptr
		void remove(Node<T1,T2>* ptr,T1 key, T2 val);			//Remove a node with key from the tree/subtree starting at ptr
	
	// helper methods
		Node<T1,T2>* removeAboveExternal(Node<T1, T2>* ptr); // external here refers to nullptr, so remove node with at least one of left and right pointer pointing to nullptr
		Node<T1,T2>* removeInternal(Node<T1, T2>* ptr); // internal here refers to a node both pointers != nullptr
		void insertAtExternal(Node<T1,T2>* ptr, bool right, T1 key, T2 val); // insert at external node, right indicates whether to insert at the right or left child
		void recursiveDealloc(Node<T1, T2>* ptr); // recursive deallocation of pointers in each vector of each node
		bool checkFindNodeReturn(tuple<Node<T1,T2>*, bool> findNodeTuple, T1 key); // to check if the node returned by findNode is the node we were looking for, or if it's the parent of the node we were looking for since the node we were looking for doesn't exist
};
//==========================================

//=========== Node =========================
//==========================================
template <typename T1, typename T2>
bool Node<T1,T2>::isFullInternal() // returns true if both child != nullptr
{ 
	return this->left != nullptr && this->right != nullptr;
}

//=========== BST ==========================
//==========================================
template <typename T1, typename T2>
BST<T1,T2>::BST() { this->root = nullptr; }
//==========================================
template <typename T1, typename T2>
BST<T1,T2>::~BST() { recursiveDealloc(root); } // just call the recursiveDealloc method - see below
//==========================================
template <typename T1, typename T2>
Node<T1,T2>* BST<T1,T2>::getRoot() { return this->root; }
//==========================================
template <typename T1, typename T2>
int BST<T1,T2>::height(Node<T1,T2>* ptr) 
{
	if (ptr == nullptr) return -1; // base case, if ptr is nullptr, return -1
	else {
		int right_h = height(ptr->right);
		int left_h = height(ptr->left);
		return (max(right_h, left_h) + 1); // recursive step, return the max of the height of the left and right subtrees + 1
	}
}
//==========================================
template <typename T1, typename T2>
tuple<Node<T1,T2>*, bool> BST<T1,T2>::findNode(Node<T1,T2>* ptr, T1 key) 
{
  if (ptr == nullptr) throw runtime_error("BST::find called on nullptr.");
	
	if (key == ptr->key) { 
		return make_tuple(ptr, false); // return pointer to node AND false doens't hold any significance in this case
	} else if (key < ptr->key) { // if key is less than current node's key
		if (ptr->left != nullptr) return findNode(ptr->left, key); // and if left child exists, go left
		else return make_tuple(ptr, false); // otherwise return pointer to the current node and false to indicate that we were supposed to go left but couldn't because left child didn't exist
	} else { // else if key is greater than current node's key
		if (ptr->right != nullptr) return findNode(ptr->right, key); // and if right child exists, go right
		else return make_tuple(ptr, true); // otherwise return pointer to the current node and true to indicate that we were supposed to go right but couldn't because right child didn't exist - this is used in the insert and remove methods
	}
}
//==========================================
template <typename T1, typename T2>
Node<T1,T2>* BST<T1,T2>::findMin(Node<T1,T2>* ptr) 
{
  if (ptr == nullptr) throw runtime_error("BST::findMin called on nullptr.");

	while (ptr->left != nullptr) { // take left turns until last node
		ptr = ptr->left;
	}
	return ptr;
}
//==========================================
template <typename T1, typename T2>
void BST<T1,T2>::insert(Node<T1,T2>* ptr, T1 key, T2 val) 
{
	if (root == nullptr) {
		root = new Node<T1,T2>(key); // create a root node if it doesn't exist
		root->value.push_back(val);	
	} else {
		auto result = findNode(ptr, key);
		Node<T1,T2>* node_ins = get<0>(result); // get the pointer to the node where the key should be inserted
		bool right = get<1>(result);

		if (key == node_ins->key) { // if node exists
			for (T2 pointer : node_ins->value) { // if value already exists, do nothing
				if (pointer == val) return;
			}
			node_ins->value.push_back(val); // otherwise push back to the node's vector
		}
		else insertAtExternal(node_ins, right, key, val); // for the case where the node doesn't exist, insert at the external node, right indicates whether to insert at the right or left child
	}
}
//==========================================
template <typename T1, typename T2>
void BST<T1,T2>::remove(Node<T1,T2>* ptr, T1 key, T2 val) 
{
	Node<T1,T2>* node_rmv = get<0>(findNode(ptr, key)); // get the pointer to the node where val to be removed exists

	if (key == node_rmv->key) { // if node for that city exists
		for (auto it = node_rmv->value.begin(); it != node_rmv->value.end(); it++) { // iterate over the vector
			if (val == *it) { // if the value exists, delete it
				delete *it; // free memory here
				it = node_rmv->value.erase(it);
				break;
			}
		}

		if (node_rmv->value.empty()) { // if after removal of val from node's vector, the node is now empty, remove the node altogether
			if (node_rmv->isFullInternal()) {  // if internal, call removeInternal()
				removeInternal(node_rmv);
			} else {
				removeAboveExternal(node_rmv); // otherwise call removeAboveExternal
			}
		}	
	} else throw runtime_error("No node with this key exists.");
}
//==========================================
//============== helper methods ============
template <typename T1, typename T2>
Node<T1,T2>* BST<T1,T2>::removeInternal(Node<T1, T2>* ptr) // internal here refers to a node both pointers != nullptr
{
	Node<T1, T2>* min = findMin(ptr->right); // find the min of the right subtree
	ptr->key = min->key; // replace the key and value of the node to be removed with the key and value of the min of the right subtree
	ptr->value = min->value;

	removeAboveExternal(min); // remove the min node of the right subtree
	return ptr;
}
//==========================================
template <typename T1, typename T2>
Node<T1,T2>* BST<T1,T2>::removeAboveExternal(Node<T1,T2>* ptr) // external here refers to nullptr, so remove node with at least one of left and right pointer pointing to nullptr
{
	if (ptr->left == nullptr && ptr->right == nullptr) { // for the case of both child nullptr
		if (ptr == root) {
			delete ptr;
			root = nullptr;
			return nullptr;
		} else {
			(ptr->parent->left == ptr ? ptr->parent->left : ptr->parent->right) = nullptr; 
			Node<T1,T2>* parent = ptr->parent;
			delete ptr;
			return parent;
		}		
	}	else { // one child nullptr
		Node<T1,T2>* child = (ptr->left != nullptr ? ptr->left : ptr->right); // reconnect the nodes
		if (ptr == root) {
			root = child; // if root, simply set root to the child
			child->parent = nullptr;
		} else {
			Node<T1,T2>* grand_parent = ptr->parent;
			
			child->parent = grand_parent; // connect grandparent and child directly
			(grand_parent->left == ptr ? grand_parent->left : grand_parent->right) = child;
		}

		delete ptr;
		return child; // return a pointer to child
	}
}
//==========================================
template <typename T1, typename T2>
void BST<T1,T2>::insertAtExternal(Node<T1,T2>* ptr, bool right, T1 key, T2 val) 
{
	if (ptr == nullptr) throw runtime_error("BST::insertAtExternal called on nullptr.");

	Node<T1,T2>* new_node = new Node<T1,T2>(key); // create a new node, push back the value
	new_node->value.push_back(val);

	new_node->parent = ptr; // connect the new node to the parent
	(right ? ptr->right : ptr->left) = new_node;
}
//==========================================
template <typename T1, typename T2>
void BST<T1,T2>::recursiveDealloc(Node<T1, T2>* ptr) 
{
  if (ptr == nullptr) return; // base case
	
	recursiveDealloc(ptr->left); // binary recursion - postorder traversal
	recursiveDealloc(ptr->right);

	if (std::is_pointer<T2>::value) { // to define special case for when T2 is a pointer (in our case, T2 is indeed a pointer)
		for (T2 pointer : ptr->value) { // iterate and free memory
			delete pointer;
		}
		ptr->value.clear(); // clear the vector
	}
	delete ptr;
}
//==========================================
template <typename T1, typename T2>
bool BST<T1,T2>::checkFindNodeReturn(tuple<Node<T1,T2>*, bool> findNodeTuple, T1 key) // to check if the node returned by findNode is the node we were looking for, or if it's the parent of the node we were looking for since the node we were looking for doesn't exist
{
	Node<T1,T2>* node = get<0>(findNodeTuple);
	if (node->key == key) return true;
	else return false;
}

#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using std::string;
using std::cin;
using std::cout;
using std::endl;

class AVLTreeNode {
public:

	AVLTreeNode* parent;  // Pointer to the parent node
    AVLTreeNode* left;    // Pointer to the left child
    AVLTreeNode* right;   // Pointer to the right child
    string word;          // The word stored in the node
    int wordCount;        // Number of times the word appears
    int height;           // Height of the node

	AVLTreeNode (const string& w){
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		wordCount = 1;
		height = 0;
		word = w;
	}

};

// Wordlist class
class Wordlist
{
private:

	AVLTreeNode* root; // DO NOT REMOVE
	// Stores the total number of unique words in the AVL tree.
	unsigned int size; 
	
	// Inserts a word into the subtree rooted at 'root'.
	AVLTreeNode* insertNode(AVLTreeNode* root, const string& w);

	// Helper function to count the number of singletons (words with a frequency of 1).
	void singletonsCounter(AVLTreeNode* node, int* counter) const;

	// Helper function to check if a specific word exists in the subtree rooted at 'node'.
	bool wordFinder(const string& w, AVLTreeNode* node) const;

	// Helper function to count the occurrences of a specific word in the subtree rooted at 'node'.
	int WordCounter(const string& w, AVLTreeNode* node) const;

	// Creates a deep copy of the entire tree rooted at 'node'.
	AVLTreeNode* copyTree(AVLTreeNode* node);

	// Recursively traverses the subtree rooted at 'node' and prints each word in sorted order.
	void WordPrinter(AVLTreeNode* node, int& count) const;

	// Creates a deep copy of the subtree rooted at 'node'.
	AVLTreeNode* copySubtree(AVLTreeNode* node);

	// Counts the number of nodes in the subtree rooted at 'node'.
	int countNodes(AVLTreeNode* node) const;

	// Helper function to find the most frequent word in the subtree rooted at 'node'.
	void MFnode(AVLTreeNode* node, AVLTreeNode*& Most_Frequent_node) const;

	// Returns the height of the subtree rooted at 'node'.
	int height(AVLTreeNode* node) const;

	// Calculates and returns the balance factor of the subtree rooted at 'node'.
	int getBalance(AVLTreeNode* node) const;

	// Performs a left rotation on the subtree rooted at 'node'.
	AVLTreeNode* rotateLeft(AVLTreeNode* node);

	// Performs a right rotation on the subtree rooted at 'node'.
	AVLTreeNode* rotateRight(AVLTreeNode* node);

	// Helper function to remove a word from the subtree rooted at 'node'.
	AVLTreeNode* removeWord(AVLTreeNode* node, const string& w, bool& wordFound);

	// Finds the in-order successor of the given 'node'.
	AVLTreeNode* findSuccessor(AVLTreeNode* node) const;


public:
	// public methods go here
	Wordlist();
	Wordlist(const string &filename);
	~Wordlist();
	Wordlist(const Wordlist& other);
	Wordlist& operator=(const Wordlist& other);
	int differentWords() const;
	int totalWords() const;
	string mostFrequent() const;
	int singletons() const;
	bool contains(const string& w) const;
	int getCount(const string& w) const;
	void printWords() const;
	void deleteSubtree(AVLTreeNode* node);
	void insert(const string& w);
	bool remove(const string& w);
	


	// Prints useful statistics about the word list
	void printStatistics() const;

	// Returns the root of the AVL tree
	AVLTreeNode* getRoot() const { return root; }; // DO NOT REMOVE
};
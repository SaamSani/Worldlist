#include "Wordlist.h"
#include <iomanip>
using std::setprecision;
using std::fixed;

// Prints useful statistics about the word list
void Wordlist::printStatistics() const
{
	cout << "Number of different words: " << differentWords() << endl;
	cout << "    Total number of words: " << totalWords() << endl;
	cout << "       Most frequent word: " << mostFrequent() << endl;
	cout << "     Number of singletons: " << singletons()
		<< setprecision(0) << fixed
		<< " (" << 100.0 * singletons() / differentWords() << "%)"
		<< endl;
}

// Default constructor - creates an empty Wordlist with root set to nullptr
Wordlist::Wordlist(){
		root = nullptr;
}


// File constructor - reads words from a file and inserts them into the tree
Wordlist::Wordlist(const string &filename) {
    root = nullptr; // Initialize root to nullptr

    // Open the file
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Couldn't open the file");
    }

    string line;
    string word;

    // Read file line by line
    while (getline(file, line)) {
        if (line.empty()) {
            continue; // Skip empty lines
        }

        // Extract words from the line
        std::istringstream lineExtraction(line);
        while (lineExtraction >> word) {
            insert(word); // Insert each word into the AVL tree
        }
    }

    file.close(); // Close the file
}

// Destructor to clean up memory allocated for the AVL tree
Wordlist::~Wordlist(){
	deleteSubtree(root);
	root = nullptr;
}

// Recursively deletes all nodes in a subtree
void Wordlist::deleteSubtree(AVLTreeNode* node){
	if(node == nullptr){
		return;
	}

    // Recursively delete left and right subtrees
	deleteSubtree(node->left);
	deleteSubtree(node->right);

	delete node;

}


// Helper function to count nodes recursively
int Wordlist::countNodes(AVLTreeNode* node) const  {
	if(node == nullptr){
		return 0;
	}
	// Count the current node and recursively count the left and right subtrees
	return 1 + countNodes(node->left) + countNodes(node->right);
}



// Public method to count distinct words
int Wordlist::differentWords() const {
    return countNodes(root); // Start counting from the root
}


// Helper function to sum word counts recursively
int countTotalWords(AVLTreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->wordCount + countTotalWords(node->left) + countTotalWords(node->right);
}


// Public method to calculate total word count
int Wordlist::totalWords() const {
    return countTotalWords(root); // Start summing from the root
}

// Helper function to find the most frequent word node recursively
void Wordlist::MFnode(AVLTreeNode* node, AVLTreeNode*& Most_Frequent_node) const {
    if (node == nullptr) {
        return; // Base case: stop recursion at null nodes
    }

    // Update the most frequent node if:
    // 1. There is no Most_Frequent_node yet (first node being evaluated)
    // 2. Current node's wordCount is greater than the most frequent node's wordCount
    // 3. There is a tie in wordCount, and the current word is lexicographically smaller
    if (Most_Frequent_node == nullptr || 
        node->wordCount > Most_Frequent_node->wordCount || 
        (node->wordCount == Most_Frequent_node->wordCount && node->word < Most_Frequent_node->word)) {
        Most_Frequent_node = node;
    }

    // Recurse through left and right subtrees
    MFnode(node->left, Most_Frequent_node);
    MFnode(node->right, Most_Frequent_node);
}

// Finds and returns the most frequent word
string Wordlist::mostFrequent() const {
    if (root == nullptr) {
        throw std::invalid_argument("The word list is empty."); // Handle empty tree
    }

    AVLTreeNode* mostFrequentNode = nullptr;
    MFnode(root, mostFrequentNode); 

    return mostFrequentNode->word + " " + std::to_string(mostFrequentNode->wordCount);
}

// Helper function to count singletons (words with count 1)
void Wordlist::singletonsCounter(AVLTreeNode* node, int* counter) const{
    if (node == nullptr) {
        return;
    }

    if (node->wordCount == 1) {
        (*counter)++; // Increment counter if the node is a singleton
    }

    singletonsCounter(node->left, counter);
    singletonsCounter(node->right, counter);
}

// Public method to count singletons
int Wordlist::singletons() const {
    int x = 0; 
    singletonsCounter(root, &x); 
    return x;
}

// Checks if the word exists in the tree
bool Wordlist::contains(const string& w) const{
	return wordFinder(w, root);
}

// Helper function to search for a word recursively
bool Wordlist::wordFinder(const string& w, AVLTreeNode* node) const{
	if(node == nullptr){
		return false;
	}

	if(node->word == w){
		return true;
	}
    
	// Recur left or right depending on lexicographic order
	if (w < node->word) { 
        return wordFinder(w, node->left);
    } 
	else { 
        return wordFinder(w, node->right);
    }
}

// Returns the count of a specific word in the tree
int Wordlist::getCount(const string& w) const{
	return WordCounter(w, root);

}

// Helper function to count occurrences of a word recursively
int Wordlist::WordCounter(const string& w, AVLTreeNode* node) const{
	if(node == nullptr){
		return 0;
	}

	if(node->word == w){
		return node->wordCount;
	}

	if (w < node->word) { 
        return WordCounter(w, node->left);
    } 
	else { 
        return WordCounter(w, node->right);
    }

}

// Print all words in the tree in sorted order with their counts
void Wordlist::printWords() const{
	int count = 1;
	WordPrinter(root, count);
}

// Helper function to recursively print words in sorted order
void Wordlist::WordPrinter(AVLTreeNode* node, int& count) const{
	if(node == nullptr){
		return;
	}

	WordPrinter(node->left, count); 

    std::cout << count << ". " << node->word << " " << node->wordCount << std::endl;
    count++;

    WordPrinter(node->right, count); 
}

// Creates a deep copy of a subtree rooted at the given node
AVLTreeNode* Wordlist::copySubtree(AVLTreeNode* node){
	if (node == nullptr) {
        return nullptr; 
    }

	AVLTreeNode* newNode = new AVLTreeNode(node->word);
	newNode->wordCount = node->wordCount;

    newNode->left = copySubtree(node->left);
    newNode->right = copySubtree(node->right);

    return newNode;

}

// Copy constructor for Wordlist
Wordlist::Wordlist(const Wordlist& other){
	root = copySubtree(other.root);
}

// Assignment operator for Wordlist
Wordlist& Wordlist::operator=(const Wordlist& other) {
    if (this == &other) {
        return *this; 
    }

    deleteSubtree(root);

    root = copySubtree(other.root);

    return *this;
}

// Public method to insert a word into the AVL tree
void Wordlist::insert(const string& w) {
    root = insertNode(root, w);
}

// Helper function to insert a word into a subtree
AVLTreeNode* Wordlist::insertNode(AVLTreeNode* node, const string& w){
	if (node == nullptr) {
        ++size; // Increment the size of the tree
        return new AVLTreeNode(w); // Create a new node if position is found
    }

    if (w < node->word) {
        // Insert into the left subtree
        AVLTreeNode* leftChild = insertNode(node->left, w);
        node->left = leftChild;
        leftChild->parent = node;
    } else if (w > node->word) {
        // Insert into the right subtree
        AVLTreeNode* rightChild = insertNode(node->right, w);
        node->right = rightChild;
        rightChild->parent = node;
    } else {
        // Word already exists, increment its count
        node->wordCount++;
        return node;
    }

	node->height = 1 + std::max(height(node->left), height(node->right));
	int balance = getBalance(node);

	if(balance > 1 && w < node->left->word){
		return rotateRight(node);
	}

	if(balance < -1 && w > node->right->word){
		return rotateLeft(node);
	}

	if(balance > 1 && w > node->left->word){
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}

	if (balance < -1 && w < node->right->word) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

	return node;


}

// Returns the height of a node
int Wordlist::height(AVLTreeNode* node) const {
	if(node == nullptr){
		return 0;
	}
	return node->height;

}

// Calculates the balance factor of a node
int Wordlist::getBalance(AVLTreeNode* node) const {
	if(node ==  nullptr){
		return 0;
	}
	else{
		return height(node->left)-height(node->right);
	}
	
}

// Performs a left rotation on the subtree rooted at the given node
AVLTreeNode* Wordlist::rotateLeft(AVLTreeNode* node) {
    AVLTreeNode* newRoot = node->right; // New root will be the right child
    AVLTreeNode* subtree = newRoot->left; // Left subtree of the new root

    newRoot->left = node; // Move current node under the new root
    node->right = subtree; // Update the right child of the old root

    // Update parent pointers
    if (subtree) subtree->parent = node;
    newRoot->parent = node->parent;
    node->parent = newRoot;

    // Update the root if necessary
    if (newRoot->parent) {
        if (newRoot->parent->left == node) {
            newRoot->parent->left = newRoot;
        } else {
            newRoot->parent->right = newRoot;
        }
    } else {
        root = newRoot;
    }

    // Update heights
    node->height = 1 + std::max(height(node->left), height(node->right));
    newRoot->height = 1 + std::max(height(newRoot->left), height(newRoot->right));

    return newRoot; // Return the new root
}

// Performs a right rotation on the subtree rooted at the given node
AVLTreeNode* Wordlist::rotateRight(AVLTreeNode* node) {
    AVLTreeNode* newRoot = node->left; // New root will be the left child
    AVLTreeNode* subtree = newRoot->right; // Right subtree of the new root

    newRoot->right = node; // Move current node under the new root
    node->left = subtree; // Update the left child of the old root

    // Update parent pointers
    if (subtree) subtree->parent = node;
    newRoot->parent = node->parent;
    node->parent = newRoot;

    // Update the root if necessary
    if (newRoot->parent) {
        if (newRoot->parent->left == node) {
            newRoot->parent->left = newRoot;
        } else {
            newRoot->parent->right = newRoot;
        }
    } else {
        root = newRoot;
    }

    // Update heights
    node->height = 1 + std::max(height(node->left), height(node->right));
    newRoot->height = 1 + std::max(height(newRoot->left), height(newRoot->right));

    return newRoot; // Return the new root
}

// Removes a word from the AVL tree
bool Wordlist::remove(const string& w){
	bool wordfound = false;	
	root = removeWord(root, w, wordfound);
	return wordfound;
}

// Helper function to remove a word from the subtree
AVLTreeNode* Wordlist::removeWord(AVLTreeNode* node, const string& w, bool& wordFound) {
    if (!node) return nullptr; // Base case: null node

    if (w < node->word) {
        node->left = removeWord(node->left, w, wordFound); // Search in left subtree
    } else if (w > node->word) {
        node->right = removeWord(node->right, w, wordFound); // Search in right subtree
    } else {
        wordFound = true; // Word found

        // Case 1: Node has one or no child
        if (!node->left || !node->right) {
            AVLTreeNode* temp = node->left ? node->left : node->right;
            if (temp) temp->parent = node->parent; // Update parent pointer
            delete node; // Free memory
            --size;
            return temp;
        }

        // Case 2: Node has two children
        AVLTreeNode* temp = findSuccessor(node->right); // Find successor
        node->word = temp->word; // Copy the successor's data
        node->wordCount = temp->wordCount;
        node->right = removeWord(node->right, temp->word, wordFound); // Remove the successor
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Finds the successor of a node (smallest value in the right subtree)
AVLTreeNode* Wordlist::findSuccessor(AVLTreeNode* node) const {
    if (!node) return nullptr;
    while (node->left) {
        node = node->left;
    }
    return node;
}


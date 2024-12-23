# Wordlist Class - AVL Tree-Based Word Frequency Counter

This project implements a **Wordlist** class that uses an **AVL Tree** as its underlying data structure. The class counts word frequencies from a file and provides useful statistics, such as the total number of words, most frequent words, and singletons. It is designed to demonstrate efficient data handling using self-balancing binary search trees.

---

## Features

### AVL Tree Implementation
1. **Self-Balancing**:
   - Ensures \(O(\log n)\) time complexity for insertions, deletions, and lookups.
   - Uses rotations to maintain balance after each modification.

2. **Custom AVL Tree Node**:
   - Each node stores:
     - `word`: The string being tracked.
     - `wordCount`: The frequency of the word.
     - `height`: Height of the node in the tree.
     - Pointers to its parent, left child, and right child.

### Wordlist Class
1. **File Input**:
   - Reads words directly from a text file and inserts them into the AVL tree.

2. **Statistics**:
   - **Number of Different Words**: Counts unique words in the file.
   - **Total Word Count**: Sum of all word frequencies.
   - **Most Frequent Word**: Finds the word with the highest frequency.
   - **Singletons**: Counts words that appear only once, along with the percentage of singletons.

3. **Operations**:
   - Insert words into the tree, maintaining AVL balance.
   - Remove words from the tree while ensuring AVL properties.
   - Check if a word exists in the tree.
   - Retrieve the frequency of any given word.

4. **Output**:
   - Print statistics and word frequencies in sorted order.

---

## Code Overview

### **Wordlist.h**
Defines the `Wordlist` class and `AVLTreeNode` struct. Key components include:
- AVL Tree node structure with attributes for word, frequency, height, and pointers.
- Helper methods for rotations, balancing, and recursive tree operations.
- Public methods for word insertion, removal, statistics, and printing.

### **Wordlist.cpp**
Implements all methods defined in `Wordlist.h`. Key highlights:
- **Insert**: Adds a word to the AVL tree or increments its frequency.
- **Remove**: Deletes a word while maintaining tree balance.
- **Statistics**:
  - Uses recursive helpers to count nodes, words, and singletons.
  - Finds the most frequent word using an in-order traversal.
- **Printing**:
  - Outputs words in ascending order with their frequencies.
  - Displays statistics, including singleton percentage.

---

## How to Use

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/wordlist-avl.git
   cd wordlist-avl

/* Unit-II Trees: Binary Tree, Binary Search Tree, Height Balanced Trees: AVL/RB Tree, 2-3Trees, B
 and B+ Trees, Splay Trees, Heaps, Priority Queues, Mergeable heaps, Tries, Prefix and Suffix Trees,
Skip Lists; operations, their analysis, applications to searching */

#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

/////////////////////
// Binary Search Tree
/////////////////////
struct BSTNode {
    int key;
    BSTNode *left, *right;
    BSTNode(int k) : key(k), left(NULL), right(NULL) {}
};

class BST {
public:
    BSTNode* insert(BSTNode* root, int key) {
        if (!root) return new BSTNode(key);
        if (key < root->key)
            root->left = insert(root->left, key);
        else
            root->right = insert(root->right, key);
        return root;
    }

    BSTNode* search(BSTNode* root, int key) {
        if (!root || root->key == key) return root;
        if (key < root->key) return search(root->left, key);
        return search(root->right, key);
    }
};

/////////////////////
// AVL Tree
/////////////////////
struct AVLNode {
    int key, height;
    AVLNode *left, *right;
    AVLNode(int k) : key(k), height(1), left(NULL), right(NULL) {}
};

class AVLTree {
    int height(AVLNode* n) {
        return n ? n->height : 0;
    }

    int balance(AVLNode* n) {
        return height(n->left) - height(n->right);
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        y->left = x->right;
        x->right = y;
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        x->right = y->left;
        y->left = x;
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));
        return y;
    }

public:
    AVLNode* insert(AVLNode* root, int key) {
        if (!root) return new AVLNode(key);
        if (key < root->key) root->left = insert(root->left, key);
        else root->right = insert(root->right, key);

        root->height = 1 + max(height(root->left), height(root->right));
        int bal = balance(root);

        if (bal > 1 && key < root->left->key) return rightRotate(root);
        if (bal < -1 && key > root->right->key) return leftRotate(root);
        if (bal > 1 && key > root->left->key) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (bal < -1 && key < root->right->key) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }
};

/////////////////////
// Red-Black Tree (uses STL map for simplicity)
/////////////////////
class RBTree {
    map<int, bool> tree;
public:
    void insert(int key) {
        tree[key] = true;
    }

    bool search(int key) {
        return tree.find(key) != tree.end();
    }
};

/////////////////////
// B-Tree Node (Simplified)
/////////////////////
class BTreeNode {
public:
    vector<int> keys;
    vector<BTreeNode*> children;
    bool leaf;

    BTreeNode(bool leaf = true) : leaf(leaf) {}

    void insert(int key) {
        keys.push_back(key);  // Simplified: no splitting
    }
};

/////////////////////
// Trie
/////////////////////
class TrieNode {
public:
    TrieNode* children[26];
    bool isEnd;
    TrieNode() {
        isEnd = false;
        for (auto& c : children) c = NULL;
    }
};

class Trie {
public:
    TrieNode* root;
    Trie() { root = new TrieNode(); }

    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int i = c - 'a';
            if (!node->children[i]) node->children[i] = new TrieNode();
            node = node->children[i];
        }
        node->isEnd = true;
    }

    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int i = c - 'a';
            if (!node->children[i]) return false;
            node = node->children[i];
        }
        return node->isEnd;
    }
};

/////////////////////
// Min Heap (Priority Queue)
/////////////////////
class MinHeap {
    vector<int> heap;

    void heapify_up(int i) {
        while (i != 0 && heap[(i - 1)/2] > heap[i]) {
            swap(heap[i], heap[(i - 1)/2]);
            i = (i - 1)/2;
        }
    }

public:
    void insert(int key) {
        heap.push_back(key);
        heapify_up(heap.size() - 1);
    }

    int extract_min() {
        if (heap.empty()) return -1;
        int min = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        make_heap(heap.begin(), heap.end(), greater<>());
        return min;
    }
};

/////////////////////
// Splay Tree (Search Only)
/////////////////////
class SplayTree {
public:
    BSTNode* rightRotate(BSTNode* x) {
        BSTNode* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    BSTNode* leftRotate(BSTNode* x) {
        BSTNode* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    BSTNode* splay(BSTNode* root, int key) {
        if (!root || root->key == key) return root;

        if (key < root->key) {
            if (!root->left) return root;
            if (key < root->left->key) {
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            } else if (key > root->left->key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right)
                    root->left = leftRotate(root->left);
            }
            return (root->left) ? rightRotate(root) : root;
        } else {
            if (!root->right) return root;
            if (key > root->right->key) {
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            } else if (key < root->right->key) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left)
                    root->right = rightRotate(root->right);
            }
            return (root->right) ? leftRotate(root) : root;
        }
    }
};

/////////////////////
// Main for Testing
/////////////////////
int main() {
    BST bst;
    BSTNode* bst_root = NULL;
    bst_root = bst.insert(bst_root, 10);
    bst.insert(bst_root, 5);
    bst.insert(bst_root, 20);
    cout << "BST Search 5: " << (bst.search(bst_root, 5) ? "Found" : "Not Found") << endl;

    AVLTree avl;
    AVLNode* avl_root = NULL;
    avl_root = avl.insert(avl_root, 30);
    avl.insert(avl_root, 20);
    avl.insert(avl_root, 10);
    cout << "AVL Root: " << avl_root->key << endl;

    RBTree rb;
    rb.insert(15);
    cout << "RBTree Search 15: " << (rb.search(15) ? "Found" : "Not Found") << endl;

    Trie trie;
    trie.insert("hello");
    cout << "Trie Search 'hello': " << (trie.search("hello") ? "Yes" : "No") << endl;

    MinHeap heap;
    heap.insert(10); heap.insert(2); heap.insert(15);
    cout << "Heap Min: " << heap.extract_min() << endl;

    SplayTree splay;
    BSTNode* splay_root = NULL;
    splay_root = bst.insert(splay_root, 50);
    splay_root = bst.insert(splay_root, 30);
    splay_root = splay.splay(splay_root, 30);
    cout << "Splay Root: " << splay_root->key << endl;

    return 0;
}



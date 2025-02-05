#include <iostream>
#include <stack>

using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data = 0) : data(data) {
        parent = left = right = nullptr;
        this->color = RED;
    }
};

class RBTree {
private:
    Node* root;
    Node* TNULL;

    inline void initializeNULLNode(Node* node, Node* parent) {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = BLACK;
    }

    inline void inOrderHelper(Node* node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

    inline Node* searchTreeHelper(Node* node, int key) {
        while (node != TNULL && key != node->data) {
            if (key < node->data) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return node;
    }

    inline void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    inline void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    inline void fixInsert(Node* k) {
        Node* u;
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) break;
        }
        root->color = BLACK;
    }

    void printHelper(Node* root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            } else {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = root->color ? "BLACK" : "RED";
            cout << root->data << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

public:
    RBTree() {
        TNULL = new Node();
        TNULL->color = BLACK;
        root = TNULL;
    }

    inline void insert(int key) {
        Node* node = new Node(key);
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED;

        Node* y = nullptr;
        Node* x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        fixInsert(node);
    }

    inline bool search(int key) {
        return searchTreeHelper(this->root, key) != TNULL;
    }

    inline void inOrder() {
        inOrderHelper(this->root);
    }

    void printTree() {
        if (root) {
            printHelper(this->root, "", true);
        }
    }
};


RBTree tree;
int main() {
    clock_t start = clock();
    for(int i = 1; i <= 1000000; i++) tree.insert(i);
    clock_t end = clock();
    // for(int i = 1; i <= 1000000; i++) tree.search(i);
    cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC * 1000<< " ms" << endl;
}

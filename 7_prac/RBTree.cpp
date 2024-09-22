#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node* parent;
    char color; // 'r' for red, 'b' for black

    Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr), color('r') {}
};

class RedBlackTree {
private:
    Node* NIL;

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != NIL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != NIL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node* k) {
        while (k->parent->color == 'r') {
            if (k->parent == k->parent->parent->right) {
                Node* u = k->parent->parent->left;
                if (u->color == 'r') {
                    u->color = 'b';
                    k->parent->color = 'b';
                    k->parent->parent->color = 'r';
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 'b';
                    k->parent->parent->color = 'r';
                    leftRotate(k->parent->parent);
                }
            } else {
                Node* u = k->parent->parent->right;
                if (u->color == 'r') {
                    u->color = 'b';
                    k->parent->color = 'b';
                    k->parent->parent->color = 'r';
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 'b';
                    k->parent->parent->color = 'r';
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 'b';
    }

public:
    RedBlackTree() : NIL(new Node(0)), root(NIL) {}

    void insert(int value) {
        Node* node = new Node(value);
        node->parent = nullptr;
        node->left = NIL;
        node->right = NIL;
        node->color = 'r';

        Node* y = nullptr;
        Node* x = root;

        while (x != NIL) {
            y = x;
            if (node->value < x->value) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->value < y->value) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = 'b';
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        fixInsert(node);
    }

    void inorder(Node* node) {
        if (node != NIL) {
            inorder(node->left);
            std::cout << node->value << " ";
            inorder(node->right);
        }
    }

    void breadthFirst(Node* node) {
        std::queue<Node*> queue;
        queue.push(node);
        while (!queue.empty()) {
            node = queue.front();
            queue.pop();
            std::cout << node->value << " ";
            if (node->left != NIL) {
                queue.push(node->left);
            }
            if (node->right != NIL) {
                queue.push(node->right);
            }
        }
    }

    double average(Node* node, int& count, double& total) {
        if (node != NIL) {
            total += node->value;
            count++;
            average(node->left, count, total);
            average(node->right, count, total);
        }
    }

    int pathLength(Node* node, int value, int length) {
        if (node == NIL) {
            return -1;
        }
        if (node->value == value) {
            return length;
        }
        if (value < node->value) {
            return pathLength(node->left, value, length + 1);
        } else {
            return pathLength(node->right, value, length + 1);
        }
    }

    void printTree(Node* node, int indent = 0) {
        if (node != NIL) {
            for (int i = 0; i < indent; i++) {
                std::cout << " ";
            }
            std::cout << node->value << " (" << (node->color == 'r' ? "R" : "B") << ")" << std::endl;
            printTree(node->left, indent + 4);
            printTree(node->right, indent + 4);
        }
    }

    void run() {
        while (true) {
            std::cout << "\nMenu:" << std::endl;
            std::cout << "1. Insert value" << std::endl;
            std::cout << "2. Symmetric traversal" << std::endl;
            std::cout << "3. Breadth-first traversal" << std::endl;
            std::cout << "4. Calculate average" << std::endl;
            std::cout << "5. Calculate path length" << std::endl;
            std::cout << "6. Exit" << std::endl;
            std::cout << "7. Print tree" << std::endl;
            int choice;
            std::cin >> choice;
            switch (choice) {
                case 1: {
                    int value;
                    std::cout << "Enter value: ";
                    std::cin >> value;
                    insert(value);
                    break;
                }
                case 2: {
                    std::cout << "Symmetric traversal: ";
                    inorder(root);
                    std::cout << std::endl;
                    break;
                }
                case 3: {
                    std::cout << "Breadth-first traversal: ";
                    breadthFirst(root);
                    std::cout << std::endl;
                    break;
                }
                case 4: {
                    int count = 0;
                    double total = 0;
                    average(root, count, total);
                    std::cout << "Average: " << total / count << std::endl;
                    break;
                }
                case 5: {
                    int value;
                    std::cout << "Enter value: ";
                    std::cin >> value;
                    int length = pathLength(root, value, 0);
                    if (length == -1) {
                        std::cout << "Value not found" << std::endl;
                    } else {
                        std::cout << "Path length: " << length << std::endl;
                    }
                    break;
                }
                case 6:
                    return;
                case 7:
                    printTree(root);
                default:
                    std::cout << "Invalid choice" << std::endl;
                    break;
            }
        }
    }

    Node* root;
};


int main() {
    RedBlackTree tree;
    tree.insert(8);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(6);
    tree.insert(14);
    tree.insert(4);
    tree.insert(7);
    tree.insert(13);
    tree.insert(2);
    tree.insert(5);
    tree.printTree(tree.root);

    tree.run();

    return 0;
}

#include <iostream>
#include <queue>

using namespace std;

// Структура для представления узла дерева
struct Node {
    int value; // значение узла
    Node* left; // левый дочерний узел
    Node* right; // правый дочерний узел
    Node* parent; // родительский узел
    char color; // цвет узла ('r' для красного, 'b' для черного)

    // Конструктор узла
    Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr), color('r') {}
};

// Класс для представления красно-черного дерева
class RedBlackTree {
private:
    Node* NIL; // особый узел, представляющий конец дерева

    // Функция для левого поворота
    void leftRotate(Node* x) {
        // Узел y - правый дочерний узел x
        Node* y = x->right;
        x->right = y->left;
        if (y->left != NIL) {
            // Установка родительского узла для левого дочернего узла y
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            // Если x - корень дерева, то y становится новым корнем
            root = y;
        } else if (x == x->parent->left) {
            // Если x - левый дочерний узел своего родителя, то y становится левым дочерним узлом
            x->parent->left = y;
        } else {
            // Если x - правый дочерний узел своего родителя, то y становится правым дочерним узлом
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // Функция для правого поворота
    void rightRotate(Node* x) {
        // Узел y - левый дочерний узел x
        Node* y = x->left;
        x->left = y->right;
        if (y->right != NIL) {
            // Установка родительского узла для правого дочернего узла y
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            // Если x - корень дерева, то y становится новым корнем
            root = y;
        } else if (x == x->parent->right) {
            // Если x - правый дочерний узел своего родителя, то y становится правым дочерним узлом
            x->parent->right = y;
        } else {
            // Если x - левый дочерний узел своего родителя, то y становится левым дочерним узлом
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Функция для восстановления баланса дерева после вставки узла
    void fixInsert(Node* k) {
        // Пока родительский узел k - красный
        while (k->parent->color == 'r') {
            // Если родительский узел k - правый дочерний узел своего родителя
            if (k->parent == k->parent->parent->right) {
                // Узел u - левый дочерний узел родителя родителя k
                Node* u = k->parent->parent->left;
                if (u->color == 'r') {
                    // Если u - красный, то перекрашиваем u и родителя k в черный, а родителя родителя k в красный
                    u->color = 'b';
                    k->parent->color = 'b';
                    k->parent->parent->color = 'r';
                    k = k->parent->parent;
                } else {
                    // Если u - черный, то производим правый поворот в k
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 'b';
                    k->parent->parent->color = 'r';
                    leftRotate(k->parent->parent);
                }
            } else {
                // Если родительский узел k - левый дочерний узел своего родителя
                Node* u = k->parent->parent->right;
                if (u->color == 'r') {
                    // Если u - красный, то перекрашиваем u и родителя k в черный, а родителя родителя k в красный
                    u->color = 'b';
                    k->parent->color = 'b';
                    k->parent->parent->color = 'r';
                    k = k->parent->parent;
                } else {
                    // Если u - черный, то производим левый поворот в k
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
        // Корень дерева всегда черный
        root->color = 'b';
    }

public:
    // Конструктор дерева
    RedBlackTree() : NIL(new Node(0)), root(NIL) {}

    // Функция для вставки узла в дерево
    void insert(int value) {
        // Создание нового узла
        Node* node = new Node(value);
        node->parent = nullptr;
        node->left = NIL;
        node->right = NIL;
        node->color = 'r';

        // Поиск места для вставки узла
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

        // Вставка узла
        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->value < y->value) {
            y->left = node;
        } else {
            y->right = node;
        }

        // Если родительский узел нового узла - корень дерева, то новый узел становится корнем
        if (node->parent == nullptr) {
            node->color = 'b';
            return;
        }

        // Если родительский узел нового узла - левый или правый дочерний узел своего родителя, то вызываем функцию восстановления баланса
        if (node->parent->parent == nullptr) {
            return;
        }

        fixInsert(node);
    }

    // Функция для симметричного обхода дерева
    void inorder(Node* node) {
        // Если узел не пустой, то обходим его левое поддерево, печатаем значение узла и обходим его правое поддерево
        if (node != NIL) {
            inorder(node->left);
            std::cout << node->value << " ";
            inorder(node->right);
        }
    }

    // Функция для обхода дерева в ширину
    void breadthFirst(Node* node) {
        // Создание очереди для хранения узлов
        std::queue<Node*> queue;
        queue.push(node);
        while (!queue.empty()) {
            // Извлечение узла из очереди и печать его значения
            node = queue.front();
            queue.pop();
            std::cout << node->value << " ";
            // Добавление левого и правого дочерних узлов в очередь
            if (node->left != NIL) {
                queue.push(node->left);
            }
            if (node->right != NIL) {
                queue.push(node->right);
            }
        }
    }

    // Функция для вычисления среднего значения узлов дерева
    double average(Node* node, int& count, double& total) {
        // Если узел не пустой, то добавляем его значение к общей сумме и увеличиваем счетчик узлов
        if (node != NIL) {
            total += node->value;
            count++;
            average(node->left, count, total);
            average(node->right, count, total);
        }
    }

    // Функция для вычисления длины пути до узла
    int pathLength(Node* node, int value, int length) {
        // Если узел пустой, то возвращаем -1
        if (node == NIL) {
            return -1;
        }
        // Если значение узла совпадает с искомым значением, то возвращаем длину пути
        if (node->value == value) {
            return length;
        }
        // Если искомое значение меньше значения узла, то ищем его в левом поддереве
        if (value < node->value) {
            return pathLength(node->left, value, length + 1);
        }
        // Если искомое значение больше значения узла, то ищем его в правом поддереве
        else {
            return pathLength(node->right, value, length + 1);
        }
    }

    // Функция для печати дерева
    void printTree(Node* node, int indent = 0) {
        // Если узел не пустой, то печатаем его значение и рекурсивно печатаем его левое и правое поддеревья
        if (node != NIL) {
            for (int i = 0; i < indent; i++) {
                std::cout << " ";
            }
            std::cout << node->value << " (" << (node->color == 'r' ? "R" : "B") << ")" << std::endl;
            printTree(node->left, indent + 4);
            printTree(node->right, indent + 4);
        }
    }

    // Функция для запуска интерактивного режима
    void run() {
        while (true) {
            // Печать меню
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

// Основная функция
int main() {
    // Создание дерева
    RedBlackTree tree;
    // Вставка узлов в дерево
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
    // Печать дерева
    tree.printTree(tree.root);

    // Запуск интерактивного режима
    tree.run();

    return 0;
}

// Программа на C++ для печати эйлерова пути в заданном эйлеровом или полуэйлеровом графе
#include <algorithm>
#include <iostream>
#include <list>
#include <string.h>
using namespace std;

// Класс, представляющий неориентированный граф
class Graph {
    int V; // Количество вершин
    list<int>* adj; // Динамический массив списков смежности
public:
    // Конструктор и деструктор
    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    }
    ~Graph() { delete[] adj; }

    // Функции для добавления и удаления ребер
    void addEdge(int u, int v)
    {
        // Добавляем ребро между вершинами u и v
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void rmvEdge(int u, int v);

    // Методы для печати эйлерова пути
    void printEulerTour();
    void printEulerUtil(int s);

    // Функция, возвращающая количество достижимых вершин из v. Использует DFS
    int DFSCount(int v, bool visited[]);

    // Вспомогательная функция для проверки, является ли ребро u-v допустимым следующим ребром в эйлеровом пути или контуре
    bool isValidNextEdge(int u, int v);
};

/* Основная функция, печатающая эйлеров путь. Сначала она находит вершину с нечетной степенью (если такая есть), а затем вызывает printEulerUtil() для печати пути */
void Graph::printEulerTour()
{
    // Находим вершину с нечетной степенью
    int u = 0;
    for (int i = 0; i < V; i++)
        if (adj[i].size() & 1) {
            u = i;
            break;
        }

    // Печатаем путь, начиная с вершины с нечетной степенью
    printEulerUtil(u);
    cout << endl;
}

// Печатаем эйлеров путь, начиная с вершины u
void Graph::printEulerUtil(int u)
{
    // Рекурсивно обходим все вершины, смежные с этой вершиной
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i;

        // Если ребро u-v не удалено и оно является допустимым следующим ребром
        if (v != -1 && isValidNextEdge(u, v)) {
            cout << u << "-" << v << " ";
            rmvEdge(u, v);
            printEulerUtil(v);
        }
    }
}

// Функция для проверки, является ли ребро u-v допустимым следующим ребром в эйлеровом пути или контуре
bool Graph::isValidNextEdge(int u, int v)
{
    // Ребро u-v является допустимым в одном из следующих двух случаев:

    // 1) Если v является единственной смежной вершиной u
    int count = 0; // Для хранения количества смежных вершин
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
        if (*i != -1)
            count++;
    if (count == 1)
        return true;

    // 2) Если есть несколько смежных вершин, то u-v не является мостом. Выполняем следующие шаги для проверки, является ли u-v мостом

    // 2.a) Количество достижимых вершин из u
    bool visited[V];
    memset(visited, false, V);
    int count1 = DFSCount(u, visited);

    // 2.b) Удаляем ребро (u, v) и после удаления ребра считаем количество достижимых вершин из u
    rmvEdge(u, v);
    memset(visited, false, V);
    int count2 = DFSCount(u, visited);

    // 2.c) Добавляем ребро обратно в граф
    addEdge(u, v);

    // 2.d) Если count1 больше, то ребро (u, v) является мостом
    return (count1 > count2) ? false : true;
}

// Функция для удаления ребра u-v из графа. Удаляет ребро, заменяя значение смежной вершины на -1.
void Graph::rmvEdge(int u, int v)
{
    // Находим v в списке смежности u и заменяем его на -1
    list<int>::iterator iv
            = find(adj[u].begin(), adj[u].end(), v);
    *iv = -1;

    // Находим u в списке смежности v и заменяем его на -1
    list<int>::iterator iu
            = find(adj[v].begin(), adj[v].end(), u);
    *iu = -1;
}

// DFS-реализация для подсчета достижимых вершин из v
int Graph::DFSCount(int v, bool visited[])
{
    // Помечаем текущую вершину как посещенную
    visited[v] = true;
    int count = 1;

    // Рекурсивно обходим все вершины, смежные с этой вершиной
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (*i != -1 && !visited[*i])
            count += DFSCount(*i, visited);

    return count;
}

// Основная функция для тестирования вышеуказанных функций
int main()
{
    // Сначала создаем и тестируем графы, показанные на диаграмме выше
    Graph g1(10);
    g1.addEdge(0, 1);
    g1.addEdge(0, 3);
    g1.addEdge(1, 2);
    g1.addEdge(1, 3);
    g1.addEdge(1, 8);
    g1.addEdge(2, 8);
    g1.addEdge(2, 9);
    g1.addEdge(3, 4);
    g1.addEdge(3, 6);
    g1.addEdge(4, 6);
    g1.addEdge(5, 6);
    g1.addEdge(5, 7);
    g1.addEdge(6, 7);
    g1.addEdge(7, 8);
    g1.addEdge(7, 9);
    g1.addEdge(8, 9);
    g1.printEulerTour();

    return 0;
}

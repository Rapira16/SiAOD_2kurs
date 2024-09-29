// Программа на C++ для обхода графа в ширину (BFS)
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Функция для обхода графа в ширину, начиная с вершины s
void bfs(vector<vector<int>>& adj, int s)
{
    // Создаем очередь для обхода графа в ширину
    queue<int> q;

    // Изначально помечаем все вершины как не посещенные
    // Когда мы добавляем вершину в очередь, мы помечаем ее как посещенную
    vector<bool> visited(adj.size(), false);

    // Помечаем стартовую вершину как посещенную и добавляем ее в очередь
    visited[s] = true;
    q.push(s);

    // Итерируемся по очереди
    while (!q.empty()) {

        // Извлекаем вершину из очереди и печатаем ее
        int curr = q.front();
        q.pop();
        cout << curr << " ";

        // Получаем все смежные вершины извлеченной вершины curr
        // Если смежная вершина еще не посещена, помечаем ее как посещенную и добавляем ее в очередь
        for (int x : adj[curr]) {
            if (!visited[x]) {
                visited[x] = true;
                q.push(x);
            }
        }
    }
}

// Функция для добавления ребра в граф
void addEdge(vector<vector<int>>& adj,
             int u, int v)
{
    // Добавляем ребро между вершинами u и v
    adj[u].push_back(v);
    adj[v].push_back(u); // Неориентированный граф
}

int main()
{
    // Количество вершин в графе
    int V = 10;

    // Представление графа в виде списка смежности
    vector<vector<int>> adj(V);

    // Добавляем ребра в граф
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 3);
    addEdge(adj, 1, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 8);
    addEdge(adj, 2, 8);
    addEdge(adj, 2, 9);
    addEdge(adj, 3, 4);
    addEdge(adj, 3, 6);
    addEdge(adj, 4, 6);
    addEdge(adj, 5, 6);
    addEdge(adj, 5, 7);
    addEdge(adj, 6, 7);
    addEdge(adj, 7, 8);
    addEdge(adj, 7, 9);
    addEdge(adj, 8, 9);

    // Выполняем обход графа в ширину, начиная с вершины 0
    cout << "BFS starting from 0 : \n";
    bfs(adj, 0);

    return 0;
}

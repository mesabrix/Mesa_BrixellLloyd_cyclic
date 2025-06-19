#include <iostream>
using namespace std;

const int MAX = 100;
int graph[MAX][MAX];
int parent[MAX];
int nodes;

int find(int x) {
    while (parent[x] != -1) {
        x = parent[x];
    }
    return x;
}

bool makeUnion(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    if (rootA == rootB) {
        return false;
    }
    parent[rootA] = rootB;
    return true;
}

int getInput(int row, int col) {
    int value;
    while (true) {
        cout << "Enter 0 or 1 for [" << row << "][" << col << "]: ";
        cin >> value;
        if (cin.fail() || (value != 0 && value != 1)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again.\n";
        } else {
            return value;
        }
    }
}

int main() {
    cout << "Enter number of nodes: ";
    while (!(cin >> nodes) || nodes <= 0 || nodes > MAX) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Enter number between 1 and " << MAX << ": ";
    }

    cout << "\nEnter the adjacency matrix:\n";
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            graph[i][j] = getInput(i, j);
        }
    }

    for (int i = 0; i < nodes; i++) {
        parent[i] = -1;
    }

    bool hasCycle = false;
    int from = -1, to = -1;

    for (int i = 0; i < nodes; i++) {
        for (int j = i + 1; j < nodes; j++) {
            if (graph[i][j]) {
                if (!makeUnion(i, j)) {
                    hasCycle = true;
                    from = i;
                    to = j;
                    break;
                }
            }
        }
        if (hasCycle) break;
    }

    cout << "\n--- BFS (Union-Find) Result ---\n";
    if (hasCycle) {
        cout << "Cycle found between nodes " << from << " and " << to << ".\n";
    } else {
        cout << "No cycle found using BFS.\n";
    }

    return 0;
}

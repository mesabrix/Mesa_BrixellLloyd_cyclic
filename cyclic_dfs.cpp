#include <iostream>
using namespace std;

const int MAX = 100;
int graph[MAX][MAX];
int visited[MAX];
int nodes;

bool dfs(int current, int parent, int &start, int &end) {
    visited[current] = 1;
    for (int next = 0; next < nodes; next++) {
        if (graph[current][next]) {
            if (!visited[next]) {
                if (dfs(next, current, start, end)) {
                    return true;
                }
            } else if (next != parent) {
                start = current;
                end = next;
                return true;
            }
        }
    }
    return false;
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
        visited[i] = 0;
    }

    bool hasCycle = false;
    int from = -1, to = -1;

    for (int i = 0; i < nodes; i++) {
        if (!visited[i]) {
            if (dfs(i, -1, from, to)) {
                hasCycle = true;
                break;
            }
        }
    }

    cout << "\n--- DFS Result ---\n";
    if (hasCycle) {
        cout << "Cycle found between nodes " << from << " and " << to << ".\n";
    } else {
        cout << "No cycle found using DFS.\n";
    }

    return 0;
}

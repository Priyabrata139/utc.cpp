#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int state;
    int cost;

    Node(int s, int c) : state(s), cost(c) {}

    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

int uniformCostSearch(const vector<vector<pair<int, int>>>& graph, int start, int goal) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    vector<bool> visited(graph.size(), false);

    pq.push(Node(start, 0));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.state == goal) {
            return current.cost;
        }

        if (!visited[current.state]) {
            visited[current.state] = true;

            for (const auto& neighbor : graph[current.state]) {
                int nextState = neighbor.first;
                int costToNext = neighbor.second;

                if (!visited[nextState]) {
                    pq.push(Node(nextState, current.cost + costToNext));
                }
            }
        }
    }

    return -1;
}

int main() {
    vector<vector<pair<int, int>>> graph = {
        {{1, 4}, {2, 2}},
        {{3, 5}},
        {{3, 1}},
        {}
    };

    int startNode = 0;
    int goalNode = 3;

    int result = uniformCostSearch(graph, startNode, goalNode);

    if (result != -1) {
        cout << "Cost from node " << startNode << " to node " << goalNode << ": " << result << endl;
    } else {
        cout << "Goal node is not reachable from the start node." << endl;
    }

    return 0;
}

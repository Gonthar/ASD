#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

const int MAX_PROJECTS = 500000;

int main() {
    std::ios_base::sync_with_stdio(0);
    std::vector<int> neighbours[MAX_PROJECTS];
    int manpower[MAX_PROJECTS];
    int indegree[MAX_PROJECTS];
    std::priority_queue< std::pair < int, int > > project_queue;
    int projects = 0, dependencies = 0, goal = 0, x = 0, y = 0, answer = 0;

    std::cin >> projects >> dependencies >> goal;

    // weight list
    for (int i = 1; i <= projects; ++i) {
        std::cin >> manpower[i];
        indegree[i] = 0; //
    }

    // neighbour list
    for (int j = 0; j < dependencies; ++j) {
        std::cin >> x >> y;
        neighbours[y].emplace_back(x);
        indegree[x]++;
    }

    for (int k = 1; k <= projects; ++k) {
        if (!indegree[k]) { project_queue.push(std::make_pair(-manpower[k], k)); }
    }

    for (int l = 0; l < goal; ++l) {
        int tmp = project_queue.top().second;
        project_queue.pop();
        answer = std::max(answer, manpower[tmp]);
        int size = neighbours[tmp].size();
        for (int m = 0; m < size; ++m) {
            --indegree[neighbours[tmp][m]];
            if (!indegree[neighbours[tmp][m]]) {
                project_queue.push(std::make_pair(-manpower[neighbours[tmp][m]], neighbours[tmp][m]));
            }
        }
    }

    std::cout << answer << std::endl;
    return 0;
}
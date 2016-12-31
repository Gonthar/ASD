#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

const long MAX_ISLANDS = 200000;

typedef std::pair<long, long> Island;

long lazy_captain(long a, long b, std::vector<Island>& map) {
    long minx = 0, miny = 0;
    if (a == b ) return 0;
    minx = abs(map[a].first - map[b].first);
    miny = abs(map[a].second - map[b].second);
    return std::min(minx, miny);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n = 0;
    long a = 0, b = 0;
    std::vector<Island> map;
    std::cin >> n;
    long dist[n + 1][n + 1];
    map.emplace_back(0, 0); //island 0, so all the others will be numbered 1 to n
    for (int i = 1; i <= n; ++i) {
        std::cin >> a >> b;
        map.emplace_back(a, b);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dist[i][j] = lazy_captain(i, j, map);
        }
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    std::cout << dist[1][n] << std::endl;
    return 0;
}
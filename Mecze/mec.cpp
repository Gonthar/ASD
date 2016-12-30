#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(0);
    int n = 0; //players
    int m = 0; //games
    int currp = 0;
    std::cin >> n >> m;
    std::vector<std::string> db;
    for(int i = 0; i < n; i++) {
        db.push_back("");
    }
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n/2; j++) {
            std::cin >> currp;
            db[currp-1] += "0";
        }
        for(int j = 0; j < n/2; j++) {
            std::cin >> currp;
            db[currp-1] += "1";
        }
    }
    std::sort(db.begin(), db.end());
    db.erase(std::unique(db.begin(), db.end()), db.end());
    assert(db.size() <= (unsigned)n);
    if(db.size() == (unsigned)n) {
        std::cout << "TAK" << std::endl;
    } else {
        std::cout << "NIE" << std::endl;
    }
    return 0;
}
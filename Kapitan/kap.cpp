#include <iostream>

const long MAX_ISLANDS = 200000;

typedef std::pair<long, long> Island;

long lazy_captain(long a, long b) {
    return (a < b) ? a : b;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    long a = 44;
    long b = 5;
    std::cout << lazy_captain(a, b) << std::endl;
    return 0;
}
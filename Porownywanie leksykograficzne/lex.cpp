#include <iostream>
#include <string>
#include <vector>
#include <math.h>

const int MAX = 300000;
const int P = 147;
const long long Q = 236887699;

int count_hash(int l, int r, std::vector<long long> &hash, std::vector<long long> &pow) {
    if (l == 0) {
        return hash[r];
    }
    return (Q + (hash[r] - hash[l - 1] * pow[r - l + 1]) % Q) % Q;
}

char query(int a, int b, int c, int d, std::vector<long long> &hash, std::vector<long long> &pow, char str[]) {
    long long hasha, hashc;
    int qlength = std::min(b - a, d - c);
    int l = 0, r = qlength, half = 0, diff = 0;
    while (l <= r) {
        half = (l + r) / 2;
        hasha = count_hash(a, a + half, hash, pow);
        hashc = count_hash(c, c + half, hash, pow);
        if (hasha == hashc) {
            l = half + 1;
            diff = half + 1;
        } else {
            r = half - 1;
        }
    }
    if (diff == qlength + 1) {
        if (b - a == d - c) {
            return '=';
        }
        return b - a < d - c ? '<' : '>';
    }
    return str[a + diff] < str[c + diff] ? '<' : '>';
}

int main() {
    std::ios_base::sync_with_stdio(0);
    int a = 0, b = 0, c = 0, d = 0;
    int slength = 0, queries = 0;

    std::vector<long long> hash(MAX);
    std::vector<long long> pow(MAX);
    char str[MAX];

    std::cin >> slength >> queries >> str;

    for (int i = 0; i < slength; i++) {
        str[i] -= ('a' - 1);
    }
    pow[0] = 1;
    for (int i = 1; i < slength; i++) {
        pow[i] = pow[i - 1] * P % Q;
    }
    hash[0] = str[0];
    for (int i = 1; i < slength; i++) {
        hash[i] = (hash[i - 1] * P + str[i]) % Q;
    }

    for (int i = 0; i < queries; ++i) {
        std::cin >> a >> b >> c >> d;
        --a; --b; --c; --d;
        std::cout << query(a, b, c, d, hash, pow, str) << std::endl;
    }
    return 0;
}
#include <iostream>
#include <vector>

void update(long x, unsigned long long val, long m, std::vector<unsigned long long>& db) {
    long v = m + x;
    db[v] += val;
    while(v != 1) {
        v /= 2;
        db[v] = db[2 * v] + db[2 * v + 1];
    }
}

long long query(long low, long high, long half, std::vector<unsigned long long>& db) {
    long vl = half + low;
    long vh = half + high;
    unsigned long long res = db[vl];
    if(vl != vh) {
        res += db[vh] % 1000000000;
    }
    while(vl / 2 != vh / 2) {
        if(vl % 2 == 0) {
            res += db[vl + 1] % 1000000000;
        }
        if(vh % 2 == 1) {
            res += db[vh - 1] % 1000000000;
        }
        vl = vl / 2;
        vh = vh / 2;
    }
    return res % 1000000000;
}

long findTreeLength(long n) {
    long res = 1;
    while(res < n) {
        res *= 2;
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    long n = 0; //permutation length
    long k = 0; //length of k-inversion
    long m = 0;
    long tmp = 0;
    unsigned long long tmp2 = 0;
    unsigned long long answer = 0;
    std::cin >> n >> k;
    m = findTreeLength(n);
    std::vector<unsigned long long> db(m * 2);
    for (long i = 0; i < n; i++) {
        std::cin >> tmp;
        update(i, tmp, m, db);
    }
    std::vector<std::vector<unsigned long long> > inversions(k, std::vector<unsigned long long>(m * 2));

    for(long i = 0; i < n; i++) {
        tmp = db[i + m];
        update(tmp, 1, m, inversions[0]);
        for(long j = 1; j < k; j++) {
            if(tmp + 1 <= n) {
                tmp2 = query(tmp + 1, n, m, inversions[j - 1]) % 1000000000;
                update(tmp, tmp2, m, inversions[j]);
            }
        }
    }

    answer = inversions[k-1][1] % 1000000000;
    std::cout << answer << std::endl;
    return 0;
}
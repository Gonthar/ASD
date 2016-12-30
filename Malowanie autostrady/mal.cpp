#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_N 1000000

long n; //road length
long size; //structure size
long w[4 * MAX_N];
bool act[4 * MAX_N];

long findX(long n) {
    int tmp = n;
    while (tmp < size) tmp *= 2;
    return tmp - size;
}

long findY(long n) {
    int tmp = n;
    while (tmp < size) tmp = (tmp * 2 + 1);
    return tmp - size;
}

//zacząć od [a, b], 1
void push(long a, long b, long v) {
    long x, y;
    x = findX(v);
    y = findY(v);

    if (x >= a && y <= b) return;
    if (y < a || x > b) return;
    if (act[v] == true) {
        w[v * 2] = w[v] / 2;
        w[v * 2 + 1] = w[v] / 2;
        act[v * 2] = true;
        act[v * 2 + 1] = true;
        act[v] = false;
    }

    push(a, b, v * 2);
    push(a, b, v * 2 + 1);
}

long value(long v) {
    long x, y;
    x = findX(v);
    y = findY(v);
    return y - x + 1;
}

void insert(long a, long b, int v) {
    push(a, b, 1);
    long va = size + a, vb = size + b;
    w[va] = (v == 0) ? 0 : value(va);
    act[va] = true;
    if (a != b){
        w[vb] = w[va];
        act[vb] = true;
    }

    while (va != 1) {
        if (va / 2 != vb / 2) {
            if (va % 2 == 0) {
                w[va + 1] = (v == 0) ? 0 : value(va);
                act[va + 1] = true;
            }
            if (vb % 2 == 1) {
                w[vb - 1] = (v == 0) ? 0 : value(vb);
                act[vb - 1] = true;
            }
        }
        va /= 2; vb /= 2;
        w[va] = w[va * 2] + w[va * 2 + 1];
        w[vb] = w[vb * 2] + w[vb * 2 + 1];
    }
    w[1] = w[2] + w[3];
}

void update(long x, int val) {
    long v = size + x;
    w[v] = val;
    while(v != 1) {
        v /= 2;
        w[v] = w[2 * v] + w[2 * v + 1];
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

void findTreeLength() {
    size = 1;
    while(size < n) {
        size *= 2;
    }
}

int main() {
    std::ios_base::sync_with_stdio(0);
    long m = 0; //number of nights
    long a = 0, b = 0, c = 0;
    char ch;
    std::cin >> n >> m;
    findTreeLength();
    for (long i = m; i > 0; --i) {
        std::cin >> a >> b >> ch;
        c = (ch == 'C') ? 0 : 1;
        insert(a, b, c);
        std::cout << w[1] << std::endl;
    }
}
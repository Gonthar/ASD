#include <iostream>
#include <vector>
#include <climits>

long maximum(long a, long b, long c, long d, long e) {
    long max = a;
    if(b > max) {
        max = b;
    }
    if(c > max) {
        max = c;
    }
    if(d > max) {
        max = d;
    }
    if(e > max) {
        max = e;
    }
    return max;
}

long slowClimb(std::vector< std::vector <long> > &v, std::vector< std::vector< std::vector <long> > > &w,
               int depth, int x, int y, int forb, int n) {
    if(y < 0 || y >= n) {
        return -1;
    }
    if(depth == 0 || x == 0) {
        if(forb == y ) {
            return -1;
        } else {
            return w[x][forb][y];
        }
    } else {
        long a = 0, b = 0, c = 0, d = 0, e = 0;
        a = slowClimb(v, w, depth-1, x-1, y-2, forb, n);
        b = slowClimb(v, w, depth-1, x-1, y-1, forb, n);
        c = slowClimb(v, w, depth-1, x-1, y, forb, n);
        d = slowClimb(v, w, depth-1, x-1, y+1, forb, n);
        e = slowClimb(v, w, depth-1, x-1, y+2, forb, n);
        return (maximum(a, b, c, d, e) + v[x][y]);
    }
}

/*
 * Checks 10 possible previous locations for fast traveller
 */
long fastClimb(std::vector< std::vector <long> > &v, std::vector< std::vector< std::vector <long> > > &w,
               int row, int fast, int slow, int n) {
    long max = 0;
    int checked = 0;
    long tmp = 0;
    for(int j = 2; j <= 3; j++) {
        for (int i = 0; i < 3; i++) {
            checked = (fast - 1 + i);
            if(checked >= 0 && checked < n) {
                tmp = slowClimb(v, w, j, row, slow, checked, n);
                if(tmp > max) {
                    max = tmp;
                }
            }
        }
    }
    return max + v[row][fast];
}

int main() {
    std::ios_base::sync_with_stdio(0);
    int m = 0; //height
    int n = 0; //width
    long best = 0;
    std::cin >> m >> n;
    //input data, M x N
    std::vector< std::vector<long> > mountain(m, std::vector<long>(n));
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            std::cin >> mountain[i][j];
        }
    }
    //collection of best scores, format [row][pos of fast climber][pos of slow climber] M x N x N
    std::vector< std::vector < std::vector< long > > > climb(m, std::vector< std::vector<long> >(n, std::vector<long>(n)));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i != j) {
                climb[0][i][j] = mountain[0][i] + mountain [0][j];
            } else {
                climb[0][i][j] = LONG_MIN;
            }
            climb[1][i][j] = LONG_MIN;
        }
    }
    for(int k = 2; k < m; k++){
        for(int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(i != j){
                    climb[k][i][j] = fastClimb(mountain, climb, k, i, j, n);
                } else {
                    climb[k][i][j] = LONG_MIN;
                }
            }
        }
    }
    //find best score
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(climb[m-1][i][j] > best) {
                best = climb[m-1][i][j];
            }
        }
    }

    std::cout << best << std::endl;
    return 0;
}
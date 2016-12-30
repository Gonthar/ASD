#include <iostream>

const int MIL = 1000000000;

int main() {
    int n;
    std::cin >> n;
    int data[n];
    long answer;
    for(int i = 0; i < n; ++i) {
        std::cin >> data[i];
    }
    long **left;
    left = new long *[n];
    for(int i = 0; i < n; i++) {
        left[i] = new long[n];
    }
    long **right;
    right = new long *[n];
    for(int i = 0; i < n; i++) {
        right[i] = new long[n];
    }

    for(int i = 0; i < n; i++) {
        right[i][i] = 1;
        left[i][i] = 1;
    }
    for(int k = 0; k < n; k++) {
        for(int beg = 0, end = k+1; end < n; beg++, end++) {
            if(k == 0) {
                left[beg][end] = (data[beg] < data[end]) ? 1 : 0;
                right[beg][end] = (data[beg] < data[end]) ? 1 : 0;
            } else {
                left[beg][end] = ( ((data[beg] < data[beg+1])?(left[beg+1][end]):(0)) +
                                   ((data[beg] < data[end])?(right[beg+1][end]):(0))         )%MIL;

                right[beg][end] = ( ((data[end-1] < data[end])?(right[beg][end-1]):(0))    +
                                    ((data[beg] < data[end])?(left[beg][end-1]):(0))         )%MIL;
            }
        }
    }
    answer = (left[0][n-1] + right[0][n-1])%MIL;
    if(n == 1) {
        answer = 1;
    }
    std::cout << answer << std::endl;
    return 0;
}
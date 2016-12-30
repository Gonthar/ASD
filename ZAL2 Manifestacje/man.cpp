#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <iterator>
#include <set>

const long MANIFESTATIONS = 1000000;

struct Cmp {
    bool operator ()(const std::pair<long, long> &a, const std::pair<long, long> &b) {
        if (a.second == b.second) {
            return a.first < b.first;
        } else {
            return a.second > b.second;
        }
    }
};

std::set <std::pair<long, long>, Cmp> attendance; // format: mani_id, attendees
std::vector< std::tuple < long, long, bool > > input; //false for beg, true for end
std::vector< std::pair < long, long > > queries; //format: moment, order_asked
std::vector< std::tuple < long, long, long> > answers; //format: order_asked (unique), mani_id, attendance
std::vector< long > manif(MANIFESTATIONS + 1);

void erase_from_set(long a, long b) {
    attendance.erase(std::pair<long, long>(a, b));
}

void add_to_set(long a, long b) {
    attendance.insert(std::pair<long, long>(a, b));
}

void update_set (long man_id, bool b) {
    if (b) {
        erase_from_set(man_id, manif[man_id]);
        if (manif[man_id] != 1) {
            add_to_set(man_id, manif[man_id] - 1);
        }
        manif[man_id]--;
    } else {
        if (manif[man_id] != 0) {
            erase_from_set(man_id, manif[man_id]);
        }
        add_to_set(man_id, manif[man_id] + 1);
        manif[man_id]++;
    }
}

int main() {
    std::ios_base::sync_with_stdio(0);
    long p = 0, k = 0, r = 0, t = 0, j = 0, citizens = 0, moments = 0;
    std::cin >> citizens >> moments;
    for (long i = 1; i <= citizens; ++i) {
        std::cin >> p >> k >> r;
        input.emplace_back(p, r, false);
        input.emplace_back(k + 1, r, true);
    }
    std::sort(input.begin(), input.end());
    for (long i = 1; i <= moments; ++i) {
        std::cin >> t;
        queries.emplace_back(t, i);
    }
    std::sort(queries.begin(), queries.end());

    add_to_set(1, 0);
    for (long i = 0; i < moments; ++i) {
        long limit = queries[i].first;
        for (; std::get<0>(input[j]) <= limit; j++) { //&& input[j] != NULL
            if (std::get<2>(input[j])) {
                update_set(std::get<1>(input[j]), true); //--
            } else {
                update_set(std::get<1>(input[j]), false); //++
            }
        }
        std::pair<long, long> answer_tmp = *attendance.begin();
        answers.emplace_back(queries[i].second, answer_tmp.first, answer_tmp.second);
    }
    std::sort(answers.begin(), answers.end());

    for (const auto& i : answers) {
        std::cout << std::get<1>(i) << " " << std::get<2>(i) << std::endl;
    }
    return 0;
}

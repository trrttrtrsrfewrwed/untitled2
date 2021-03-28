#include <iostream>
#include <vector>
#include <algorithm>

class Solver {
public:
    explicit Solver(size_t n, size_t h, size_t q): n(n), h(h), q(q) {
    }

    int solve() {
        size_t query_answer = 0;

        for (size_t i = 0; i < n; ++i) {
            count_results.emplace_back(i, countQuery(i));
        }

        // сортируем элементы в убывающем порядке
        std::sort(count_results.begin(), count_results.end(), [](std::pair<size_t, size_t> sort_res1, std::pair<size_t, size_t> sort_res2) {
            return sort_res1.second < sort_res2.second;
        });

        size_t curr_size = h;

        for (size_t i = 0; i < n; ++i) {
            auto curr_count_result = count_results[i];

            if (i != 0) {
                // Если текущий город такого же размера, что и предыдущий, пропускаем его
                if (curr_count_result.second == count_results[i - 1].second) {
                    query_answer += curr_size;
                    continue;
                }
            }

            curr_size = binarySearchSize(curr_size, curr_count_result);
            query_answer += curr_size;
        }

        return resultQuery(query_answer);
    }

    size_t binarySearchSize(size_t curr_size, std::pair<size_t, size_t> curr_count_result) {
        size_t query_city = curr_count_result.first;

        size_t already_calced = 0;

        size_t l = 0;
        size_t r = curr_size + 1;
        while (l < r - 1) {
            size_t m = (l + r) / 2;
            if (decreaseQuery(query_city, m - already_calced)) {
                already_calced = m;
                l = m;
            } else {
                r = m;
            }
        }
        return r - 1;
    }

    bool decreaseQuery(size_t query_city, size_t query_decrease) {
        bool decrease_result = false;
        std::cout << "-" << " " << query_city << " " << query_decrease << std::endl;
        std::string answer;
        std::cin >> answer;

        if (answer == "OK") {
            decrease_result = true;
        } else if (answer == "FAIL") {
            decrease_result = false;
        }
        return decrease_result;
    }

    size_t countQuery(size_t query_city) {
        size_t count_result;
        std::cout << "?" << " " << query_city << std::endl;
        std::cin >> count_result;
        return count_result;
    }

    int resultQuery(size_t query_answer) {
        std::cout << "!" << " " << query_answer << std::endl;
        std::string answer;
        std::cin >> answer;

        if (answer == "OK") {
            return 0;
        } else if (answer == "-1") {
            return -1;
        }
        return -1;
    }

private:
    std::vector<std::pair<size_t, size_t>> count_results;

    size_t n;
    size_t h;
    size_t q;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // число тестов
    size_t t = 0;

    // число городов, лимит на размер министерства, лимит на число запросов
    size_t n, h, q;

    std::cin >> t;
    std::cin >> n >> h >> q;

    Solver solver(n, h, q);

    for (size_t i = 0; i < t; ++i) {
        if (solver.solve() == -1) {
            return 0;
        }
    }

    return 0;
}

#include <iostream>
#include <unordered_set>
#include <vector>

void solve(std::vector<int> numbers) {
    std::unordered_multiset<int> set;
    set.reserve(numbers.size());

    for (int number : numbers) {
        set.insert(number);
    }

    int max_count = 0;
    int number = 0;  // get overriden

    for (auto n : set) {
        int count = set.count(n);

        if (max_count < count || (max_count == count && n > number)) {
            number = n;
            max_count = count;
        }
    }

    std::cout << number << " found " << max_count << " times" << std::endl;
}

int main() {
    std::vector<int> data(1000);
    for (auto& v : data) {
        v = (rand() % 1000) * (rand() % 100) / 100;
    }
    solve(data);
}
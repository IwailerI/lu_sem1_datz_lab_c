/*
Andrejs Piroženoks, ap24069
Program created: 2024/09/12

C6. Given natural number n and integer values a(1), a(2), ... a(n). Find and
print the most frequent value (and its frequency) in the sequence. If there are
several, then the biggest one should be taken.
*/

#include <algorithm>
#include <iostream>
#include <vector>

/// @brief structure to hold a value and quantity of times it was encountered.
/// The only reason this exists, is that C++ does not support multiple return
/// values and I consider return-by-pointer parameters a bad practice.
struct Frequency {
    int value;
    int amount;
};

/// @brief Finds the mode of the vector, if multiple values are available
/// returns maximum of the mode.
/// @warning undefined behaviour if numbers is empty
Frequency find_mode_max(std::vector<int> numbers) {
    // Why is set / unordered set / map / unordered map not used?
    // I hate implementation of sets in C++. But I am content with working with
    // vectors. So if the algorithm complexity practically remains the same, why
    // not choose a simpler data structure?
    // sorted vectors: O(n log2 n)
    // unordered set or map (hash set): O(~n) (amortized average)
    // ordered set or map (search tree): O(n log2 n)

    // numbers is passed by value, so vector should not be modified at callsite
    // default ascending sort order will do
    std::sort(numbers.begin(), numbers.end());

    Frequency current, best;

    current.value = numbers[0];
    current.amount = 0;

    best = current;

    for (int elem : numbers) {
        if (elem == current.value) {
            current.amount++;
        } else {
            // note the >= instead of >
            // because later values will be larger, we need to override the
            // result if amount if the same
            if (current.amount >= best.amount) {
                best = current;
            }
            current.amount = 1;
            current.value = elem;
        }
    }

    // don't forget to flush current into best, if appropriate
    if (current.amount >= best.amount) {
        best = current;
    }

    return best;
}

/// @brief Prompts user for an integer.
/// @return Integer input by the user.
int input_int() {
    while (true) {
        std::string input;
        std::cin >> input;

        int integer;
        try {
            integer = std::stoi(input);
        } catch (std::out_of_range) {
            std::cout << "Provided integer is out of range." << std::endl;
            continue;
        } catch (std::invalid_argument) {
            std::cout << "Please enter a valid integer." << std::endl;
            continue;
        }

        return integer;
    }
}

/// @brief Prompts user for a natural number.
/// @return Integer input by the user.
int input_natural() {
    while (true) {
        int integer = input_int();
        if (integer <= 0) {
            std::cout << "Please enter a natural integer." << std::endl;
            continue;
        }
        return integer;
    }
}

/// @brief Prompts user for a yes / no answer.
/// @return Value provided by the user.
bool input_bool() {
    while (true) {
        std::cout << "1 - yes; 2 - no" << std::endl;
        int i = input_int();
        if (i > 2) {
            std::cout << "Invalid choice." << std::endl;
            continue;
        }

        return i == 1;
    }
}

/// @brief A wrapper around find_mode_max with textual I/O.
void calculation() {
    std::cout << "Please enter number n." << std::endl;
    int n = input_natural();

    std::vector<int> data;
    data.reserve(n);

    std::cout << "Please enter " << n << " elements." << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "(" << i + 1 << "/" << n << ")" << std::endl;
        data.push_back(input_int());
    }

    auto res = find_mode_max(data);

    std::cout << "Value: " << res.value << " (" << res.amount
              << ((res.amount == 1) ? " entry" : " entries") << ")"
              << std::endl;
}

int main() {
    do {
        calculation();
        std::cout << "Again?\n";
    } while (input_bool());
}
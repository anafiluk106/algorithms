#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm> // для std::sort
#include <climits>   // для INT_MAX

// Наивный метод (O(n^2))
int min_difference_naive(const std::vector<int>& arr) {
    int min_diff = INT_MAX;
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = i + 1; j < arr.size(); ++j) {
            int diff = std::abs(arr[i] - arr[j]);
            if (diff < min_diff) {
                min_diff = diff;
            }
        }
    }
    return min_diff;
}

// Оптимизированный метод (O(n log n))
int min_difference_optimized(std::vector<int> arr) { // Копируем массив, чтобы не менять оригинал
    if (arr.size() < 2) return 0;
    std::sort(arr.begin(), arr.end()); // O(n log n)
    int min_diff = INT_MAX;
    for (size_t i = 1; i < arr.size(); ++i) { // O(n)
        int diff = arr[i] - arr[i - 1];
        if (diff < min_diff) {
            min_diff = diff;
        }
    }
    return min_diff;
}

std::vector<int> generate_random_list(int n, int min_val = 0, int max_val = 10000) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = min_val + rand() % (max_val - min_val + 1);
    }
    return arr;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    std::vector<int> sizes = {100, 1000, 10000}; // Размеры для теста

    std::cout << "Сравнение методов поиска минимальной разницы:\n";
    std::cout << "=============================================\n";

    for (int n : sizes) {
        std::vector<int> arr = generate_random_list(n, 0, 100000);

        // Замер времени для наивного метода
        auto start_naive = std::chrono::high_resolution_clock::now();
        int result_naive = min_difference_naive(arr);
        auto end_naive = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_naive = end_naive - start_naive;

        // Замер времени для оптимизированного метода
        auto start_opt = std::chrono::high_resolution_clock::now();
        int result_opt = min_difference_optimized(arr);
        auto end_opt = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_opt = end_opt - start_opt;

        // Вывод результатов
        std::cout << "\nРазмер массива: " << n << std::endl;
        std::cout << "Минимальная разница (наивный): " << result_naive
                  << " | Время: " << time_naive.count() << " сек. (O(n^2))" << std::endl;
        std::cout << "Минимальная разница (оптимизир.): " << result_opt
                  << " | Время: " << time_opt.count() << " сек. (O(n log n))" << std::endl;
    }
    return 0;
}
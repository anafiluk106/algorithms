#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm> // для std::find

// Медленный метод (O(n^2))
std::vector<int> remove_duplicates_naive(const std::vector<int>& arr) {
    std::vector<int> result;
    for (int num : arr) {
        // Ищем элемент в текущем результате (линейный поиск -> O(n) для каждого элемента)
        if (std::find(result.begin(), result.end(), num) == result.end()) {
            result.push_back(num);
        }
    }
    return result;
}

// Быстрый метод (O(n))
std::vector<int> remove_duplicates_optimized(const std::vector<int>& arr) {
    std::unordered_set<int> seen;
    std::vector<int> result;
    for (int num : arr) {
        // Проверяем, есть ли элемент в множестве (O(1) в среднем)
        if (seen.find(num) == seen.end()) {
            seen.insert(num);   // Вставляем в множество
            result.push_back(num); // Вставляем в результат
        }
    }
    return result;
}

std::vector<int> generate_random_list(int n, int min_val = 0, int max_val = 100) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = min_val + rand() % (max_val - min_val + 1);
    }
    return arr;
}

// Функция для рисования текстовой гистограммы
void draw_bar(const std::string& label, double value, double max_value, int width = 30) {
    int bar_length = static_cast<int>((value / max_value) * width);
    std::cout << label << " [" << value << " сек.] " << std::string(bar_length, '#') << std::endl;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    std::vector<int> sizes = {1000, 5000, 10000};

    for (int n : sizes) {
        std::cout << "\n--- Размер массива: " << n << " ---\n";
        // Генерируем массив в узком диапазоне, чтобы дубликатов было много
        std::vector<int> arr = generate_random_list(n, 0, 50);

        // Медленный метод
        auto start_naive = std::chrono::high_resolution_clock::now();
        auto result_naive = remove_duplicates_naive(arr);
        auto end_naive = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_naive = end_naive - start_naive;

        // Быстрый метод
        auto start_opt = std::chrono::high_resolution_clock::now();
        auto result_opt = remove_duplicates_optimized(arr);
        auto end_opt = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_opt = end_opt - start_opt;

        // Проверка корректности (размеры должны совпадать)
        std::cout << "Исходный размер: " << arr.size()
                  << ", после удаления дубликатов: " << result_naive.size() << " (оба метода)\n";

        std::cout << "Время выполнения:\n";
        double max_time = std::max(time_naive.count(), time_opt.count());
        draw_bar("Наивный (O(n^2))   ", time_naive.count(), max_time);
        draw_bar("Оптимизированный (O(n))", time_opt.count(), max_time);
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <cstdlib> // для rand() и srand()
#include <ctime>   // для time()

// Структура для хранения информации о паре элементов
struct Pair {
    size_t idx1, idx2;
    int val1, val2;
};

// Функция для поиска всех пар с заданной суммой
// Сложность: O(n^2) - два вложенных цикла
std::vector<Pair> find_pairs_with_sum(const std::vector<int>& arr, int target_sum) {
    std::vector<Pair> pairs;
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[i] + arr[j] == target_sum) {
                pairs.push_back({i, j, arr[i], arr[j]});
            }
        }
    }
    return pairs;
}

// Функция генерации случайного списка целых чисел
std::vector<int> generate_random_list(int n, int min_val = 0, int max_val = 100) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = min_val + rand() % (max_val - min_val + 1);
    }
    return arr;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Инициализация генератора случайных чисел

    int n, min_val, max_val, target_sum;

    std::cout << "Введите размер массива (n): ";
    std::cin >> n;
    std::cout << "Введите минимальное значение: ";
    std::cin >> min_val;
    std::cout << "Введите максимальное значение: ";
    std::cin >> max_val;

    std::vector<int> arr = generate_random_list(n, min_val, max_val);

    // Вывод массива для наглядности
    std::cout << "\nСгенерированный массив:\n";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n\n";

    std::cout << "Введите целевую сумму для поиска пар: ";
    std::cin >> target_sum;

    // Поиск пар
    std::vector<Pair> result = find_pairs_with_sum(arr, target_sum);

    // Вывод результатов
    if (result.empty()) {
        std::cout << "Пар с суммой " << target_sum << " не найдено.\n";
    } else {
        std::cout << "Найдены следующие пары с суммой " << target_sum << ":\n";
        for (const auto& pair : result) {
            std::cout << "arr[" << pair.idx1 << "] = " << pair.val1
                      << " + arr[" << pair.idx2 << "] = " << pair.val2
                      << " = " << target_sum << std::endl;
        }
    }

    std::cout << "\nСложность алгоритма: O(n^2)" << std::endl;
    return 0;
}
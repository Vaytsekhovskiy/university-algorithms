// 9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#define _CRT_SECURE_NO_WARNINGS   

#include <iostream>  
#include <vector>  
#include <cstdlib>  
#include <ctime>  
using namespace std;
/**
 *
 * @param m количество столбцов матрицы
 * @param n количество строк матрицы
 * т.к. матрица квадратная, то m = n
 */
int m, n;
/**
 * @brief Функция которая выводит матрицу на экран
 * 
 * @param matrix Входящая матрица, которую необходимо вывести на экран
 *
 *
 * @return Выведенную матрицу на экран
 */
void printMatrix(const vector<vector<int>>& matrix) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        cout << "\n";
    }
}
/**
 * @brief Функция которая выводит массив на экран
 *
 * @param array Входной массив, который необходимо вывести на экран
 *
 *
 * @return Выведенный массив на экран
 */
void printArray(const vector<int>& array) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
}
/**
 * @brief Функция которая сортирует переданный массив пузырьковой сортировкой
 *
 * @param arr Входной массив, который необходимо отсортировать
 * @param comparisons количество сравнений элементов
 * @param swaps количество перестановок элементов
 *
 *
 * @return Количество массивов и перестановок будут сохранены в comparisons, swaps соответственно
 */
void bubbleSort(vector<int>& arr, long& comparisons, long& swaps) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (abs(arr[j]) > abs(arr[j + 1])) {
                swaps++;
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
/**
 * @brief Функция которая сортирует переданный массив сортировкой выбором
 *
 * @param arr Входной массив, который необходимо отсортировать
 * @param comparisons количество сравнений элементов
 * @param swaps количество перестановок элементов
 *
 *
 * @return Количество массивов и перестановок будут сохранены в comparisons, swaps соответственно
 */
void selectionSort(vector<int>& arr, long& comparisons, long& swaps) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (abs(arr[j]) < abs(arr[i])) {
                swaps++;
                swap(arr[j], arr[i]);
            }
        }
    }
}
/**
 * @brief Функция которая сортирует переданный массив сортировкой всавками
 *
 * @param arr Входной массив, который необходимо отсортировать
 * @param comparisons количество сравнений элементов
 * @param swaps количество перестановок элементов
 *
 *
 * @return Количество массивов и перестановок будут сохранены в comparisons, swaps соответственно
 */
void insertionSort(vector<int>& arr, long& comparisons, long& swaps) {
    for (int i = 1; i < n; i++) {
        int j = i - 1;
        int temp = arr[i];
        comparisons++;
        while (j >= 0 && abs(arr[j]) > abs(temp)) {
            comparisons++;
            arr[j + 1] = arr[j];
            j--;
            swaps++;
        }
        arr[j + 1] = temp;
    }
}
/**
 * @brief Функция которая сортирует переданный массив сортировкой Шелла
 *
 * @param arr Входной массив, который необходимо отсортировать
 * @param comparisons количество сравнений элементов
 * @param swaps количество перестановок элементов
 *
 *
 * @return Количество массивов и перестановок будут сохранены в comparisons, swaps соответственно
 */
void shellSort(vector<int>& arr, long& comparisons, long& swaps) {
    for (int interval = n / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < n; i++) {
            comparisons++;
            int temp = arr[i];
            int j;
            for (j = i; j >= interval && abs(arr[j - interval]) > abs(temp); j -= interval) {
                swaps++;
                arr[j] = arr[j - interval];
            }
            arr[j] = temp;
        }
    }
}
/**
 * @brief Функция которая сортирует переданный массив быстрой сортировкой
 *
 * @param arr Входной массив, который необходимо отсортировать
 * @param comparisons количество сравнений элементов
 * @param swaps количество перестановок элементов
 *
 *
 * @return Количество массивов и перестановок будут сохранены в comparisons, swaps соответственно
 */
void quickSort(vector<int>& arr, long& comparisons, long& swaps, int& low, int& high) {
    if (n == 0) return;
    if (low >= high) return;
    int middle = low + (high - low) / 2;
    int opora = arr[middle];
    // разделить на подмассивы, который > и < опорного 
    int i = low, j = high;
    while (i <= j) {
        while (abs(arr[i]) < abs(opora)) {
            comparisons++;
            i++;
        }
        while (abs(arr[j]) > abs(opora)) {
            comparisons++;
            j--;
        }
        if (i <= j) { // меняем местами 
            swaps++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    // вызов рекурсии для сортировки левой и правой части 
    if (low < j) quickSort(arr, comparisons, swaps, low, j);
    if (high > i) quickSort(arr, comparisons, swaps, i, high);
}
/**
 * @brief Entry point
 * В качестве выбора количества параметров, 
 * в соответствии с вариантом возьмём функцию
 * M(I)=30*I*5*6, I=1…7
 * В качестве основания логарифмической шкалы,
 * будет выбран логарифм по основанию 7
 * Execution of the program
 * starts here.
 *
 *
 *
 *
 * @return Program exit status
 */
int main()
{
    setlocale(LC_ALL, "Rus");
    long comparisons_b = 0, swaps_b = 0;
    long comparisons_s = 0, swaps_s = 0;
    long comparisons_i = 0, swaps_i = 0;
    long comparisons_sh = 0, swaps_sh = 0;
    long comparisons_q = 0, swaps_q = 0;
    for (int j = 1; j <= 7; j++) {
        cout << "I = " << j << endl;
        n = 30 * j * 5 * 6;
        m = n / 150;
        vector<vector<int>> arrays(m, vector<int>(n));
        // заполняем массив случайными числами  
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                arrays[i][j] = rand() % 100 - 50;
            }
        }
        //cout << "Неупорядоченная матрица:" << endl;
        //printMatrix(arrays);
        for (int i = 0; i < m; i++) {
            vector<int> array = arrays[i];

            // Пузырьковая сортировка  
            bubbleSort(array, comparisons_b, swaps_b);
            //printArray(array);

            // Сортировка выбором  
            array = arrays[i];
            selectionSort(array, comparisons_s, swaps_s);
            //printArray(array);

            // Сортировка вставками  
            array = arrays[i];
            insertionSort(array, comparisons_i, swaps_i);
            //printArray(array);

            // Сортировка Шелла  
            array = arrays[i];
            shellSort(array, comparisons_sh, swaps_sh);
            //printArray(array);

            // Быстрая сортировка  
            array = arrays[i];
            int begin = 0;
            int end = n - 1;
            quickSort(array, comparisons_q, swaps_q, begin, end);
            //printArray(array);
        }
        cout << "Пузырьковая. Сравнений: " << comparisons_b << ", Перестановок: " << swaps_b << endl;
        cout << "Выбором. Сравнений: " << comparisons_s << ", Перестановок: " << swaps_s << endl;
        cout << "Вставками. Сравнений: " << comparisons_i << ", Перестановок: " << swaps_i << endl;
        cout << "Шелла. Сравнений: " << comparisons_sh << ", Перестановок: " << swaps_sh << endl;
        cout << "Быстрая. Сравнений: " << comparisons_q << ", Перестановок: " << swaps_q << endl;
        comparisons_b = 0, swaps_b = 0;
        comparisons_s = 0, swaps_s = 0;
        comparisons_i = 0, swaps_i = 0;
        comparisons_sh = 0, swaps_sh = 0;
        comparisons_q = 0, swaps_q = 0;
    }

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

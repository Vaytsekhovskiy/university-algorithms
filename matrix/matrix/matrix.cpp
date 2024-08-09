// matrix.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
// ANSI escape коды для цветов
#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
// Функция для поиска квадратов из единиц
void findSquares(int** arr, int N, int M) {
    for (int i = 0; i <= N - M; i++) {
        for (int j = 0; j <= N - M; j++) {
            int isSquare = 1;
            for (int k = i; k < i + M; k++) {
                for (int l = j; l < j + M; l++) {
                    if (arr[k][l] != 1) {
                        isSquare = 0;
                        break;
                    }
                }
                if (!isSquare) {
                    break;
                }
            }
            if (isSquare) {
                printf("Найден квадрат из единиц с левым верхним углом в (%d, %d)\n", j, i);
            }
        }
    }
}
void printMatrix(int** arr, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%s%d%s ", arr[i][j] ? GREEN : RED, arr[i][j], RESET);
        }
        printf("\n");
    }
}
int main(void) {
    setlocale(LC_ALL, "Rus");
    int N = 0;
    printf("%s%s%s ", CYAN, "Введите размер массива :", RESET);
    scanf("%d", &N);
    // Выделение памяти для двумерного массива
    int** array = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        array[i] = (int*)malloc(N * sizeof(int));
    }

    // Заполнение случайными элементами
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            array[i][j] = rand() % 2; // 0 <= rand() <= 32767
        }
    }
    // Вывод исходной матрицы на экран
    printf("%s%s%s", MAGENTA, "Исходная матрица\n", RESET);
    printMatrix(array, N);
    // Нахождение квадратов
    int M = 0;
    printf("%s%s%s ", YELLOW, "Введите размер искомого квадрата:", RESET);
    scanf("%d", &M);
    findSquares(array, N, M);
    return 0;
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

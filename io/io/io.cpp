// io.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_WORD_LENGTH 100

// Функция для подсчета количества вхождений символа в слове
int countOccurrences(char* word, char ch) {
    int count = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == ch) {
            count++;
        }
    }
    return count;
}

int main() {
    setlocale(LC_ALL, "Rus");
    char filename[100];
    char searchChar;

    printf("Введите имя файла: ");
    scanf("%s", filename);

    // Открываем файл для чтения
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return 1;
    }

    printf("Введите символ для поиска: ");
    scanf(" %c", &searchChar);

    char word[MAX_WORD_LENGTH];
    char maxOccurrencesWord[MAX_WORD_LENGTH];
    int maxOccurrences = 0;

    // Считываем слова из файла
    while (fscanf(file, "%s", word) == 1) {
        // Печатаем слова, содержащие заданный символ
        if (strchr(word, searchChar) != NULL) {
            printf("%s\n", word);

            // Находим слово с наибольшим количеством вхождений символа
            int occurrences = countOccurrences(word, searchChar);
            if (occurrences > maxOccurrences) {
                maxOccurrences = occurrences;
                strcpy(maxOccurrencesWord, word);
            }
        }
    }

    // Печатаем слово с наибольшим количеством вхождений символа
    if (maxOccurrences > 0) {
        printf("\nСлово с наибольшим количеством вхождений символа '%c' - %s (%d вхождений)\n", searchChar, maxOccurrencesWord, maxOccurrences);
    }
    else {
        printf("\nВ файле нет слов, содержащих символ '%c'\n", searchChar);
    }

    // Закрываем файл
    fclose(file);

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

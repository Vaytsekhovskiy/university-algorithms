// 8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS   

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstring> // для функции strcpy
#include <map>

using namespace std;

unsigned int crc32(char* buffer, unsigned int len) {
    int temp_crc = 0xF;
    // 0xFFFFFFFF;
    int temp_poly = 0xE;
    // 0xEDB88320;
    unsigned int crc = temp_crc; // добавленный регистр, 
    //некоторое стартовое значение

    while (len--) {
        crc ^= *buffer++;
        for (int bit = 0; bit < 8; bit++) {
            if (crc & 1) crc = (crc >> 1) ^ temp_poly; // xor на предложенный полином
            // полином может быть разных значений
            else crc = (crc >> 1);
        }
    }
    return crc ^ temp_crc;
}

unsigned int findCollision(unsigned int target_hash) {
    int len = 0;
    int res = 0;
    while(res < 2000) {
        while (len < 20) {
            char* buffer = new char[len + 1]; // +1 для завершающего нуля
            buffer[len] = '\0';
            for (int i = 0; i < len; ++i) {
                buffer[i] = 'a' + rand() % 26;
                unsigned int hash = crc32(buffer, len);
                //printf("%d : %s\n", hash, buffer);
                // Проверка на совпадение с искомым хеш-кодом
                if (hash == target_hash) {
                    // Вывод найденных данных и их хеш-кода
                    cout << "Найдена коллизия:" << endl;
                    cout << "Данные: " << buffer << endl;
                    cout << "Хеш-код: " << hash << endl;
                    cout << "\n";
                    return 0; // Завершаем программу, когда найдена коллизия
                }
            }
            len++;
        }
        res++;
    }
    cout << "Коллизия не найдена." << endl;
    cout << "\n";
    return 0;
}

void findWords(map<unsigned int, string> hashTable) {
    cout << "Введите хеш-код, по которому будет найдено значение";
    cout << "\n";
    unsigned int hashCode;
    cin >> hashCode;
    bool wasFound = false;
    while (hashCode != 0) {
        wasFound = false;
        for (const auto& entry : hashTable) {
            if (entry.first == hashCode) { 
                wasFound = true;
                printf("Найденное значение: %s\n", entry.second.c_str()); 
                break;
            }
        }
        if (!wasFound) { 
            cout << "Значение по данному хэшу не было найдено"; 
            cout << "\n";
        }
        cin >> hashCode;
    }
}

int main() {
    setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы
    ifstream fin; 
    fin.open("C:\\Users\\fdsaf\\Desktop\\e.txt");

    // Проверяем, открыт ли файл успешно
    if (!fin.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return 1;
    }
    string word1, word2;
    char* combined;
    map<unsigned int, string> hashTable;
    while (fin >> word1) {
        // Считываем второе слово
        if (!(fin >> word2)) {
            // Если не удалось считать второе слово, выходим из цикла
            break;
        }
        // Выделение памяти для объединенной строки, включая место для завершающего нуля
        combined = new char[word1.length() + word2.length() + 1];

        // Копирование содержимого строк в новую строку
        strcpy(combined, word1.c_str());
        strcat(combined, word2.c_str());
        unsigned int hash = crc32(combined, word1.length() + word2.length() + 1);
        hashTable[hash] = word1 + " " + word2;
        printf("%s %s : %d \n", word1.c_str(), word2.c_str(), hash);
        findCollision(hash);
    }
    fin.close();
    findWords(hashTable);
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

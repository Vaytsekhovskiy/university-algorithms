#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
int main(void) {
    setlocale(LC_ALL, "Rus");
	int N = 0;
    printf("������� ������ �������: \n");
	scanf("%d", N);
	// ��������� ������ ��� ���������� �������
	int** array = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++) {
		array[i] = (int*)malloc(N * sizeof(int));
	}

	// ���������� ���������� ����������
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			array[i][j] = rand() % 2; // 0 <= rand() <= 32767
		}
	}
	// ���������� ���������
	int M = 0;
	scanf("%d", M);
    printf("������� ������ �������� ��������: \n");
	findSquares(array, N, M);
	return 0;
}
// ������� ��� ������ ��������� �� ������
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
                printf("������ ������� �� ������ � ����� ������� ����� � (%d, %d)\n", i, j);
            }
        }
    }
}
//����� ���������� ������ � �� N ����� � N ��������, 
// ���������� �������� �������� ���� � �������, 
// �������� � ������� ������� rand().
// ���������� � ��� ������� ���� ��������� �� ������ �� �������� ����� �.
// ���� ����� �������� �������, �� ������� ���������� �� ����� ������� �����.

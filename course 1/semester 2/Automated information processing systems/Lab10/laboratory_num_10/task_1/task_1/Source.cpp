#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

void fillA(int K, vector <int>& A)
{
	cout << "Массив, заполненный случайными числами: " << endl;
	for (int i = 0; i < K; i++)
	{
		A[i] = rand() % 100 + 1;
		cout << A[i] << " ";
	}
}

void fillB(int N, int M, vector <vector <int>>& B, vector <int>& A, int K)
{
	for (int i = 0; i < M; i++)
	{
		B[i].resize(N);
		for (int g = 0; g < N; g++)
		{
			if (i * N + g < K)
			{
				B[i][g] = (A[i * N + g]);
			}
			else
			{
				B[i][g] = 0;
			}
		}
	}
}

void ArrayToMatrix2()
{
	int K, M, N;
	cout << "Введите размер массива A: ";
	cin >> K;
	vector <int> A(K);
	fillA(K, A);
	cout << "\nВведите размер двумерного массива B\nЧисло строк: ";
	cin >> M;
	cout << "Число столбцов: ";
	cin >> N;
	vector <vector <int>> B(M);
	fillB(N, M, B, A, K);
	cout << endl;
	for (int i = 0; i < M; i++)
	{
		for (int g = 0; g < N; g++)
		{
			cout << B[i][g] << " ";
		}
		cout << endl;
	}

}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	ArrayToMatrix2();
	return(0);
}

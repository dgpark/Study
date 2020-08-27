//Method1 less memory more time
#include <iostream>
#include <algorithm>

using namespace std;

int main(void) {
	int N, M;

	scanf_s("%d %d", &N, &M);
	
	int* array = new int[N+M];

	for (int i = 0; i < N+M; i++) {
		scanf_s("%d", &array[i]);
	}
	sort(array, array+(N+M));
	
	for (int i = 0; i < N + M; i++) {
		printf("%d ", array[i]);
	}

	delete[] array;
	return 0;
}

/*
//method2 more memory less time
#include <iostream>
#include <algorithm>

using namespace std;

int main(void) {
	int N, M;

	scanf("%d %d", &N, &M);

	int* arrayA = new int[N];
	int* arrayB = new int[M];
	//int* array = new int[N + M];

	for (int i = 0; i < N; i++) {
		scanf("%d", &arrayA[i]);
	}
	for (int i = 0; i < M; i++) {
		scanf("%d", &arrayB[i]);
	}

	int i=0, j = 0, k = 0;
	while (j < N && k < M) {
		if (arrayA[j] <= arrayB[k]) {
			printf("%d ", arrayA[j++]);
		}
		else {
			printf("%d ", arrayB[k++]);
		}
	}

	while (j < N)
		printf("%d ", arrayA[j++]);

	while (k < M)
		printf("%d ", arrayB[k++]);


	delete[] arrayA;
	delete[] arrayB;
	//delete[] array;
	return 0;
}

*/
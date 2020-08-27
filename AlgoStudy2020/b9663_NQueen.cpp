#include <iostream>

bool NQueenPossible(int(&row)[15], int& N, int col);
void NQueen(int(&row)[15], int& N, int rowNum, int& count);

int main(void) {
	int row[15];
	int N;
	int count = 0;

	scanf("%d", &N);

	NQueen(row, N, 0, count);

	printf("%d", count);

	return 0;
}

bool NQueenPossible(int(&row)[15], int& N, int rowNum) {
	if (rowNum == 0) {
		return true;
	}
	for (int parentRowNum = 0; parentRowNum < rowNum; parentRowNum++) {
		if (row[rowNum] == row[parentRowNum] || (rowNum - parentRowNum) == abs(row[rowNum] - row[parentRowNum])) {
			return false;
		}
	}
	return true;
}

//row[rowNum] = rowNum번째 row의 column number
void NQueen(int(&row)[15], int& N, int rowNum, int& count) {
	for (int col = 0; col < N; col++) {
		row[rowNum] = col;
		// Nqueen을 놓을 수 있으면 계속, 없으면 가지치기
		if (NQueenPossible(row, N, rowNum)) {
			if (rowNum == N - 1) {
				count++;
				// NQueen의 위치들을 알고 싶다면 vector에 row 배열을 push_back하면 됨.
				return;
			}
			else {
				NQueen(row, N, rowNum + 1, count);
			}
		}
	}
}
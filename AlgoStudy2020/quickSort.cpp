#include <iostream>

void quickSort(int(&data)[10], int start, int end);

int main(void) {
	int data[10] = { 1,4,2,8,6,9,5,10,3,7 };

	quickSort(data, 0, 9);

	for (int i = 0; i < 10; i++) {
		printf("%d ", data[i]);
	}

	return 0;
}

void quickSort(int(&data)[10], int start, int end) {
	if (start >= end) {
		return;
	}

	int pivot = start;
	int lStart = pivot + 1;
	int rStart = end;
	int temp;

	while (lStart <= rStart) {
		while (lStart <= end && data[lStart] <= data[pivot]) {
			lStart++;
		}
		while (rStart > start && data[rStart] >= data[pivot]) {
			rStart--;
		}

		if (lStart > rStart) {
			temp = data[pivot];
			data[pivot] = data[rStart];
			data[rStart] = temp;
		}
		else {
			temp = data[lStart];
			data[lStart] = data[rStart];
			data[rStart] = temp;
		}
	}

	quickSort(data, start, rStart - 1);
	quickSort(data, rStart + 1, end);
}

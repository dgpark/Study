#include <stdio.h>
#include <stack>

using namespace std;

int main(void) {
	int N;
	long long left, right, width, height, area, maxArea = 0;
	long long heightList[100000];
	stack<long long> stackHeightIndex;

	while (true) {
		scanf("%d", &N);
		if (N == 0)
			break;
		for (int index = 0; index < N; ++index) {
			//test case �Է�
			scanf("%lld", &heightList[index]);
			while (!stackHeightIndex.empty() && heightList[stackHeightIndex.top()] > heightList[index]) {
				height = heightList[stackHeightIndex.top()];
				stackHeightIndex.pop();
				left = stackHeightIndex.empty() ? 0 : stackHeightIndex.top() + 1;
				right = index;
				width = right - left;
				area = width * height;
				if (area > maxArea)
					maxArea = area;
			}
			stackHeightIndex.push(index);
		}
		//for���� �����µ� stack�� ���������� ������ index�� push�� ��.
		while (!stackHeightIndex.empty()) {
			height = heightList[stackHeightIndex.top()];
			stackHeightIndex.pop();
			left = stackHeightIndex.empty() ? 0 : stackHeightIndex.top() + 1;
			right = N;
			width = right - left;
			area = width * height;
			if (area > maxArea)
				maxArea = area;
		}
		printf("%lld\n", maxArea);
		maxArea = 0;
	}
	return 0;
}

// �� line�� ù ���ڿ� 0�� �־��������� �׽�Ʈ���̽� �Է�.
// ���� ��ȣ���� �޹�ȣ�� ���̰� ũ�� ���ÿ� �ش� index push
// ������ top ��ȣ���� ���� ��ȣ�� ���̰� Ŭ ��� pop()
// pop()�� �� ��� �غ��� ���� :  (������ȣ) - (stack�� top ��ȣ+1)
// pop()�� �� ��� ���� : pop�� index�� ����
// maxArea�� ���� ����.

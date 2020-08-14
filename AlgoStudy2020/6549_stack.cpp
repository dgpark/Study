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
			//test case 입력
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
		//for문이 끝났는데 stack이 남아있으면 마지막 index가 push된 것.
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

// 각 line의 첫 숫자에 0이 주어질때까지 테스트케이스 입력.
// 이전 번호보다 뒷번호의 높이가 크면 스택에 해당 index push
// 스택의 top 번호보다 다음 번호의 높이가 클 경우 pop()
// pop()을 할 경우 밑변의 길이 :  (다음번호) - (stack의 top 번호+1)
// pop()을 할 경우 높이 : pop한 index의 높이
// maxArea에 정답 저장.

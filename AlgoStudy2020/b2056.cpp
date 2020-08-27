#include <stdio.h>
#include <vector>

using namespace std;

int main(void) {
	int N, workTime, numOfPre, prerequisite, lastPrerequisite, max = 0;
	int time[10001];

	scanf("%d", &N);

	for (int i = 1; i < N + 1; ++i) {
		scanf("%d %d", &workTime, &numOfPre);
		time[i] = workTime;
		lastPrerequisite = 0;
		for (int j = 0; j < numOfPre; ++j) {
			scanf("%d", &prerequisite);
			if (lastPrerequisite < time[prerequisite]) { // 선행작업은 항상 N번째 작업보다 작은 숫자의 작업이다. 즉, 이미 입력된 값.
				lastPrerequisite = time[prerequisite]; // 선행작업중 가장 늦게 끝나는 작업의 시간 저장.
			}
		}
		time[i] += lastPrerequisite;
		if (time[i] > max) {
			max = time[i];
		}
	}

	printf("%d", max);

	return 0;
}


/*

1. 입력 작업시간[10000]에 첫번째 값 입력. (각 row의 2번째 값만큼 반복문 돌며 세번째 값인 선행작업 입력)
2. 선행요소들 중 가장 큰 값(마지막에 끝나는 값)에 해당 작업의 시간 더하기.
3. 저장한 max값 출력.

*/
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
			if (lastPrerequisite < time[prerequisite]) { // �����۾��� �׻� N��° �۾����� ���� ������ �۾��̴�. ��, �̹� �Էµ� ��.
				lastPrerequisite = time[prerequisite]; // �����۾��� ���� �ʰ� ������ �۾��� �ð� ����.
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

1. �Է� �۾��ð�[10000]�� ù��° �� �Է�. (�� row�� 2��° ����ŭ �ݺ��� ���� ����° ���� �����۾� �Է�)
2. �����ҵ� �� ���� ū ��(�������� ������ ��)�� �ش� �۾��� �ð� ���ϱ�.
3. ������ max�� ���.

*/
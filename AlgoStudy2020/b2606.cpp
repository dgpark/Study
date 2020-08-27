#include <stdio.h>

int Find(int x, int(&parent)[101]);
void Union(int x, int y, int(&parent)[101]);

int main(void) {
	int parent[101], inputNum[2];
	int computerNum, edgeNum, count = 0;
	scanf("%d %d", &computerNum, &edgeNum);

	for (int i = 0; i < computerNum + 1; i++) {
		parent[i] = i;
	}

	for (int i = 0; i < edgeNum; i++) {
		scanf("%d %d", &inputNum[0], &inputNum[1]);
		Union(inputNum[0], inputNum[1], parent);
	}

	for (int i = 2; i < computerNum + 1; i++) {
		if (Find(i, parent) == Find(1, parent)) {
			count++;
		}
	}

	printf("%d", count);

	return 0;
}

int Find(int x, int(&parent)[101]) {
	if (parent[x] == x) {  //parent[x]==x�̸� �ʱ�ȭ��.
		return parent[x];
	}
	return parent[x] = Find(parent[x], parent);
}

void Union(int x, int y, int(&parent)[101]) {
	int xParent = Find(x, parent);
	int yParent = Find(y, parent);
	if (xParent != yParent) {
		parent[yParent] = xParent;
	}
	return;
}


//�Է�����
// ù��°�� ��ǻ�� ���� computerNum�Է�. computerNum�� �׻� 100 �����̹Ƿ� int parent[101]; ����
// �ι�°�� ��Ʈ��ũ ���� Edge�� �� �Է�. edgeNum��ŭ for�� �ݺ�.

//Ǯ��
//Union Find �̿�. x�� ��ǻ���� Find(x)�� == Find(1)�̸� count++;
//Edge ����ŭ for�� �ݺ��ϸ� Union(x,y) ����
//Union�Լ� ������ x,y�� root�� ã�� parent[y�� ��Ʈ] = x�� ��Ʈ ����

//int parent[100],int computerNum, int edgeNum; �Լ� Union, �Լ� Find �̿�.



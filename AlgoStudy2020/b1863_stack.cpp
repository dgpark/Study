#include <stdio.h>
#include <stack>

using namespace std;

int main(void) {
	int N, x, y, count = 0;
	stack<int> yChange;

	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d %d", &x, &y);
		while (!yChange.empty() && yChange.top() >= y) { // y���� ������ ���� �ǹ��� �νĵǹǷ� stack���� �ߺ��Ͽ� ���� ���� �ʴ´�. (ī���� ���� �ʰ� pop���� ����)
			if (yChange.top() != y)
				++count;
			yChange.pop();
		}
		if (y != 0) // 0�� ���̰� ���� ������ �ǹ��� counting���� �ʴ´�. push (X)
			yChange.push(y);
	}

	// ������ �Է°��� push�� ��� ó��
	if (!yChange.empty())
		count += yChange.size(); // �Է¹��� ���� y���� 0�̹Ƿ� stack�� ����ŭ count�� ���Ѵ�.

	printf("%d", count);

	return 0;
}

// N���� (x, y)�Է¹ޱ�.
// y�� stack.top()���� �������� stack�� y�� push. 
// y�� stack.top() �������� stack.top()�� ũ�ų� ������������ pop.
// pop()�� �� count += 1.
// �ǹ��� �ּ� ������ ���µ� x���� ��� Ǯ������ �ʳ�,,,?

#include <stdio.h>
#include <stack>

using namespace std;

int main(void) {
	int N, x, y, count = 0;
	stack<int> yChange;

	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d %d", &x, &y);
		while (!yChange.empty() && yChange.top() >= y) { // y값이 같으면 같은 건물로 인식되므로 stack에는 중복하여 값을 넣지 않는다. (카운팅 하지 않고 pop으로 제거)
			if (yChange.top() != y)
				++count;
			yChange.pop();
		}
		if (y != 0) // 0은 높이가 없기 때문에 건물로 counting하지 않는다. push (X)
			yChange.push(y);
	}

	// 마지막 입력값이 push된 경우 처리
	if (!yChange.empty())
		count += yChange.size(); // 입력범위 밖은 y값이 0이므로 stack의 수만큼 count를 더한다.

	printf("%d", count);

	return 0;
}

// N개의 (x, y)입력받기.
// y가 stack.top()보다 높아지면 stack에 y값 push. 
// y가 stack.top() 낮아지면 stack.top()이 크거나 같아질때까지 pop.
// pop()할 때 count += 1.
// 건물의 최소 개수를 세는데 x값은 없어도 풀수있지 않나,,,?

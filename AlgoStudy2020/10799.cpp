#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main(void) {
	stack<int> ironBar;
	string input;
	int count = 0;


	getline(cin, input);


	for (int i = 0; i < input.size(); ++i) {
		if (input[i] == '(' && input[i + 1] == ')') {
			//레이저
			count += ironBar.size();
			++i;//i+1이 )이므로 레이저는 for문 종류시 i에 +2로 처리.
		}
		else if (input[i] == '(') {
			//쇠막대기 시작
			ironBar.push(input[i]);
		}
		else {
			//쇠막대기 끝
			++count;
			ironBar.pop();
		}
	}

	printf("%d", count);

	return 0;
}


// 조건 : 1)긴막대 위에 짧은 막대만 포갠다(놓을때 끝 점은 겹치면 안됨.)
// 각 쇠막대기 자르는 레이저 적어도 하나 존재
// 레이저는 각 막대기의 끝점과 겹치지 않음.
// 쇠막대기 몇개의 조각으로 잘리는가? ():레이저 (:쇠막대기 시작 ): 쇠막대기 끝

// 한줄의 string으로 입력받음.
//[i]와 [i+1]을 탐색하여 레이저()여부 확인. string의 끝인 \0에 도달하면 종료.(for문 마지막의 [i+1]이 \0을 가리키므로 에러 걱정x.)

// (는 Stack에 push.
// 레이저()가 나오면 현재 stack의 사이즈만큼 count 추가.
// )가 나오면 count + 1


/* 개량한 코드 
//기존코드 속도 4m/s. 개량코드 0m/s. 속도는 scanf로 입력받는지 getline으로 입력받는지의 차이였음. 
//getline으로 한줄을 입력받아도 내부적으로 cin이 여러번 호출되는 구조인것을 생각 못했었음.
#include <stdio.h>
#include <stack>
#include <string>

using namespace std;

int main(void) {
	char input[100001];
	int count = 0, stacksize = 0;

	scanf("%s", input);

	for (int i = 0; input[i]; ++i) {
		if (input[i] == '(' && input[i + 1] == ')') {
			//레이저
			count += stacksize;
			++i;//i+1이 )이므로 레이저는 for문 종류시 i에 +2로 처리.
		}
		else if (input[i] == '(') {
			//쇠막대기 시작
			++stacksize;
		}
		else {
			//쇠막대기 끝
			++count;
			--stacksize;
		}
	}

	printf("%d", count);

	return 0;
}
*/
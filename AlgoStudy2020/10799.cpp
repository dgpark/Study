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
			//������
			count += ironBar.size();
			++i;//i+1�� )�̹Ƿ� �������� for�� ������ i�� +2�� ó��.
		}
		else if (input[i] == '(') {
			//�踷��� ����
			ironBar.push(input[i]);
		}
		else {
			//�踷��� ��
			++count;
			ironBar.pop();
		}
	}

	printf("%d", count);

	return 0;
}


// ���� : 1)�丷�� ���� ª�� ���븸 ������(������ �� ���� ��ġ�� �ȵ�.)
// �� �踷��� �ڸ��� ������ ��� �ϳ� ����
// �������� �� ������� ������ ��ġ�� ����.
// �踷��� ��� �������� �߸��°�? ():������ (:�踷��� ���� ): �踷��� ��

// ������ string���� �Է¹���.
//[i]�� [i+1]�� Ž���Ͽ� ������()���� Ȯ��. string�� ���� \0�� �����ϸ� ����.(for�� �������� [i+1]�� \0�� ����Ű�Ƿ� ���� ����x.)

// (�� Stack�� push.
// ������()�� ������ ���� stack�� �����ŭ count �߰�.
// )�� ������ count + 1


/* ������ �ڵ� 
//�����ڵ� �ӵ� 4m/s. �����ڵ� 0m/s. �ӵ��� scanf�� �Է¹޴��� getline���� �Է¹޴����� ���̿���. 
//getline���� ������ �Է¹޾Ƶ� ���������� cin�� ������ ȣ��Ǵ� �����ΰ��� ���� ���߾���.
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
			//������
			count += stacksize;
			++i;//i+1�� )�̹Ƿ� �������� for�� ������ i�� +2�� ó��.
		}
		else if (input[i] == '(') {
			//�踷��� ����
			++stacksize;
		}
		else {
			//�踷��� ��
			++count;
			--stacksize;
		}
	}

	printf("%d", count);

	return 0;
}
*/
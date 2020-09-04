#include <string>
#include <vector>

using namespace std;

int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    bool match[101][101] = { 0, };

    // match �Է�
    for (vector<int> input : results) {
        match[input[0]][input[1]] = true;
    }

    // �÷��̵� �ͼ�
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (match[i][k] && match[k][j]) {
                    match[i][j] = true;
                }
            }
        }
    }

    // answer
    for (int i = 1; i <= n; ++i) {
        int count = 0;
        for (int j = 1; j <= n; ++j) {
            // check match whether it is known or not
            if (match[i][j] || match[j][i]) count++;
        }
        if (count == n - 1) answer++;
    }

    return answer;
}

// �÷��̵�ͼ� �˰���.
// a[i][j] �º� ���� ����.
// for������ a[i][k] && a[k][j] �̸� a[i][j]�� true�� ����.

// a[x][i] || a[i][x] �̸� count++;
// count == n-1�̸� answer++ 
//https://programmers.co.kr/learn/courses/30/lessons/49191

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int priorCount = 0;
    vector<int> nextVector;
};

int main(void) {
    int N, M;
    int small, tall;
    queue<Node> q;
    vector<int> order;

    scanf("%d %d", &N, &M);
    Node* students = new Node[N];

    // Node�� ���� Ű ���� �Է�.
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &small, &tall);
        students[small - 1].nextVector.push_back(tall - 1);
        students[tall - 1].priorCount++;
    }

    //Node���� prior�� 0�� Node�� queue�� �Է�
    for (int i = 0; i < N; i++) {
        if (students[i].priorCount == 0) {
            q.push(students[i]);
            order.push_back(i + 1);
        }
    }

    //���� ����
    while (!q.empty()) {
        Node student = q.front();
        q.pop();
        for (int i = 0; i < student.nextVector.size(); i++) {
            students[student.nextVector[i]].priorCount--;
            if (students[student.nextVector[i]].priorCount == 0) {
                q.push(students[student.nextVector[i]]);
                order.push_back(student.nextVector[i] + 1);
            }
        }
    }

    for (int i = 0; i < order.size(); i++) {
        printf("%d ", order[i]);
    }

    delete[] students;
    return 0;
}

//�ٸ� ������� �ڵ�ó�� 32000 ������ �迭�� �̸� �Ҵ��Ѵٸ� ���� ����ü ������� �ʾƵ� ��.
//���� prior[32001]�� ó������ �Ҵ��ϴ� ��� �������� �ʿ��� ���̸�ŭ �Ҵ�޾ұ� ������ ����ü�� �̿��Ͽ� prior �����.


/*
��� �˰��� : Topology
�ʿ��� ��.
1) �ڿ� ����� ��� üũ next[] -> size �˼� �����Ƿ� vector�� ����
+ ���� ���� prior ���� counting.
-> struct Node ����. Node.next(vector����), Node.prior
Node* student = new Node[N];

2) Ű ���� ������ ���� queue
-> prior�� ���� ������� ���ʷ� queue�� �ִ´�.
(while������ Ȯ�� : ������ ť�� empty�� �ݺ��� ����.)

ó���� for���� ���� prior�� 0�� ������ queue�� �߰�.
���� �ش� queue�� ���Ҹ� pop()�ϸ鼭 �ش� ���Ұ� ����Ű��
����� prior�� -1. if������ -1�� ����� prior�� 0�� �Ǹ�
�ش� ��� queue�� �߰�

*/
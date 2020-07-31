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

    // Node에 비교한 키 순서 입력.
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &small, &tall);
        students[small - 1].nextVector.push_back(tall - 1);
        students[tall - 1].priorCount++;
    }

    //Node에서 prior이 0인 Node를 queue에 입력
    for (int i = 0; i < N; i++) {
        if (students[i].priorCount == 0) {
            q.push(students[i]);
            order.push_back(i + 1);
        }
    }

    //순서 정렬
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

//다른 사람들의 코드처럼 32000 길이의 배열을 미리 할당한다면 굳이 구조체 사용하지 않아도 됨.
//나는 prior[32001]을 처음부터 할당하는 대신 동적으로 필요한 길이만큼 할당받았기 때문에 구조체를 이용하여 prior 계산함.


/*
사용 알고리즘 : Topology
필요한 것.
1) 뒤에 연결된 노드 체크 next[] -> size 알수 없으므로 vector로 구현
+ 뒤의 노드는 prior 개수 counting.
-> struct Node 생성. Node.next(vector형식), Node.prior
Node* student = new Node[N];

2) 키 순서 결정을 위한 queue
-> prior이 없는 노드들부터 차례로 queue에 넣는다.
(while문으로 확인 : 조건은 큐가 empty면 반복문 종료.)

처음에 for문을 돌며 prior이 0인 노드들을 queue에 추가.
이후 해당 queue의 원소를 pop()하면서 해당 원소가 가리키는
노드의 prior을 -1. if문으로 -1한 노드의 prior이 0이 되면
해당 노드 queue에 추가

*/
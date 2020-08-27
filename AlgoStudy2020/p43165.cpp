#include <string>
#include <vector>

using namespace std;

void plusNum(const vector<int>& numbers, int sum, const int& n_th, const int& target, int& answer);
void minusNum(const vector<int>& numbers, int sum, const int& n_th, const int& target, int& answer);

int solution(vector<int> numbers, int target) {
    int answer = 0;
    int sum = 0;
    plusNum(numbers, sum, 0, target, answer);
    minusNum(numbers, sum, 0, target, answer);

    return answer;
}

void plusNum(const vector<int>& numbers, int sum, const int& n_th, const int& target, int& answer) {
    sum += numbers[n_th];
    if (n_th + 1 == numbers.size()) {
        if (sum == target) answer++;
    }
    else {
        plusNum(numbers, sum, n_th + 1, target, answer);
        minusNum(numbers, sum, n_th + 1, target, answer);
    }
}

void minusNum(const vector<int>& numbers, int sum, const int& n_th, const int& target, int& answer) {
    sum -= numbers[n_th];
    if (n_th + 1 == numbers.size()) {
        if (sum == target) answer++;
    }
    else {
        plusNum(numbers, sum, n_th + 1, target, answer);
        minusNum(numbers, sum, n_th + 1, target, answer);
    }
}

//https://programmers.co.kr/learn/courses/30/lessons/43165?language=cpp
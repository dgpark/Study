#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> multiply(const vector<int>& a, const vector<int>& b); // 일반 곱셈 O(N^2). 단, 숫자 1234의 경우 4321순으로 vector[0], vector[1], ... , vector[3] 에 저장되어 있음)
void normalize(vector<int>& num); // num[]의 자릿수 올림
vector<int> karatsuba(const vector<int>& a, const vector<int>& b);
void addTo(vector<int>& a, const vector <int>& b, int k); // a += b*(10^k)
void subFrom(vector <int>& a, const vector<int>& b); // a -= b (a>=b라고 가정. karatsuba 함수에서 a>=b로 처리되게 짜여있음)


int main(void) {
	vector<int> a;
	vector<int> b;
	for (int i = 100; i > 0; --i)
		a.push_back(i % 10);

	for (int i = 91; i > 0; --i)
		b.push_back(i % 10);
	vector<int> c = karatsuba(b, a);

	int cSize = c.size();
	for (int i = cSize - 1; i >= 0; --i)
		printf("%d ", c[i]);

	return 0;
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> c(a.size() + b.size() + 1, 0);

	int aSize = a.size();
	int bSize = b.size();

	for (int i = 0; i < aSize; ++i)
		for (int j = 0; j < bSize; ++j)
			c[i + j] += a[i] * b[j];
	normalize(c);
	return c;
}

void normalize(vector<int>& num) {
	num.push_back(0);

	//자릿수 올림 처리
	int size = num.size();
	for (int i = 0; i + 1 < size; ++i) {
		if (num[i] < 0) {
			int borrow = (abs(num[i]) + 9) / 10;
			num[i + 1] -= borrow;
			num[i] += borrow * 10;
		}
		else {
			num[i + 1] += num[i] / 10;
			num[i] %= 10;
		}
	}
	//앞에 남은 0 제거
	while (num.size() > 1 && num.back() == 0)
		num.pop_back();
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	int aSize = a.size(), bSize = b.size();

	//a>=b가 되도록 처리
	if (aSize < bSize)
		return karatsuba(b, a);
	//기저 사례 : a 또는 b가 비어있는 경우
	if (aSize == 0 || bSize == 0)
		return vector<int>();
	//기저 사례 : a가 비교적 짧은 경우 O(n^2)의 알고리즘 적용.
	//(karatsuba 알고리즘이 굉장히 큰 수의 연산에서는 O(N^2)보다 훨씬 빠르지만, 복잡하여 입력의 크기가 작은 수의 경우엔 더 느리기 때문)
	if (aSize <= 50)
		return multiply(a, b);
	int half = aSize / 2;

	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end()); // b.size < half인 경우 b1 = 0이 됨.

	//z2 = a1*b1
	vector<int> z2 = karatsuba(a1, b1);

	//z0 = a0*b0
	vector<int> z0 = karatsuba(a0, b0);

	//z1 = {(a0 + a1) * (b0 + b1)} -z0 -z2
	addTo(a0, a1, 0);
	addTo(b0, b1, 0);
	vector<int> z1 = karatsuba(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);

	//a,b가 모두 같은 자릿수일 경우(a = 256자리, b=256자리)
	//ret = z0 + z1*10^half + z2*10(half+half)
	vector<int> ret(z2.size() + half * 2, 0);
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half * 2);

	return ret;
}

void addTo(vector<int>& a, const vector <int>& b, int k) {
	int originalASize = a.size();
	if (a.size() < b.size() + k)
		a.resize(b.size() + k);
	a.push_back(0);

	int aSize = a.size();
	for (int i = originalASize; i < aSize; ++i)
		a[i] = 0;

	int bSize = b.size();

	for (int i = 0; i < bSize; ++i)
		a[i + k] += b[i];

	normalize(a);
}

void subFrom(vector <int>& a, const vector<int>& b) {
	int bSize = b.size();

	for (int i = 0; i < bSize; i++)
		a[i] -= b[i];
	normalize(a);
}

// 책 알고리즘 문제해결전략을 참고 함.
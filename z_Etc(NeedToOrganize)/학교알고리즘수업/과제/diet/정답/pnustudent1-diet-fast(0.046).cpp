#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

struct Food { int P, S, F, M, cost; } food[1 << 20], base;

ifstream inF("diet.inp");
ofstream outF("diet.out");
int i, cnt, pos, addr, mAddr;

int popF() {
	int val = addr & 1 << pos++;
	addr &= ~val;
	return val;
}

void pushF(int val) { addr |= val << --pos; }

int main() {
	inF >> cnt;

	for (i = cnt - 1; i >= 0; i--)
		inF >> food[1 << i].P >> food[1 << i].S >> food[1 << i].F >> food[1 << i].M >> food[1 << i].cost;

	inF >> base.P >> base.S >> base.F >> base.M;
	base.cost = (1 << 31) - 1;

	pos = cnt - 1;
	addr = 1 << pos;

	while (1) {
		Food &now = food[addr];
		int sat = now.P >= base.P && now.S >= base.S && now.F >= base.F && now.M >= base.M,
			cost = now.cost - base.cost;

		if (sat && (cost < 0 || cost == 0 && bitset<20>(addr).count() < bitset<20>(mAddr).count())) {
			mAddr = addr;
			base.cost = now.cost;
		}

		if (!pos) {
			while (popF());
			while (pos <= cnt && !popF());
			if (pos > cnt) break;

			pushF(0);
		}
		else if (cost > 0 || sat) {
			popF(); pushF(0);
		}

		now = food[addr];
		pushF(1);

		Food &fut = food[addr], &add = food[1 << pos];

		fut.P = now.P + add.P;
		fut.S = now.S + add.S;
		fut.F = now.F + add.F;
		fut.M = now.M + add.M;
		fut.cost = now.cost + add.cost;
	}

	for (i = 1; i <= cnt; i++)
		if (mAddr & (1 << cnt - i)) outF << i << " ";
}
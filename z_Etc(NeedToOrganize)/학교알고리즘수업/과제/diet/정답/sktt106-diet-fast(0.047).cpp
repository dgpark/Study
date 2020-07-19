#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

int n;
int food[20][5];
int goal[4], total[4] = {};
int add = 1, price = 0, foodCount = 20, answer = (1 << 20) - 1;

void backtrack(int index, int protein, int carb, int fat, int mineral, int list, int count, int aggregate) {
	bool reached = true;
	int temp[4] = { protein, carb, fat, mineral };
	for (int i = 0; i < 4; i++) {
		if (temp[i] + food[index][i] < goal[i]) {
			reached = false;
			break;
		}
	}

	if (reached) {
		if (aggregate + food[index][4] < price) {
			price = aggregate + food[index][4];
			answer = list + (add << index);
			foodCount = count + 1;
		}
		else if (aggregate + food[index][4] == price) {
			if (count + 1 < foodCount) {
				answer = list + (add << index);
				foodCount = count + 1;
			}
			else if (count + 1 == foodCount) {
				list += (add << index);
				for (int i = 0; i < 20; i++) {
					int a = answer & (add << i);
					int b = list & (add << i);
					if ((a != 0) && (b != 0)) continue;
					else if (a != 0) break;
					else if (b != 0) {
						answer = list;
						break;
					}
				}
			}
		}
		if (index == n - 1) return;
		backtrack(index + 1, protein, carb, fat, mineral, list, count, aggregate);
	}
	else {
		if (index == n - 1) return;
		if (price < aggregate + food[index][4]) {
			backtrack(index + 1, protein, carb, fat, mineral, list, count, aggregate);
		}
		else {
			backtrack(index + 1, protein, carb, fat, mineral, list, count, aggregate);
			backtrack(index + 1, protein + food[index][0], carb + food[index][1], fat + food[index][2], mineral + food[index][3], list + (add << index), count+ 1, aggregate + food[index][4]);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);

	ifstream readFile("diet.inp");

	readFile >> n;
	for (int i = 0; i < n; i++) { 
		readFile >> food[i][0] >> food[i][1] >> food[i][2] >> food[i][3] >> food[i][4];
		for (int j = 0; j < 4; j++) { total[j] += food[i][j]; }
		price += food[i][4];
	}
	readFile >> goal[0] >> goal[1] >> goal[2] >> goal[3];

	readFile.close();

	ofstream writeFile("diet.out");

	for (int i = 0; i < 4; i++) { if (total[i] < goal[i]) { return 0; } }
	for (int i = 0; i < 4; i++) {
		if (total[i] == goal[i]) {
			for (int i = 1; i <= n; i++) { writeFile << i << " "; }
			return 0;
		}
	}

	backtrack(0, 0, 0, 0, 0, 0, 0, 0);
	
	int check = 1;
	for (int i = 0; i < n; i++) {
		if ((answer & check) != 0) writeFile << i + 1 << " ";
		check <<= 1;
	}
	
	writeFile.close();
}
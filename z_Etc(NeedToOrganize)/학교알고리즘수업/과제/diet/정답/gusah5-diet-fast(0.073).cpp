#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int num;
int minCost = 0;
int mat[20][5];
int sel[20] = {0,};
int coverage[4] = {0,};
int currentCover[4] = {0,};
vector<int> list;
void check(int, int);

int main() {
  ifstream read("diet.inp");
  ofstream write("diet.out");

  read >> num;

  // read
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < 5; j++) {
      read >> mat[i][j];
    }
    minCost += mat[i][4];
    list.push_back(i+1);
  }

  for (int i = 0; i < 4; i++) {
    read >> coverage[i];
  }

  check(0, 0);

  for (vector<int>::iterator i = list.begin(); i < list.end(); i++) {
    write << *i << " ";
  }
  write << endl;

  read.close();
  write.close();
}

void check(int index, int cost) {
  if (index >= num) {
    return;
  }
  if (cost >= minCost) {
    return;
  }

  for (int i = index; i < num; i++) {
    currentCover[0] += mat[i][0];
    currentCover[1] += mat[i][1];
    currentCover[2] += mat[i][2];
    currentCover[3] += mat[i][3];
    sel[i]++;
    index++;
    cost += mat[i][4];

    if (currentCover[0] >= coverage[0] &&
        currentCover[1] >= coverage[1] &&
        currentCover[2] >= coverage[2] &&
        currentCover[3] >= coverage[3]
    ) {
//      for (int j = 0; j < num; j++) {
//        if (sel[j] == 1) {
//          cout << j + 1 << " ";
//        }
//      }

//      cout << "  " << cost << " " << minCost << endl;
//      cout << endl;

      if (minCost > cost) {
        minCost = cost;
        list.clear();
        for (int j=0; j < num; j++) {
          if(sel[j] == 1) list.push_back(j+1);
        }
      } else if (minCost == cost) {
        int c = 0;
        for (int j=0; j < num; j++) {
          if(sel[j] == 1) c++;
        }

        if (c < list.size()) {
          list.clear();
          for (int j=0; j < num; j++) {
            if(sel[j] == 1) list.push_back(j+1);
          }
        }
      }
    }
    check(index, cost);

    currentCover[0] -= mat[i][0];
    currentCover[1] -= mat[i][1];
    currentCover[2] -= mat[i][2];
    currentCover[3] -= mat[i][3];
    sel[i]--;
    cost -= mat[i][4];
  }
}
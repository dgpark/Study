#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void swap(long long (*values1)[2], long long (*values2)[2]){
	long long temp[1][2];
	temp[0][0] = values1[0][0];
	temp[0][1] = values1[0][1];
	
	values1[0][0] = values2[0][0];
	values1[0][1] = values2[0][1];
	
	values2[0][0] = temp[0][0];
	values2[0][1] = temp[0][1];
}

//퀵소트 구현
void quickSorting(long long (*values)[2], int left, int right)
{
	int pivot = left;
	int j = pivot;
	int i = left+1;
	
	if(left < right){
		for(; i <= right; i++){
			if(values[i][0] * values[pivot][1] < values[i][1] * values[pivot][0]){
				j++;
				swap(values[j], values[i]);
			}
			else if(values[i][0] * values[pivot][1] == values[i][1] * values[pivot][0]){
				if(values[i][1] < values[pivot][1]){
					j++;
					swap(values[j], values[i]);
				}
			}
		}
		swap(values[left], values[j]);
		pivot = j;
		
		quickSorting(values, left, pivot-1);
		quickSorting(values, pivot+1, right);
	}
	
	 
}
        	
void searching(int num, int search1, int search2, long long (*values)[2]){
	ofstream outStream("two.txt");
	
	outStream << values[search1-1][0] << " / " << values[search1-1][1] << endl;
	outStream << values[search2-1][0] << " / " << values[search2-1][1] << endl;
	
}

void printing(int num, long long (*values)[2]){
	for(int i=0; i<num; i++){
		for(int j=0; j<2; j++){
			cout << values[i][j] << " ";
		}
		cout << endl;
	}
}

long long convert(std::string const & s){
	std::stringstream ss(s);
	long long result;
	ss >> result;
	return result;
}

int main(void)
{ 
	int num, search1, search2; // 10 <= num <= 100,000
	//a = 4294967296; // unsigned long은 4294967295까지. 
	ifstream inStream("3.inp");
	
	inStream >> num >> search1 >> search2;
	
	long long values[num][2]; // *(values[2])가 맞는지 확인. ? (*values)[2] 
	string check;
	
	int j=0;
	for(int i=0; i<num*3; i++){
		inStream >> check;
		if(check != "/"){
			values[i/3][j++] = convert(check);
		}
		if(j==2){ j=0; }
	}
	
	quickSorting(values, 0, num-1);
	cout << values[98998][0] << " " << values[99000][1];
	//searching(num, search1, search2, values);
	
	return 0;
}

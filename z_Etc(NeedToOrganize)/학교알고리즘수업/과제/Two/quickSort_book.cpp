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

void partition(long long (*values)[2] ,int left, int right, int& pivot)
{
	int i,j;
	long long pivotItem[1][2];
	
	pivotItem[0][0] = values[left][0];
	pivotItem[0][1] = values[left][1];
	
	j = left;
	for(i = left+1; i <= right; i++){
		if(values[i][0] * pivotItem[0][1] < pivotItem[0][0] * values[i][1]){
			j++;
			swap(values[i], values[j]);
		}
		else if(values[i][0] * pivotItem[0][1] == pivotItem[0][0] * values[i][1]){
			if(values[i][1] < pivotItem[0][1]){
				j++;
				swap(values[i], values[j]);
			}
		}
	}
	pivot = j;
	swap(values[left], values[pivot]);
}

//퀵소트 구현
void quickSorting(long long (*values)[2], int left, int right)
{
	int pivot;
	
	if(right > left){
		partition(values, left, right, pivot);
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
	searching(num, search1, search2, values);
	
	return 0;
}

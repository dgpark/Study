#include <iostream>
#include <fstream>

using namespace std;

void Sorting(int num, long long (*values)[2]){ // values[][2]도 가능 
	for(int i=0; i<num; i++){
		//if()
		
	}
}

long long searching(){
	
}

void printing(int num, long long (*values)[2]){
	for(int i=0; i<num; i++){
		for(int j=0; j<2; j++){
			cout << values[i][j] << " ";
		}
		cout << endl;
	}
}

int main(void)
{ 
	int num, search1, search2; // 10 <= num <= 100,000
	//a = 4294967296; // unsigned long은 4294967295까지. 
	ifstream inStream("1.inp");
	ofstream outStream("test.txt");
	
	inStream >> num >> search1 >> search2;
	cout << num << search1 << search2 << endl;//
	
	long long values[num][2]; // *(values[2])가 맞는지 확인. ? (*values)[2] 
	string check;
	
	int j=0;
	for(int i=0; i<num*3; i++){
		inStream >> check;
		if(check != "/"){
			values[i/3][j++] = stoll(check);
		}
		if(j==2){ j=0; }
	}
	
	printing(num, values);
	Sorting(num, values);
	
	return 0;
}

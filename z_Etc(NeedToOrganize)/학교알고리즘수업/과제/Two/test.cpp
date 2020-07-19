#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <typeinfo>

using namespace std;

void readText(char* fileName, int &num, int &search1,int &search2, long long **values){
	ifstream inStream("1.inp");
	ofstream outStream("test.txt");
	
	inStream >> num >> search1 >> search2;
	
	//check num
	cout << num << search1 << search2 << endl;//
	string line[num];
	getline(inStream,line[0]);//맨윗줄의 end of line 처 
	
	for(int i=0; i<num; i++){
		getline(inStream,line[i]);
		//check line
		istringstream iss(line[i]);
		string token;
		int j=0;
		
		//token화 하기. /로 분리 -> values[i][0]과 values[i][1]에 저장 
		while(getline(iss, token, ' ')){
			if(token != "/"){
				cout << token << endl;//
				values[i][0] = stoll(token);
			}
			j++;
		}
	}
	
}

/*void compareSort(values){
	inStream >> 
};*/

long long searching(){
	
};

int main(void)
{ 
	int num, search1, search2; // 10 <= num <= 100,000
	long long **values; // *(values[2])가 맞는지 확인. ? (*values)[2] 
	//a = 4294967296; // unsigned long은 4294967295까지. 
	
	readText("1.inp", num, search1, search2, values);
	
	
	return 0;
}

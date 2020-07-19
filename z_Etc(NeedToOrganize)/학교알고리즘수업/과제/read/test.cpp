/*

 <알고리즘 진행 방법>
->  RadixSort -> scan
(scan : ngs[i-1]과 ngs[i]를 비교, 같으면 count++. 다르면 count 종료.
종료시 count가 maxCount보다 많으면 maxCount = count;
종료시 count가 maxCount와 같거나 작으면 pass. 

필요 class
-> read()

필요 함수
-> readInput(), radixSort(), countSort()//radixSort안에 위치, scan()//writeOutput 안에 위치, writeOutput()

필요 변수
->  string ngs, vector<string> array.
int count=0, maxCount=0; 
 
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Read{
private:
	string ngs;
	vector<string> array;
	int count=0, maxCount=0;
public:
	void readInput();
	void radixSort();
	void countSort();	//In radixSort();
	void scan(); 		//In writeOutput();
	void writeOutput();
};

void Read::readInput(){
	ifstream inStream("1.inp");
	int i=0;
	while(!inStream.eof()){
		inStream >> ngs;
		array.push_back(ngs);
	}
	//delete below code When submit.
	cout << array[]
	/*
	int size = array.size();
	
	for(int i=0; i<size; i++){
		cout << array[i] << endl;
	}
	*/
}

int main(void){
	Read r;
	r.readInput();
	
	
	return 0;
}





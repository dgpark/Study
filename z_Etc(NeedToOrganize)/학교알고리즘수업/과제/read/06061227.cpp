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
#include <list>

using namespace std;

class Read{
private:
	string ngs;
	vector<string> array;
	list<string> li;
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
	string test = "abcdd";
	bool d = test[0] == 97;
	bool c = 'a' == 97;
	cout << c << endl;
	cout << d << endl;
	
	/*string alphabet[23];
	alphabet[0] = "right";
	cout << alphabet[test[0] - 97] << endl;*/
	//cout << test[3] - 97 << endl; // 중요 개념!! 
	
	list<string> alphabet[26];
	
	
	
	
	
	
	alphabet[0].push_back("abcd");
	alphabet[0].push_back("efgh");
	
	cout << "!!" << endl;
	cout << alphabet[0].size() << endl;
	cout << alphabet[0].front();
	alphabet[0].pop_front();
	//cout << alphabet[0].front();
	cout << endl;
	
	cout << test.size() << endl;
	cout << endl;
	cout << endl;
	cout << 'ca' - 97;
	
	/*string alphabet[23];
	alphabet[0] = "right";
	cout << alphabet[test[0] - 97] << endl;*/
	//cout << test[3] - 97 << endl; // 중요 개념!! 
	
	
	/*string test = "abcdd";
	const int a = 1;
	cout << a << endl;
	
	string alphabet[10];
	alphabet[1] = "abc"; 
	cout << alphabet[test[0]];
	*/
	return 0;
}





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
	list<string> alphabet[27]; // alphabet26 + 1(for NULL)
	int aCount[27]; //alphabet count. ex) a: 5, b:11, ...
	int count=0, maxCount=0;
public:
	void readInput();
	void radixSort();
	void scan(); 		//In writeOutput();
	void writeOutput();
};

void Read::readInput(){
	ifstream inStream("test.inp");
	int i=0;
	while(!inStream.eof()){
		inStream >> ngs;
		array.push_back(ngs);
	}
	//array.push_back("empty");
	//array.push_back("empty");
	//array.push_back("empty");
	//array.push_back("empty");
	//array.push_back("empty");
	cout << array.size() << endl;
	
	//delete below code When submit.

	/*
	int size = array.size();
	
	for(int i=0; i<size; i++){
		cout << array[i] << endl;
	}
	*/
}

void Read::radixSort(){
	// firste variable of loop
	for(int lineNum=0; lineNum<array.size(); ++lineNum){ // countSort, sNum = string Number, cNum = character Number 
		if(array[lineNum].size()-1 < 49){ // if array size = 5, bound is array[4];
			//cout << "check01" << endl;
			alphabet[26].push_back(array[lineNum]); 
		}
		else{
			//cout << "check02" << endl;
		//	cout << array[lineNum][loc] << endl;
	//		cout << array[lineNum][loc] - 97 << endl;
			alphabet[array[lineNum][49] - 97].push_back(array[lineNum]);
			}
		}
	for(int i=0; i<27; i++){
		aCount[i] = alphabet[i].size();
	}
	cout << "check1" << endl;
	for(int loc=48; loc>0; --loc){ // loc = location of characters in string // 2(lower bound)-1(because it is array) = 1 (loc Num). loc>0 -> until loc == 1 valid
		for(int aList=0; aList<27; aList++){
			for(int i=0; i<aCount[aList]; i++){
				if(alphabet[i].size()-1 < loc){
					alphabet[26].push_back(alphabet[i].front());
					alphabet[i].pop_front();

				}
				else{
					alphabet[(alphabet[i].front())[loc]-97].push_back(alphabet[i].front());
					alphabet[i].pop_front();
				}
			}
		}
	}
	cout << "check2" << endl;
	int temp=0;
	for(int aLoc=0; aLoc<27; aLoc++){
		for(int aList=0; aList < alphabet[aLoc].size(); aList++){
			array[temp++] = alphabet[aLoc].front();
			alphabet[aLoc].pop_front();
		}
	}
	
	cout << "finish" << endl;

/*
	for(int i=0; i<10; ++i){
		cout << array[i] << endl;
	}
*/	
	
}

int main(void){
	Read r;
	r.readInput();
	r.radixSort();
	cout << "right?" << endl;
	
	return 0;
}





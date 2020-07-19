/*

 <�˰��� ���� ���>
->  RadixSort -> scan
(scan : ngs[i-1]�� ngs[i]�� ��, ������ count++. �ٸ��� count ����.
����� count�� maxCount���� ������ maxCount = count;
����� count�� maxCount�� ���ų� ������ pass. 

�ʿ� class
-> read()

�ʿ� �Լ�
-> readInput(), radixSort(), countSort()//radixSort�ȿ� ��ġ, scan()//writeOutput �ȿ� ��ġ, writeOutput()

�ʿ� ����
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





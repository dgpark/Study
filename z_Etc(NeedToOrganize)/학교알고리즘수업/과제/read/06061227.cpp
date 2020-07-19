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
	//cout << test[3] - 97 << endl; // �߿� ����!! 
	
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
	//cout << test[3] - 97 << endl; // �߿� ����!! 
	
	
	/*string test = "abcdd";
	const int a = 1;
	cout << a << endl;
	
	string alphabet[10];
	alphabet[1] = "abc"; 
	cout << alphabet[test[0]];
	*/
	return 0;
}





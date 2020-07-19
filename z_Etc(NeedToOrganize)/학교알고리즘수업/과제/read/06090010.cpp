#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Read{
private:
	string ngs;
	vector<string> array;
	//int aCount[27]; //alphabet count. ex) a: 5, b:11, ...
	//int count=0, maxCount=0;
public:
	void readInput();
	void start();
	void radixSort(vector<string> b, int r);
	size_t getMax(vector<string> arr, int n);
	void countSort(vector<string> a, int size, size_t k);
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
	cout << array.size() << endl;
	
	//delete below code When submit.

	/*
	int size = array.size();
	
	for(int i=0; i<size; i++){
		cout << array[i] << endl;
	}*/
}

void Read::start(){
	radixSort(array, (int)(sizeof(array) / sizeof(array[0])));
}

void Read::radixSort(vector<string> b, int r){
	size_t max = getMax(b,r);
	for(size_t digit = max; digit > 0; digit--){
		countSort(b,r,digit - 1);
	}
	
	
	int size1 = b.size();
	
	for(int i=0; i<size1; i++){
		cout << b[i] << endl;
	}
	
}

size_t Read::getMax(vector<string> arr, int n){
	size_t max = arr[0].size();
	for( int i = 1; i < n; i++){
		if(arr[i].size() > max){
			max = arr[i].size();
		}
	}
	return max;
}

void Read::countSort(vector<string> a, int size, size_t k){
	string *b = NULL; int *c = NULL;
	b = new string[size];
	c = new int[257];
	
	for(int i = 0; i < 257; i++){
		c[i] = 0;
	}
	
	for(int j = 0; j < size; j++){
		c[k < a[j].size() ? (int)(unsigned char)a[j][k]+1 : 0]++;
	}
	
	for(int f = 1; f < 257; f++){
		c[f] += c[f-1];
	}
	
	for(int r = size-1; r >= 0; r-- ){
		b[c[k<a[r].size() ? (int)(unsigned char)a[r][k] + 1 : 0] -1] = a[r];
		c[k < a[r].size() ? (int)(unsigned char)a[r][k] + 1 : 0]--;
	}
	
	for(int l = 0; l < size; l++){
		a[l] = b[l];
	}
	
	delete[] b;
	delete[] c;
}

int main(void){
	Read r;
	r.readInput();
	r.start();
	return 0;
}



#include <iostream>
#include <vector>

using namespace std;

int main(void){
	vector<string> a;
	string b[2];
	a.push_back("abc");
	a.push_back("efg");
	
	b[0] = "abc";
	b[1] = "abc";
	int count = 0;
	if(b[0] == b[1]){
		count++;
	}
	
	cout << count;
	
	string c[2];
	
	c[0] = a[0];
	c[1] = a[1];
	
	cout << c[0] << endl;
 	cout << c[1] << endl;
	
	bool abc = b[0] == b[1];
	cout << abc;
	return 0;
}

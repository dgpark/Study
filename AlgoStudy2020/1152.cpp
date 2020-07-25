#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

int main(void) {
	vector<string> v;
	string sentence;
	getline(cin, sentence);
	if (sentence[0] == ' ') {
		sentence.erase(0, 1);
	}

	if (sentence[sentence.length() - 1] == ' ') {
		sentence.erase(sentence.length() - 1, 0);
	}

	istringstream ss(sentence);
	string stringBuffer;


	while (getline(ss, stringBuffer, ' '))
	{
		v.push_back(stringBuffer);
	}

	printf("%d", v.size());

	return 0;
}
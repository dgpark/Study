#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(void) {

	string word;
	map<char, int> count;

	for (int i = 0; i < 26; i++) {
		count[char(97 + i)] = 0;
	}

	getline(cin, word);

	for (int i = 0; i < word.length(); i++) {
		word[i] = tolower(word[i]);
		count[word[i]]++;
	}

	int max = 0, index = 0;
	bool duplicate = false;
	for (int i = 0; i < 26; i++) {
		if (count[char(97 + i)] > max) {
			max = count[char(97 + i)];
			index = 97 + i;
			duplicate = false;
		}
		else if (count[char(97 + i)] == max) {
			duplicate = true;
		}
	}

	duplicate == false ? printf("%c", toupper(char(index))) : printf("?");

	return 0;
}

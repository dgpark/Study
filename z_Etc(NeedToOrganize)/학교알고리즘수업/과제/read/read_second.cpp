#include <iostream>
#include <fstream>

using namespace std;

size_t getMax(string array[], int num){
    size_t max = array[0].size();
    for (int i = 1; i < num; i++){
        if (array[i].size()>max)
            max = array[i].size();
    }
    return max;
}

void countSort(string array[], int size1, size_t loc){
    string *array2 = NULL; int *count = NULL;
    array2 = new string[size1];
    count = new int[27];

    for (int i = 0; i <27; i++){
        count[i] = 0;
    }
    for (int j = 0; j <size1; j++){   
        count[loc < array[j].size() ? (int)(unsigned char)array[j][loc] -96 : 0]++;
    }

    for (int f = 1; f <27; f++){
        count[f] += count[f - 1];
    }

    for (int r = size1 - 1; r >= 0; r--){
        array2[count[loc < array[r].size() ? (int)(unsigned char)array[r][loc] -96 : 0] - 1] = array[r];
        count[loc < array[r].size() ? (int)(unsigned char)array[r][loc] -96 : 0]--;
    }

    for (int l = 0; l < size1; l++){
        array[l] = array2[l];
    }

    delete[] array2;
    delete[] count;
}


void radixSort(string array[], int size1){
    size_t max = getMax(array, size1);
    
    for (size_t loc = max; loc > 0; loc--){
        countSort(array, size1, loc-1);
    }
    
}

void scan(string array[], int size1){
	ofstream outStream("read.out");

	int count=0;
	int maxCount=0;
	int index = 0;
	for(int i=0; i<size1-1; i++){
		if(array[i] == array[i+1]){
			count++;
		}
		else{
			if(count > maxCount){
				maxCount = count;
				index = i-1;
			}
			count = 0;
		}
	}
	outStream << array[index];
}

int main(void) {
    ifstream inStream("read.inp");    
	string line;
	int size;
	//count size
	while (getline(inStream, line))
        ++size;
	string data[size];	
	ifstream inStream2("read.inp");
	// make string array
	for(int i=0; i<size; i++){
		inStream2 >> data[i];
	}
	
    radixSort(data, (int)(sizeof(data) / sizeof(data[0])));
	scan(data, (int)(sizeof(data) / sizeof(data[0])));
    
    return 0;
}

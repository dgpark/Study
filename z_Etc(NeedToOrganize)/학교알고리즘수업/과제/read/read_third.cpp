#include <iostream>
#include <fstream>
#include <vector>

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
    count = new int[5];

    for (int i = 0; i <5; i++){
        count[i] = 0;
    }
    for (int j = 0; j <size1; j++){   
    	if(loc < array[j].size()){
    		if(array[j][loc] == 'a'){
    			count[1]++;
			}
			else if(array[j][loc] == 'c'){
				count[2]++;
			}
			else if(array[j][loc] == 'g'){
				count[3]++;
			}
			else{
				count[4]++;
			}
		}
		else{
			count[0]++;
		}
    }

    for (int temp = 1; temp <5; temp++){
        count[temp] += count[temp - 1];
    }

    for (int temp = size1 - 1; temp >= 0; temp--){
    	if(loc < array[temp].size()){
    		if(array[temp][loc] == 'a'){
    			array2[count[1]-1] = array[temp];
    			count[1]--;
			}
			else if(array[temp][loc] == 'c'){
				array2[count[2]-1] = array[temp];
				count[2]--;
			}
			else if(array[temp][loc] == 'g'){
				array2[count[3]-1] = array[temp];
				count[3]--;
			}
			else{
				array2[count[4]-1] = array[temp];
				count[4]--;
			}
		}
		else{
			array2[count[0]-1] = array[temp];
			count[0]--;
		}
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
    ifstream inStream("2.inp");    
	string line;
	vector<string> array;
	int size;
	//count size
	while (getline(inStream, line)){
		array.push_back(line);
	}
	size = array.size();
	string data[size];
	// make string array
	for(int i=0; i<size; i++){
		data[i] = array[i];
	}
	
    radixSort(data, (int)(sizeof(data) / sizeof(data[0])));
	scan(data, (int)(sizeof(data) / sizeof(data[0])));
    
    return 0;
}

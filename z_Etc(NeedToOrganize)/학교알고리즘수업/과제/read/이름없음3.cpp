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
    count = new int[17];

    for (int i = 0; i <5; i++){
        count[i] = 0;
    }
    for (int j = 0; j <size1; j++){   
    	if(loc < array[j].size()){
    		if(array[j][loc-1] == 'a' && array[j][loc] == 'a'){count[1]++;}
			else if(array[j][loc-1] == 'a' && array[j][loc] == 'c'){count[2]++;}
			else if(array[j][loc-1] == 'a' && array[j][loc] == 'g'){count[3]++;}
			else if(array[j][loc-1] == 'a' && array[j][loc] == 't'){count[4]++;}
			else if(array[j][loc-1] == 'c' && array[j][loc] == 'a'){count[5]++;}
			else if(array[j][loc-1] == 'c' && array[j][loc] == 'c'){count[6]++;}
			else if(array[j][loc-1] == 'c' && array[j][loc] == 'g'){count[7]++;}
			else if(array[j][loc-1] == 'c' && array[j][loc] == 't'){count[8]++;}
			else if(array[j][loc-1] == 'g' && array[j][loc] == 'a'){count[9]++;}
			else if(array[j][loc-1] == 'g' && array[j][loc] == 'c'){count[10]++;}
			else if(array[j][loc-1] == 'g' && array[j][loc] == 'g'){count[11]++;}
			else if(array[j][loc-1] == 'g' && array[j][loc] == 't'){count[12]++;}
			else if(array[j][loc-1] == 't' && array[j][loc] == 'a'){count[13]++;}
			else if(array[j][loc-1] == 't' && array[j][loc] == 'c'){count[14]++;}
			else if(array[j][loc-1] == 't' && array[j][loc] == 'g'){count[15]++;}
			else if(array[j][loc-1] == 't' && array[j][loc] == 't'){count[16]++;}
			
		}
		else{
			count[0]++;
		}
    }

    for (int temp = 1; temp <16; temp++){
        count[temp] += count[temp - 1];
    }

    for (int temp = size1 - 1; temp >= 0; temp--){
    	if(loc < array[temp].size()){
    		if(array[temp][loc-1] == 'a' && array[temp][loc] == 'a'){
    			array2[count[1]-1] = array[temp];
    			count[1]--;
			}
			else if(array[temp][loc-1] == 'a' && array[temp][loc] == 'c'){
				array2[count[2]-1] = array[temp];
				count[2]--;
			}
			else if(array[temp][loc-1] == 'a' && array[temp][loc] == 'g'){
				array2[count[3]-1] = array[temp];
				count[3]--;
			}
			else if(array[temp][loc-1] == 'a' && array[temp][loc] == 't'){
				array2[count[4]-1] = array[temp];
				count[4]--;
			}
			if(array[temp][loc-1] == 'c' && array[temp][loc] == 'a'){
    			array2[count[5]-1] = array[temp];
    			count[5]--;
			}
			else if(array[temp][loc-1] == 'c' && array[temp][loc] == 'c'){
				array2[count[6]-1] = array[temp];
				count[6]--;
			}
			else if(array[temp][loc-1] == 'c' && array[temp][loc] == 'g'){
				array2[count[7]-1] = array[temp];
				count[7]--;
			}
			else if(array[temp][loc-1] == 'c' && array[temp][loc] == 't'){
				array2[count[8]-1] = array[temp];
				count[8]--;
			}
			if(array[temp][loc-1] == 'g' && array[temp][loc] == 'a'){
    			array2[count[9]-1] = array[temp];
    			count[9]--;
			}
			else if(array[temp][loc-1] == 'g' && array[temp][loc] == 'c'){
				array2[count[10]-1] = array[temp];
				count[10]--;
			}
			else if(array[temp][loc-1] == 'g' && array[temp][loc] == 'g'){
				array2[count[11]-1] = array[temp];
				count[11]--;
			}
			else if(array[temp][loc-1] == 'g' && array[temp][loc] == 't'){
				array2[count[12]-1] = array[temp];
				count[12]--;
			}
			if(array[temp][loc-1] == 't' && array[temp][loc] == 'a'){
    			array2[count[13]-1] = array[temp];
    			count[13]--;
			}
			else if(array[temp][loc-1] == 't' && array[temp][loc] == 'c'){
				array2[count[14]-1] = array[temp];
				count[14]--;
			}
			else if(array[temp][loc-1] == 't' && array[temp][loc] == 'g'){
				array2[count[15]-1] = array[temp];
				count[15]--;
			}
			else if(array[temp][loc-1] == 't' && array[temp][loc] == 't'){
				array2[count[16]-1] = array[temp];
				count[16]--;
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
    
    for (size_t loc = max; loc > 1; loc--){
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

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//퀵소트 구현
void quickSorting(long long (*values)[2], int left, int right)
{
	long long pivot[1][2];
	long long temp[1][2];
	int fixLeft, fixRight;
	fixLeft = left;
	fixRight = right;
    pivot[0][0] = values[left][0];
    pivot[0][1] = values[left][1];
	
	
	while(left < right){
	//do while문경우 --연산먼저하므로 index를 1초과한값으로 시작

        while((values[right][0] * pivot[0][1] >= pivot[0][0] * values[right][1]) && (left < right)){
        	right--;
        }
		if(left != right){
			temp[0][0] = values[left][0];
			temp[0][1] = values[left][1];
			
			values[left][0] = values[right][0];
			values[left][1] = values[right][1];
			
			values[right][0] = temp[0][0];
			values[right][1] = temp[0][1];
		}
		
		while((values[left][0] * pivot[0][1] <= pivot[0][0] * values[left][1])){
			left++;
		}
		if(left != right){
			temp[0][0] = values[right][0];
			temp[0][1] = values[right][1];
			
			values[right][0] = values[left][0];
			values[right][1] = values[left][1];
			
			values[left][0] = temp[0][0];
			values[left][1] = temp[0][1];
		}
	} // end of while
	
	if(values[left][0] * pivot[0][1] < pivot[0][0] * values[left][1]){
		temp[0][0] = pivot[0][0];
		temp[0][1] = pviot[0][1];
		
		pivot[0][0] = values[left-1][0];
		pivot[0][1] = values[left-1][1];
		values
		
		values[left-1][0] = temp[0][0];
		values[left-1][1] = temp[0][1];
	}
	else if(values[left][0] * pivot[0][1] > pivot[0][0] * values[left][1]){
		temp[0][0] = pivot[0][0];
		temp[0][1] = pviot[0][1];
		
		pivot[0][0] = values[right+1][0];
		pivot[0][1] = values[right+1][1];
		
		values[right+1][0] = temp[0][0];
		values[right+1][1] = temp[0][1];
	}
	else{ //같을때 
		//나중에 추가  
	}
	left = fixLeft;
	right = fixRight;
	
	if(left < )
	 
}
        	
        /*	cout << "1" << endl;
          	do
            i++;
            while(values[i][0] * pivot[0][1] > values[i][1] * pivot[0][0]); //오름차순을 원할경우 >를 <로
			do
            j--;
            while(values[j][0] * pivot[0][1] < values[j][1] * pivot[0][0]); //오름차순을 원할경우 <를 >로
            if(i<j){                        
                temp1[0][0] = values[i][0];
				temp1[0][1] = values[i][1];
				
			   	values[i][0] = values[j][0];
				values[i][1] = values[j][1];
				
				values[j][0] = temp1[0][0];
				values[j][1] = temp1[0][1];
            }
            else //찾은 두소요가 겹치거나 엇갈리면 한바퀴 끝
            	break;
        }
        cout << "2" << endl;
               // j위치 요소를 기준이 되었던 pivot 과 Swap
        temp1[0][0] = values[j][0];
		temp1[0][1] = values[j][1];
				
		values[j][0] = values[left][0];
		values[j][1] = values[left][1];
				
		values[left][0] = temp1[0][0];
		values[left][1] = temp1[0][1];
        
		//Swap ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
        
		quick_sort(values, left, j-1); // 가운데가 된 pivot을 중심으로 왼쪽 영역 재귀
        quick_sort(values, j+1, right);// 가운데가 된 pivot을 중심으로 오른쪽 영역 재귀
    }
}

/*void Sorting(int num, long long (*values)[2]){ // values[][2]도 가능 
	long long temp[1][2];
	int j = 0;
	for(int i=0; i<num; i++){
		for(int k=i+1; k<num; k++){
			if(values[i][0] * values[k][1] == values[i][1] * values[k][0]){
				if(values[i][1] > values[k][1]){
					temp[0][0] = values[i][0];
					temp[0][1] = values[i][1];
				
					values[i][0] = values[k][0];
					values[i][1] = values[k][1];
				
					values[k][0] = temp[0][0];
					values[k][1] = temp[0][1];
				}
			}
			else if(values[i][0] * values[k][1] > values[i][1] * values[k][0] ){
				temp[0][0] = values[i][0];
				temp[0][1] = values[i][1];
				
				values[i][0] = values[k][0];
				values[i][1] = values[k][1];
				
				values[k][0] = temp[0][0];
				values[k][1] = temp[0][1];
			}
		}
	}
}*/

void searching(int num, int search1, int search2, long long (*values)[2]){
	ofstream outStream("two.out");
	
	outStream << values[search1-1][0] << " / " << values[search1-1][1] << endl;
	outStream << values[search2-1][0] << " / " << values[search2-1][1] << endl;
	
}

void printing(int num, long long (*values)[2]){
	for(int i=0; i<num; i++){
		for(int j=0; j<2; j++){
			cout << values[i][j] << " ";
		}
		cout << endl;
	}
}

long long convert(std::string const & s){
	std::stringstream ss(s);
	long long result;
	ss >> result;
	return result;
}

int main(void)
{ 
	int num, search1, search2; // 10 <= num <= 100,000
	//a = 4294967296; // unsigned long은 4294967295까지. 
	ifstream inStream("1.inp");
	
	inStream >> num >> search1 >> search2;
	
	long long values[num][2]; // *(values[2])가 맞는지 확인. ? (*values)[2] 
	string check;
	
	int j=0;
	for(int i=0; i<num*3; i++){
		inStream >> check;
		if(check != "/"){
			values[i/3][j++] = convert(check);
		}
		if(j==2){ j=0; }
	}
	
	//Sorting(num, values);	
	quickSorting(values, 0, num-1); 
	//searching(num, search1, search2, values);
	printing(num, values);
	return 0;
}

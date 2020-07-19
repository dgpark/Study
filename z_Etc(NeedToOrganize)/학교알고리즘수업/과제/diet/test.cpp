#include <iostream>
#include <fstream>

using namespace std;

class Diet{
private:
	int num;
	int **gred;
	int goal[4] = {0};
	int find[5] = {0};
	int C[20] = {-1}; //Saved Combination of Gredient. 
public:
	void readInput();
	int getNum();
	void check(int n);
};

void Diet::readInput(){
	ifstream inStream("1.inp");
	inStream >> num;
	
	gred = new int *[num];
	for(int i=0; i<num; i++){
		gred[i] = new int [5];
		for(int j=0; j<5; j++){
			inStream >> gred[i][j];
			cout << gred[i][j] << " ";
		}
		cout << endl;
	}
	
	for(int i=0; i<4; i++){
		inStream >> goal[i];
		cout << goal[i] << " ";
	}
}

int Diet::getNum(){
	return num;
}

void Diet::check(int n){
	int x[n];
	
	for(int i=0; i<n; i++){
		x[i] = i;
		cout << x[i];// Container to get a Combination
	}
	
	while(n>0){
		for(int i=0; i<num; i++){
			for(int j=0; j<5; j++){
				
			}
		}
		
		if(x[0] == num-(n+1)){
			break;
		}
	}
}


int main(void)
{	
	Diet d;
	d.readInput();
	
	d.check(5);
	/*for(int i=0; i<d.getNum(); i++){
		check(i);
	}
	*/
	
	return 0;
}


//



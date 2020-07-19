#include <iostream>
#include <fstream>

using namespace std;

class GraphStore{
	int numOfNode[4];
	int **connectedEdge;
public:
	void store();
	
	void swap(int *connectedEdge1, int*connectedEdge2);
	void partition(int *connectedEdge, int left,int right, int& pivot);
	void quickSorting(int *connectedEdge, int left, int right);
	
	void check();
	
	void printing();
	
	GraphStore(){
		for(int i=0; i<4; ++i){
			numOfNode[i] = 0;
		}
		connectedEdge = NULL;
	}
	~GraphStore(){
		delete[] connectedEdge;
		connectedEdge=NULL;
	}
};

void GraphStore::store(){
	ifstream inStream("3.inp");	
	connectedEdge = new int*[4];
	
	for(int i=0; i<4; ++i){
		inStream >> numOfNode[i];
		connectedEdge[i] = new int[numOfNode[i]];
		for(int n=0; n<numOfNode[i]; ++n){
			inStream >> connectedEdge[i][n];
		}
		quickSorting(connectedEdge[i],0,numOfNode[i]-1);
	}
}

void GraphStore::swap(int *connectedEdge1, int *connectedEdge2){
	int temp;
	temp = *connectedEdge1;
	*connectedEdge1 = *connectedEdge2;
	*connectedEdge2 = temp;
}

void GraphStore::partition(int *connectedEdge,int left, int right, int& pivot){
	int i,j;
	int pivotItem;
	
	pivotItem = connectedEdge[left];
	j = left;
	for(i = left+1; i <= right; ++i){
		if( connectedEdge[i] > pivotItem){
			j++;
			swap(&connectedEdge[i], &connectedEdge[j]);
		}
	}
	pivot = j;
	swap(&connectedEdge[left], &connectedEdge[pivot]);
}


void GraphStore::quickSorting(int *connectedEdge, int left, int right){
	int pivot;
	
	if(right > left){
		partition(connectedEdge, left, right, pivot);
		quickSorting(connectedEdge, left, pivot-1);
		quickSorting(connectedEdge, pivot+1, right);
	}
}

void GraphStore::printing(){
	for(int i=0; i<4; ++i){
		for(int j=0; j<numOfNode[i]; ++j){
			cout << connectedEdge[i][j] << " ";
		}
		cout << endl;
	}
}

void GraphStore::check(){
	ofstream outStream("friend.out");
	int temp, minus, bk;
	bk=0;
	
	for(int i=0; i<4; ++i){
		for(int j=0; j<numOfNode[i]; ++j){
			temp = connectedEdge[i][j];
			minus = temp;
			if( temp > numOfNode[i]-(j+1)){
				connectedEdge[i][numOfNode[i]-1] = -1;
				cout << "!!!" << endl;
				break;
			}
			else if(connectedEdge[i][j] > 0 && j != numOfNode[i]-1){
				connectedEdge[i][j] = 0;
				if(temp-1 == 0){
					for(int k=j+1; k<(j+2)+(temp-1); ++k){
						if(connectedEdge[i][k] > 0){
							--connectedEdge[i][k];
							--minus;
							cout << "a" << connectedEdge[i][k] << " ";
						}
						else{
							for(int m=k+1; m<numOfNode[i]; ++m){
								if(connectedEdge[i][m]>0){
									--connectedEdge[i][m];
									--minus;
									cout << "fixed!" << connectedEdge[i][m+1] << " ";
									k=m;
									if(minus == 0){
										break;
									}
								}
								else if(m==numOfNode[i]-1 && minus >0){
									cout << "false" << endl;
									connectedEdge[i][numOfNode[i]-1] = -1;
									bk = -1;
									break;
								}
							}
						}
						if(bk == -1) {
							break;
						}
					}
				}
				else{
					for(int k=j+1; k<(j+2)+(temp-1); ++k){
						if(connectedEdge[i][k] > 0){
							--connectedEdge[i][k];
							--minus;
							cout << "a" << connectedEdge[i][k] <<" ";
						}
						else{
							for(int m=k+1; m<numOfNode[i]; ++m){
								if(connectedEdge[i][m]>0){
									--connectedEdge[i][m];
									--minus;
									cout << "fixed!!" << connectedEdge[i][m+1] << " ";
									k=m;
									if(minus == 0){
										break;
									}
								}
								else if(m==numOfNode[i]-1 && minus >0){
									cout << "false" << endl;
									connectedEdge[i][numOfNode[i]-1] = -1;
									bk = -1;
									break;
								}
							}
						}
						if(bk == -1) {
							break;
						}
					}
				}
				cout << endl;
			}
			else if(connectedEdge[i][j] < 0 || connectedEdge[i][numOfNode[i]-1] < 0){
				connectedEdge[i][numOfNode[i]-1] = -1;
				break;
			}
			else if(j == numOfNode[i]-1){
				cout << "last element" << connectedEdge[i][j]<< endl;
			}
			else{
				cout << "pass 0" << endl;
			}
			if(bk == -1) {
				bk=0;
				break;
			}
		}//end of inner for loop
		
		if(connectedEdge[i][numOfNode[i]-1] == 0){
			cout << "yes" << endl;
			outStream << "yes" << endl;
		}
		else{
			cout << "no" << endl;
			outStream << "no" << endl;
		}
		cout << endl;
	}
}

int main(void)
{
	GraphStore g1;
	g1.store();
	g1.check();
	
	return 0;
}

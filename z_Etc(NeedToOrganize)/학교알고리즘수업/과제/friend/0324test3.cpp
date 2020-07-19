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
	ifstream inStream("1.inp");	
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

int main(void)
{
	GraphStore g1;
	g1.store();
	g1.printing();
//	for(int i=0; i<4; ++i){
//		GraphStore g1;
//		g1.store();
//		g1.quickSorting();
//		g1.Check();
//	}
	
	return 0;
}

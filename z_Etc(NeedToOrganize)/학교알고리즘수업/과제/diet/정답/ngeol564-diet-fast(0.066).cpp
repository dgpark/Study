#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct {
int P,S,F,M,R;
}I;

int N,M,*sel,f[4];
vector<int> result;
I s,*t;

void Dfs(int count, int sum){
    if(sum >= M) return;
    if(count >= N) return;
    for (int i=count; i < N; i++){
        s.P+=t[i].P; s.S+=t[i].S; s.F+=t[i].F; s.M+=t[i].M;
        sel[i]++;count++;sum+=t[i].R;

        if(s.P>=f[0]&&s.S>=f[1]&&s.F>=f[2]&&s.M>=f[3]){
            if(sum<M){
                M = sum; result.clear();
                for(int j=0;j<N;j++) {
                    if(sel[j]==1) result.push_back(j+1);
                }
            }
            else if(sum==M){
                int c=0;
                for(int j=0;j<N;j++) {
                    if(sel[j]==1) {
                        c++;
                    }
                }
                if(c<result.size()){
                    result.clear();
                    for(int j=0;j<N;j++) {
                        if(sel[j]==1) result.push_back(j+1);
                    }
                }
            }
        }
        Dfs(count, sum);

        s.P-=t[i].P; s.S-=t[i].S; s.F-=t[i].F; s.M-=t[i].M;
        sel[i]--;sum-=t[i].R;
    }
}

int main()
{
    ifstream n("diet.inp");
    ofstream u("diet.out");

    int i;s.P=s.S=s.F=s.M=0;

    n>>N;

    sel=new int[N];t=new I[N];

    for(i=0;i<N;i++){
        n>>t[i].P>>t[i].S>>t[i].F>>t[i].M>>t[i].R;
        M+=t[i].R;sel[i]=0;
        result.push_back(i+1);
    }

    n>>f[0]>>f[1]>>f[2]>>f[3];

    Dfs(0,0);

    for(i=0;i<result.size()-1;i++) u<<result[i]<<" ";
    u<<result[result.size()-1];

    return 0;
}
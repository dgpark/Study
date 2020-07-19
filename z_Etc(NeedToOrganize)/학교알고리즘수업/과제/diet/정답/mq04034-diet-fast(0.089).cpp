#include <stdio.h>

int maxP,maxS,maxF,maxM;
int minPri,path,mindeep;

int cnt;
int *node;
int ll(int P,int S,int F,int M,int Pri,int,int);
int rr(int P,int S,int F,int M,int Pri,int deep,int num){
    deep++;
    num = num << 1;
    if(deep < cnt+1){
        ll(P,S,F,M,Pri,deep,num);
        rr(P,S,F,M,Pri,deep,num);
    }
    return 0;
}
int ll(int P,int S,int F,int M,int Pri,int deep,int num){
    P +=  *(node + 0 + 5 * (deep - 1));
    S +=  *(node + 1 + 5 * (deep - 1));
    F +=  *(node + 2 + 5 * (deep - 1));
    M +=  *(node + 3 + 5 * (deep - 1));
    Pri +=  *(node + 4 + 5 * (deep - 1));
    deep++;
    num = (num<<1)+1;
    if(P>=maxP && S >=maxS && F >=maxF && M>=maxM){
        if(Pri < minPri || minPri == -1) {
            minPri = Pri;
            path = num;
            mindeep = deep;
        }
        else if(Pri == minPri){
            int mincn = 0;
            int nowcn = 0;
            for(int k=0;k<mindeep;k++){
                mincn +=(path>>k)&1;
            }
            for(int k=0;k<deep;k++){
                nowcn +=(num>>k)&1;
            }
            if(mincn > nowcn){
                minPri = Pri;
                path = num;
                mindeep = deep;
            }
        }
        return 0;
    }
    if(deep<cnt+1){
        ll(P,S,F,M,Pri,deep,num);
        rr(P,S,F,M,Pri,deep,num);
    }
    return 0;
}
int main(){
    minPri = -1;
    FILE *fs = fopen("diet.inp","r"),*fout = fopen("diet.out","w");
    fscanf(fs,"%d",&cnt);
    node = new int[cnt*5];
    for(int k=0;k<cnt*5;k++)
        fscanf(fs,"%d",node+k);
    fscanf(fs,"%d",&maxP);
    fscanf(fs,"%d",&maxS);
    fscanf(fs,"%d",&maxF);
    fscanf(fs,"%d",&maxM);
    ll(0,0,0,0,0,1,0);
    rr(0,0,0,0,0,1,0);

    int lisss[21];
    int ccccc= 0;
    for(int k=0;k<mindeep;k++){
        if((path>>k)&1 == 1){
            lisss[ccccc] = mindeep-1-k;
            ccccc++;
        }
    }
    for(int k=0;k<ccccc;k++){
        fprintf(fout,"%d ",lisss[ccccc-1-k]);
    }
    return 0;
}
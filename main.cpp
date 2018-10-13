#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <list>
#include <algorithm>
using namespace std;
int flag=0;

struct nod{
    int x,y,cost;
};
int tata[100]={0}, h[100]={0};

int cmp(nod a, nod b){
    return b.cost-a.cost;
}

void ordoneaza(vector<nod> &v){
    for(int i=0;i<v.size()-1;i++)
        for(int j=i+1;j<v.size();j++)
            if(v[i].cost>v[j].cost)
                swap(v[i],v[j]);
}

void initializeaza(int *tata, int *h,int n){
    for(int i=0;i<=n;i++)
        tata[i]=h[i]=0;
}

int reprezentant(int u){
    if(tata[u]==0)
        return u;
    tata[u]=reprezentant(tata[u]);
    return tata[u];
}

void reuneste(int u, int v){
    int ru,rv;
    ru=reprezentant(u);
    rv=reprezentant(v);
    if(h[ru]>h[rv])
        tata[rv]=ru;
    else {
        tata[ru]=rv;
        if(h[rv]==h[ru])
            h[rv]++;
    }
}

void kruskal(vector<nod> &muchii_apcm,int n,vector<nod> &v){
    int exi, exf,flag=0;
    //sort(v.begin(),v.end(),cmp);
        for(int i=0;i<v.size();i++){
            exi=v[i].x;
            exf=v[i].y;
            cout<<exi<<" "<<exf<<endl;
            if(reprezentant(exi)!=reprezentant(exf)){
                muchii_apcm.push_back(v[i]);
                flag++;
                reuneste(exi,exf);
                if(flag==n-1)
                    break;
            }
    }
}

int main()
{
    ifstream fin("kruskal.in");
    int n,m,exi,exf,pondere;
    fin>>n>>m;
    vector<nod> v;
    vector<nod> muchii_apcm;
    struct nod q;
    for(int i=0;i<m;i++){
        fin>>exi>>exf>>pondere;
        q.x=exi;
        q.y=exf;
        q.cost=pondere;
        v.push_back(q);
    }
    fin.close();

   ordoneaza(v);

    kruskal(muchii_apcm,n,v);

    if(muchii_apcm.size()!=n-1){
        cout<<"Nu se poate crea un apcm."<<endl;
        return 0;
    }
    int cost=0;
    ofstream g("kruskal.out");

    for(int i=0;i<muchii_apcm.size();i++){
        g<<"("<<muchii_apcm[i].x<<","<<muchii_apcm[i].y<<") cu costul "<<muchii_apcm[i].cost<<endl;
        cost+=muchii_apcm[i].cost;
    }

    g<<"Cost total "<<cost;
    g.close();

    return 0;
}

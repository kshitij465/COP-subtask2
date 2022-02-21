#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include <vector>
#include <chrono>
#include <iostream>
using namespace std;


struct ksh
{   vector<vector<float> >* matrix;
    vector<vector<float> >* weight;
    vector<vector<float> >* bias;
    vector<vector<float> >* ans;    
    int l;
    int r;

};

void* rowmult(void* arg){
    struct ksh* lmao = (struct ksh *) arg;
    int l=lmao->l;
    int r=lmao->r;
    for(int i=l;i<=r;i++){
        for(int j=0;j<(*(lmao->bias))[0].size();j++){
            for(int k=0;k<(*(lmao->weight)).size();k++){
                (*(lmao->ans))[i][j]+=((*(lmao->matrix))[i][k]*(*(lmao->weight))[k][j]);
            }
            (*(lmao->ans))[i][j]+=(*(lmao->bias))[i][j];
        }
    }
    return NULL;
}
vector<vector<float>> mult_matrix_pthread(vector<vector<float>> matrix,vector<vector<float>> weight,vector<vector<float>> bias){
    int thr=8;
    int perthread=matrix.size()/thr;
    int extra=matrix.size()%thr;
    int maxindex=0;
    vector<vector<float>> ans(bias.size(),vector<float>(bias[0].size(),0.0));
    struct ksh strr[thr];
    pthread_t threads[thr];
    auto start_timer = chrono::high_resolution_clock::now();
    for(int i=0;i<thr;i++){
        int l=maxindex;
        int r=maxindex+perthread-1;
        strr[i].l=l;
        strr[i].ans=&ans;
        if(i+1<=extra){r++;}
        strr[i].r=r;
        // cout<<l<<" "<<r<<"\n";
        strr[i].matrix=&matrix;
        strr[i].weight=&weight;
        strr[i].bias=&bias;
        maxindex=r+1;
        // cout<<l<<" "<<r<<"\n"; 
        
        pthread_create(&threads[i], NULL,rowmult,&strr[i]);
    }

    for(int i=0;i<thr;i++){pthread_join(threads[i], NULL);}
    auto stop_timer = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop_timer - start_timer);
    cout << "Time taken by pthread mult : " << ((long double)duration.count())/((long double) 1e9) <<"s "<< endl;
    return ans;

}
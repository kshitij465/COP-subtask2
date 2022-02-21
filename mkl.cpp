#include "/usr/include/mkl/mkl.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include <iostream>
using namespace std;

vector<vector<float>> mult_matrix_mkl(vector<vector<float>> matrix,vector<vector<float>> weight,vector<vector<float>> bias){
    float *mat,*wei,*bia;
    mat=(float *)malloc(matrix.size()*matrix[0].size()*sizeof(float));
    wei=(float *)malloc(weight.size()*weight[0].size()*sizeof(float));
    bia=(float *)malloc(bias.size()*bias[0].size()*sizeof(float));
    int index=0;
    for(int i=0;i<matrix.size();i++){
        for(int j=0;j<matrix[0].size();j++){
            mat[index]=matrix[i][j];
            index++;
        }
    }
    index=0;
    for(int i=0;i<weight.size();i++){
            for(int j=0;j<weight[0].size();j++){
                wei[index]=weight[i][j];
                index++;
            }
        }
    
    index=0;
    for(int i=0;i<bias.size();i++){
            for(int j=0;j<bias[0].size();j++){
                bia[index]=bias[i][j];
                index++;
            }
    }
    
    float a=1;
    auto start_timer = chrono::high_resolution_clock::now();
    cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,
        matrix.size(),bias[0].size(),weight.size(),a,mat,matrix.size(),
        wei,weight.size(),a,bia,bias.size());
    auto stop_timer = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop_timer - start_timer);
    cout << "Time taken by mkl mult : " << ((long double)duration.count())/((long double) 1e9) <<"s "<< endl;
    vector<vector<float> > ans(bias.size(), vector<float>(bias[0].size(),0.0));
    index=0;
    for(int i=0;i<bias.size();i++){
            for(int j=0;j<bias[0].size();j++){
                ans[i][j]=bia[index];
                index++;
            }
    }
    return(ans);

}
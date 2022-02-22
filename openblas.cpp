#include "/usr/include/x86_64-linux-gnu/openblas-pthread/cblas.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include<chrono>
using namespace std;

vector<vector<float>> mult_matrix_openblas(vector<vector<float>> matrix,vector<vector<float>> weight,vector<vector<float>> bias){
    /* memmory allocation for matrices */
    float *mat,*wei,*bia;
    mat=(float *)malloc(matrix.size()*matrix[0].size()*sizeof(float));
    wei=(float *)malloc(weight.size()*weight[0].size()*sizeof(float));
    bia=(float *)malloc(bias.size()*bias[0].size()*sizeof(float));

    /* copying data from matrices to vectors */
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
    int m = matrix.size();
    int n = bias[0].size();
    int k = weight.size();

    /* calculating FC using openblas */
    cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,
        m,n,k,a,mat,k,wei,n,a,bia,n);
    vector<vector<float> > ans(bias.size(), vector<float>(bias[0].size(),0.0));
    
    /* copying data from vector to output matrix */
    index=0;
    for(int i=0;i<bias.size();i++){
            for(int j=0;j<bias[0].size();j++){
                ans[i][j]=bia[index];
                index++;
            }
    }
    return(ans);
}
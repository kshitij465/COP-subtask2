#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include<string>
#include<math.h>
#include<chrono>

using namespace std;

vector<vector<float>> mult_matrix_mkl(vector<vector<float>> matrix,vector<vector<float>> weight,vector<vector<float>> bias);

vector<vector<float>> mult_matrix_openblas(vector<vector<float>> matrix,vector<vector<float>> weight,vector<vector<float>> bias);

vector<vector<float>> mult_matrix_pthread(vector<vector<float>> matrix,vector<vector<float>> weight,vector<vector<float>> bias);

int main(){
    /* vector containing dimensions of test matrices */
    vector<int> dimensions;
    for(int i=1;i<=50;i++){
        dimensions.push_back(10*i);
    }

    /* initialising vectors that will contain plotting data for box plot */
    vector<long double> min_mkl, min_openblas, min_pthread;
    vector<long double> max_mkl, max_openblas, max_pthread;
    vector<long double> median_mkl, median_openblas, median_pthread;
    vector<long double> quarter_mkl, quarter_openblas, quarter_pthread;
    vector<long double> three_quarter_mkl, three_quarter_openblas, three_quarter_pthread;
    for(int i=0;i<50;i++){
        vector<vector<float>> input(dimensions[i], vector<float>(dimensions[i]));
        vector<vector<float>> weight(dimensions[i], vector<float>(dimensions[i]));
        vector<vector<float>> bias(dimensions[i], vector<float>(dimensions[i]));
        vector<vector<float>> output_mkl(dimensions[i], vector<float>(dimensions[i]));
        vector<vector<float>> output_openblas(dimensions[i], vector<float>(dimensions[i]));
        vector<vector<float>> output_pthread(dimensions[i], vector<float>(dimensions[i]));
        vector<long double> time_mkl, time_openblas, time_pthread;

        for(int j=1;j<=50;j++){
            /* generating random matrices for input, weight and bias */
            for(int k=0;k<dimensions[i];k++){
                for(int l=0;l<dimensions[i];l++){
                    input[k][l] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                    input[k][l]*=100;
                    weight[k][l] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                    weight[k][l]*=100;
                    bias[k][l] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                    bias[k][l]*=100;
                }
            }

            /* calculating time for MKL */
            auto start_timer = chrono::high_resolution_clock::now();
            output_mkl = mult_matrix_mkl(input,weight,bias);
            auto stop_timer = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(stop_timer - start_timer);
            time_mkl.push_back((long double)duration.count()/1000000000);

            /* calculating time for OpenBLAS */
            start_timer = chrono::high_resolution_clock::now();
            output_openblas = mult_matrix_openblas(input,weight,bias);
            stop_timer = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(stop_timer - start_timer);
            time_openblas.push_back((long double)duration.count()/1000000000);

            /* calculating time for Pthread */
            start_timer = chrono::high_resolution_clock::now();
            output_pthread = mult_matrix_pthread(input,weight,bias);
            stop_timer = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::nanoseconds>(stop_timer - start_timer);
            time_pthread.push_back((long double)duration.count()/1000000000);
        }
        sort(time_mkl.begin(),time_mkl.end());
        sort(time_openblas.begin(),time_openblas.end());
        sort(time_pthread.begin(),time_pthread.end());
        
        min_mkl.push_back(time_mkl[0]);
        min_openblas.push_back(time_openblas[0]);
        min_pthread.push_back(time_pthread[0]);
        max_mkl.push_back(time_mkl[49]);
        max_openblas.push_back(time_openblas[49]);
        max_pthread.push_back(time_pthread[49]);
        median_mkl.push_back((time_mkl[24]+time_mkl[25])/2);
        median_openblas.push_back((time_openblas[24]+time_openblas[25])/2);
        median_pthread.push_back((time_pthread[24]+time_pthread[25])/2);
        quarter_mkl.push_back((time_mkl[11]+time_mkl[12])/2);
        quarter_openblas.push_back((time_openblas[11]+time_openblas[12])/2);
        quarter_pthread.push_back((time_pthread[11]+time_pthread[12])/2);
        three_quarter_mkl.push_back((time_mkl[36]+time_mkl[37])/2);
        three_quarter_openblas.push_back((time_openblas[36]+time_openblas[37])/2);
        three_quarter_pthread.push_back((time_pthread[36]+time_pthread[37])/2);
    }

    /* writing plotting data for mkl to "mkl_data.txt" */
    ofstream fout;
    fout.open("mkl_data.txt");
    for(int i=0;i<50;i++){
        fout<<dimensions[i]<<"\t"<<min_mkl[i]<<"\t"<<quarter_mkl[i]<<"\t"<<median_mkl[i]<<"\t"<<three_quarter_mkl[i]<<"\t"<<max_mkl[i]<<endl;
    }
    fout.close();

    /* writing plotting data for openblas to "openblas_data.txt" */
    fout.open("openblas_data.txt");
    for(int i=0;i<50;i++){
        fout<<dimensions[i]<<"\t"<<min_openblas[i]<<"\t"<<quarter_openblas[i]<<"\t"<<median_openblas[i]<<"\t"<<three_quarter_openblas[i]<<"\t"<<max_openblas[i]<<endl;
    }
    fout.close();

    /* writing plotting data for pthread to "pthread_data.txt" */
    fout.open("pthread_data.txt");
    for(int i=0;i<50;i++){
        fout<<dimensions[i]<<"\t"<<min_pthread[i]<<"\t"<<quarter_pthread[i]<<"\t"<<median_pthread[i]<<"\t"<<three_quarter_pthread[i]<<"\t"<<max_pthread[i]<<endl;
    }
    fout.close();
}
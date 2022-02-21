#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<math.h>

using namespace std;

vector<vector<float>> mult_matrix_mkl(vector<vector<float>> matrix,vector<vector<float>> weight,vector<vector<float>> bias);

vector<vector<float>> mult_matrix_openblas(vector<vector<float>> matrix,vector<vector<float>> weight,vector<vector<float>> bias);

vector<vector<float>> mult_matrix_pthread(vector<vector<float>> matrix,vector<vector<float>> weight,vector<vector<float>> bias);

/* Error reporting if an input file doesn't exist */

void Filenotexists(string s){
    cout<<"ERROR: "<<s<<" not found\n";
}

/* readMatrix reads a matrix from given text file and stores it in a 2D vector */

void readMatrix(string filename, int &n, int &m, vector<vector<float>> &matrix){
    ifstream fin;
    fin.open(filename);
    string line;
    getline(fin, line);
    m = stoi(line);
    getline(fin, line);
    n = stoi(line);
    matrix.assign(n,vector<float>(m));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            getline(fin, line);
            matrix[j][i] = stof(line);
        }
    }
    fin.close();
}

/* fullyconnected calculates product of inputmatrix and weightmatrix and adds biasmatrix to the output
outputmatrix is printed in a text file given as command line argument */

void fullyconnected(vector<string> args){
    int a,b,c,d,e,f;
    ifstream fin;
    fin.open(args[2]);
    if(!fin){
        Filenotexists(args[2]);
        return;
    }
    fin.close();
    fin.open(args[3]);
    if(!fin){
        Filenotexists(args[3]);
        return;
    }
    fin.close();
    fin.open(args[4]);
    if(!fin){
        Filenotexists(args[4]);
        return;
    }
    fin.close();
    vector<vector<float>> inputmatrix;
    readMatrix(args[2], a, b, inputmatrix);
    vector<vector<float>> weightmatrix;
    readMatrix(args[3], c, d, weightmatrix);
    vector<vector<float>> biasmatrix;
    readMatrix(args[4], e, f, biasmatrix);
    if(b!=c){
        cout<<"inputmatrix and weightmatrix are not compatible\n";
        return;
    }
    if(a!=e || d!=f){
        cout<<"Dimensions of outputmatrix and biasmatrix do not match\n";
        return;
    }
    vector<vector<float>> outputmatrix(a, vector<float>(d,0.0));

    if(args[6] == "mkl"){
        outputmatrix = mult_matrix_mkl(inputmatrix, weightmatrix, biasmatrix);
    }else if(args[6] == "openblas"){
        outputmatrix = mult_matrix_openblas(inputmatrix, weightmatrix, biasmatrix);
    }else if(args[6] == "pthread"){
        outputmatrix = mult_matrix_pthread(inputmatrix, weightmatrix, biasmatrix);
    }else{
        // Report error in case of invalid implementation
        cout<<"ERROR: Invalid argument: "<<args[6]<<"\n";
    }

    ofstream fout;
    fout.open(args[5]);
    fout<<to_string(d)<<"\n"<<to_string(a)<<"\n";
    for(int i=0;i<d;i++){
        for(int j=0;j<a;j++){
            fout<<to_string(outputmatrix[j][i])<<"\n";
        }
    }
    fout.close();
}

int main(int argc, char* argv[]){
    vector<string> args(argv, argv+argc);
    if(argc == 7){
        if(args[1] == "fullyconnected"){
            if((args[2].substr(args[2].size()-4, 4) != ".txt") || (args[3].substr(args[3].size()-4, 4) != ".txt") || (args[4].substr(args[4].size()-4, 4) != ".txt") || (args[5].substr(args[5].size()-4, 4) != ".txt")){
                // Check if input file is a text file
                cout<<"ERROR: Invalid file extension\nOnly text files are accepted\n";
            }else{
                fullyconnected(args);
            }
        }else{
            cout<<"ERROR: Invalid argument: "<<args[1]<<"\n";
        }
    }else{
        // Report error if number of command line arguments is invalid
        cout<<"ERROR: Invalid number of command line arguments\n";
    }
}
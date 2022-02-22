# Matrix multiplication 

Matrix multiplication speed is accelerated using linear algebra libraries - MKL and OpenBLAS

The below functions are implemented in `"main.cpp"`.

## fullyconnected
It computes the product of an input matrix of dimensions AxB and a weight matrix of dimensions BxC, to output a matrix of dimension AxC. A bias matrix is also added to this output matrix.
Following implementations are used to calculate FC-

### Math Kernel Library (MKL)
It accelerates the computation of FC by a significant factor. It is implemented in `"mkl.cpp"`.


This implementation can be called from command line as-
```sh
make
./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt mkl
```

### OpenBLAS
This also accelerates the computation of FC by a significant factor. It is implemented in `"openblas.cpp"`.

This implementation can be called from command line as-
```sh
make
./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt openblas
```

### pthread
This somewhat accelerates the computation of FC but not as much as MKL or OpenBLAS. Computation becomes faster as multiples threads are used and computation is divided among threads. It is implemented in `"threads.cpp"`. The number of threads is set to 8.

This implementation can be called from command line as-
```sh
make
./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt pthread
```

To check if pthread implementation gives correct output-
```sh
make
./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt check
```

The inputmatrix and weightmatrix should be compatible. Otherwise, an error is raised stating the same. Moreover, dimension of biasmatrix should be AxC. outputmatrix is printed in 'outputmatrix.txt'.

## readMatrix
This function is used to read a matrix from given text file.

Plotting data is generated using `"plot.cpp"`.
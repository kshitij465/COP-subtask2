output: main.cpp mkl.cpp openblas.cpp threads.cpp
	g++ -I /usr/include/mkl mkl.cpp  -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl -pthread threads.cpp openblas.cpp -I /usr/include/x86_64-linux-gnu/openblas-pthread/ -L /usr/include/x86_64-linux-gnu/ -lopenblas -lpthread -lgfortran main.cpp -o yourcode.out

clean:
	rm *.o yourcode.out
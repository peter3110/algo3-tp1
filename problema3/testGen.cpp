#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <assert.h>
#include <cstdlib>
using namespace std;

void genTest(int N, int M){   // hace casos de prueba para n=1...N
	// int n = 20;
	// int M = 100000;
  for(int n=2; n<=N; n++) {
    cout << n << " " << M << endl;
    for(int i = 0; i < n - 1; i++) {
      for(int j = i + 1; j < n; j++) {
        // cout << M+1 << " ";            // mejor caso
        // cout << 1 << " ";              // peor caso
        cout << rand() % M + 1 << " ";    // caso promedio
      }
    }
    cout << "0" << endl;
  }
}

int main(int argc, char **argv){
  freopen("promedio.in","w",stdout);
	genTest(atoi(argv[1]), atoi(argv[2]));
  return 0;
}

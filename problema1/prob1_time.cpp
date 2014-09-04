 
#include <iostream>
#include <vector>
#include <assert.h>
#include <cstdio>
#include <cstdio>
#include <sys/time.h>
using namespace std;

timeval start, end;

void init_time(){
gettimeofday(&start,NULL);
}

double get_time(){
gettimeofday(&end,NULL);
return (1000000*(end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec))/1000000.0;
}

int main() {

	double time;


  freopen("testRND", "r", stdin);
  //freopen("output.out", "w", stdout);

  int n, actual, temp, c, cantPasos;
  vector<int> puente, res;

  while(cin >> n >> c) {			// leo cada una de las instancias

	  /* Actualizo las variables correctamente para la resolución de esta instancia */
	  c = c + 1;
	  puente.resize(n + 1);
	  res.resize(n); fill(res.begin(), res.end(), 0);

	  for(int i=1; i<=n; i++) { cin >> puente[i]; }		// leo la entrada

	   ///empieza tiempo
	   time=0.0;
		init_time();

	  actual = 0; cantPasos = 0;	// actual me dice en que tablón estoy y cantPasos la cantidad de pasos que tardo en llegar al otro lado del puente

	  while(actual <= n) {			// hasta haber cruzado el puente, hago..

		temp = 0; actual += c;

		while(temp < c && puente[actual] == 1) {		// si estoy en un tablón malo, voy retrocediendo
														// no más de c tablones, en cuyo caso no hay solución.
			actual--;
			temp++;
		}
		if(temp == c) {cout << "no" << endl; break; }	// retrocedí c tablones. Entonce no hay solución

	    res[cantPasos] = actual; cantPasos++;
	  }
	  time += get_time();
	 cout<< n << " ";
	printf("%.9f\n", time);
	  if(temp==c) { continue; }							// si no había solución, voy a resolver la próxima instancia
	//  cout << cantPasos << " ";
	 // for(int i=0; i<cantPasos; i++) {cout << res[i] << " ";}
	  //cout << endl;										// si había solución, devuelvo la respuesta
  }

  return 0;
}

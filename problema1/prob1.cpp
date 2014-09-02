
#include <iostream>
#include <vector>
#include <assert.h>
#include <cstdio>
using namespace std;

int main() {

  freopen("input.in", "r", stdin);
  freopen("output.out", "w", stdout);
  
  int n, actual, temp, c, cantPasos, ultimo;
  vector<int> puente, res;
  
  while(cin >> n >> c) {			// leo cada una de las instancias
	  
	  /* Actualizo las variables correctamente para la resolución de esta instancia */
	  c = c + 1;
	  puente.resize(n + 1); 
	  res.resize(n); fill(res.begin(), res.end(), 0);
	  
	  for(int i=1; i<=n; i++) { cin >> puente[i]; }		// leo la entrada
	  cin >> ultimo;									// leo el cero que marca el final de cada instancia
	  
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
	  if(temp==c) { continue; }							// si no había solución, voy a resolver la próxima instancia
	  cout << cantPasos << " ";
	  for(int i=0; i<cantPasos; i++) {cout << res[i] << " ";}
	  cout << endl;										// si había solución, devuelvo la respuesta
  }
  
  return 0;
}

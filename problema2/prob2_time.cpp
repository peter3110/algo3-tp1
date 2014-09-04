
#include <iostream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
#include <set>
#include <sys/time.h>
using namespace std;

/* Funciones Auxialires */

bool esMenor(tuple<int, int, int> a, tuple<int, int, int> b);

/* El main del programa que resuelve */

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
  /* de donde leemos la entrada y adonde ponemos el output */
  freopen("input.in", "r", stdin);
 // freopen("output.out", "w", stdout);

  /* variables */
  int n, izq, alt, der, ultimoRes, actualiceHeap;
  vector<int> res;

  /* Para cada instancia que nos pasan, resolvemos el problema */
  while(cin >> n) {
	  vector<tuple<int, int, int> > bordes;

	  /* Leemos la entrada */
	  for(int i=0; i<n; i++)  {
		  cin >> izq >> alt >> der;
		  tuple<int,int,int> a = make_tuple(izq, alt, 1); bordes.push_back(a);
		  tuple<int,int,int> b = make_tuple(der, alt, 2); bordes.push_back(b);
	  }

	  /* para medir tiempo */
	   ///empieza tiempo
	   time=0.0;
		init_time();

	  /* ordenamos los bordes según un criterio */
	  sort(bordes.begin(), bordes.end(), esMenor);

	  /* Inicializamos las estructuras de datos que vamos a utilizar */
	  priority_queue<int> heap; multiset<int> elems_heap; multiset<int>::iterator it;
	  heap.push(0); elems_heap.insert(0);

	  for(int i=0; i<bordes.size(); i++) {

		  if(i==bordes.size() - 1) {			// cuando es el final del último edificio, siempre hay un cambio de altura a altura = 0
			  res.push_back(get<0>(bordes[i])); res.push_back(0);
			  //cout << get<0>(bordes[i]) <<" 0"<<endl;
			  break;
		  }

		  if(get<2>(bordes[i]) == 1) {			// si es un borde izquierdo
			  heap.push(get<1>(bordes[i])); elems_heap.insert(get<1>(bordes[i]));
		  } else {								// si es un borde derecho
			  it = elems_heap.find(get<1>(bordes[i]));
			  elems_heap.erase(it);
		  }

		  actualiceHeap = 0;
		  while(actualiceHeap == 0) {			// actualizo cuál es el elemento tope correcto del heap
			  if(elems_heap.find(heap.top()) != elems_heap.end()) {
				  actualiceHeap = 1;
			  } else {
				  heap.pop();
			  }
		  }

		  if(heap.top() != ultimoRes && get<0>(bordes[i]) != get<0>(bordes[i+1])) {		// hay modificación en altura y el borde actual está situado
																						// en una posición distinta sobre el eje x que el borde próximo a analizar
			  ultimoRes = heap.top();
			  res.push_back(get<0>(bordes[i])); res.push_back(heap.top());
			  //cout << get<0>(bordes[i]) <<" "<< heap.top()<<endl; 						// actualizo la respuesta final
		  }

	  }
	  	  time += get_time();
	 cout<< n << " ";
	printf("%.6f\n", time);
	  // t = clock() - t;
	  // printf ("%f\n",((float)t)/CLOCKS_PER_SEC);
  }

  return 0;
}

/* Funciones Auxiliares */

bool esMenor(tuple<int, int, int> a, tuple<int, int, int> b) {
	if(get<0>(a) == get<0>(b) && get<2>(a) == get<2>(b)) {return get<1>(a) < get<1>(b);}
	if(get<0>(a) != get<0>(b)) {return get<0>(a) < get<0>(b);}
	return get<2>(a) < get<2>(b);
}

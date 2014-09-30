
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <assert.h>
#include <cstdio>
#include <utility>
#include <sys/time.h>
#include <iomanip>
using namespace std;

/* Funciones Auxiliares */

pair<bool, int> nuevoHazard2(int productoi, int camionj, vector<int> &productosEnCamion, vector<int> &hazardCamion, vector <vector<int> > &hazards, int &M);
int hazardOfSubset(int subset, int &n);
void llenarHazards(vector <vector<int> > &hazards, int &n, int hazard2[]);
void resolver(int i, int &primerCamionVacio, int &mejorHastaAhora, vector<int> &resTemp, vector<int> &res, vector<int> &hazardCamion,
			  vector<int> &productosEnCamion, int &M, int &n, int hazard2[], vector <vector<int> > &hazards);
pair<bool, int> nuevoHazard(int productoi, int camion, vector<int> &productosEnCamion, int &M, int hazard2[], vector <vector<int> > &hazards);


/* El main del programa que resuelve el problema */

int main(){
	
	/* Variables locales */
	const int maxN = 20;			  // por la naturaleza del problema, asumimos que el valor máximo de N le ponemos un límite
	int hazard2[1 << maxN];			  // aca guardamos el hazard total que genera cada posible subconjunto de productos
	vector< vector<int> > hazards;	  // aca guardamos el hazard que hay entre cada par de productos
	int primerCamionVacio, mejorHastaAhora, temp, M, n;
	vector<int> resTemp, res, hazardCamion, productosEnCamion;
    
    /* Para cada entrada que nos pasan, resuelvo el problema */
	while(cin >> n >> M) {
		
		/* inicializo la matriz de hazards */
		vector<int> v1(n, 0);
		hazards.resize(n); fill(hazards.begin(), hazards.end(), v1);
		
		/* lleno la matriz de hazards según el los hazards de esta instancia */
		for(int i=0; i<n-1; i++) {
			for(int j=i+1; j<n; j++) {
				cin >> temp;
				hazards[i][j] = temp;
				hazards[j][i] = temp;
			}
		}
		
		/* Inicializo las variables que van a ser modificadas en el backtracking */
		primerCamionVacio = 0; mejorHastaAhora = n;
		hazardCamion.resize(n); fill(hazardCamion.begin(), hazardCamion.end(), 0);
		productosEnCamion.resize(n); 
		fill(productosEnCamion.begin(), productosEnCamion.end(), 0);
		resTemp.resize(n); fill(resTemp.begin(), resTemp.end(), -1);
		
		/* Precalculo el hazard total que genera cada subconjunto de productos */
		llenarHazards(hazards, n, hazard2);
		
		/* Resuelvo el problema con backtracking */
		resolver(0, primerCamionVacio, mejorHastaAhora, resTemp, res, hazardCamion, productosEnCamion, M, n, hazard2, hazards);

		/* Devuelvo el resultado */
		cout << mejorHastaAhora << " ";
		for(int i=0; i<n; i++) { cout << res[i] << " ";}
		cout << endl;
		
		/* Leo el 0 que marca la finalización de esta instancia */
		cin >> temp;
	}
	
    return 0;
}

/* La funcion recursiva "resolver", que hace el backtracking */

void resolver(int productoi, int &primerCamionVacio, int &mejorHastaAhora, vector<int> &resTemp, vector<int> &res, vector<int> &hazardCamion,
			  vector<int> &productosEnCamion, int &M, int &n, int hazard2[], vector <vector<int> > &hazards) {
    
    if(productoi == n) { return; }
		
    int primerCamionVacioTemp = primerCamionVacio;
    
          for(int camionj=0; camionj<=primerCamionVacioTemp; camionj++) {	// no pruebo poner el producto en dos camiones vacíos distintos (camiones indistinguibles) - PODA 1
			                                                            
                pair<bool, int> sePuedeAgregar = nuevoHazard(productoi,camionj,productosEnCamion,M,hazard2, hazards);
                int hazardViejo = hazardCamion[camionj];
                
                if(sePuedeAgregar.first) {								// no me pasé del hazard permitido para el camion
          
                    resTemp[productoi] = camionj + 1;					// para numerar los camiones como se pide, con índices entre 1 y C
                    productosEnCamion[camionj] += (1<<productoi);		// agrego el producto i al camion camionj
                    hazardCamion[camionj] = sePuedeAgregar.second;		// actualizo el hazard total del camion camionj
                    
                    if(camionj == primerCamionVacioTemp) {
							primerCamionVacio++; 
					}													// actualizo el último camión que usé para realizar bien la PODA 1	
                    
                    if(primerCamionVacio <= mejorHastaAhora) {			// no intento poner más productos si se que no va a ser de forma óptima - PODA 2
						resolver(productoi+1, primerCamionVacio, mejorHastaAhora, resTemp, res, hazardCamion, productosEnCamion, M, n, hazard2, hazards);
                    }
                    
                    if(productoi + 1 == n) {				
						  if(primerCamionVacio <= mejorHastaAhora) {	// si llegue al último producto y encontré una mejor solución, 
																		// actualizo la respuesta final
								mejorHastaAhora = primerCamionVacio;
								res = resTemp;
						  }
					}

                    productosEnCamion[camionj] -= (1<<productoi);						// saco el producto i del camion j
                    hazardCamion[camionj] = hazardViejo;

					if(camionj == primerCamionVacioTemp) { primerCamionVacio--; }		// para la correcta realización de la PODA 1
                } 
          }
          return;
}

/* Funciones Auxiliares */

/* Devuelve, para cierto subconjunto "subset" de productos, el hazard que generan entre todos */
int hazardOfSubset(int subset, vector <vector<int> > &hazards, int &n){
	int res = 0;
	for(int i = 0; i < n; i++) if((subset & (1 << i)) != 0)
		for(int j = i + 1; j < n; j++) if((subset & (1 << j)) != 0)
				res += hazards[i][j];
	return res;
}

/* Recorremos todos los posibles subconjuntos de productos y junto con la funcion hazardOfSubset 
 * llenamos el arreglo hazard2, que contiene el hazard total que genera cada subconjunto de productos */
void llenarHazards(vector <vector<int> > &hazards, int &n, int hazard2[]){
	for(int subset = 0; subset < (1 << n); subset++)
		hazard2[subset] = hazardOfSubset(subset, hazards, n);
}

/* Analizamos cuál es el hazard total que generaría agregar el producto productoi en el camion camionj 
 * y devolvemos un par, que dice si era posible agregar el producto al camión, y cuánto hazard total hubiera generado */
pair<bool, int> nuevoHazard(int productoi, int camionj, vector<int> &productosEnCamion, int &M, int hazard2[], vector <vector<int> > &hazards) {

	int nuevoHz = hazard2[productosEnCamion[camionj] | (1 << productoi)];
	pair<bool, int> res = make_pair((nuevoHz<=M), nuevoHz);				// menor o igual, porque cada camion soporta hasta M de hazard total
    return res;
}

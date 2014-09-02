#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <assert.h>
using namespace std;

void llenarHazards();
void resolver(int i);
bool nuevoHazard(int i, int j);    // devuelve hazard que agregaría al camion j
                                   // el producto i, si se lo agregamos.

int n, M, temp, nuevoHz; 
int primerCamionVacio, mejorHastaAhora;
vector<int> resTemp, res, hazardCamion;
vector<int> productosEnCamion;
vector< vector<int> > hazards;
    // productosEnCamion[i,j]: para cada camion i, ver si en él esta el producto j
    // hazards[i,j]: 
const int maxN = 20;
int hazard2[1 << maxN];

int nuevoHazard2(int subset){
	return hazard2[subset];
}

int hazardOfSubset(int subset){
	int res = 0;
	for(int i = 0; i < n; i++) if((subset & (1 << i)) != 0)
		for(int j = i + 1; j < n; j++) if((subset & (1 << j)) != 0)
				res += hazards[i][j];
	return res;
}

void llenarHazards(){
	for(int subset = 0; subset < (1 << n); subset++)
		hazard2[subset] = hazardOfSubset(subset);
}

bool nuevoHazard(int i, int j) {

	nuevoHz = hazard2[productosEnCamion[j] | (1 << i)];
    return (nuevoHz < M);
}


int main(){

	/* para escribir en un archivo */
	freopen("3.in2","r",stdin); 
	freopen("3.out2","w",stdout); 
    
    /* Leo la entrada y inicializo variables*/
    
	while(cin >> n >> M){
    //cin >> n >> M;
    vector<int> v1(n, 0);
    hazards.resize(n); fill(hazards.begin(), hazards.end(), v1);
    resTemp.resize(n); fill(resTemp.begin(), resTemp.end(), -1);
    
    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            cin >> temp;
            hazards[i][j] = temp;
            hazards[j][i] = temp;
        }
    }
    
    primerCamionVacio = 0; mejorHastaAhora = n;
    hazardCamion.resize(n); fill(hazardCamion.begin(), hazardCamion.end(), 0);
    productosEnCamion.resize(n); 
    
    fill(productosEnCamion.begin(), productosEnCamion.end(), 0);
    llenarHazards();
    
    /* Resuelvo el problema con backtracking */
    resolver(0);
    
    /* Devuelvo el resultado */
    cout << mejorHastaAhora << " ";
    for(int i=0; i<n; i++) {cout << res[i] << " ";}
    cout << endl;
	}
	
    return 0;
}


void resolver(int i) {
    
    if(i == n) { return; }
    
    int primerCamVacioTemp = primerCamionVacio;
    
          for(int j=0; j<=primerCamVacioTemp; j++) {
                
                bool sePuedeAgregar = nuevoHazard(i, j);
                int nuevoHzTemp = nuevoHz;
                int hazardViejo = hazardCamion[j];
                
                if(sePuedeAgregar) {
          
                    resTemp[i] = j;
					// assert((productosEnCamion[j] & (1 << i)) == 0);
                    productosEnCamion[j] += (1<<i);
                    hazardCamion[j] = nuevoHzTemp;
                    if(j == primerCamVacioTemp) {
							primerCamionVacio++; 
							//cerr<<"Sumo un camion: "<<primerCamionVacio<<endl;
					}
                    
                    resolver(i+1);
                    
                    if(i + 1 == n) {
						  if(primerCamionVacio <= mejorHastaAhora) {
							  
								mejorHastaAhora = primerCamionVacio;
								res = resTemp;
								
							    //cerr << "MejorHastaAhora: "<<mejorHastaAhora<<endl;
							    //cerr << "Actualizo res: ";
							    //for(int i=0; i<n; i++) {cerr << resTemp[i]<<" ";}cerr<<endl;
						  }
					}

                    productosEnCamion[j] -= (1<<i);
                    hazardCamion[j] = hazardViejo; 

					if(j == primerCamVacioTemp) { primerCamionVacio--; }
                } 

          }
          return;
}

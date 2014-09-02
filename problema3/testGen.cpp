#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <assert.h>
using namespace std;

void genTest(){
	int n = 13;
	int m = 21;
	cout << n << " " << m << endl;
	for(int i = 0; i < n - 1; i++)
		for(int j = i + 1; j < n; j++)
			cout << 1 << " ";
}

int main(){
freopen("3.in2","w",stdout);
	genTest();
    return 0;
}

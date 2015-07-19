#include <cstdio>
#include <vector>

using namespace std;

int main()
{
	int n;
	int a;
	double t;
	int r;
	int cant = 1970;
	int ene = 200;
	//~ vector<float> sumas_n(ene,0);
	vector<double> sumas_t(ene,0);
	
	for(int i = 0; i < cant; i++)
	{
		scanf("%i",&n);
		scanf("%i",&a);
		scanf("%lf",&t);
		scanf("%i",&r);
		
		//~ sumas_n[n-1]++;
		sumas_t[n-1] = sumas_t[n-1] + t;
	}
	
	for(int i = 0; i < ene; i++)
	{
		printf("%i, %lf \n",i+1,sumas_t[i]/10);
	}
	
}


#include <cstdio>
#include <vector>

using namespace std;

int main()
{
	int n;
	double t1;
	double t2;
	double t3;
	double t4;
	int cant = 292;
	int ene = 50;
	vector<double> sumas_n(ene,0);
	vector<double> sumas_t1(ene,0);
	vector<double> sumas_t2(ene,0);
	vector<double> sumas_t3(ene,0);
	vector<double> sumas_t4(ene,0);
	
	for(int i = 0; i < cant; i++)
	{
		scanf("%i",&n);
		scanf("%lf",&t1);
		scanf("%lf",&t2);
		scanf("%lf",&t3);
		scanf("%lf",&t4);
		
		sumas_n[n-1]++;
		sumas_t1[n-1] = sumas_t1[n-1] + t1;
		sumas_t2[n-1] = sumas_t2[n-1] + t2;
		sumas_t3[n-1] = sumas_t3[n-1] + t3;
		sumas_t4[n-1] = sumas_t4[n-1] + t4;
	}
	
	for(int i = 0; i < ene; i++)
	{
		printf("%i, %lf, %lf, %lf, %lf \n",i+1,sumas_t1[i]/sumas_n[i],sumas_t2[i]/sumas_n[i],sumas_t3[i]/sumas_n[i],sumas_t4[i]/sumas_n[i]);
	}
	
}


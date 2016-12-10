#include "polymino.h"
#include "f.h"



int main()		
{
	setlocale(LC_ALL, "rus");

	
	polymino MySolver();
	cout << "_________________________________________" << endl;
	

	system("pause");
	return 0;
}
















/*for (int i = 1; i < N / 2; ++i) //turn right
{
int tmp = 0;
for (int k = i; k < N - i; ++k)
{
tmp = x[i][k];
x[i][k] = x[N - k + 1][i];
x[N - k + 1][i] = x[N - i + 1][N - k + 1];
x[N - i + 1][N - k + 1] = x[k][N - i + 1];
x[k][N - i + 1] = tmp;
}
}*/
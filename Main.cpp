#include "polymino.h"
#include "f.h"

int main()		
{
	setlocale(LC_ALL, "rus");
	unsigned int start_time = clock();	//timer (start)
	size_t q = 3;						//enter a few figures, each figure in its own [file].txt
	int *square = new int[q];
	f *fgr = new f[q];

	string namefile;
	for (size_t quantity = 0; quantity < q; quantity++)
	{
		namefile = to_string(quantity + 1);
		string s1 = "Figures&Result\\", s2 = ".txt";
		string s = s1 + namefile + s2;

		fgr[quantity].read(s);
		fgr[quantity].delZeros();		
	}

	polymino BestSolverEver(fgr, q);
	BestSolverEver.compare();
	BestSolverEver.resultFile();
	
	unsigned int end_time = clock();	//timer (end)
	unsigned int time = end_time - start_time; 
	cout << "Working time: " << time/1000.0 << "sec." << endl;
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
#include "polymino.h"
#include "f.h"

int main()		
{
	setlocale(LC_ALL, "rus");

	size_t q = 3;						//will be enter a few figures, each figure in its own file.txt
	int *square = new int[q];
	f *fgr = new f[q];

	string namefile;
	for (int quantity = 1; quantity <= q; quantity++)
	{
		namefile = to_string(quantity);
		string s1 = "D:\\HomeWork\\Figures&Result\\", s2 = ".txt";
		string s = s1 + namefile + s2;
		cout << endl << "\t#" << quantity << endl;

		fgr[quantity].read(s);
		/*fgr[quantity].checkCorrect();
		fgr[quantity].delZeros();
		fgr[quantity].res();*/
	}

	polymino BestSolverEver(fgr, q);
	BestSolverEver.print();

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
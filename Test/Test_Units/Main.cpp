#include "AllIn.h"
#include "polymino.h"
#include "f.h"

int main()
{
	size_t q = 2;						//enter a few figures, each figure in its own [file].txt

	if (q > 1)
	{
		int *square = new int[q];
		f *fgr = new f[q];
		string namefile;
		for (size_t quantity = 0; quantity < q; quantity++)
		{
			namefile = to_string(quantity + 1);
			string s2 = ".txt";
			string s = namefile + s2;

			fgr[quantity].read(s);
			fgr[quantity].delZeros();
		}

		polymino BestSolverEver(fgr, q);
		BestSolverEver.compare();
	}
	else
		cout << "Only ONE figure was entered! \nPlease check the data and try again." << endl;
	system("pause");
	return 0;
}

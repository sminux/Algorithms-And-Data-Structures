#include "polymino.h"
#include "f.h"

int main()		
{
	setlocale(LC_ALL, "rus");

	size_t q = 0;
	cout << "Enter the quantity of figures:  ";//each figure in its oun file.txt
	cin >> q;
	string c;
	for (int quantity = 1; quantity <= q; quantity++){
		c = to_string(quantity);
		string s1 = "D:\\", s2 = ".txt";
		string s = s1 + c + s2;
		ifstream F(s);
		if (!F.is_open())
		{
			cout << "Wrong path to the file!" << endl;
		}
		else
		{
			size_t k = 0, lines = 0;
			bool flag = false;
			queue<size_t> q;
			size_t i; char c;
			try
			{
				while (!F.eof())
				{
					F >> c;
					if (c != ' ') k++;
					if (c == '\n') lines++;
				}
				cout << "Check: " << k << ' ' << lines;
				if (k > (lines-1)*(lines-1))
					throw invalid_argument("\nIncorrect input data!");
				else
				{
					k = 0;
					while (!F.eof())
					{
						F >> i;
						q.push(size_t(i));
						k++;
					}
					size_t N = sqrt((double)k);
					size_t **x = new size_t*[N];
					for (size_t i = 0; i < N; i++) x[i] = new size_t[N];

					for (size_t i = 0; i < N; i++)
					{
						for (size_t j = 0; j < N; j++)
						{
							x[i][j] = q.front();
							q.pop();
							cout << x[i][j] << ' ';
						}
						cout << endl;
					}

					cout << endl << quantity << " figure:" << endl;

					f fgr(x, N);
					//fgr.delZeros();
					//if(fgr.checkCorrect()) fgr.print(); 
					fgr.print();
					cout << endl;
				
					for (size_t i = 0; i < N; i++) delete[] x[i];
					delete[] x;
					F.close();

				}
			}
			catch (invalid_argument& e)
			{
				cerr << e.what() << endl;
			}	
		}		


	}

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
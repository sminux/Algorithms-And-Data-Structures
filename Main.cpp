#include "polymino.h"
#include "f.h"

void delZeros(int **arr, int n) //from square matrix to normal
{
	int a = n, b = n;
	int z = 0;

	/*try{
		for (int j(0); j < b; j++)//for colums
		{
			for (int i(0); i < a; i++)
				z = z + arr[i][j];			
			cout <<'-' << z << ' ';

			if ((z == 0) && (j != (b-1)))
			{
				for (int i(0); i < a; i++){
					arr[i][j] = arr[i][j + 1];
					arr[i][j + 1] = 0;	//last colomn in memory yet
				}		
				for (int i = 0; i < b; i++)	delete arr[b-1];
				b -= 1;
			} 
			else if ((z == 0) && (j == (b - 1)))
			{
				for (int i = 0; i < b; i++)	delete arr[b-1];
				b -= 1;
			} else z = 0;//for next colomn' counter
		}

		for (int i(0); i < a; i++)//for rows
		{
			for (int j(0); j < b; j++)
				z = z + arr[i][j];
			cout << z << ' ' << endl;

			if ((z == 0) && (i!=(a-1)))
			{
				for (int l(0); l < a-1; l++)
					for (int j(0); j < b; j++)
					{
						arr[l][j] = arr[l + 1][j];
						arr[l + 1][j] = 0;	//last row in memory yet
					}
				for (int j = 0; j < b; j++)
				{
					delete arr[i];
				}
				a -= 1;
			}
			else if ((z == 0) && (i == (a - 1)))//delete last row
			{
				for (int j = 0; j < b; j++)
				{
					delete arr[i];
				}
				a -= 1;
			}
			else z = 0;
		}
	}
	catch(err)
	{
		alert("Error!");
	}*/

		
	for (int i(0); i < a; i++){	//look
		for (int j = 0; j<b; j++){
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}
}

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
			queue<int> tmp;
			int i;
			int count = 0;
			while (!F.eof()){
				F >> i;
				tmp.push(i);
				++count;
			}
			int N = sqrt((double)count);
			int **x = new int*[N];
			for (int i = 0; i < N; i++) x[i] = new int[N];

			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++){
					x[i][j] = tmp.front();
					tmp.pop();
				}
			
			//delZeros(x, N);//will try
			f fgr(x, N, N);
			fgr.Print();
			fgr.checkCorrect();
			cout << fgr.square() << endl;
			for (int i = 0; i<N; i++) delete[] x[i];
			delete[] x;

			F.close();
		}
		cout << endl;
	}
	
	
	system("pause");
	return 0;
}
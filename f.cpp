#include "f.h"

f::f()
{
	cout << "in|";		//initialization label
	
	**data;
	c = 0, r = 0;
	hint = "";
}

f::f(size_t **data, int r, int c)
{
	this->r = r;
	this->c = c;
	this->data = data;
}

int **f::read(string s)
{
	ifstream F(s);
	if (!F.is_open())
	{
		cout << "Wrong path to the file!" << endl;
	}
	else
	{
		size_t k = 0, lines = 0;
		queue<size_t> q;
		size_t entr;

		try
		{
			char ch;
			while (!F.eof())
			{
				F >> ch;
				if (!(isdigit(ch)))	//input data is not a int
					throw invalid_argument("\nIncorrect input data! Not a digit!");
			}
			F.close();
			ifstream F(s);

			char *str = new char[1024];
			while (!F.eof())
			{
				F.getline(str, 1024, '\n');
				lines++;
			}

			F.seekg(0, ios::beg);	//cursor to the beginning of file
			F.clear();

			while (!F.eof())
			{
				F >> entr;
				k++;
			}
			if (k > lines*lines)	//if amount of elements more than dimention
				throw invalid_argument("\nIncorrect input data!");
			else
			{
				F.seekg(0, ios::beg);
				F.clear();			//for repeated reading
				k = 0;
				while (!F.eof())
				{
					F >> entr;
					q.push(entr);
					k++;
				}
				size_t N = sqrt((double)k);
				size_t **x = new size_t*[N];
				for (size_t i = 0; i < N; i++) x[i] = new size_t[N];

				cout << endl;
				for (size_t i = 0; i < N; i++)
				{
					for (size_t j = 0; j < N; j++)
					{
						x[i][j] = q.front();
						q.pop();
					}
				}

				data = x;	//go on with data[][]
				c = N;
				r = N;		

				//for (size_t i = 0; i < N; i++) delete[] x[i];
				//delete[] x;
				F.close();
			}
		}
		catch (invalid_argument& e)
		{
			cerr << e.what() << endl;
		}
	}
}

int f::square()
{
	int Sq = 0;
	for (size_t i(0); i < r; i++)
	{
		for (size_t j(0); j < c; j++)
		{
			if (data[i][j] == 1) Sq += 1; 
		}
	}
	return Sq;
}

int f::plenum()
{
	int fulness = (c*r) - square();
	return fulness;
}

bool f::checkCorrect()
{
	bool flag = false;

	const size_t new_A = c * r;	//make new array for adjacency matrix
	size_t **A = new size_t*[new_A];
	for (size_t a = 0; a < new_A; a++) A[a] = new size_t[new_A];
	for (size_t i(0); i < new_A; i++)
			for (size_t j(0); j < new_A; j++) A[i][j] = 0;
	

	for (size_t i(0); i < r; i++)
	{
		for (size_t j(0); j < c - 1; j++)
		{
			if ((data[i][j] == 1)&&(data[i][j] == data[i][j + 1]))
			{
				A[i*c + j][i*c + j + 1] = 1;		//matrix is simetric
				A[i*c + j + 1][i*c + j] = 1;
			}
			if ((data[j][i] == 1) && (data[j][i] == data[j][i + 1]))
			{
				A[i*r + j][i*r + j + 1] = 1;		//matrix is simetric
				A[i*r + j + 1][i*r + j] = 1;
			}
		}
	}

	for (size_t i(0); i < c; i++)
	{
		for (size_t j(0); j < r - 1; j++)
		{
			
			if ((data[j][i] == 1) && (data[j][i] == data[j + 1][i]))
			{
				A[i*c + j][(i+1)*c + j] = 1;		//matrix is simetric
				A[(i+1)*c + j][i*c + j] = 1;
			}
		}
	}


	for (size_t i(0); i < new_A; i++)
	{
		for (size_t j(0); j < new_A; j++)
		{
			cout << A[i][j] << ' ';
		}
		cout << endl;
	}
	
	/*size_t *used = new size_t[new_A];
	used = {0,};
	int horizont = 0, vertical = 0;
	for (size_t i(0); i < new_A; i++)
	{
		for (size_t j(0); j < new_A; j++)
		{
			if ((A[i][j] == 1) && (used[j] == 0))
			{
				swap(i, j);
				used[j] = 1;
				horizont += 1;
			}
		}
	}
	for (size_t i(0); i < new_A; i++)
	{
		for (size_t j(0); j < new_A; j++)
		{
			if ((A[j][i] == 1) && (used[i] == 0))
			{
				swap(i, j);
				used[i] = 1;
				vertical += 1;
			}
		}
	}
	
	(horizont != vertical)? flag = false: flag = true;

	delZeros();*/ 

	bool polymino = false;

	if (flag)	
		(plenum() == 0) ? polymino = false : polymino = true;

	return polymino;
}

void f::findAngle()
{
	size_t **record = new size_t*[r];
	for (size_t i = 0; i < r; i++) record[i] = new size_t[c];

	record = data;

	int row_length = 0, column_length = 0, new_row_length, new_column_length;
	int record_r, record_c;
	
	for (int i = 0; i < 4; i++)
	{ 
		new_row_length = 0; new_column_length = 0;
		if ((c > 1) && (r > 1))		//else we have no angle
		{ 
			if ((data[0][0] == 1) && (data[0][0] == data[0][1]) && (data[0][0] == data[1][0]))
			{ 

				for (int Y = 0; Y < c; Y++)
				{
					if (data[0][Y] == 1)new_column_length++;
				}
				
				for (int Y = 0; Y < r; Y++)
				{
					if (data[Y][0] == 1)new_row_length++;
				}
				

				if ((new_row_length >= row_length) && (new_column_length >= column_length))
				{
					for (int i(0); i < r; i++)
					{
						for (int j(0); j < c; j++)
							record[i][j] = data[i][j];
					}
					record_c = c;
					record_r = r;
					row_length = new_row_length;
					column_length = new_column_length;
				}
			}	
			rotation90R();
		}
		
	}

	data = record;
	c = record_c; r = record_r;
}

void f::delZeros()	//from square matrix to normal
{
	for (size_t i = 0; i < r; i++)	//delete  empty rows
	{
		int zeros = 0;
		for (size_t j = 0; j < c; j++)
			if (data[i][j] != 0) zeros = 1;
		if (zeros == 0)
		{
			for (size_t y = i; y < r - 1; y++)
				for (size_t j = 0; j < c; j++)
					data[y][j] = data[y + 1][j];
			r--;
			i = 0; 
		}
	}
	
	for (size_t i = 0; i < c; i++)	//delete  empty colums
	{
		int zeros = 0;
		for (size_t j = 0; j < r; j++)
			if (data[j][i] != 0) zeros = 1;
		if (zeros == 0)
		{
			for (size_t y = i; y < c - 1; y++)
				for (size_t j = 0; j < r; j++)
					data[j][y] = data[j][y+1];
			c--;
			i = 0;
		}
	}
	cout << "dim: [" << r << " * " << c << "]" << endl;
}

void f::flipVerticaly()
{
	for (size_t i = 0; i < r/2; i++)
	{	
		for (size_t j = 0; j < c; j++) swap(data[i][j], data[r - i - 1][j]);
	}
	hint += "F(v)";
}

void f::flipHorizontaly()
{
	for (size_t i = 0; i < c / 2; i++)
	{
		for (size_t j = 0; j < r; j++) swap(data[j][i], data[j][c - i - 1]);
	}
	hint += "F(h)";
}

void f::rotation90R()
{				//P -> P.transponize -> P.flip(horisontaly)
	int n = 0;
	(r > c) ? n = r : n = c;	//it's easy to ratate square matrix

	for (size_t i = 0; i < n ; ++i)
		for (size_t j = i; j < n; ++j)		//beggining from [i] 'cause transponation over main diagonal
			swap(data[i][j], data[j][i]);

	swap(r, c);
	flipHorizontaly();
	hint += "R";
}

void f::rotation90L()
{
	int n = 0;
	(r > c) ? n = r : n = c;	//it's easy to ratate square matrix
	for (int i(0); i < 3; i++) rotation90R();
	hint += "L";
}

void f::print()
{
	for (size_t i(0); i < r; i++)
	{
		for (size_t j(0); j < c; j++)
			cout << data[i][j] << ' ';
		cout << endl;
	}
	cout << "_____________________" << endl;
}

int f::get_c()
{
	return c;
}

int f::get_r()
{
	return r;
}

size_t **f::array()
{
	return data;
}

f::~f()
{
}

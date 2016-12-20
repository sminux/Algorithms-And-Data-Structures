#include "polymino.h"

polymino::polymino(f *figures, int n)
{
	this->n = n;
	this->figures = new f[n];
	cout << "reinitialisation";
	for (size_t i(0); i < n; i++) this->figures[i] = figures[i];

	hint = ' ';
}
/*int polymino::poligon()
{
	int globalSquare = 0;
	for (int num(0); num < n; num++)
	{
		for (size_t i(0); i < n; i++) solvation = figures[num].array();
		for (size_t i(0); i < figures[num].get_r(); i++)
		{
			for (size_t j(0); j < figures[num].get_c(); j++)
			{
				if (solvation[i][j] == 1) globalSquare += 1;
			}
		}
	}

	(globalSquare % 2 != 0) ? (cout << "Figures do not add up!" << endl) : (cout << "Area of " << globalSquare << endl);
	return globalSquare;
}*/


/*void polymino::poligonVariability()
{
	

}*/

size_t **polymino::mergeFigures(size_t **first_figure, int r1, int c1, size_t ** second_figure, int r2, int c2)
{
	size_t **record = new size_t*[r1];
	for (size_t i = 0; i < r1; i++) record[i] = new size_t[c1];

	int row_length = 0, column_length = 0, new_row_length, new_column_length;
	int record_r, record_c;

	for (int i = 0; i < 4; i++)
	{
		new_row_length = 0; new_column_length = 0;
		if ((c1 > 1) && (r1 > 1))		//else we have no angle
		{
			if ((first_figure[0][0] == 1) && (first_figure[0][0] == first_figure[0][1]) && (first_figure[0][0] == first_figure[1][0]))
			{

				for (int Y = 0; Y < c1; Y++)
				{
					if (first_figure[0][Y] == 1)new_column_length++;
				}

				for (int Y = 0; Y < r1; Y++)
				{
					if (first_figure[Y][0] == 1)new_row_length++;
				}


				if ((new_row_length >= row_length) && (new_column_length >= column_length))
				{
					for (int i(0); i < r1; i++)
					{
						for (int j(0); j < c1; j++)
							record[i][j] = first_figure[i][j];
					}
					record_c = c1;
					record_r = r1;
					row_length = new_row_length;
					new_column_length = new_column_length;
				}
			}
			int n = 0;
			(r1 > c1) ? n = r1 : n = c1;	//it's easy to ratate square matrix

			for (size_t i = 0; i < n; ++i)
				for (size_t j = i; j < n; ++j)		//beggining from [i] 'cause transponation over main diagonal
					swap(first_figure[i][j], first_figure[j][i]);

			swap(r1, c1);
			for (size_t i = 0; i < c1 / 2; i++)
			{
				for (size_t j = 0; j < r1; j++) swap(first_figure[j][i], first_figure[j][c1 - i - 1]);
			}
			hint += "R";
		}

	}

	first_figure = record;
	c1 = record_c; r1 = record_r;

	size_t **additional_arr = new size_t*[r1 + r2]; 
	for (int i = 0; i < r1 + r2; i++) additional_arr[i] = new size_t[c1 + c2];
	for (int i(0); i < r1 + r2; i++)
		for (int j(0); j < c1 + c2; j++) additional_arr[i][j] = 1;

	size_t **fake_figure = new size_t*[r1];
	for (int i = 0; i < r1; i++) fake_figure[i] = new size_t[c1];

	fake_figure = first_figure;

	int units = 0;
	for (int i(0); i < r2; i++)
	{
		for (int j(0); j < c2; j++)
			if (second_figure[i][j] == 1)units++;
	}


	for (int i(0); i < r1; i++)
	{
		for (int j(0); j < c1; j++)
		{
			if (first_figure[i][j] == 1) {
				additional_arr[i][j] = 0;
			}
			else if (first_figure[i][j] == 0) {
				additional_arr[i][j] = 1;
			}
		}
	}
	bool point = true;		//to check the first equivalention
	/*serch for 2nd massiv in fake_figure*/
	for (int i(0); i < r1; i++)
	{
		for (int j(0); j < c1; j++)
		{
			int koefficient_of_similarity = 0;
			for (int subarrayX = i; subarrayX < i + r2; subarrayX++)
			{
				for (int subarrayY = j; subarrayY < j + c2; subarrayY++)
				{
					if ((fake_figure[subarrayX][subarrayY] == 0) && (second_figure[subarrayX - i][subarrayY - j] == 1)) koefficient_of_similarity++;
				}
			}

			if ((koefficient_of_similarity == units) && (point == true))
			{
				for (int subarrayX = i; subarrayX < i + r2; subarrayX++)
				{
					for (int subarrayY = j; subarrayY < j + c2; subarrayY++)
					{
						if (second_figure[subarrayX - i][subarrayY - j] == 1) fake_figure[subarrayX][subarrayY] = 1;
					}
				}
				point = false;
			}
		}
	}
	colums = c1; rows = r1;
	return fake_figure;
	/*if (get_solve) return fake_figure;
	else
	{
		point = true;
		//serch for 2nd massiv in additional
		for (int i(0); i < r1; i++)
		{
			for (int j(0); j < c1; j++)
			{

				int koefficient_of_similarity = 0;
				for (int subarrayX = 0; subarrayX < r2; subarrayX++)
				{
					for (int subarrayY = 0; subarrayY < c2; subarrayY++)
					{
						if (additional_arr[i + subarrayX][j + subarrayY] == second_figure[subarrayX][subarrayY]) koefficient_of_similarity++;
					}
					if ((koefficient_of_similarity == r2*c2) && (point == true))
					{
						for (int subarrayX = 0; subarrayX < i + r2; subarrayX++)
							for (int subarrayY = 0; subarrayY < j + c2; subarrayY++)
							{
								additional_arr[subarrayX][subarrayY] = 0;
							}
						point = false;
					}
				}

			}
		}

		//invert
		for (int i(0); i < r1 + r2; i++)
		{
			for (int j(0); j < c1 + c2; j++)
			{
				if (additional_arr[i][j] == 1) additional_arr[i][j] = 0;
				else additional_arr[i][j] = 1;
			}
		}

		colums = c1 + c2;		rows = r1 + r2;

		//delete extra colums&rows
		for (size_t i = 0; i < rows; i++)	//delete  empty rows
		{
			int zeros = 0;
			for (size_t j = 0; j < colums; j++)
				if (additional_arr[i][j] != 0) zeros = 1;
			if (zeros == 0)
			{
				for (size_t y = i; y < rows - 1; y++)
					for (size_t j = 0; j < colums; j++)
						additional_arr[y][j] = additional_arr[y + 1][j];
				rows--;
				i = 0;
			}
		}
		for (size_t i = 0; i < colums; i++)	//delete  empty colums
		{
			int zeros = 0;
			for (size_t j = 0; j < rows; j++)
				if (additional_arr[j][i] != 0) zeros = 1;
			if (zeros == 0)
			{
				for (size_t y = i; y < colums - 1; y++)
					for (size_t j = 0; j < rows; j++)
						additional_arr[j][y] = additional_arr[j][y + 1];
				colums--;
				i = 0;
			}
		}

		return additional_arr;
	}*/
}

void polymino::compare()
{	    
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++) 
		{
			if (figures[j].square() < figures[j + 1].square()) 
			{
				swap(figures[j], figures[j + 1]);
			}
		}
	}

	bool get_solve = false;

	solvation = figures[0].array();
	colums = figures[0].get_c(); rows = figures[0].get_r();

	while (!get_solve)
	{
		for (int i = 0; i < (n - 1); i++)
		{
			solvation = mergeFigures(solvation, rows, colums, figures[i + 1].array(), figures[i + 1].get_r(), figures[i + 1].get_c());
			f result(solvation, rows, colums);
			if (result.plenum() == 0) get_solve = true;
		}

		

	}
	
			
}

void polymino::resultFile()
{
	ofstream f_res("Figures&Result\\result.txt");
	if (!f_res.is_open())
	{
		cout << "Wrong path to the result file!" << endl;
	}
	else
	{
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < colums; j++)
			{
				f_res << solvation[i][j] << ' ';
			}
			f_res << endl;
		}
	}
	f_res.close();
	
}

polymino::~polymino()
{

}
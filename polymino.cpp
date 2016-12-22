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

void polymino::searchEmpty(size_t **figure, int r1, int c1, size_t ** second_figure, int r2, int c2)
{
	int units = 0;
	for (int i(0); i < r2; i++)
		for (int j(0); j < c2; j++) if (second_figure[i][j] == 1) units++;

	bool point = true;		//to check the first equivalention

	for (int i(0); i < r1 - r2 + 1; i++)
	{
		for (int j(0); j < c1 - c2 + 1; j++)
		{
			int koefficient_of_similarity = 0;

			for (int subarrayX = 0; subarrayX < r2; subarrayX++)
			{
				for (int subarrayY = 0; subarrayY < c2; subarrayY++)
				{
					if ((figure[subarrayX + i][subarrayY + j] == 0) && (second_figure[subarrayX][subarrayY] == 1)) koefficient_of_similarity++;
				}
			}
			if ((koefficient_of_similarity == units) && (point == true))
			{
				for (int subarrayX = 0; subarrayX < r2; subarrayX++)
				{
					for (int subarrayY = 0; subarrayY < c2; subarrayY++)
					{
						if (second_figure[subarrayX][subarrayY] == 1) figure[subarrayX + i][subarrayY + j] = 1;
					}
				}
				point = false;
			}
		}
	}
}

size_t **polymino::mergeFigures(size_t **first_figure, int r1, int c1, size_t ** second_figure, int r2, int c2)
{
	int sq = 0;
	for (int i(0); i < r1; i++)
		for (int j(0); j < c1; j++)
			if (first_figure[i][j] == 1) sq++;
	for (int i(0); i < r2; i++)
		for (int j(0); j < c2; j++)
			if (second_figure[i][j] == 1) sq++;

	f prob_f(first_figure, r1, c1);
	prob_f.findAngle();

	f prob_f_second(second_figure, r2, c2);

	rows = prob_f.get_r();
	colums = prob_f.get_c();

	size_t **fake_figure = new size_t*[rows];
	for (int i = 0; i < rows; i++) fake_figure[i] = new size_t[colums];

	fake_figure = prob_f.array();


	bool find = false;

	if ((sq <= r1*c1) && (prob_f.plenum() >= prob_f_second.square())) //if empty area is adecuatly for second figure
	{ 
		if ((prob_f.get_r() >= prob_f_second.get_r()) && (prob_f.get_c() >= prob_f_second.get_c()))
		{
			searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
			f prob_f_new(fake_figure, rows, colums);
			if (prob_f_new.array() == prob_f.array()) {
				prob_f_second.flipHorizontaly();
				searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
				f prob_f_new(fake_figure, rows, colums);
				if (prob_f_new.array() == prob_f.array()) {
					prob_f_second.flipVerticaly();
					searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
					f prob_f_new(fake_figure, rows, colums);
					if (prob_f_new.array() == prob_f.array()) {
						prob_f_second.flipHorizontaly();
						searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
						f prob_f_new(fake_figure, rows, colums);
						if (prob_f_new.array() == prob_f.array()) {
							prob_f_second.flipVerticaly();	//back to begining state
						}
						//(else) - nothing 'couse we came to start state
					}
					else find = true;
				}
				else find = true;
			}
			else find = true;
		}

		if ((prob_f.get_r() < prob_f_second.get_r()) && (prob_f.get_c() < prob_f_second.get_c()))
		{
			prob_f_second.rotation90R();
			searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
			f prob_f_new(fake_figure, rows, colums);
			if (prob_f_new.array() == prob_f.array()) {
				prob_f_second.flipHorizontaly();
				searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
				f prob_f_new(fake_figure, rows, colums);
				if (prob_f_new.array() == prob_f.array()) {
					prob_f_second.flipVerticaly();
					searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
					f prob_f_new(fake_figure, rows, colums);
					if (prob_f_new.array() == prob_f.array()) {
						prob_f_second.flipHorizontaly();
						searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
						f prob_f_new(fake_figure, rows, colums);
						if (prob_f_new.array() == prob_f.array()) {
							prob_f_second.flipVerticaly();	//back to begining state
						}
						//(else) - nothing 'couse we came to start state
					}
					else find = true;
				}
				else find = true;
			}
			else find = true;
			//else cout << "Can't compare figures!" << endl;
		}

		if(find = true) return fake_figure;
		else {
			cout << "Can't compare figures!" << endl;
			return fake_figure;
		}
	}
	else
	{
		size_t **additional_arr = new size_t*[r1 + r2 - 1];
		for (int i = 0; i < r1 + r2; i++) additional_arr[i] = new size_t[c1 + c2 - 1];
		for (int i(0); i < r1 + r2 - 1; i++)
			for (int j(0); j < c1 + c2 - 1; j++) additional_arr[i][j] = 0;

		for (int i(0); i < r1; i++)
			for (int j(0); j < c1; j++)
				additional_arr[i][j] = first_figure[i][j];

		while ((find == false) || ((colums != c1 + c2 - 1)&&(rows != r1 + r2 - 1)))
		{
			searchEmpty(additional_arr, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
			f prob_f_new(additional_arr, rows, colums);
			if (prob_f_new.array() == prob_f.array()) {
				prob_f_second.flipHorizontaly();
				searchEmpty(additional_arr, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
				f prob_f_new(additional_arr, rows, colums);
				if (prob_f_new.array() == prob_f.array()) {
					prob_f_second.flipVerticaly();
					searchEmpty(additional_arr, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
					f prob_f_new(additional_arr, rows, colums);
					if (prob_f_new.array() == prob_f.array()) {
						prob_f_second.flipHorizontaly();
						searchEmpty(additional_arr, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
						f prob_f_new(additional_arr, rows, colums);
						if (prob_f_new.array() == prob_f.array()) {
							prob_f_second.flipVerticaly();	//back to begining state
						}
						//(else) - nothing 'couse we came to start state
					}
					else find = true;
				}
				else find = true;
			}
			else find = true;

			colums++; rows++;
			if (find = true) return additional_arr;
			else {
				cout << "Can't compare figures!" << endl;
				return additional_arr;
			}
		}
	}

	/*

	



	if ((prob_f.get_r() >= prob_f_second.get_r()) && (prob_f.get_c() >= prob_f_second.get_c()))
	{
		if (find = false)
		{
			//serch for 2nd massiv in fake_figure
			
		}
		else return fake_figure;

		
	}

	else if((prob_f.get_r() < prob_f_second.get_r()) && (prob_f.get_c() < prob_f_second.get_c()))
	{
		if (find = false)
		{ 
			prob_f_second.rotation90R();

			int rows2 = prob_f_second.get_r();
			int cols2 = prob_f_second.get_c();

			second_figure = prob_f_second.array();
			//serch again
			for (int i(0); i < rows - rows2 + 1; i++)
			{
				for (int j(0); j < colums - cols2 + 1; j++)
				{
					int koefficient_of_similarity = 0;

					for (int subarrayX = 0; subarrayX < rows2; subarrayX++)
					{
						for (int subarrayY = 0; subarrayY < cols2; subarrayY++)
						{
							if ((fake_figure[subarrayX + i][subarrayY + j] == 0) && (second_figure[subarrayX][subarrayY] == 1)) koefficient_of_similarity++;
						}
					}
					if ((koefficient_of_similarity == units) && (point == true))
					{
						for (int subarrayX = 0; subarrayX < rows2; subarrayX++)
						{
							for (int subarrayY = 0; subarrayY < cols2; subarrayY++)
							{
								if (second_figure[subarrayX][subarrayY] == 1) fake_figure[subarrayX + i][subarrayY + j] = 1;
							}
						}
						point = false;
						find = true;
					}
				}
			}	
		}
		else return fake_figure;

		if (find = false)
		{
			prob_f_second.flipHorizontaly();

			int rows2 = prob_f_second.get_r();
			int cols2 = prob_f_second.get_c();

			second_figure = prob_f_second.array();
			//serch again
			for (int i(0); i < rows - rows2 + 1; i++)
			{
				for (int j(0); j < colums - cols2 + 1; j++)
				{
					int koefficient_of_similarity = 0;

					for (int subarrayX = 0; subarrayX < rows2; subarrayX++)
					{
						for (int subarrayY = 0; subarrayY < cols2; subarrayY++)
						{
							if ((fake_figure[subarrayX + i][subarrayY + j] == 0) && (second_figure[subarrayX][subarrayY] == 1)) koefficient_of_similarity++;
						}
					}
					if ((koefficient_of_similarity == units) && (point == true))
					{
						for (int subarrayX = 0; subarrayX < rows2; subarrayX++)
						{
							for (int subarrayY = 0; subarrayY < cols2; subarrayY++)
							{
								if (second_figure[subarrayX][subarrayY] == 1) fake_figure[subarrayX + i][subarrayY + j] = 1;
							}
						}
						point = false;
						find = true;
					}
				}
			}
		}
		else return fake_figure;

		if (find = false)
		{
			prob_f_second.flipVerticaly();

			int rows2 = prob_f_second.get_r();
			int cols2 = prob_f_second.get_c();

			second_figure = prob_f_second.array();
			//serch again
			for (int i(0); i < rows - rows2 + 1; i++)
			{
				for (int j(0); j < colums - cols2 + 1; j++)
				{
					int koefficient_of_similarity = 0;

					for (int subarrayX = 0; subarrayX < rows2; subarrayX++)
					{
						for (int subarrayY = 0; subarrayY < cols2; subarrayY++)
						{
							if ((fake_figure[subarrayX + i][subarrayY + j] == 0) && (second_figure[subarrayX][subarrayY] == 1)) koefficient_of_similarity++;
						}
					}
					if ((koefficient_of_similarity == units) && (point == true))
					{
						for (int subarrayX = 0; subarrayX < rows2; subarrayX++)
						{
							for (int subarrayY = 0; subarrayY < cols2; subarrayY++)
							{
								if (second_figure[subarrayX][subarrayY] == 1) fake_figure[subarrayX + i][subarrayY + j] = 1;
							}
						}
						point = false;
						find = true;
					}
				}
			}
		}
		else return fake_figure;

		if (find = false)
		{
			prob_f_second.flipHorizontaly();

			int rows2 = prob_f_second.get_r();
			int cols2 = prob_f_second.get_c();

			second_figure = prob_f_second.array();
			//serch again
			for (int i(0); i < rows - rows2 + 1; i++)
			{
				for (int j(0); j < colums - cols2 + 1; j++)
				{
					int koefficient_of_similarity = 0;

					for (int subarrayX = 0; subarrayX < rows2; subarrayX++)
					{
						for (int subarrayY = 0; subarrayY < cols2; subarrayY++)
						{
							if ((fake_figure[subarrayX + i][subarrayY + j] == 0) && (second_figure[subarrayX][subarrayY] == 1)) koefficient_of_similarity++;
						}
					}
					if ((koefficient_of_similarity == units) && (point == true))
					{
						for (int subarrayX = 0; subarrayX < rows2; subarrayX++)
						{
							for (int subarrayY = 0; subarrayY < cols2; subarrayY++)
							{
								if (second_figure[subarrayX][subarrayY] == 1) fake_figure[subarrayX + i][subarrayY + j] = 1;
							}
						}
						point = false;
						find = true;
					}
				}
			}
		}
		else return fake_figure;


	}
		
	


//////////////////////////////////////////

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
	}
	*/
}

void polymino::compare()
{	    
	for (int i = 0; i < n - 1; i++)
	{
		if (figures[i].get_c()*figures[i].get_r() < figures[i + 1].get_c()*figures[i + 1].get_r())//increase by dimention
		{ 
			swap(figures[i], figures[i + 1]);
		}
			
		if (figures[i].get_c()*figures[i].get_r() == figures[i + 1].get_c()*figures[i + 1].get_r())
		{
			if (figures[i].square() > figures[i + 1].square())//decrease by square
			{
				swap(figures[i], figures[i + 1]);
			}
		}
	}
	cout << endl;

	bool get_solve = false;
	
	solvation = figures[0].array();
	colums = figures[0].get_c(); 
	rows = figures[0].get_r();

	for (int i = 0; i < n - 1; i++)
	{
		solvation = mergeFigures(solvation, rows, colums, figures[i + 1].array(), figures[i + 1].get_r(), figures[i + 1].get_c());
		
		/*if (result.plenum() == 0) get_solve = true;
		else hint = "No ansver";*/
	}
	f result(solvation, rows, colums);
	result.print();
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
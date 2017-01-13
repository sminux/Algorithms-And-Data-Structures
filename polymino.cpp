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

bool polymino::equivalent(size_t **first, size_t ** second, int r, int c)
{
	int absolut = 0;
	for (int i(0); i < r; i++)
		for (int j(0); j < c; j++)
			if (first[i][j] == second[i][j]) absolut++;
	
	if (absolut == r*c) return true;
		else return false;
}

void polymino::backFigure(size_t **figure_p, size_t **figure_s, int r1, int c1, int r2, int c2)
{
	for (int i(0); i < r1; i++)
		for (int j(0); j < c1; j++)
			figure_p[i][j] = figure_s[i][j];

	for (int i = r1; i < r2 - 1; i++)
		for (int j = c1; j < c2 - 1; j++)
			figure_p[i][j] = 0;
}



size_t **polymino::searchEmpty(size_t **figure, int r1, int c1, size_t ** second_figure, int r2, int c2)
{
	int units = 0;
	for (int i(0); i < r2; i++)
		for (int j(0); j < c2; j++) if (second_figure[i][j] == 1) units++;

	size_t **record = new size_t*[r1];
	for (int i = 0; i < rows; i++) record[i] = new size_t[c1];
	for (int i(0); i < r1; i++)
		for (int j(0); j < c1; j++) record[i][j] = figure[i][j];

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
						if (second_figure[subarrayX][subarrayY] == 1) record[subarrayX + i][subarrayY + j] = 1;
					}
				}
				point = false;
			}
		}
	}

	return record;
}

f polymino::mergeFigures(f first_figure, int r1, int c1, f second_figure, int r2, int c2)
{
	int c_rec = c1 + c2 - 1, r_rec = r1 + r2 - 1;

	int sq = 0;
	for (int i(0); i < r1; i++)
		for (int j(0); j < c1; j++)
			if (first_figure.array()[i][j] == 1) sq++;
	for (int i(0); i < r2; i++)
		for (int j(0); j < c2; j++)
			if (second_figure.array()[i][j] == 1) sq++;

	f record(first_figure.array(), r1, c1);	//to return

	first_figure.findAngle();

	size_t **fake_figure = new size_t*[rows];
	for (int i = 0; i < rows; i++) fake_figure[i] = new size_t[colums];
	/*for (int i(0); i < r1; i++)
	for (int j(0); j < c1; j++) fake_figure[i][j] = first_figure.array()[i][j];*/
	fake_figure = first_figure.array();

	second_figure.findAngle();

	int record_plenum = c1 + r1 + r2 + c2;		//берём заведомо больше
	rows = first_figure.get_r();
	colums = first_figure.get_c();


	bool find = false;

	/*  if empty area is adecuatly for second figure  */
	if ((sq <= r1*c1) && (first_figure.plenum() >= second_figure.square()))
	{
		if ((first_figure.get_r() >= second_figure.get_r()) && (first_figure.get_c() >= second_figure.get_c()))
		{
			rows = first_figure.get_r();		//maybe it is not nessesary
			colums = first_figure.get_c();	//

			f prob_f_new(searchEmpty(fake_figure, rows, colums, second_figure.array(), second_figure.get_r(), second_figure.get_c()), rows, colums);

			if (equivalent(prob_f_new.array(), first_figure.array(), first_figure.get_r(), first_figure.get_c()) == false)
			{
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "hint: no rotation" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
				}
				find = true;
			}
			cout << "..." << endl;

			fake_figure = first_figure.array();/////////////////////

			second_figure.flipVerticaly();

			prob_f_new.reInitialise(searchEmpty(fake_figure, rows, colums, second_figure.array(), second_figure.get_r(), second_figure.get_c()), rows, colums);

			if (equivalent(prob_f_new.array(), first_figure.array(), first_figure.get_r(), first_figure.get_c()) == false)
			{
				if ((prob_f_new.plenumHalf() < record_plenum) || (prob_f_new.plenumHalf() == 0))
				{
					std::cout << "hint: V" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
				}
				find = true;
			}
			cout << "..." << endl;

			fake_figure = first_figure.array();//////////////////////


			second_figure.flipHorizontaly();

			prob_f_new.reInitialise(searchEmpty(fake_figure, rows, colums, second_figure.array(), second_figure.get_r(), second_figure.get_c()), rows, colums);

			if (equivalent(prob_f_new.array(), first_figure.array(), first_figure.get_r(), first_figure.get_c()) == false)
			{
				if ((prob_f_new.plenumHalf() < record_plenum) || (prob_f_new.plenumHalf() == 0))
				{
					std::cout << "hint: V_H" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
				}
				find = true;
			}
			cout << "..." << endl;


			fake_figure = first_figure.array();///////////////////////////

			second_figure.flipVerticaly();

			prob_f_new.reInitialise(searchEmpty(fake_figure, rows, colums, second_figure.array(), second_figure.get_r(), second_figure.get_c()), rows, colums);

			if (equivalent(prob_f_new.array(), first_figure.array(), first_figure.get_r(), first_figure.get_c()) == false)
			{
				if ((prob_f_new.plenumHalf() < record_plenum) || (prob_f_new.plenumHalf() == 0))
				{
					std::cout << "hint: V_H_V" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
				}
				find = true;
			}
			cout << "..." << endl;

		}

		if ((record.array() == first_figure.array()) || ((first_figure.get_r() < second_figure.get_r()) || (first_figure.get_c() < second_figure.get_c())))
		{
			second_figure.rotation90R();	//turn and check again

			rows = first_figure.get_r();		//maybe it is not nessesary
			colums = first_figure.get_c();	//

			fake_figure = first_figure.array();

			f prob_f_new(searchEmpty(fake_figure, rows, colums, second_figure.array(), second_figure.get_r(), second_figure.get_c()), rows, colums);

			if (equivalent(prob_f_new.array(), first_figure.array(), first_figure.get_r(), first_figure.get_c()) == false)
			{
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "hint: R" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
				}
				find = true;
			}
			cout << "..." << endl;

			fake_figure = first_figure.array();

			second_figure.flipVerticaly();

			prob_f_new.reInitialise(searchEmpty(fake_figure, rows, colums, second_figure.array(), second_figure.get_r(), second_figure.get_c()), rows, colums);

			if (equivalent(prob_f_new.array(), first_figure.array(), first_figure.get_r(), first_figure.get_c()) == false)
			{
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "hint: R_V" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
				}
				find = true;
			}
			cout << "..." << endl;

			fake_figure = first_figure.array();

			second_figure.flipHorizontaly();

			prob_f_new.reInitialise(searchEmpty(fake_figure, rows, colums, second_figure.array(), second_figure.get_r(), second_figure.get_c()), rows, colums);

			if (equivalent(prob_f_new.array(), first_figure.array(), first_figure.get_r(), first_figure.get_c()) == false)
			{
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "hint: R_V_H" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
				}
				find = true;
			}
			cout << "..." << endl;

			fake_figure = first_figure.array();

			second_figure.flipVerticaly();

			prob_f_new.reInitialise(searchEmpty(fake_figure, rows, colums, second_figure.array(), second_figure.get_r(), second_figure.get_c()), rows, colums);

			if (equivalent(prob_f_new.array(), first_figure.array(), first_figure.get_r(), first_figure.get_c()) == false)
			{
				if ((prob_f_new.plenumHalf() < record_plenum) || (prob_f_new.plenumHalf() == 0))
				{
					std::cout << "hint: R_V_H_V" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
				}
				find = true;
			}
			cout << "..." << endl;

		}
	}


	/* try to extend the boundaries */
	if ((record.array() == first_figure.array()) || (find == false))
	{
		int enter = 1;
		std::cout << "\n Extend area!" << endl;

		first_figure.findAngle();
		rows = first_figure.get_r();
		colums = first_figure.get_c();

		second_figure.findAngle();

		size_t **additional_arr = new size_t*[rows + r2 - 1];
		for (int i = 0; i < rows + second_figure.get_r(); i++) additional_arr[i] = new size_t[colums + second_figure.get_c() - 1];
		for (int i(0); i < rows + second_figure.get_r() - 1; i++)
			for (int j(0); j < colums + second_figure.get_c() - 1; j++) additional_arr[i][j] = 0;

		for (int i(0); i < rows; i++)
			for (int j(0); j < colums; j++)
				additional_arr[i][j] = first_figure.array()[i][j];

		f prob_f_new(additional_arr, rows, colums);

		while ((colums < c_rec + 1) && (rows < r_rec + 1))	//bottleneck
		{
			cout << "ROWS: " << rows << "\tCOLUMS: " << colums << endl;
			prob_f_new.reInitialise(searchEmpty(additional_arr, rows, colums, second_figure.array(), second_figure.get_r(), second_figure.get_c()), rows, colums);
			if (equivalent(prob_f_new.array(), first_figure.array(), first_figure.get_r(), first_figure.get_c()) == false)
			{
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "hint: no rotation" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
					find = true;
				}
			}
			cout << "..." << endl;

			backFigure(additional_arr, first_figure.array(), first_figure.get_r(), first_figure.get_c(), rows, colums);

			second_figure.flipVerticaly();

			prob_f_new.reInitialise(searchEmpty(additional_arr, rows, colums, second_figure.array(), second_figure.get_r(), second_figure.get_c()), rows, colums);

			if (equivalent(prob_f_new.array(), first_figure.array(), first_figure.get_r(), first_figure.get_c()) == false)
			{
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "hint: V" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
					find = true;
				}
			}
			cout << "..." << endl;

			backFigure(additional_arr, first_figure.array(), first_figure.get_r(), first_figure.get_c(), rows, colums);

			second_figure.flipHorizontaly();

			prob_f_new.reInitialise(searchEmpty(additional_arr, rows, colums, second_figure.array(), second_figure.get_r(), second_figure.get_c()), rows, colums);

			if (equivalent(prob_f_new.array(), first_figure.array(), first_figure.get_r(), first_figure.get_c()) == false)
			{
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "hint: V_H" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
					find = true;
				}
			}
			cout << "..." << endl;

			backFigure(additional_arr, first_figure.array(), first_figure.get_r(), first_figure.get_c(), rows, colums);

			second_figure.flipVerticaly();

			prob_f_new.reInitialise(searchEmpty(additional_arr, rows, colums, second_figure.array(), second_figure.get_r(), second_figure.get_c()), rows, colums);

			if (equivalent(prob_f_new.array(), first_figure.array(), first_figure.get_r(), first_figure.get_c()) == false)
			{
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "hint: V_H_V" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
					find = true;
				}
			}
			cout << "..." << endl;

			backFigure(additional_arr, first_figure.array(), first_figure.get_r(), first_figure.get_c(), rows, colums);

			second_figure.rotation90R();	//turn and check again

			prob_f_new.reInitialise(searchEmpty(additional_arr, rows, colums, second_figure.array(), second_figure.get_r(), second_figure.get_c()), rows, colums);

			if (equivalent(prob_f_new.array(), first_figure.array(), first_figure.get_r(), first_figure.get_c()) == false)
			{
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "hint: R" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
					find = true;
				}
			}
			cout << "..." << endl;

			backFigure(additional_arr, first_figure.array(), first_figure.get_r(), first_figure.get_c(), rows, colums);

			second_figure.flipVerticaly();

			prob_f_new.reInitialise(searchEmpty(additional_arr, rows, colums, second_figure.array(), second_figure.get_r(), second_figure.get_c()), rows, colums);

			if (equivalent(prob_f_new.array(), first_figure.array(), first_figure.get_r(), first_figure.get_c()) == false)
			{
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "hint: R_V" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
					find = true;
				}
			}
			cout << "..." << endl;

			backFigure(additional_arr, first_figure.array(), first_figure.get_r(), first_figure.get_c(), rows, colums);

			second_figure.flipHorizontaly();

			prob_f_new.reInitialise(searchEmpty(additional_arr, rows, colums, second_figure.array(), second_figure.get_r(), second_figure.get_c()), rows, colums);

			if (equivalent(prob_f_new.array(), first_figure.array(), first_figure.get_r(), first_figure.get_c()) == false)
			{
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "hint: R_V_H" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
					find = true;
				}
			}
			cout << "..." << endl;

			backFigure(additional_arr, first_figure.array(), first_figure.get_r(), first_figure.get_c(), rows, colums);

			second_figure.flipVerticaly();

			prob_f_new.reInitialise(searchEmpty(additional_arr, rows, colums, second_figure.array(), second_figure.get_r(), second_figure.get_c()), rows, colums);

			if (equivalent(prob_f_new.array(), first_figure.array(), first_figure.get_r(), first_figure.get_c()) == false)
			{
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "hint: R_V_H_V" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
					find = true;
				}
			}
			cout << "..." << endl;

			cout << "end of " << enter << " extention: [ " << colums << " * " << rows << " ]" << endl;
			if (colums != c_rec + 1) colums = colums + 1;
			if (rows != r_rec + 1) rows = rows + 1;
			enter++;
		}

	}	

	if (find == true) return record;
	else return first_figure;
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

	result = figures[0];

	for (int i = 0; i < n - 1; i++)
	{
		cout << "compare " << i + 1 << " & " << i + 2 << endl;
		result = mergeFigures(result, result.get_r(), result.get_c(), figures[i + 1], figures[i + 1].get_r(), figures[i + 1].get_c());
	}
	result.delZeros();
}

void polymino::resultFile()
{
	size_t **solution = new size_t*[result.get_r()];
	for (int i = 0; i < rows; i++) solution[i] = new size_t[result.get_c()];
	solution = result.array();

	ofstream f_res("Figures&Result\\result.txt");
	if (!f_res.is_open())
	{
		cout << "Wrong path to the result file!" << endl;
	}
	else
	{
		for (size_t i = 0; i < result.get_r(); i++)
		{
			for (size_t j = 0; j < result.get_c(); j++)
			{
				f_res << solution[i][j] << ' ';
			}
			f_res << endl;
		}
	}
	f_res.close();
	
}

polymino::~polymino()
{

}
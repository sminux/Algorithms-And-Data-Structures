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

	f record(first_figure, r1, c1);	//to return
	f prob_f(first_figure, r1, c1);
	prob_f.findAngle();

	size_t **fake_figure = new size_t*[rows];
	for (int i = 0; i < rows; i++) fake_figure[i] = new size_t[colums];
	for (int i(0); i < r1; i++)
		for (int j(0); j < c1; j++) fake_figure[i][j] = prob_f.array()[i][j];

	f prob_f_second(second_figure, r2, c2);
	prob_f_second.findAngle();

	int record_plenum = c1 + r1 + r2 + c2;		//берем заведомо больше
	rows = prob_f.get_r();
	colums = prob_f.get_c();


	bool find = false;

	if ((sq <= r1*c1) && (prob_f.plenum() >= prob_f_second.square())) //if empty area is adecuatly for second figure
	{
		if ((prob_f.get_r() >= prob_f_second.get_r()) && (prob_f.get_c() >= prob_f_second.get_c()))
		{
			rows = prob_f.get_r();		//maybe it is not nessesary
			colums = prob_f.get_c();	//

			searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
			f prob_f_new(fake_figure, rows, colums);
			if (prob_f_new.array() != prob_f.array())
			{
				cout << "! " << prob_f_new.plenumHalf() << endl;
				prob_f_new.print();
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
				}
				find = true;
			}


			fake_figure = prob_f.array();

			prob_f_second.flipVerticaly();
			searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
			prob_f_new.reInitialise(fake_figure, rows, colums);
			if (prob_f_new.array() != prob_f.array())
			{
				cout << "! " << prob_f_new.plenumHalf() << endl;
				prob_f_new.print();
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "Y" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
				}
				find = true;
			}

			fake_figure = prob_f.array();

			prob_f_second.flipHorizontaly();
			searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
			prob_f_new.reInitialise(fake_figure, rows, colums);
			if (prob_f_new.array() != prob_f.array())
			{
				cout << "! " << prob_f_new.plenumHalf() << endl;
				prob_f_new.print();
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "Y" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
				}
				find = true;
			}

			fake_figure = prob_f.array();

			prob_f_second.flipVerticaly();
			searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
			prob_f_new.reInitialise(fake_figure, rows, colums);
			if (prob_f_new.array() != prob_f.array())
			{
				cout << "! " << prob_f_new.plenumHalf() << endl;
				prob_f_new.print();
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "Y" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
				}
				find = true;
			}

		}

		if ((record.array() == prob_f.array()) || ((prob_f.get_r() < prob_f_second.get_r()) || (prob_f.get_c() < prob_f_second.get_c())))
		{
			prob_f_second.rotation90R();	//turn and check again


			rows = prob_f.get_r();		//maybe it is not nessesary
			colums = prob_f.get_c();	//

			fake_figure = prob_f.array();

			searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
			f prob_f_new(prob_f.array(), rows, colums);
			if (prob_f_new.array() != prob_f.array())
			{
				cout << "! " << prob_f_new.plenumHalf() << endl;
				prob_f_new.print();
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "Y" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
				}
				find = true;
			}

			fake_figure = prob_f.array();

			prob_f_second.flipVerticaly();
			searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
			prob_f_new.reInitialise(fake_figure, rows, colums);
			if (prob_f_new.array() != prob_f.array())
			{
				cout << "! " << prob_f_new.plenumHalf() << endl;
				prob_f_new.print();
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "Y" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
				}
				find = true;
			}

			fake_figure = prob_f.array();

			prob_f_second.flipHorizontaly();
			searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
			prob_f_new.reInitialise(fake_figure, rows, colums);
			prob_f_new.print();
			if (prob_f_new.array() != prob_f.array())
			{
				cout << "! " << prob_f_new.plenumHalf() << endl;
				prob_f_new.print();
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "Y" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
				}
				find = true;
			}

			fake_figure = prob_f.array();

			prob_f_second.flipVerticaly();
			searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
			prob_f_new.reInitialise(fake_figure, rows, colums);
			if (prob_f_new.array() != prob_f.array())
			{
				cout << "! " << prob_f_new.plenumHalf() << endl;
				prob_f_new.print();
				if (prob_f_new.plenumHalf() < record_plenum)
				{
					std::cout << "Y" << endl;
					record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
					record_plenum = prob_f_new.plenumHalf();
				}
				find = true;
			}

		}
	}


	if ((record.array() == prob_f.array()) && (find == false))
		{
			std::cout << "TRUE!" << endl;
			prob_f_second.findAngle();
			prob_f.findAngle();
			rows = prob_f.get_r();
			colums = prob_f.get_c();

			size_t **additional_arr = new size_t*[rows + r2 - 1];
			for (int i = 0; i < rows + r2; i++) additional_arr[i] = new size_t[colums + c2 - 1];
			for (int i(0); i < rows + r2 - 1; i++)
				for (int j(0); j < colums + c2 - 1; j++) additional_arr[i][j] = 0;

			for (int i(0); i < rows; i++)
				for (int j(0); j < colums; j++)
					additional_arr[i][j] = prob_f.array()[i][j];
			
			f prob_f_new(additional_arr, rows, colums);
		
			while ((colums != c1 + c2 - 1) && (rows != r1 + r2 - 1))
			{
				searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
				prob_f_new.reInitialise(fake_figure, rows, colums);
				if (prob_f_new.array() != prob_f.array())
				{
					if (prob_f_new.plenumHalf() < record_plenum)
					{
						record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
						record_plenum = prob_f_new.plenumHalf();
						find = true;
					}
				}

				for (int i(0); i < rows; i++)
					for (int j(0); j < colums; j++)
						additional_arr[i][j] = prob_f.array()[i][j];

				prob_f_second.flipVerticaly();
				searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
				prob_f_new.reInitialise(fake_figure, rows, colums);
				if (prob_f_new.array() != prob_f.array())
				{
					if (prob_f_new.plenumHalf() < record_plenum)
					{
						record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
						record_plenum = prob_f_new.plenumHalf();
						find = true;
					}
				}

				for (int i(0); i < rows; i++)
					for (int j(0); j < colums; j++)
						additional_arr[i][j] = prob_f.array()[i][j];

				prob_f_second.flipHorizontaly();
				searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
				prob_f_new.reInitialise(fake_figure, rows, colums);
				if (prob_f_new.array() != prob_f.array())
				{
					if (prob_f_new.plenumHalf() < record_plenum)
					{
						record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
						record_plenum = prob_f_new.plenumHalf();
						find = true;
					}
				}

				for (int i(0); i < rows; i++)
					for (int j(0); j < colums; j++)
						additional_arr[i][j] = prob_f.array()[i][j];

				prob_f_second.flipVerticaly();
				searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
				prob_f_new.reInitialise(fake_figure, rows, colums);
				if (prob_f_new.array() != prob_f.array())
				{
					if (prob_f_new.plenumHalf() < record_plenum)
					{
						record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
						record_plenum = prob_f_new.plenumHalf();
						find = true;
					}
				}

				for (int i(0); i < rows; i++)
					for (int j(0); j < colums; j++)
						additional_arr[i][j] = prob_f.array()[i][j];

				////////////////////////////////////////////////////
				prob_f_second.rotation90R();	//turn and check again

				searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
				f prob_f_new(fake_figure, rows, colums);
				if (prob_f_new.array() != prob_f.array())
				{
					if (prob_f_new.plenumHalf() < record_plenum)
					{
						record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
						record_plenum = prob_f_new.plenumHalf();
						find = true;
					}
				}

				for (int i(0); i < rows; i++)
					for (int j(0); j < colums; j++)
						additional_arr[i][j] = prob_f.array()[i][j];

				prob_f_second.flipVerticaly();
				searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
				prob_f_new.reInitialise(fake_figure, rows, colums);
				if (prob_f_new.array() != prob_f.array())
				{
					if (prob_f_new.plenumHalf() < record_plenum)
					{
						record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
						record_plenum = prob_f_new.plenumHalf();
						find = true;
					}
				}

				for (int i(0); i < rows; i++)
					for (int j(0); j < colums; j++)
						additional_arr[i][j] = prob_f.array()[i][j];

				prob_f_second.flipHorizontaly();
				searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
				prob_f_new.reInitialise(fake_figure, rows, colums);
				if (prob_f_new.array() != prob_f.array())
				{
					if (prob_f_new.plenumHalf() < record_plenum)
					{
						record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
						record_plenum = prob_f_new.plenumHalf();
						find = true;
					}
				}

				for (int i(0); i < rows; i++)
					for (int j(0); j < colums; j++)
						additional_arr[i][j] = prob_f.array()[i][j];

				prob_f_second.flipVerticaly();
				searchEmpty(fake_figure, rows, colums, prob_f_second.array(), prob_f_second.get_r(), prob_f_second.get_c());
				prob_f_new.reInitialise(fake_figure, rows, colums);
				if (prob_f_new.array() != prob_f.array())
				{
					if (prob_f_new.plenumHalf() < record_plenum)
					{
						record.reInitialise(prob_f_new.array(), prob_f_new.get_r(), prob_f_new.get_c());
						record_plenum = prob_f_new.plenumHalf();
						find = true;
					}
				}
				colums++; rows++;
			}

		}
			

		/*
	{
		size_t **additional_arr = new size_t*[r1 + r2 - 1];
		for (int i = 0; i < r1 + r2; i++) additional_arr[i] = new size_t[c1 + c2 - 1];
		for (int i(0); i < r1 + r2 - 1; i++)
			for (int j(0); j < c1 + c2 - 1; j++) additional_arr[i][j] = 0;

		for (int i(0); i < r1; i++)
			for (int j(0); j < c1; j++)
				additional_arr[i][j] = first_figure[i][j];

		f prob_f_new(first_figure, rows, colums);

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

		prob_f_second.rotation90R();

		while ((find == false) || ((colums != c1 + c2 - 1) && (rows != r1 + r2 - 1)))
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
		}*/
	

	if (find == true) return record.array();
	else
	{
		cout << "Can't compare figures!" << endl;
		return record.array();
	}
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
		//figures[i].reInitialise(solvation, rows, colums);
		//figures[i].print();
		//if (result.plenum() == 0) get_solve = true;
		//else hint = "No ansver";
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
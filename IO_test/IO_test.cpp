#include "AllIn.h"
#include <gtest/gtest.h>

void generate_test()
{
	srand(time(NULL));

	ofstream test("D:\\HomeWork\\Figures&Result\\test.txt");

	if (!test) {
		cout << "Cannot open file!";
	}

	int val = rand() % 1000;

	test << val << endl;

	for (int i = 0; i < val; i++)
	{
		test << i << endl;
		int size = rand() % 1;

		test << size << endl;

		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				test << rand() % 2 << " ";
			}
			test << endl;
		}
	}

	test.close();
}

class f
{
private:
	size_t **data;
	size_t c = 0, r = 0;
public:
	f()
	{
		cout << "ok";
		size_t **data;
		size_t c = 0, r = 0;
	}

	int get_c()
	{
		return c;
	}
	int get_r()
	{
		return r;
	}
	int **read()
	{
		ifstream F("D:\\HomeWork\\Figures&Result\\test.txt");
		if (!F.is_open())
		{
			cout << "Wrong path to the file!" << endl;
		}
		else
		{
			size_t k = 0, lines = 0;
			queue<size_t> q;
			size_t entr;

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
				F.clear();		//for repeated reading
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
						cout << x[i][j] << ' ';
						q.pop();
					}
					cout << endl;
				}

				data = x;	//go in for data[][]
				c = N;
				r = N;
				cout << "\t   Dim: " << c << " * " << r << endl;

				//for (size_t i = 0; i < N; i++) delete[] x[i];
				//delete[] x;
				F.close();
			}
		}
	}

	int square()
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

	void checkCorrect();
	int findAngle();
	void res()
	{
		ofstream f_res("D:\\HomeWork\\Figures&Result\\resut.txt");
		if (!f_res.is_open())
		{
			cout << "Wrong path to the result file!" << endl;
		}
		else
		{
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					f_res << data[i][j] << ' ';
				}
				f_res << endl;
			}
		}
		f_res.close();
	}

	explicit f(const size_t cols) :c{ cols }
	{}
};

class f_test : testing::Test
{
	f* figure;
	f_test()
	{
		figure = new f;
	}
	~f_test()
	{
		delete figure;
	}
};


TEST(InputCheck, figureEmpty)
{
	generate_test();
	f figure;
	bool S = false;
	figure.read();
	if( figure.square() > 0) S = true;
	EXPECT_EQ(true, S);
}

TEST(InputCheck, checkCols)
{
	generate_test();
	f figure;
	figure.read();
	EXPECT_EQ(figure.get_c(), figure.get_r());
}

TEST(O_test, OutputData)
{
	f figure;
	figure.read();
	figure.res();
	ASSERT_EQ(1,1);
}


int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
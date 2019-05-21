#include "Matrix.h"
#include "Exceptions.h"
#define ZERO 0.0001

MyMatrix::MyMatrix()
{
}

MyMatrix::MyMatrix(MyVector v)
{
	MyMatrix m;
	m.data.push_back(v);
	*this = m;
}

int MyMatrix::row()
{
	return this->data.size();
}

MyVector & MyMatrix::operator[](int index)
{
	return this->data[index];
}

std::ostream& operator<<(std::ostream& os, MyMatrix& m) {
	for (int i = 0; i < m.row(); i++)
	{
		for (int j = 0; j < m.col(); j++)
		{
			os << std::setprecision(6) << m[i][j] << " ";
		}
		os << std::endl;
	}
	return os;
};

MyMatrix& operator+(MyMatrix& a, MyMatrix& b)
{
	a = add(a, b);
	return a;
}

MyMatrix& operator-(MyMatrix& a, MyMatrix& b)
{
	a = sub(a, b);
	return a;
}

MyMatrix operator*(MyMatrix a, MyMatrix b)
{
	MyMatrix c;
	c = mul(a, b);
	return c;
}


int MyMatrix::col()
{
	return this->data[0].dimension();
}

MyMatrix add(MyMatrix a, MyMatrix b)
{
	if (a.col() != b.col() || a.row() != b.row())
		throw Exceptions(dimension);

	MyMatrix m;
	for (int i = 0; i < a.row(); i++)
	{
		MyVector v;
		for (int j = 0; j < a.col(); j++)
		{
			v.data.push_back(a[i][j] + b[i][j]);
		}
		m.data.push_back(v);
	}
	return m;
}

MyMatrix sub(MyMatrix a, MyMatrix b)
{
	if (a.col() != b.col() || a.row() != b.row())
		throw Exceptions(dimension);

	MyMatrix m;
	for (int i = 0; i < a.row(); i++)
	{
		MyVector v;
		for (int j = 0; j < a.col(); j++)
		{
			v.data.push_back(a[i][j] - b[i][j]);
		}
		m.data.push_back(v);
	}
	return m;
}

MyMatrix mul(MyMatrix a, MyMatrix b)
{
	MyMatrix m;
	if (a.col() != b.row())
	{
		throw Exceptions(dimension);
	}
	else
		for (int i = 0; i < a.row(); i++)
		{
			MyVector v;
			for (int j = 0; j < b.col(); j++)
			{
				v.data.push_back(0);
				for (int k = 0; k < a.col(); k++)
				{
					v[j] += a[i][k] * b[k][j];
				}
			}
			m.data.push_back(v);
		}
	return m;
}

int rank(MyMatrix m)
{
	int r = m.row();
	m = GaussianElimination(m);
	for (int i = 0; i < m.row(); i++)
	{
		if (m[i].isZero() == true) r--;
	}
	return r;
}

MyMatrix GaussianElimination(MyMatrix m)
{
	/* old version
	double zero = 0.001;
	MyVector temp;
	int x = 0, y = 0;
	int i, j;
	while (x < m.row() && y < m.col())
	{
		while (x < m.row() && m[y][x] < zero && m[y][x]>(-zero))
		{
			j = y + 1;
			while (j < m.col() && m[j][x]<zero && m[j][x]>(-zero)) j++;
			if (j >= m.col())
			{
				x++;
				continue;
			}
			temp = m[j];
			m[j] = m[y];
			m[y] = temp;
			break;
		}
		if (x >= m.row())break;

		for (i = m.row() - 1; i > x; i--)
		{
			m[y][i] /= m[y][x];
		}
		m[y][x] = 1;

		for (j = 0; j < m.col(); j++)
		{
			if (j == y)continue;
			for (i = m.row() - 1; i >= x; i--)
				m[j][i] -= m[y][i] * m[j][x];
		}
		x++; y++;
	}
	return m;
	*/

	MyVector v;
	int pivotpos = 0;
	for (int i = 0; i < m.row(); i++)
	{
		int temp = i;
		while (temp < m.row() && abs(m[temp][i]) < ZERO)temp++;

		if (temp == m.row())continue;

		v = m[i];
		m[i] = m[temp];
		m[temp] = v;
		for (int j = pivotpos + 1; j < m.row(); j++)
		{
			double radio = m[j][i] / m[i][i];
			for (int k = 0; k < m.col(); k++)
			{
				m[j][k] -= m[i][k] * radio;
				if (std::abs(m[j][k]) <= ZERO)
				{
					m[j][k] = 0;
				}
			}
		}
		pivotpos++;
	}
	return m;
}

MyMatrix transpose(MyMatrix m)
{
	MyMatrix t;
	for (int i = 0; i < m.col(); i++)
	{
		MyVector v;
		for (int j = 0; j < m.row(); j++)
		{
			v.data.push_back(m[j][i]);
		}
		t.data.push_back(v);
	}
	return t;
}

double Determinants(MyMatrix m)
{
	/* TLE
	double d = 0;
	if (m.col() != m.row())
	{
		//error
	}
	else if (m.col() == 2)
	{
		return m[0][0] * m[1][1] - m[0][1] * m[1][0];
	}
	else
	{
		for (int i = 0; i < m.row(); i++)
		{
			MyMatrix temp;
			for (int j = 1; j < m.col(); j++)
			{
				MyVector v;
				for (int k = 0; k < m.row(); k++)
				{
					if (k != i) v.data.push_back(m[j][k]);
				}
				temp.data.push_back(v);
			}
			d += m[0][i] * Determinants(temp) * pow(-1,i);
		}
	}
	return d;
	*/

	double d = 1;
	if (m.row() != m.col())
	{
		throw Exceptions(rowNotEqualCol);
	}
	else if (m.row() == 2)
	{
		return m[0][0] * m[1][1] - m[0][1] * m[1][0];
	}
	else
	{
		m = GaussianElimination(m);
		for (int i = 0; i < m.row(); i++)
		{
			d *= m[i][i];
		}
	}
	return d;
}

//The matrix do not push c column and r row.
MyMatrix subMatrix(MyMatrix m, int c, int r)
{
	MyMatrix s;
	for (int i = 0; i < m.row(); i++)
	{
		MyVector v;
		for (int j = 0; j < m.col(); j++)
		{
			if (j != r)v.data.push_back(m[i][j]);
		}
		if (i != c) s.data.push_back(v);
	}
	return s;
}

MyMatrix Adjoint(MyMatrix m)
{
	MyMatrix adj;
	double d = Determinants(m);
	if (d == 0)
	{
		for (int i = 0; i < m.row(); i++)
		{
			MyVector v;
			for (int j = 0; j < m.col(); j++)
			{
				v.data.push_back(pow(-1, j + i) * Determinants(subMatrix(m, j, i)));
			}
			adj.data.push_back(v);
		}
	}
	else
	{
		adj = Inverse(m);
		for (int i = 0; i < adj.row(); i++)
		{
			for (int j = 0; j < adj.col(); j++)
			{
				adj[i][j] *= d;
			}
		}
	}

	return adj;
}

MyMatrix Inverse(MyMatrix m)	//some error number and TLE when size too large
{
	MyMatrix inv;
	double d = Determinants(m);
	if (d == 0)
	{
		throw Exceptions(noInverse);
	}
	else
	{
		/*
		inv = Adjoint(m);
		d = 1 / d;
		for (int i = 0; i < inv.row(); i++)
		{
			for (int j = 0; j < inv.col(); j++)
			{
				inv[i][j] *= d;
			}
		}
		*/

		//Identity matrix
		inv = m;
		for (int i = 0; i < inv.row(); i++)
		{
			for (int j = 0; j < inv.col(); j++)
			{
				inv[i][j] = (i == j) ? 1 : 0;
			}
		}

		//GaussianElimination
		MyVector v;
		for (int i = 0; i < m.row(); i++)
		{
			int temp = i;
			while (temp < m.row() && abs(m[temp][i]) < ZERO)temp++;

			if (temp == m.row())break;

			v = m[i];
			m[i] = m[temp];
			m[temp] = v;

			v = inv[i];
			inv[i] = inv[temp];
			inv[temp] = v;

			for (int j = i + 1; j < m.row(); j++)
			{
				double radio = m[j][i] / m[i][i];
				for (int k = 0; k < m.col(); k++)
				{
					m[j][k] -= m[i][k] * radio;
					inv[j][k] -= inv[i][k] * radio;
				}
			}

		}

		for (int i = 0; i < m.row(); i++)
		{
			double radio = m[i][i];
			for (int j = 0; j < m.col(); j++)
			{
				m[i][j] /= radio;
				inv[i][j] /= radio;
			}
		}

		for (int i = m.row() - 1; i >= 0; i--)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				double radio = m[j][i];
				MyVector v = inv[i];
				for (int k = 0; k < v.dimension(); k++)
				{
					v[k] *= radio;
				}
				inv[j] = sub(inv[j], v);
			}
		}
	}
	return inv;
}

MyMatrix SolveLinearSystem(MyMatrix a, MyMatrix b)
{
	if (a.row() != b.row() || b.col() != 1)
	{
		throw Exceptions(dimension);
	}
	MyMatrix AugmentedMatrix = a;
	for (int i = 0; i < a.row(); i++)
	{
		AugmentedMatrix[i].data.push_back(b[i][0]);
	}
	if (rank(AugmentedMatrix) != rank(a))
	{
		//inconsistent
		std::cout << "Inconsistent." << std::endl;
		throw Exceptions(done);
	}
	else if (rank(a) < a.row())
	{
		//infinity
		std::cout << "Infinity of solutions." << std::endl;
		throw Exceptions(done);
	}


	MyMatrix inv = Inverse(a);
	MyMatrix ans = mul(inv, b);
	return ans;
}

MyMatrix LeastSquare(MyMatrix x, MyMatrix y)	//TLE when size too large.
{
	MyMatrix tx = transpose(x);
	MyMatrix s = mul(tx, x);
	return mul(mul(Inverse(s), tx), y);
}

void FindEigen(MyMatrix m, MyMatrix& eigenVector, MyMatrix& eigenValue)
{

	MyMatrix temp_m;
	MyVector temp_v;
	if (m.col() == 2 && m.row() == 2)
	{
		double equation[3];
		int pos;
		equation[2] = 1;
		equation[1] = (m[0][0] + m[1][1])*(-1);
		equation[0] = m[0][1] * m[1][0] * (-1) + m[0][0] * m[1][1];
		temp_v.data.push_back(((-1)*equation[1] + std::sqrt(std::pow(equation[1], 2) - 4 * equation[2] * equation[0])) / 2 * equation[2]);
		temp_v.data.push_back(((-1)*equation[1] - std::sqrt(std::pow(equation[1], 2) - 4 * equation[2] * equation[0])) / 2 * equation[2]);
		eigenValue.data.push_back(temp_v);
		for (int i = 0; i < 2; i++)
		{
			temp_v.data.clear();
			temp_m = m;
			for (int j = 0; j < 2; j++)
			{
				temp_m[j][j] -= eigenValue[0][i];
			}
			temp_m = GaussianElimination(temp_m);
			temp_v = temp_m[0];
			double temp_d = temp_v[0];
			temp_v[0] = temp_v[1];
			temp_v[1] = temp_d;
			temp_v[0] *= (-1);
			if (temp_v[0] == 0)
			{
				throw(egienerror);
			}
			eigenVector.data.push_back(normalize(temp_v));
		}
	}
	else if (m.col() == 3 && m.row() == 3)
	{
		struct pivot {
			int row;
			int col;
		};
		double equation[4];
		double Q, R, theta;
		equation[3] = -1;
		equation[2] = m[2][2] + m[0][0] + m[1][1];
		equation[1] = (-1)*(m[2][2] * m[0][0] + m[2][2] * m[1][1] + m[0][0] * m[1][1]) +
			m[2][0] * m[0][2] + m[2][1] * m[1][2] + m[0][1] * m[1][0];
		equation[0] = m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[1][0] * m[2][1] -
			(m[2][0] * m[0][2] * m[1][1] + m[0][0] * m[2][1] * m[1][2] + m[0][1] * m[1][0] * m[2][2]);
		for (int i = 0; i < 4; i++)
		{
			equation[i] *= -1;
		}
		Q = (pow(equation[2], 2) - 3 * equation[1]) / 9;
		R = (2 * pow(equation[2], 3) - 9 * equation[1] * equation[2] + 27 * equation[0]) / 54;
		double k = R / sqrt(pow(Q, 3));
		theta = std::acos(k);
		temp_v.data.push_back((-2)*sqrt(Q)*std::cos(theta / 3) - equation[2] / 3);
		temp_v.data.push_back((-2)*sqrt(Q)*cos((theta + acos(-1) * 2) / 3) - equation[2] / 3);
		temp_v.data.push_back((-2)*sqrt(Q)*cos((theta - acos(-1) * 2) / 3) - equation[2] / 3);
		eigenValue.data.push_back(temp_v);
		for (int i = 0; i < 3; i++)
		{
			std::vector<pivot>pivotpos;
			double sol[3] = { 1,1,1 };
			temp_m = m;
			for (int j = 0; j < 3; j++)
			{
				temp_m[j][j] -= temp_v[i];
				if (std::abs(temp_m[j][j]) <= ZERO)
				{
					temp_m[j][j] = 0;
				}
			}
			temp_m = GaussianElimination(temp_m);

			for (int j = temp_m.row() - 1; j >= 0; j--)
			{
				for (int k = 0; k < temp_m.col(); k++)
				{
					if (temp_m[j][k] != 0)
					{
						pivotpos.push_back(pivot{ j,k });
						break;
					}
				}
			}


			for (int j = 0; j < pivotpos.size(); j++)
			{
				if (temp_m.col() - 1 - pivotpos[j].col == 0)
				{
					sol[pivotpos[j].col] = 0;
				}
				else
				{
					for (int k = pivotpos[j].col + 1; k < temp_m.col(); k++)
					{
						if (k == pivotpos[j].col + 1)
						{
							sol[pivotpos[j].col] = temp_m[pivotpos[j].row][k] * (-1)*sol[k];
						}
						else
						{
							sol[pivotpos[j].col] = sol[pivotpos[j].col] + temp_m[pivotpos[j].row][k] * (-1)*sol[k];

						}
					}
					sol[pivotpos[j].col] /= temp_m[pivotpos[j].row][pivotpos[j].col];
				}
			}

			MyVector ansVec;
			for (int j = 0; j < 3; j++)
			{
				if (abs(sol[j]) <= ZERO)
				{
					ansVec.data.push_back(0);
				}
				else
				{
					ansVec.data.push_back(sol[j]);
				}
			}
			eigenVector.data.push_back(normalize(ansVec));


		}

	}
	else
	{
		//???
	}
}

void PowerMethod(MyMatrix m, MyMatrix& eigenVector, MyMatrix& eigenValue)	//Error when number too large
{
	MyVector v;
	if (m.col() != m.row())
	{
		throw Exceptions(dimension);
	}
	MyMatrix guess;
	double error;
	for (int i = 0; i < m.row(); i++)
	{
		MyVector v;
		v.data.push_back(1);
		guess.data.push_back(v);
	}

	do
	{
		MyMatrix newGuess = mul(m, guess);

		for (int i = newGuess.row() - 1; i >= 0; i--)
		{
			newGuess[i][0] /= newGuess[0][0];
		}

		error = guess[1][0] / guess[0][0] - newGuess[1][0] / newGuess[0][0];
		guess = newGuess;
	} while (abs(error) > ZERO);
	v.data.push_back(1);
	for (int i = 1; i < guess.row(); i++)
	{
		guess[i][0] /= guess[0][0];
		v.data.push_back(guess[i][0]);
	}
	guess[0][0] = 1;

	v = normalize(v);

	eigenVector = mul(transpose(mul(m, guess)), guess);
	eigenValue = mul(transpose(guess), guess);
	eigenValue[0][0] = eigenVector[0][0] / eigenValue[0][0];
	eigenVector = v;
}
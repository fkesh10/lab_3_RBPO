module;
#include <math.h>
#include <ostream>
export module Math;

export class Complex
{
private:
	double m_re;
	double m_im;
public:
	Complex(double _re)
	{
		m_re = _re;
		m_im = 0;
	}
	Complex()
	{
		m_re = 0;
		m_im = 0;
	}
	Complex(double _re, double _im)
	{
		m_re = _re;
		m_im = _im;
	}

	static Complex FromExponentialForm(double _mod, double _arg)
	{
		Complex exp_obj;
		exp_obj.m_re = _mod * cos(_arg);
		exp_obj.m_im = _mod * sin(_arg);
		return exp_obj;
	}
	static Complex FromAlgebraicForm(double _re, double _im)
	{
		Complex alg_obj(_re, _im);
		//alg_obj.m_re = _re;
		//alg_obj.m_im = _im;
		return alg_obj;
	}
	double Re() const
	{
		return m_re;
	}
	double Im() const
	{
		return m_im;
	}
	double Mod() const
	{
		return sqrt(m_re * m_re + m_im * m_im);
	}
	double Arg() const
	{
		return atan2(m_im, m_re);
	}

	explicit operator double() const {
		return m_re;
	}
	Complex operator-()
	{
		Complex obj(*this);
		obj.m_im *= -1;
		obj.m_re *= -1;
		return obj;
	}
	Complex& operator++()
	{
		m_re++;
		return (*this);
	}
	Complex operator++(int _post_inc)
	{
		Complex obj(*this);
		++(*this);
		return obj;
	}
	Complex& operator--()
	{
		m_re--;
		return (*this);
	}
	Complex operator--(int _post_dec)
	{
		Complex obj(*this);
		--(*this);
		return obj;
	}
	Complex& operator+=(Complex _obj)
	{
		m_re += _obj.m_re;
		m_im += _obj.m_im;
		return (*this);
	}
	Complex& operator-=(Complex _obj) {
		m_re -= _obj.m_re;
		m_im -= _obj.m_im;
		return (*this);
	}
	Complex& operator*=(Complex _obj) {
		double temp_re = m_re;
		double temp_im = m_im;
		m_re = temp_re * _obj.m_re - temp_im * _obj.m_im;
		m_im = temp_re * _obj.m_im + temp_im * _obj.m_re;
		return (*this);
	}
	Complex& operator/=(Complex _obj) {
		double temp_re1 = m_re, temp_im1 = m_im;
		double temp_re2 = _obj.m_re, temp_im2 = _obj.m_im;
		m_re = (temp_re1 * temp_re2 + temp_im1 * temp_im2) / (pow(temp_re2, 2) + pow(temp_im2, 2));
		m_im = (temp_re2 * temp_im1 - temp_re1 * temp_im2) / (pow(temp_re2, 2) + pow(temp_im2, 2));
		return (*this);
	}
	friend Complex operator+ (const Complex& _obj1, const Complex& _obj2);
	friend Complex operator- (const Complex& _obj1, const Complex& _obj2);
	friend Complex operator* (const Complex& _obj1, const Complex& _obj2);
	friend Complex operator/ (const Complex& _obj1, const Complex& _obj2);

	friend Complex operator ""i(long double _im);
	friend Complex operator ""i(unsigned long long _im);

	friend std::ostream& operator<<(std::ostream& stream, const Complex& _obj);
};
export Complex operator+(const Complex& _obj1, const Complex& _obj2)
{
	return Complex(_obj1.m_re + _obj2.m_re, _obj1.m_im + _obj2.m_im);
}
export Complex operator-(const Complex& _obj1, const Complex& _obj2)
{
	return Complex(_obj1.m_re - _obj2.m_re, _obj1.m_im - _obj2.m_im);
}
export Complex operator*(const Complex& _obj1, const Complex& _obj2)
{
	return Complex((_obj1.m_re * _obj2.m_re - _obj1.m_im * _obj2.m_im),
		(_obj1.m_re * _obj2.m_im + _obj1.m_im * _obj2.m_re));
}
export Complex operator/(const Complex& _obj1, const Complex& _obj2)
{
	return Complex((_obj1.m_re * _obj2.m_re + _obj1.m_im * _obj2.m_im) /
		(_obj2.m_re * _obj2.m_re + _obj2.m_im * _obj2.m_im),
		(_obj2.m_re * _obj1.m_im - _obj1.m_re * _obj2.m_im) /
		(_obj2.m_re * _obj2.m_re + _obj2.m_im * _obj2.m_im));
}
export Complex operator""i(long double _im)
{
	return Complex(0.0, static_cast<double>(_im));
}
export Complex operator""i(unsigned long long _im)
{
	return Complex(0.0, static_cast<double>(_im));
}
export std::ostream& operator<<(std::ostream& stream, const Complex& _obj)
{
	if (_obj.m_im < 0)
	{
		stream << _obj.m_re << " " << _obj.m_im << "i";
	}
	else
	{
		stream << _obj.m_re << " + " << _obj.m_im << "i";
	}
	return stream;
}

export int FindGreatestCommonDivisor(int a, int b)
{
	int r;
	if (a < 0)
		a *= -1;
	if (b < 0)
		b *= -1;
	while (true)
	{
		if (b == 0)
			return a;
		r = a % b;
		a = b;
		b = r;
	}
}
export int FindLeastCommonMultiple(int x, int y) {
	return abs(x * y) / FindGreatestCommonDivisor(x, y);
}

//========================================================================================

export class Rational {
	int m_nominator;
	int m_denominator;
	
public:
	void normalize()
	{
		int nod = FindGreatestCommonDivisor(m_nominator, m_denominator);
		m_nominator /= nod;
		m_denominator /= nod;
		if (m_denominator < 0) {
			m_denominator *= -1;
			m_nominator *= -1;
		}
	}

	Rational()
	{
		m_nominator = 0;
		m_denominator = 1;
	}
	Rational(int _nominator, int _denominator) {
		m_denominator = _denominator;
		m_nominator = _nominator;
		normalize();
	}
	Rational(int _nominator) {
		m_nominator = _nominator;
		m_denominator = 1;
	}
	int Nominator() const {
		return m_nominator;
	}
	int Denominator() const {
		return m_denominator;
	}
	explicit operator double() const {
		return double(m_nominator) / m_denominator;
	}
	Rational operator-() {
		Rational obj(*this);
		obj.m_nominator *= -1;
		return obj;
	}
	Rational& operator++ () {
		m_nominator += m_denominator;
		return (*this);
	}
	Rational operator++ (int _param) {
		Rational obj(*this);
		(*this).m_nominator += m_denominator;
		return obj;
	}
	Rational& operator-- () {
		m_nominator -= m_denominator;
		return (*this);
	}
	Rational operator-- (int _param) {
		Rational obj(*this);
		(*this).m_nominator -= m_denominator;
		return obj;
	}
	Rational& operator+=(Rational _obj) {
		int new_den = FindLeastCommonMultiple(m_denominator, _obj.m_denominator);
		m_nominator = new_den / m_denominator * m_nominator;
		m_nominator += new_den / _obj.m_denominator * _obj.m_nominator;
		m_denominator = new_den;
		normalize();
		return (*this);
	}
	Rational& operator-=(Rational _obj) {
		int new_d = FindGreatestCommonDivisor(m_denominator, _obj.m_denominator);
		m_nominator = new_d / m_denominator * m_nominator;
		m_nominator -= new_d / _obj.m_denominator * _obj.m_nominator;
		m_denominator = new_d;
		normalize();
		return (*this);
	}
	Rational& operator*=(Rational _obj) {
		m_denominator *= _obj.m_denominator;
		m_nominator *= _obj.m_nominator;
		normalize();
		return (*this);
	}
	Rational& operator/=(Rational _obj) {
		m_denominator *= _obj.m_nominator;
		m_nominator *= _obj.m_denominator;
		normalize();
		return (*this);
	}
	friend Rational operator+ (const Rational& _obj1, const Rational& _obj2);
	friend Rational operator- (const Rational& _obj1, const Rational& _obj2);
	friend Rational operator* (const Rational& _obj1, const Rational& _obj2);
	friend Rational operator/(const Rational& _obj1, const Rational& _obj2);

	friend bool operator==(const Rational& _obj1, const Rational& _obj2);
	friend bool operator>(const Rational& _obj1, const Rational& _obj2);
	friend bool operator<(const Rational& _obj1, const Rational& _obj2);
	friend bool operator>=(const Rational& _obj1, const Rational& _obj2);
	friend bool operator<=(const Rational& _obj1, const Rational& _obj2);

	friend std::ostream& operator<<(std::ostream& stream, const Rational& _obj);
};

export Rational operator+ (const Rational& _obj1, const Rational& _obj2) {
	int denominator = FindLeastCommonMultiple(_obj1.m_denominator, _obj2.m_denominator);
	int nominator = denominator / _obj1.m_denominator * _obj1.m_nominator;
	nominator += denominator / _obj2.m_denominator * _obj2.m_nominator;
	return Rational{ nominator, denominator };
}

export Rational operator-(const Rational& _obj1, const Rational& _obj2)
{
	int denominator = FindLeastCommonMultiple(_obj1.m_denominator, _obj2.m_denominator);
	int nominator = denominator / _obj1.m_denominator * _obj1.m_nominator;
	nominator -= denominator / _obj2.m_denominator * _obj2.m_nominator;
	return Rational{ nominator, denominator };
}

export Rational operator*(const Rational& _obj1, const Rational& _obj2)
{
	return Rational{ _obj1.m_nominator * _obj2.m_nominator, _obj2.m_denominator * _obj1.m_denominator };
}

export Rational operator/(const Rational& _obj1, const Rational& _obj2)
{
	return Rational{ _obj1.m_nominator * _obj2.m_denominator,_obj1.m_denominator * _obj2.m_nominator };
}

export bool operator==(const Rational& _obj1, const Rational& _obj2)
{
	return _obj1.m_nominator == _obj2.m_nominator && _obj1.m_denominator == _obj2.m_denominator;
}

export bool operator>(const Rational& _obj1, const Rational& _obj2)
{
	int den = FindLeastCommonMultiple(_obj1.m_denominator, _obj2.m_denominator);
	return den / _obj1.m_denominator * _obj1.m_nominator > den / _obj2.m_denominator * _obj2.m_nominator;
}
export bool operator<(const Rational& _obj1, const Rational& _obj2)
{
	int den = FindLeastCommonMultiple(_obj1.m_denominator, _obj2.m_denominator);
	return den / _obj1.m_denominator * _obj1.m_nominator < den / _obj2.m_denominator * _obj2.m_nominator;
}
export bool operator>=(const Rational& _obj1, const Rational& _obj2)
{
	int den = FindLeastCommonMultiple(_obj1.m_denominator, _obj2.m_denominator);
	return den / _obj1.m_denominator * _obj1.m_nominator >= den / _obj2.m_denominator * _obj2.m_nominator;
}
export bool operator<=(const Rational& _obj1, const Rational& _obj2)
{
	int den = FindLeastCommonMultiple(_obj1.m_denominator, _obj2.m_denominator);
	return den / _obj1.m_denominator * _obj1.m_nominator <= den / _obj2.m_denominator * _obj2.m_nominator;
}

export std::ostream& operator<<(std::ostream& stream, const Rational& _obj) {
	stream << _obj.m_nominator << "|" << _obj.m_denominator;
	return stream;
}

//-----------------------------------------------------------
export Complex f(const Complex& z)
{
	Complex a(1, 10);
	Complex result = 2 * z + (a / z);
	return result;
}

export Rational f(const Rational& r) 
{
	Rational a(13, 10);
	Rational result = 2 * r + (a / r);
	result.normalize();
	return result;
}

export double f(const double& d) 
{
	double a = 1.3;
	double result = 2 * d + (a / d);
	return result;
}
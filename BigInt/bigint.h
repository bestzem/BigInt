#pragma once
#ifndef _BIGINT_H
#define _BIGINT_H
#include <iostream>
const int N = 1024;
class BigInt {
	friend std::ostream &operator<<(std::ostream &os, const BigInt &rhs);
public:
	BigInt() :cData(nullptr), length(0),sign(1){}
	BigInt(int im);
	BigInt(const char *cp);
	BigInt(const char *cp,int len);
	~BigInt();
	BigInt(const BigInt &rhs);
	BigInt& operator=(const BigInt &rhs);
	BigInt& operator+();
	BigInt& operator-();
	BigInt& operator++();
	BigInt& operator--();
	BigInt operator++(int);
	BigInt operator--(int);
	BigInt& operator=(const int &im);
	BigInt& operator+=(const BigInt &rhs);
	BigInt& operator-=(const BigInt &rhs);
	BigInt& operator*=(const BigInt &rhs);
	BigInt& operator/=(const BigInt &rhs);
	char &operator[](const size_t &pos)
	{
		return cData[pos];
	}
	const char & operator[](const size_t &pos) const
	{
		return cData[pos];
	}
	const size_t  getLen() const 
	{
		return length;
	}
	const int & getSign() const
	{
		return sign;
	}
private:
	char *cData;
	size_t length;
	int sign;//通过此处可以改善实现正负
};
//实现要与声明分离。
BigInt operator+(const BigInt &lhs, const BigInt &rhs);
BigInt operator-(const BigInt &lhs, const BigInt &rhs);
BigInt operator*(const BigInt &lhs, const BigInt &rhs);
BigInt operator/(const BigInt &lhs, const BigInt &rhs);
bool operator<(const BigInt &lhs, const BigInt &rhs);
bool operator>(const BigInt &lhs, const BigInt &rhs);
bool operator<=(const BigInt &lhs, const BigInt &rhs);
bool operator>=(const BigInt &lhs, const BigInt &rhs);
bool operator==(const BigInt &lhs, const BigInt &rhs);
bool operator!=(const BigInt &lhs, const BigInt &rhs);
#endif 
//_BIGINT_H
#include <iostream>
#include "bigint.h"
int main()
{
	std::cout << "复合运算测试" << std::endl;
	BigInt a = { "321" }, b = { "123" };
	std::cout << "a\t" << a <<"\tb\t" << b << std::endl;
	a += b;
	std::cout << "a+=b\t"<< "a\t" << a << "\tb\t" << b << std::endl;
	a -= b;
	std::cout<< "a-=b\t" << "a\t" << a << "\tb\t" << b << std::endl;
	a *= b;
	std::cout<< "a*=b\t"  << "a\t" << a << "\tb\t" << b << std::endl;
	a /= b;
	std::cout << "a/=b\t" << "a\t" << a << "\tb\t" << b << std::endl;

	std::cout << "算数运算测试" << std::endl;
	BigInt c = { 321 }, d = { 123 };//构造函数测试
	std::cout << "c\t" << c << "\td\t" << d << std::endl;
	BigInt e = c + d;//一定要将声明放在.h文件中，被扫描。
	std::cout << "c+d\t" << e << std::endl;
	e = c - d;
	std::cout << "c-d\t" << e << std::endl;
	e = c*d;
	std::cout << "c*d\t" << e << std::endl;
 	d = 0;//除数为0测试
	e = c / d;
	std::cout << "c/d\t" << e << std::endl;
	d = 123;
	e = c/d;
	std::cout << "c/d\t" << e << std::endl;

	std::cout << "关系运算测试" << std::endl;
	std::cout << "c\t" << c << "\td\t" << d << "\t"
		<< (c > d ? "c>d" : "c<=d") << std::endl;
	d = 321;
	std::cout << "c\t" << c << "\td\t" << d << "\t"
		<< (c >= d ? "c>=d" : "c<d") << std::endl;
	c = 111;
	d = 000;
	std::cout << "c\t" << c << "\td\t" << d << "\t"
		<< (c == d ? "c=d" : "c!=d") << std::endl;
	d = 222;
	std::cout << "c\t" << c << "\td\t" << d <<"\t"
		<< (c < d ? "c<d" : "c>=d") << std::endl;
	d = 111;
	std::cout << "c\t" << c << "\td\t" << d << "\t"
		<< (c <= d ? "c<=d" : "c>d") << std::endl;

	std::cout << "算数运算测试" << std::endl;
	std::cout << "c\t" << c << "\td\t" << d << std::endl;
	c = ++d;
	std::cout << "c=++d\t" << c << "\t" << d << std::endl;
	c = --d;
	std::cout << "c=--d\t" << c << "\t" << d << std::endl;
	c=d++;
	std::cout << "c=d++\t" << c <<"\t"<<d<< std::endl;
	c=d--;
	std::cout <<"c=d--\t" << c << "\t" << d << std::endl;
	std::cout << "\t\t\t\t\t@zem" << std::endl;
	system("pause");
	return 0;
}
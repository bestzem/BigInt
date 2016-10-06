#include "bigint.h"
#include <exception>
std::ostream &operator<<(std::ostream &os, const BigInt &rhs)
{
	char *cp = rhs.cData;
	if (nullptr == cp)
		return os;
	if (rhs.sign<0)
	{
		os << "-";
	}
	while (*cp != '\0') os << *(cp++);
	return os;
}

BigInt::BigInt(int im)
{
	cData = new char[N];
	int pos = N ;
	cData[--pos] = '\0';
	if (im < 0)
	{
		sign = -1;
		im *= -1;
	}
	else
	{
		sign = 1;
	}
	if (im)
	{
		while (im)
		{
			cData[--pos] = im % 10+'0';
			im /= 10;
		}
	}
	else
	{
		cData[--pos] =  '0';
	}
	length = N - pos -1;
	char *res = new char[length+1];
	int rpos = 0;
	while (pos<N)
	{
		res[rpos++] =cData[pos++];
	}
	char *temp = cData;
	cData = res;
	delete[] temp;
}

BigInt::BigInt(const char * cp)
{
	if (nullptr == cp)
		return;
	length = 0;
	sign = 1;
	if (!isdigit(cp[length]))
	{
		sign = (cp[length] == '-' ? -1 : 1);
		++length;
	}
	while (cp[length++] != '\0');
	cData = new char[length];
	for (int i = 0;i < length;++i)
	{
		cData[i] = cp[i];
	}
	cData[--length] = '\0';
}

BigInt::BigInt(const char * cp,int len)
{
	if (nullptr == cp)
		return;
	length = 0;
	sign = 1;
	int len0 = 0;
	if (!isdigit(cp[length]))
	{
		sign = (cp[length] == '-' ? -1 :1);
		--len0;
	}
	len0 += len;
	length = len0;
	cData = new char[len0+1];
	for (int i = 0;i < len0&&cp[i]!='\0';++i)
	{
		cData[i] = cp[i];
	}
	cData[len0] = '\0';
}

BigInt::~BigInt()
{
	delete[] cData;
}

BigInt::BigInt(const BigInt & rhs)
{
	if (this != &rhs)
	{
		cData=new char[rhs.length + 1];
		length = rhs.length;
		sign = rhs.sign;
		for (size_t i = 0;i < length;++i)
		{
			cData[i] = rhs.cData[i];
		}
		cData[length] = '\0';
	}
	
}

BigInt & BigInt::operator=(const BigInt & rhs)
{
	// TODO: 在此处插入 return 语句
	if (this != &rhs)
	{
		BigInt temp(rhs);
		char *p = cData;
		cData=temp.cData;
		temp.cData = p;
		length = rhs.length;
		sign = rhs.sign;
	}
	return *this;
}

BigInt & BigInt::operator+()
{
	return *this;
	// TODO: 在此处插入 return 语句
}

BigInt & BigInt::operator-()
{
	sign *= -1;
	return *this;
	// TODO: 在此处插入 return 语句
}

BigInt & BigInt::operator++()
{
	// TODO: 在此处插入 return 语句
	*this += 1;
	return *this;
}

BigInt & BigInt::operator--()
{
	// TODO: 在此处插入 return 语句
	*this -= 1;
	return *this;
}

BigInt  BigInt::operator++(int)
{
	// 与前置的区别：1、返回非引用，2、参数要有一个躯壳以作区别
	BigInt temp(*this);
	*this += 1;
	return temp;
}

BigInt  BigInt::operator--(int)
{
	BigInt temp(*this);
	*this -= 1;
	return temp;
}

BigInt & BigInt::operator=(const int & im)
{
	BigInt temp(im);
	char *p = cData;
	cData = temp.cData;
	temp.cData = p;
	length = temp.length;
	sign = temp.sign;
	return *this;
	// TODO: 在此处插入 return 语句
}

BigInt & BigInt::operator+=(const BigInt & rhs)
{
	if (sign*rhs.sign < 0)
	{
		if (sign < 0)
		{
			sign *= -1;
			*this -= rhs;
			sign *= -1;
		}
		else
		{
			BigInt temp = rhs;
			*this -= (-temp);
		}
		return *this;
	}
	char *rp = rhs.cData, *lp = this->cData;
	if (nullptr == rp || nullptr == lp)	return *this;
	int rLen = rhs.length, lLen = this->length;
	int len = (rLen > lLen ? rLen : lLen)+1;
	char *cp = new char[len+1];
	for (int i = 0;i < len ;++i) cp[i] = '0';
	cp[len] = '\0';
	int i = rLen - 1, j = lLen - 1, k = len - 1, c = 0;
	for (;i >= 0 && j >= 0;--i, --j,--k)
	{
		int r = rp[i] - '0', l = lp[j] - '0';
		int cVal = r + l + c;
		cp[k] += (cVal % 10);
		c = cVal/ 10;
	}
	while (j >= 0)
	{
		int  l = lp[j] - '0'+c;
		cp[k] += (l % 10);
		c = l/ 10;
		--j;
		--k;
	}
	while (i >= 0)
	{
		int  r = rp[i] - '0'+c;
		cp[k] += (r % 10 );
		c = r / 10;
		--i;
		--k;
	}
	cp[k] = c + '0';
	delete[] cData;
	int start = 0;
	while (cp[start] == '0') ++start;
	char *res = new char[len - start + 1];
	length = len-start;
	i = 0;
	while (start < len)
	{
		res[i++] = cp[start++];
	}
	res[i] = '\0';
	cData = res;
	delete[] cp;
	return *this;
	// TODO: 在此处插入 return 语句
}

BigInt & BigInt::operator-=(const BigInt & rhs)
{

	// TODO: 在此处插入 return 语句
	if (sign*rhs.sign < 0)
	{
		if (sign < 0)
		{
			sign *= -1;
			*this += rhs;
			sign *= -1;
		}
		else
		{
			BigInt temp = rhs;
			*this += (-temp);
		}
		return *this;
	}
	if (*this < rhs)
	{
		BigInt temp = rhs;
		temp -= *this;
		*this = temp;
		sign = -1;
		return *this;
	}
	//*this>=rhs
	char *rp = rhs.cData, *lp = this->cData;
	int rLen = rhs.length, lLen = this->length;
	int len = (rLen > lLen ? rLen : lLen);
	char *cp = new char[len+1];
	for (int i = 0;i < len;++i) cp[i] = '0';
	cp[len] = '\0';
	int i = rLen - 1, j = lLen - 1, k = len - 1, c = 0;
	for (;i >= 0 && j >= 0;--i, --j, --k)
	{
		int r = rp[i] - '0', l = lp[j] - '0';
		int cVal = l-r+c;
		if (cVal < 0)
		{
			c = -1;
			cVal += 10;
		}
		else
		{
			c = 0;
		}
		cp[k] += cVal;
	}
	while (j >= 0)
	{
		int l = lp[j] - '0';
		int cVal = l  + c;
		if (cVal < 0)
		{
			c = -1;
			cVal += 10;
		}
		else
		{
			c = 0;
		}
		cp[k] += cVal;
		--j;
		--k;
	}
	delete[] this->cData;
	int start = 0;
	while (cp[start] == '0') ++start;
	char *res = new char[len - start + 1];
	length = len - start ;
	i = 0;
	while (start < len)
	{
		res[i++] = cp[start++];
	}
	res[i] = '\0';
	cData = res;
	delete[] cp;
	return *this;
}

BigInt & BigInt::operator*=(const BigInt & rhs)
{
	// TODO: 在此处插入 return 语句
	char *rp = rhs.cData, *lp = this->cData;
	int rLen = rhs.length, lLen = this->length;
	int len = N;
	char *cp = new char[len+1 ];
	for (int i = 0;i < len;++i) cp[i] = '0';
	cp[len] = '\0';
	for (int rPos = rLen - 1, cPos = len - 1;rPos >= 0;--rPos, --cPos)
	{
		int k = cPos, c = 0;
		for (int lPos = lLen - 1;lPos >= 0;--lPos,--k)
		{
			int rVal = rp[rPos] - '0';
			int lVal = lp[lPos] - '0';
			int cVal = cp[k] - '0' + rVal*lVal + c;
			cp[k]=(cVal % 10)+'0';
			c = cVal / 10;
		}
	}
	delete[] this->cData;
	int start = 0;
	while (cp[start] == '0') ++start;
	char *res = new char[len - start + 1];
	length = len - start;
	int i = 0;
	while (start < len)
	{
		res[i++] = cp[start++];
	}
	res[i] = '\0';
	cData = res;
	delete[] cp;
	sign *= rhs.sign;
	return *this;
}

BigInt & BigInt::operator/=(const BigInt & rhs)
{
	// TODO: 在此处插入 return 语句
	try {
		if (rhs == 0)
			throw std::runtime_error("divider is zero.");
	}catch (std::runtime_error err) {
		std::cout << err.what() << std::endl;
		*this = 0;
		return *this;
	}
	char *rp = rhs.cData, *lp = this->cData;
	int rLen = rhs.length, lLen = this->length;
	if (lLen == rLen)
	{
		char *cp = new char[2];
		if (*this>rhs)
		{
			int val = (lp[0]-'0') / (rp[0]-'0');
			BigInt temp{ val };
			if (temp*rhs > *this)
			{
				cp[0] = val - 1 + '0';
			}
			else
			{
				cp[0] = val+'0';
			}
			
		}
		else if(*this<rhs)
		{
			cp[0] = '0';
		}
		else
		{
			cp[0] = '1';
		}
		cp[1] = '\0';
		this->cData = cp;
		this->length = 1;
	}
	else
	{
		int len = lLen-rLen+1;
		char *cp = new char[len + 1];
		for (int i = 0;i < len;++i) cp[i] = '0';
		cp[len] = '\0';
		BigInt mod{ "0" };
		BigInt temp(lp, rLen);
		BigInt t = temp / rhs;
		cp[0] = t.cData[0];
		mod = temp - t*rhs;
		for (int i = 1,lPos = rLen;lPos<lLen;++i, ++lPos)
		{
			BigInt temp1(lp + lPos,1);
			mod *= {"10"};
			temp1 += mod;
			BigInt t=temp1 / rhs;
			cp[i] = t.cData[0];
			mod = temp1 - t*rhs;
		}
		this->cData = cp;
		this->length = len;
	}
	delete[] lp;
	sign *= rhs.sign;
	return *this;
}

BigInt operator+(const BigInt &lhs, const BigInt &rhs)
{
	BigInt sum(lhs);
	sum += rhs;
	return sum;
}

BigInt operator-(const BigInt &lhs, const BigInt &rhs)
{
	BigInt sub(lhs);
	sub -= rhs;
	return sub;
}

BigInt operator*(const BigInt &lhs, const BigInt &rhs)
{
	BigInt mul(lhs);
	mul *= rhs;
	return mul;
}

BigInt operator/(const BigInt & lhs, const BigInt & rhs)
{
	BigInt div(lhs);
	div /= rhs;
	return div;
}

bool operator<(const BigInt & lhs, const BigInt & rhs)
{
	if (lhs.getSign()*rhs.getSign() < 0)
	{
		if (lhs.getSign() > 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	size_t lLen = lhs.getLen(), rLen = rhs.getLen();
	bool flag = true;//lhs<rhs
	if (lLen == rLen)
	{
		size_t pos = 0;
		while (pos<lLen)
		{
			if (lhs[pos] > rhs[pos])
			{
				flag = false;
				break;
			}
			else if (lhs[pos] < rhs[pos])
			{
				break;
			}
			++pos;
		}
		if (pos==lLen&&lhs[--pos] == rhs[--pos])
			flag = false;
	}
	else
	{
		flag = lLen< rLen;
	}
	if (lhs.getSign() < 0)
	{
		flag = !flag;
	}
	return flag;
}

bool operator>(const BigInt & lhs, const BigInt & rhs)
{
	if (lhs.getSign()*rhs.getSign() < 0)
	{
		if (lhs.getSign() < 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	size_t lLen = lhs.getLen(), rLen = rhs.getLen();
	bool flag = true;//lhs>rhs
	if (lLen == rLen)
	{
		size_t pos = 0;
		while (pos<lLen)
		{
			if (lhs[pos] < rhs[pos])
			{
				flag = false;
				break;
			}
			else if (lhs[pos] > rhs[pos])
			{
				break;
			}
			++pos;
		}
		if (pos == lLen&&lhs[--pos] == rhs[--pos])
			flag = false;
	}
	else
	{
		flag = lLen > rLen;
	}
	if (lhs.getSign() < 0)
	{
		flag = !flag;
	}
	return flag;
}

bool operator<=(const BigInt & lhs, const BigInt & rhs)
{
	return lhs<rhs||lhs==rhs;
}

bool operator>=(const BigInt & lhs, const BigInt & rhs)
{
	return lhs>rhs || lhs == rhs;
}

bool operator==(const BigInt & lhs, const BigInt & rhs)
{
	if (lhs.getSign() != rhs.getSign())
	{
		return false;
	}
	size_t lLen = lhs.getLen(), rLen = rhs.getLen();
	bool flag = true;//lhs=rhs
	if (lLen == rLen)
	{
		size_t pos = 0;
		while (pos<lLen)
		{
			if (lhs[pos] != rhs[pos])
			{
				flag = false;
				break;
			}
			++pos;
		}
	}
	else
	{
		flag = false;
	}
	return flag;
}

bool operator!=(const BigInt & lhs, const BigInt & rhs)
{
	return !(lhs==rhs);
}

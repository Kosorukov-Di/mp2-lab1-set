// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if(len > 0) 
	{
		BitLen = len;
		MemLen = (int)((len-1)/(sizeof(TELEM)*8))+1;
		pMem = new TELEM[MemLen];
		for(int i=0; i<MemLen; i++) pMem[i] = 0;
	}
	else 
	{
		throw "Negga value!!!";
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for(int i=0; i<MemLen; i++) pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if(n<BitLen) 
	{
		return n/(sizeof(TELEM)*8);
	}
	else
	{
		throw "Out of range!!!";
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if(n<BitLen) 
	{
		int npos = n - sizeof(TELEM)*8*GetMemIndex(n);
		return 1<<npos;
	}
	else
	{
		throw "Out of range!!!";
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if(n<BitLen && n>=0) 
	{
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
	else
	{
		throw "Out of range!!!";
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if(n<BitLen && n>=0) 
	{
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}
	else
	{
		throw "Out of range!!!";
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if(n<BitLen && n>=0) 
	{
		return ((pMem[GetMemIndex(n)] | GetMemMask(n)) == pMem[GetMemIndex(n)]);
	}
	else
	{
		throw "Out of range!!!";
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if(this!=&bf){
		if(bf.MemLen != MemLen) {
			delete[] pMem;
			MemLen = bf.MemLen;
			pMem = new TELEM[MemLen];
		}
		BitLen = bf.BitLen;
		for(int i=0; i<MemLen; i++) pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if(bf.BitLen != BitLen) return false;
	for(int i=0; i<MemLen; i++) 
		if(pMem[i] != bf.pMem[i]) return false;
	return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(operator==(bf));
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{

	int b, n;
	if(BitLen < bf.BitLen) {
		b = bf.BitLen;
		n = bf.MemLen;
	} 
	else 
	{
		b = BitLen;
		n = MemLen;
	}
	TBitField or(b);
	for(int i=0; i<n; i++)
	{
		or.pMem[i]= pMem[i] | bf.pMem[i];
	}
	return or;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int b, n;
	if(BitLen < bf.BitLen) {
		b = bf.BitLen;
		n = bf.MemLen;
	} 
	else 
	{
		b = BitLen;
		n = MemLen;
	}
	TBitField or(b);
	for(int i=0; i<n; i++)
	{
		or.pMem[i]= pMem[i] & bf.pMem[i];
	}
	return or;
}

TBitField TBitField::operator~(void) // отрицание
{
	for(int i=0; i<MemLen-1; i++) pMem[i] = ~pMem[i];
	for(int i=(MemLen-1)*(sizeof(TELEM)*8); i<BitLen; i++) {
		if(GetBit(i)) ClrBit(i); else SetBit(i);
	}
	return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int inp;
	for(int i=0; i<bf.BitLen; i++) {
		istr >> inp;
		if(inp==0) bf.ClrBit(i); else bf.SetBit(i);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for(int i=0; i<bf.BitLen; i++)
		ostr << bf.GetBit(i);
	return ostr;
}

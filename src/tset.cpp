// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
//	TBitField bf(mp);
//	BitField = bf;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
	MaxPower = bf.GetLength();
	BitField = bf;
}

TSet::operator TBitField()
{
	return TBitField(BitField);
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if(Elem < MaxPower)
	{
		return BitField.GetBit(Elem);
	}
	else throw "Out of range";
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if(Elem < MaxPower)
	{
		BitField.SetBit(Elem);
	}
	else throw "Out of range";
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if(Elem<MaxPower)
	{
		BitField.ClrBit(Elem);
	}
	else throw "Out of range";
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int n;
	if(MaxPower < s.MaxPower) n = s.MaxPower; else n = MaxPower;

	TSet sum(n);
	sum.BitField = BitField | s.BitField;
	return sum;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if(Elem < MaxPower)
	{
		TSet sum(*this);
		sum.InsElem(Elem);
		return sum;
	}
	else throw "Out of range";
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if(Elem < MaxPower)
	{
		TSet sum(*this);
		sum.DelElem(Elem);
		return sum;
	}
	else throw "Out of range";
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int n;
	if(MaxPower < s.MaxPower) n = s.MaxPower; else n = MaxPower;

	TSet sum(n);
	sum.BitField = BitField & s.BitField;
	return sum;
}

TSet TSet::operator~(void) // дополнение
{
	TSet add(MaxPower);
	add.BitField=~BitField;
	return add;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	return ostr;
}

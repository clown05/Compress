#pragma once

typedef long long LongType;

struct CharInfo
{
	unsigned char _ch;
	LongType _count;
	string _code;

	CharInfo(LongType count = 0)
		:_count(count)
		, _ch(0)
	{}

	LongType operator+ (const CharInfo& ci)const
	{
		return _count + ci._count;
	}
	
	bool operator!= (const CharInfo& ci)const
	{
		return _count != ci._count;
	}

	bool operator< (const CharInfo& ci)const
	{
		return _count < ci._count;
	}
};

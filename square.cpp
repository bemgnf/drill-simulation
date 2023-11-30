#include "square.h"
#include <iostream>
#include "geometris.h"

//i->x, j->y
Square::Square(int i, int j)
{

	is_work = new bool(false);
	p1 = new float(i * prs);
	p2 = new float(j * prs);
	m = new int(i);
	n = new int(j);
	bp1 = new float();
	bp2 = new float();
	bp3 = new float();
	pgp1 = new float();
	pgp2 = new float();
	pgp3 = new float();
	gp1 = new float();
	gp2 = new float();
	gp3 = new float();
	sr = new float();
	st = new float();

}

Square::~Square()
{
	delete is_work, p1, p2, m, n, bp1, bp2, bp3, gp1, gp2, gp3, pgp1, pgp2, pgp3, st, sr;
}

const bool Square::if_work()
{
	/*if (*is_work)
	{
		std::cout << "working!\n";
	}
	else
	{
		std::cout << "not work!\n";
	}*/
	return *is_work;
}

void Square::work_on()
{
	*is_work = true;
}

void Square::work_off()
{
	*is_work = false;
}

const float Square::getRealpos(char a)//这里是在齿面的位置，是物理单位的
{
	//std::cout << "Real: x --> " << *p1 << ", y --> " << *p2 << std::endl;
	if (a=='x')
	{
		return *p1;
	}
	else
	{
		return *p2;
	}

}

const int Square::getRefpos(char a)//这里是在齿面的位置，是数数第几个的
{
	//std::cout << "Ref: x --> " << *m << ", y --> " << *n << std::endl;
	if (a == 'x')
	{
		return *m;
	}
	else
	{
		return *n;
	}

}
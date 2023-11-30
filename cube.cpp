#include "cube.h"
#include <iostream>
#include "geometris.h"

Cube::Cube(int i, int j, int k)
{
	is_exist = new bool(true);
	p1 = new float(i * prs);
	p2 = new float(j * prs);
	p3 = new float(k * prs);
	l = new int(i);
	m = new int(j);
	n = new int(k);
}

Cube::~Cube()
{
	delete is_exist, p1, p2, p3, l, m, n;
}

const bool Cube::if_exist()
{
	/*if (*is_work)
	{
		std::cout << "working!\n";
	}
	else
	{
		std::cout << "not work!\n";
	}*/
	return *is_exist;
}

void Cube::cube_del()
{
	*is_exist = false;
}

void Cube::cube_rep()
{
	*is_exist = true;
}

const float* Cube::getRealpos()
{
	//std::cout << "Real: x --> " << *p1 << ", y --> " << *p2 << "Real: z --> " << *p3 << std::endl;
	float temp[3];
	temp[0] = *p1;
	temp[1] = *p2;
	temp[2] = *p3;
	return temp;
}

const int* Cube::getRefpos()
{
	//std::cout << "Ref: x --> " << *l << ", y --> " << *m << "Ref: z --> " << *n << std::endl;
	int temp[3];
	temp[0] = *l;
	temp[1] = *m;
	temp[2] = *n;
	return temp;
}
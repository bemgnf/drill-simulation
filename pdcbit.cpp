#include <fstream>
#include <cassert>
#include <iostream>
#include "pdcbit.h"

Pdcbit::Pdcbit(unsigned short int blade, unsigned short int ccount, std::string filepath):
	blade(blade), ccount(ccount), rspeed(0), dspeed(0), doc(0)
{
	add_cutters(filepath);
	x = new float(0);
	y = new float(0);
	z = new float(0);
	alpha = new float(0);
	beta = new float(0);
	gamma = new float(0);
}

Pdcbit::~Pdcbit()
{
	delete x, y, z, alpha, beta, gamma;
	for (auto i : all_c)
	{
		if (i)
		{
			delete i;
		}
	}
}

void Pdcbit::add_cutters(std::string filepath)
{
	float dia; //直径
	unsigned short int n; //全局所属序号
	unsigned short int b; //所在刀翼号
	unsigned short int bn; //某刀翼上所属序号
	float x; //位置
	float y;
	float z;
	float alp; //方向
	float bet;
	float gam;
	std::ifstream infile;
	infile.open(filepath, std::ios::in);
	assert(infile.is_open());
	int i = 0;
	while (!infile.eof())
	{
		infile >> dia >> n >> b >> bn >>
			x >> y >> z >> alp >> bet >> gam;
		//std::cout << i << std::endl;
		all_c.push_back(new Cutter(dia, n, b, bn, x, y, z, alp, bet, gam));
		++i;
	}
	infile.close();
	std::cout << "add " << i << " cutters\n";
}

void Pdcbit::set_premeter(float rs, float ds, float d)
{
	rspeed = rs;
	dspeed = ds;
	doc = d;
}

void Pdcbit::rotate()
{
	*gamma = *gamma + 1;
}

void Pdcbit::drilling(float delt_gamma)
{
	*gamma = *gamma + delt_gamma;
	*z = *z + doc * delt_gamma / 360;
	for (auto i : all_c)
	{
		if (i)
		{
			i->move(doc * delt_gamma / 360, delt_gamma);
		}
	}
}

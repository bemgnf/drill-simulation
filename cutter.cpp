#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include "cutter.h"

Cutter::Cutter(float _dia, unsigned short int _n, unsigned short int _b, unsigned short int _bn,
	float _r, float _t, float _h, float alp, float bet, float gam):
	dia(_dia),n(_n),b(_b),bn(_bn)
{
	r = new float(_r);
	t = new float(_t);
	h = new float(_h);
	alpha = new float(alp);
	beta = new float(bet);
	gamma = new float(gam-_t);
	square_count = new int(dia / prs + 1);
	flatpoint = new std::array<Square*, 2000 * 2000>();
	buildWorkflat();
	transfertobit();
}

Cutter::~Cutter()
{
	delete square_count, r, t, h, alpha, beta, gamma;
	for (auto i : *flatpoint)
	{
		delete i;
	}
	delete flatpoint;
}

void Cutter::buildWorkflat()
{
	for (int j = 0; j < *square_count; j++)
	{
		for (int i = 0; i < *square_count; i++)
		{
			float m = i - 0.5 * dia / prs;
			int im = (m > 0.0) ? floor(m + 0.5) : ceil(m - 0.5);
			float n = j - dia / prs;
			//float n = j - 0.5 * dia / prs; 中心点
			int jn = ceil(n - 0.5);
			float rr = 0.5 * dia / prs;
			int rrr = (rr > 0.0) ? floor(rr + 0.5) : ceil(rr - 0.5);
			if ((pow(im, 2) + pow(jn+rr, 2)) <= pow(rrr, 2)) //设置的单元个数是每齿面pow(dia/prs+1,2)
			{
				(*flatpoint)[i + *square_count * j] = new Square(im, jn); //此处校正下标,注意，浮点数丢失
				//std::cout << m << ", " << n << std::endl;
			}
			/*else
			{
				(*flatpoint)[i + *square_count * j] = nullptr;
				//std::cout << i << ", " << j << "no" << std::endl;
			}*/
		}
	}
	//std::cout << "done" << std::endl;
}

Square* Cutter::get_flatpoint(float x, float y)
{
	float m = x / prs;
	int i = (m >= 0.0) ? floor(m + 0.5) : ceil(m - 0.5);
	float n = y / prs;
	int j = (n >= 0.0) ? floor(n + 0.5) : ceil(n - 0.5);
	//return (*flatpoint)[i + 0.5 * dia / prs + *square_count * (j + 0.5 * dia / prs)]; 中心点
	return (*flatpoint)[i + 0.5 * dia / prs + *square_count * (j + dia / prs)];
}

Square* Cutter::get_flatpoint(int i, int j)
{
	//return (*flatpoint)[i+ 0.5 * dia / prs + *square_count * (j+ 0.5 * dia / prs)]; 中心点
	return (*flatpoint)[i+ 0.5 * dia / prs + *square_count * (j + dia / prs)];
}

void Cutter::resetWorkflat()
{
	for (auto i : *flatpoint)
	{
		while (i&&i->if_work())
		{
			i->work_off();
		}
	}
	//std::cout << "all cutter flat reset!\n";
}

void Cutter::saveWorkflat(std::string filepath)
{
	std::ofstream outfile;
	outfile.open(filepath, std::ios::out | std::ios::trunc);
	for (auto i : (*flatpoint))
	{
		if (i)
		{
			outfile << i->getRefpos('x') <<" "<< i->getRefpos('y') << " "
				<< i->getRealpos('x') << " " << i->getRealpos('y') << " "
				<< i->if_work() << std::endl;
		}
	}
	outfile.close();
}

void Cutter::transfertobit()
{
	for (auto i : *flatpoint)
	{
		if (i)
		{
			//version6 此版本正确！！！
			*(i->pgp1) = i->getRealpos('x');
			*(i->pgp2) = i->getRealpos('z') * sin(*alpha * M_PI / -180);
			*(i->pgp3) = i->getRealpos('z') * cos(*alpha * M_PI / -180);

			*(i->bp1) = *(i->pgp1) * cos(*gamma * M_PI / -180) + *(i->pgp2) * sin(*gamma * M_PI / -180);
			*(i->bp2) = *(i->pgp2) * -sin(*gamma * M_PI / -180) + *(i->pgp2) * cos(*gamma * M_PI / -180);
			*(i->bp3) = *(i->pgp3);

			*(i->pgp1) = *(i->bp1) * cos(*beta * M_PI / -180) + *(i->bp3) * -sin(*beta * M_PI / -180);
			*(i->pgp2) = *(i->bp2);
			*(i->pgp3) = *(i->bp1) * sin(*beta * M_PI / -180) + *(i->bp3) * cos(*beta * M_PI / -180);

			*(i->bp1) = *(i->pgp1) * cos(*t * M_PI / -180) + *(i->pgp2) * sin(*t * M_PI / -180) + *r * cos(*t * M_PI / 180);
			*(i->bp2) = *(i->pgp1) * -sin(*t * M_PI / -180) + *(i->pgp2) * cos(*t * M_PI / -180) + *r * sin(*t * M_PI / 180);
			*(i->bp3) = *(i->pgp3) + *h;

			//version5
			/**(i->pgp1) = i->getRealpos('x') * cos(*t * M_PI / 180)- i->getRealpos('z') * sin(*t * M_PI / 180) ;
			*(i->pgp2) = i->getRealpos('x') * sin(*t * M_PI / 180) + i->getRealpos('z') * cos(*t * M_PI / 180) ;
			*(i->pgp3) = 0;
			
			*(i->bp1) = *(i->pgp1) * cos(*beta * M_PI / 180) + *(i->pgp3) * sin(*beta * M_PI / 180);
			*(i->bp2) = *(i->pgp2);
			*(i->bp3) = -*(i->pgp1) * sin(*beta * M_PI / 180) + *(i->pgp3) * cos(*beta * M_PI / 180);

			*(i->pgp1) = *(i->bp1) * cos(*gamma * M_PI / 180) - *(i->bp2) * sin(*gamma * M_PI / 180);
			*(i->pgp2) = *(i->bp1) * sin(*gamma * M_PI / 180) + *(i->bp2) * cos(*gamma * M_PI / 180);
			*(i->pgp3) = *(i->bp3);

			*(i->bp1) = *(i->pgp1) + *r * cos(*t * M_PI / 180);
			*(i->bp2) = *(i->pgp2) * cos(*alpha * M_PI / 180) - *(i->pgp3) * sin(*alpha * M_PI / 180) + *r * sin(*t * M_PI / 180);
			*(i->bp3) = *(i->pgp2) * sin(*alpha * M_PI / 180) + *(i->pgp3) * cos(*alpha * M_PI / 180)+ *h;*/

			//version4
			/**(i->bp1) = i->getRealpos('x') * (-sin(*gamma * M_PI / 180) * sin(*t * M_PI / 180) +
				cos(*beta * M_PI / 180) * cos(*gamma * M_PI / 180) * cos(*t * M_PI / 180)) +
				i->getRealpos('z') * sin(*beta * M_PI / 180) * cos(*gamma * M_PI / 180)
				+ *r * cos(*t * M_PI / 180);
			*(i->bp2) = i->getRealpos('x') * ((sin(*alpha * M_PI / 180) * sin(*beta * M_PI / 180) +
				sin(*gamma * M_PI / 180) * cos(*alpha * M_PI / 180) * cos(*beta * M_PI / 180)) * cos(*t * M_PI / 180) +
				sin(*t * M_PI / 180) * cos(*alpha * M_PI / 180) * cos(*gamma * M_PI / 180)) -
				i->getRealpos('z') * (-sin(*alpha * M_PI / 180) * cos(*beta * M_PI / 180) +
					sin(*beta * M_PI / 180) * sin(*gamma * M_PI / 180) * cos(*alpha * M_PI / 180))
				+ *r * sin(*t * M_PI / 180);
			*(i->bp3) = i->getRealpos('x') * ((sin(*alpha * M_PI / 180) * sin(*gamma * M_PI / 180) * cos(*beta * M_PI / 180) -
				sin(*beta * M_PI / 180) * cos(*alpha * M_PI / 180)) * cos(*t * M_PI / 180) +
				sin(*alpha * M_PI / 180) * sin(*t * M_PI / 180) * cos(*gamma * M_PI / 180)) +
				i->getRealpos('z') * (sin(*alpha * M_PI / 180) * sin(*beta * M_PI / 180) * sin(*gamma * M_PI / 180) +
					cos(*alpha * M_PI / 180) * cos(*beta * M_PI / 180))
				+ *h;*/
			//version3
			/**(i->bp1) = i->getRealpos('x') * (-sin(*alpha * M_PI / -180) * sin(*t * M_PI / -180) +
				cos(*beta * M_PI / -180) * cos(*gamma * M_PI / -180) * cos(*t * M_PI / -180)) +
				i->getRealpos('z') * ((sin(*gamma * M_PI / -180) * cos(*beta * M_PI / -180) * cos(*t * M_PI / -180) +
					sin(*t * M_PI / -180) * cos(*gamma * M_PI / -180)) * sin(*alpha * M_PI / -180) -
					sin(*beta * M_PI / -180) * cos(*alpha * M_PI / -180) * cos(*t * M_PI / -180))
				+ *r * cos(*t * M_PI / 180);
			*(i->bp2) = i->getRealpos('x') * (-sin(*alpha * M_PI / -180) * cos(*t * M_PI / -180) -
				sin(*t * M_PI / -180) * cos(*beta * M_PI / -180) * cos(*gamma * M_PI / -180)) +
				i->getRealpos('z') * ((-sin(*gamma * M_PI / -180) * sin(*t * M_PI / -180) * cos(*beta * M_PI / -180) +
					cos(*gamma * M_PI / -180) * cos(*t * M_PI / -180)) * sin(*alpha * M_PI / -180) +
					sin(*beta * M_PI / -180) * sin(*t * M_PI / -180) * cos(*alpha * M_PI / -180))
				+ *r * sin(*t * M_PI / 180);
			*(i->bp3) = i->getRealpos('x') * sin(*beta * M_PI / -180) * cos(*gamma * M_PI / -180) -
				i->getRealpos('z') * (sin(*alpha * M_PI / -180) * sin(*beta * M_PI / -180) * sin(*gamma * M_PI / -180) +
					cos(*alpha * M_PI / -180) * cos(*beta * M_PI / -180))
				+ *h;*/
			//version2
			/**(i->bp1) = i->getRealpos('x') * (-(sin(*alpha * M_PI / -180) * sin(*beta * M_PI / -180) +
				sin(*gamma * M_PI / -180) * cos(*alpha * M_PI / -180) * cos(*beta * M_PI / -180)) * sin(*t * M_PI / -180) +
				cos(*beta * M_PI / -180) * cos(*gamma * M_PI / -180) * cos(*t * M_PI / -180)) +
				i->getRealpos('y') * ((sin(*alpha * M_PI / -180) * sin(*beta * M_PI / -180) +
					sin(*gamma * M_PI / -180) * cos(*alpha * M_PI / -180) * cos(*beta * M_PI / -180)) * cos(*t * M_PI / -180) +
					sin(*t * M_PI / -180) * cos(*beta * M_PI / -180) * cos(*gamma * M_PI / -180)) + *r * cos(*t * M_PI / -180);
			*(i->bp2) = i->getRealpos('x') * (-sin(*gamma * M_PI / -180) * cos(*t * M_PI / -180) -
				sin(*t * M_PI / -180) * cos(*alpha * M_PI / -180) * cos(*gamma * M_PI / -180)) -
				i->getRealpos('y') * (-sin(*gamma * M_PI / -180) * sin(*t * M_PI / -180) +
					cos(*alpha * M_PI / -180) * cos(*gamma * M_PI / -180) * cos(*t * M_PI / -180)) + *r * sin(*t * M_PI / -180);
			*(i->bp3) = i->getRealpos('x') * (-(-sin(*alpha * M_PI / -180) * cos(*beta * M_PI / -180) +
				sin(*beta * M_PI / -180) * sin(*gamma * M_PI / -180) * cos(*alpha * M_PI / -180)) +
				sin(*beta * M_PI / -180) * cos(*gamma * M_PI / -180) * cos(*t * M_PI / -180)) +
				i->getRealpos('y') * ((-sin(*alpha * M_PI / -180) * cos(*beta * M_PI / -180) +
					sin(*beta * M_PI / -180) * sin(*gamma * M_PI / -180) * cos(*alpha * M_PI / -180)) * cos(*t * M_PI / -180) +
					sin(*beta * M_PI / -180) * sin(*t * M_PI / -180) * cos(*gamma * M_PI / -180)) + *h;*/
			//version1
			/**(i->bp1) = cos(*beta * M_PI / 180) * cos(*gamma * M_PI / 180) * i->getRealpos('x') +
				(sin(*alpha * M_PI / 180) * sin(*gamma * M_PI / 180) * cos(*beta * M_PI / 180) -
					sin(*beta * M_PI / 180) * cos(*alpha * M_PI / 180)) * i->getRealpos('y') + *r * cos(*t * M_PI / 180);
			*(i->bp2) = -sin(*gamma * M_PI / 180) * i->getRealpos('x') +
				sin(*alpha * M_PI / 180) * cos(*gamma * M_PI / 180) * i->getRealpos('y') + *r * sin(*t * M_PI / 180);
			*(i->bp3) = sin(*beta * M_PI / 180) * cos(*gamma * M_PI / 180) * i->getRealpos('x') +
				(sin(*alpha * M_PI / 180) * sin(*beta * M_PI / 180) * sin(*gamma * M_PI / 180) +
					cos(*alpha * M_PI / 180) * cos(*beta * M_PI / 180)) * i->getRealpos('y') + *h;*/
			//初始化全局坐标的齿上的坐标
			*(i->pgp1) = *(i->bp1);
			*(i->pgp2) = *(i->bp2);
			*(i->pgp3) = *(i->bp3);
			*(i->gp1) = *(i->bp1);
			*(i->gp2) = *(i->bp2);
			*(i->gp3) = *(i->bp3);
			*(i->sr) = sqrt(pow(*(i->bp1), 2) + pow(*(i->bp2), 2));
			*(i->st) = atan2(*(i->bp2), *(i->bp1)) * 180 / M_PI;
			//std::cout << *(i->bp1) << " " << *(i->bp2) << " " << *(i->bp3) << std::endl;
		}
	}
}

void Cutter::move(float dz, float dg)
{
	for (auto i : *flatpoint)
	{
		if (i)
		{
			*(i->pgp1) = *(i->gp1);
			*(i->pgp2) = *(i->gp2);
			*(i->pgp3) = *(i->gp3);
			*(i->gp1) = cos(dg * M_PI / 180) * *(i->pgp1) - sin(dg * M_PI / 180) * *(i->pgp2);
			*(i->gp2) = sin(dg * M_PI / 180) * *(i->pgp1) + cos(dg * M_PI / 180) * *(i->pgp2);
			*(i->gp3) = *(i->pgp3) + dz;
			/*std::cout << *(i->bp1) << " " << *(i->bp2) << " " << *(i->bp3) <<" "<<
				sqrt(pow(*(i->bp1), 2) + pow(*(i->bp2), 2)) << std::endl;
			std::cout << *(i->gp1) << " " << *(i->gp2) << " " << *(i->gp3) << " " <<
				sqrt(pow(*(i->gp1), 2) + pow(*(i->gp2), 2)) << std::endl;
			std::cout <<"---------------------------------" << std::endl;*/

		}
	}
}
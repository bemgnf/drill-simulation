#include <cmath>
#include <iostream>
#include <fstream>
#include "drillbase.h"

Drillbase::Drillbase(float dia, float zs):
	x_pos(0), y_pos(0), z_pos(0), x_size(dia), y_size(dia), z_size(zs)
{
	xy_count = new int(x_size / prs + 1);
	z_count = new int(z_size / prs+1);
	//version 1- basepoint = new std::array<std::array<Cube*, 5000 * 5000>*, 1500>();
	basepoint = new std::array<std::bitset<6000*6000>*, 5000>();
	buildBasepoint();
}

Drillbase::~Drillbase()
{
	delete xy_count, z_count;
	for (auto i : *basepoint)
	{
		delete i;
	}
	delete basepoint;
	/*version 1
	for (auto i : *basepoint)
	{
		for (auto j : *i)
		{
			delete j;
		}
		delete i;
	}
	delete basepoint;
	*/
}

void Drillbase::buildBasepoint()
{

	/*version 2
	std::stringstream ss;
	std::string str;
	for (int i = 0; i < *xy_count; i++)
	{
		for (int j = 0; j < *xy_count; j++)
		{
			ss << i << "_" << j << "_" << 0;
			ss >> str;
			(*basepoint)[str] = new Cube(i, j, 0);
			ss.clear();
			ss.str("");
		}
	}*/
	//��һ�δ��벻�У�Ϊʲô�أ���Ϊ��Ҫ1t�ڴ�洢����version 1-���ˣ���ɾ��
	for (int n = 0; n < *z_count; n++)
	{
		//��������Ҫע������Ķ�λ���������˵��д洢����ά���������ڡ�һ���̶ȡ���Խ���Ҳ�ܹ�ά������
		(*basepoint)[n] = new std::bitset<6000 * 6000>; 
		/*for (int m = 0; m < *xy_count; m++)
		{
			for (int l = 0; l < *xy_count; l++)
			{
				(*(*basepoint)[n])[l+m* *xy_count] = true;
			}
		}*/
	}
}

void Drillbase::delpoint(int l, int m, int n)
{
	(*(*basepoint)[n])[(l + 0.5 * x_size / prs) + (m + 0.5 * x_size / prs) * *xy_count] = 1;
}

void Drillbase::delpoint(float p1, float p2, float p3)
{
	if (p3 < 0)
	{
		return ;
	}
	float i = p1 / prs;
	int l = (p1 > 0.0) ? floor(i + 0.5) : ceil(i - 0.5);
	float j = p2 / prs;
	int m = (p2 > 0.0) ? floor(j + 0.5) : ceil(j - 0.5);
	float k = p3 / prs;
	int n = floor(k + 0.5);
	(*(*basepoint)[n])[(l + 0.5 * x_size / prs) + (m + 0.5 * x_size / prs) * *xy_count] = 1;
}

const bool Drillbase::if_exist(int l, int m, int n)
{
	//std::cout << !(*(*basepoint)[n])[(l + 0.5 * x_size / prs) + (m + 0.5 * x_size / prs) * *xy_count] << std::endl;
	return !(*(*basepoint)[n])[(l + 0.5 * x_size / prs) + (m + 0.5 * x_size / prs) * *xy_count];
}

const bool Drillbase::if_exist(float p1, float p2, float p3)
{
	if (p3<0)
	{
		return 0;
	}
	float i = p1 / prs;
	int l = (p1 > 0.0) ? floor(i + 0.5) : ceil(i - 0.5);
	float j = p2 / prs;
	int m = (p2 > 0.0) ? floor(j + 0.5) : ceil(j - 0.5);
	float k = p3 / prs;
	int n = floor(k + 0.5);
	//std::cout << !(*(*basepoint)[n])[(l + 0.5 * x_size / prs) + (m + 0.5 * x_size / prs) * *xy_count] << std::endl;
	return !(*(*basepoint)[n])[(l + 0.5 * x_size / prs) + (m + 0.5 * x_size / prs) * *xy_count];
}

const void Drillbase::savepoint(std::string filepath)
{
	std::ofstream outfile;
	outfile.open(filepath, std::ios::out | std::ios::trunc);
	//do something
	for (int i = 0; i < *z_count-1; i++)
	{
		for (int j = 0; j < pow(*xy_count,2); j++)
		{
			if (((*(*basepoint)[i])[j] && !(*(*basepoint)[i + 1.])[j]) || !(*(*basepoint)[0])[j])
			{
				outfile << int(j / (*xy_count))- 0.5 * x_size / prs << " " << 
					int(j % (*xy_count))- 0.5 * x_size / prs << " -" << i << std::endl;
			}
		}
	}
	outfile.close();
}
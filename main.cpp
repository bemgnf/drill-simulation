#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <limits>
#include <list>
#include <cmath>
#include "cube.h"
#include "drillbase.h"
#include "pdcbit.h"

int main()
{
	int bladecount = 4;
	int cuttercount = 20;
	float doc = 6.f;
	float rspeed = 2.f;
	int times = 2000;

	Pdcbit bit1 = Pdcbit(bladecount, cuttercount, std::string("cu.txt"));
	bit1.set_premeter(200.f, 20.f, doc); //前两个参数没用，随便给个即可，需要的是DOC，直接给了
	Drillbase db1 = Drillbase(300.f,125.f);
	std::stringstream ss;
	std::string str;
	
	//保存布齿的三维信息点
	if (false)
	{
		std::ofstream outfile;
		outfile.open("cutter.txt", std::ios::out | std::ios::trunc);
		for (auto i : bit1.all_c)
		{
			for (auto j : *i->flatpoint)
			{
				if (j)
				{
					outfile << *(j->bp1) << " " << *(j->bp2) << " "
						<< *(j->bp3) << std::endl;
				}
			}
		}
		outfile.close();
		std::cout << "save";
	}

	for (int i = 0; i < cuttercount; i++)
	{
		//ss << ".\\data\\cflat_" << i+1 << "_" << bit1.all_c[i]->b << "_"
		//	<< bit1.all_c[i]->bn << "_" << 0 << "_" << ".txt";
		ss << ".\\data\\cflat_" << i + 1 << "_" << 0 << "_" << ".txt";
		ss >> str;
		//std::cout << str << std::endl;
		//std::cout << *bit1.all_c[i]->get_flatpoint(0,0)->st << std::endl;

		bit1.all_c[i]->saveWorkflat(str);
		ss.clear();
	}
	//db1.savepoint(".\\data\\bcube_0_.txt");

	for (int t = 0; t < times; t++)
	{
		bit1.drilling(rspeed);
		for (int j = 0; j < bit1.all_c.size(); j++)
		{
			for (auto it : *(bit1.all_c[j]->flatpoint))
			{
				//这里判断相交是直接用齿面一点的位置坐标在全局的，有没有地层cube的存在，存在就是工作，否则没
				if (it && db1.if_exist(*(it->gp1), *(it->gp2), *(it->gp3)))
				{
					//std::cout << *(it->gp1) << " " << *(it->gp2) << " " << *(it->gp3) << std::endl;
					it->work_on();
					//这里，重头戏来了，需要更新钻头经过后base的形状，以便于下次判定
					//do something
					float ts = atan2(*(it->pgp2), *(it->pgp1));
					float hs = *(it->pgp3);
					float he = *(it->gp3);
					float s = sqrt(pow(*(it->sr) * (rspeed * M_PI / 180), 2) + pow(he - hs, 2)); //这一点掠过的弧长
					//version2
					float ds = (0.1 * prs); //这里会影响下一步的判断存在与否,算法的固有缺陷，是角度的问题，角度和长度，离钻头中的，弧长短可能没有一个格子那么大
					//这里的60 30 是随手给的，但是因为这个点tt为零的时候，是正好在方框中心，需要前后都有，因为每一个小迭代步都是小于一个方格很多的
					for (int tt = -60; tt < s / ds-30; tt++)//这里的60 30应该是随手给的（可能算过最小cube和中心的关系，感觉最终计算结果中间的齿有问题可能就是这里出的），为了延后删除的点，保证边界被算到涉及
					{
						float dx = *(it->sr) * cos(ts + tt * ds * (rspeed * M_PI / 180) / s);
						float dy = *(it->sr) * sin(ts + tt * ds * (rspeed * M_PI / 180) / s);
						float dz = hs + tt * ds * (he - hs) / s;
						//std::cout << dx << " " << dy << " " << dz << std::endl;
						db1.delpoint(dx,dy,dz);
					}
				}
			}
			//ss << ".\\data\\cflat_" << j + 1 << "_" << bit1.all_c[j]->b << "_"
			//	<< bit1.all_c[j]->bn << "_" << t + 1 << "_" << ".txt";
			ss << ".\\data\\cflat_" << j + 1 << "_" << t+1 << "_" << ".txt";
			ss >> str;
			bit1.all_c[j]->saveWorkflat(str);
			ss.clear();
			bit1.all_c[j]->resetWorkflat();
		}
		//保存base信息在这里开始,太大了，保存不了
		/*
		ss << ".\\data\\bcube_" << t + 1 << "_" << ".txt";
		ss >> str;
		db1.savepoint(str);
		ss.clear();*/
	}


	//std::cout << *bit1.all_c[0]->get_flatpoint(0, -5)->gp3 << std::endl;
	//以下为测试代码，每一个注释单元为一部分

	//bit1.all_c[0]->saveWorkflat("hello.txt");
	/*std::ofstream a;
	a.open("word.txt");
	a << "hello,world!" << std::endl;*/
	/*Cutter* a = new Cutter(20, 1, 1, 1, 12, 12, 12, 12, 12, 12);
	a->get_flatpoint(2.55f,-1.22f)->getRealpos('x');
	a->get_flatpoint(0.55f,3.22f)->getRefpos('x');
	a->get_flatpoint(2.55f,-4.22f)->if_work();
	a->get_flatpoint(-2,-2)->work_on();
	a->saveWorkflat(".\\data\\test.txt");*/
	/*std::stringstream ss;
	int i = 3;
	std::string str;
	ss << i << "hello" << i << std::endl;
	ss >> str;
	std::cout << str << std::endl;*/
	/*std::ifstream infile;
	float c, d;
	int a, b;
	bool e;
	infile.open("test.txt");
	while (!infile.eof())
	{
		infile >> a >> b >> c >> d >> e;
		if (e)
		{
			std::cout << a << " " << b << " " << c << " " << d << " " << e << std::endl;
		}
	}
	infile.close();*/
	/*
	std::vector < std::vector < std::vector <int*>>> a;
	for (int i = 0; i < 5000; i++)
	{
		std::vector < std::vector <int*>> tempi;
		for (int j = 0; j < 5000; j++)
		{
			std::vector <int*> tempij;
			for (int k = 0; k < 5000; k++)
			{
				tempij.push_back(new int(200005));
			}
			tempi.push_back(tempij);
		}
		//std::vector < std::vector <std::vector <int*>>> tempi;
		a.push_back(tempi);
	}*/
/*	auto a = new std::array<std::array<Cube*, 5000 * 5000>*, 1500>();
	std::cout << (*(*a)[1])[0] << std::endl;*/
	
	//std::cout << sizeof(bool) << std::endl;
	//std::cout << (std::numeric_limits<long long>::max)() << std::endl;
	//通过map进行字符串存储位置信息不行，太大，使用bitset单位01表示，压缩存储
	/*auto a = new std::map< std::string,int>;
	int x = 12;
	int y = 234;
	int z = 23;
	std::stringstream ss;
	std::string str;
	ss << x << "_" << y << "_" << z;
	ss >> str;
	(*a)[str]=38;
	std::cout << (*a)[str] << std::endl;*/
	/*int* a = new int(1);
	int* b = new int(1);
	bool* c = new bool(true);
	bool* d = new bool[10]();
	std::bitset<1>* aa = new std::bitset<1>;*/
	/*
	//drillbase测试通过
	auto a = new Drillbase(50, 15);
	a->if_exist(10.f, 12.011f, 11.f);
	a->delpoint(10.f, 12.011f, 11.f);
	a->if_exist(50.f, 50.f, 15.f);*/
	
	//std::cout << acos(-1) << std::endl;

}
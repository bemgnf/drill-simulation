#pragma once
#include <iostream>
#include <array>
#include "square.h"
#include "geometris.h"

class Cutter
{
public:
	Cutter(float _dia, unsigned short int _n, unsigned short int _b, unsigned short int _bn,
		float _x, float _y, float _z, float alp, float bet, float gam);
	~Cutter();

public:
	//更新移动后的工作面信息
	void move(float dz, float dg);
	//访问给定位置的单元
	Square*	get_flatpoint(float x, float y);
	Square* get_flatpoint(int x, int y);
	//保存当前的工作面信息
	void saveWorkflat(std::string filepath);
	//重置工作面布尔信息为0
	void resetWorkflat();


private:
	//生成齿工作面，默认布尔值信息为0
	void buildWorkflat();
	void transfertobit();

public:
	const float dia; //cutter diameter
	const int* square_count; //每行或每列单元个数，加一
	unsigned short int const n; //全钻头所有排列序号
	unsigned short int const b; //所处的刀翼序号
	unsigned short int const bn; //所在刀翼的齿序号
	//注意这里的i,j,并不是三维坐标的xy，应是对应关系：i->z,j->x,0->y
	std::array<Square*, 2000 * 2000>* flatpoint; //存储工作面的布尔信息

private:
	//这里是第三个齿面坐标，但是需要注意的是，在实际钻头过程中已经发现了，
	//三个旋转的角度无法在一个框架中同时实现，故需要根据这里的数据经过中间坐标系转换计算出第三个坐标，
	//就是说，这里的第三个坐标系并不是一个单独的坐标，会有三个一起形成这一个齿面坐标在钻头坐标中的位置
	//位置参数
	const float* r;
	const float* t;
	const float* h;
	//方向参数
	const float* alpha; //x轴转角
	const float* beta; //y轴转角
	const float* gamma; //z轴转角

};
#pragma once
#include <vector>
#include "cutter.h"
#include "geometris.h"

class Pdcbit
{
public:
	Pdcbit(unsigned short int blade, unsigned short int ccount, std::string filepath);
	~Pdcbit();
	//设定钻进参数
	void set_premeter(float rs, float ds, float d);
	//旋转运动
	void rotate();
	//钻进
	void drilling(float delt_gamma);

private:
	//导入文件生成钻头上各个齿的相对关系
	void add_cutters(std::string filepath);
public:
	std::vector<Cutter*> all_c; //保存所有的齿

private:
	const unsigned short int blade; //刀翼数目
	const unsigned short int ccount; //齿的数目
	float rspeed; //转速
	float dspeed; //钻速
	float doc; //吃入深度
	//这是第二个钻头坐标,其实这里只需要z轴值和转角就行了，因为假设了稳定没有侧向移动
	//位置参数
	float* x;
	float* y;
	float* z;
	//方向参数
	float* alpha; //x轴转角
	float* beta; //y轴转角
	float* gamma; //z轴转角
};

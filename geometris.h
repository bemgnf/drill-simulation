#pragma once

#define CARTESION //选择坐标形式

/*定义所有的空间运动位于第一卦限内*/
/*
enum COO_FORMATE //坐标形式
{
	CARTESION,   //笛卡尔
	CYLINDRICAL, //柱坐标
	SPHERICAL    //球坐标
};
*/
//这里的精度设置为0.05f，可以同时保证画图的速度没有计算的速度快，能够同时运行
static float prs = 0.05f;//1.25f; //最小划分精度，0.01mm，一般不能用0.01的精度，时间空间的花销太大，最多就是0.1了

#ifdef CARTESION
struct coo
{

	//位置参数
	float* x;
	float* y;
	float* z;
	//方向参数
	float* alpha; //x轴转角
	float* beta; //y轴转角
	float* gamma; //z轴转角
};
#endif // CARTESION

#ifdef CYLINDRICAL

struct coo
{
	//位置参数
	float* rou;
	float* theta;
	float* h;
	//方向参数
	float* alpha; //x轴转角
	float* beta; //y轴转角
	float* gamma; //z轴转角
};
#endif // CYLINDRICAL

#ifdef SPHERICAL

struct coo
{
	//位置参数
	float* rou;
	float* theta;
	float* phi;
	//方向参数
	float* alpha; //x轴转角
	float* beta; //y轴转角
	float* gamma; //z轴转角
};
#endif // SPHERICAL
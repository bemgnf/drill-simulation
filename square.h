#pragma once

//齿工作面的单元正方形
//定位点是储存这个数组的坐标位置
//以靠近圆形中心为锚点
class Square
{
public:
	Square(int i, int j);
	~Square();
	//设置为工作点
	void work_on();
	//设置为非工作点
	void work_off();
	//是否在工作
	const bool if_work();
	//返回物理位置坐标,“float”
	const float getRealpos(char a);
	//返回数学下标参考,“int”
	const int getRefpos(char a);

public:
	float* bp1; //单元中心点钻头x坐标
	float* bp2; //单元中心点钻头y坐标
	float* bp3; //单元中心点钻头z坐标
	float* sr; //单元中心点钻头r坐标
	float* st; //单元中心点钻头theta坐标


	float* pgp1; //单元中心点钻头x坐标
	float* pgp2; //单元中心点钻头y坐标
	float* pgp3; //单元中心点钻头z坐标

	float* gp1; //单元中心点全局x坐标
	float* gp2; //单元中心点全局y坐标
	float* gp3; //单元中心点全局z坐标

private:
	bool* is_work; //储存本点的工作状态信息
	const int* m; //单元中心点x下标
	const int* n; //单元中心点y下标
	const float* p1; //单元中心点x坐标
	const float* p2; //单元中心点y坐标

};

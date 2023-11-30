#pragma once

//单元正方体的数据存储结构
class Cube
{
public:
	Cube(int i, int j, int k);
	~Cube();

public:
	//是否存在
	const bool if_exist();
	//返回物理位置坐标
	const float* getRealpos();
	//返回数学下标参考
	const int* getRefpos();
	//齿经过后，删除单元
	void cube_del();
	//恢复单元
	void cube_rep();

private:
	bool* is_exist; //是否存在
	//float prs; //划分精度，mm
	const int* l; //单元中心点x下标
	const int* m; //单元中心点y下标
	const int* n; //单元中心点y下标
	const float* p1; //单元中心点x坐标
	const float* p2; //单元中心点y坐标
	const float* p3; //单元中心点y坐标
};

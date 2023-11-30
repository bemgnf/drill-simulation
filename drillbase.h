#pragma once
#include <bitset>
#include <array>
#include <string>
#include <sstream>
#include "cube.h"
#include "geometris.h"
class Drillbase
{
public:
	Drillbase(float dia, float zs);
	~Drillbase();
	//去除已经经过的点
	void delpoint(float p1, float p2, float p3);
	void delpoint(int l, int m, int n);
	//是否存在
	const bool if_exist(float p1, float p2, float p3);
	const bool if_exist(int l, int m, int n);
	//保存信息吗？可以保存表面，但是这里由于只有两种状态，需要用判断刚开始变化的那个位置坐标
	//很难，数据量太大，时间突破天际
	const void savepoint(std::string filepath);

private:
	void buildBasepoint();

public:
	const int* xy_count;
	const int* z_count;

private:
	//这是第一个世界坐标
	const float x_pos, y_pos, z_pos; //坐标位置，正方形上面中心与原点重合，z轴向下
	const float x_size, y_size;
	const float z_size; //大小
	/*version 1 -这里的钻进基础信息不能暴力穷举，设备性能不允许，只能利用平面信息来压缩存储*/
	std::array<std::bitset<6000 * 6000>*, 5000>* basepoint; //存储钻进基体的空间信息
	//std::map<std::string, Cube*>* basepoint; //version 2
};


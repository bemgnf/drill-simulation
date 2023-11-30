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
	//ȥ���Ѿ������ĵ�
	void delpoint(float p1, float p2, float p3);
	void delpoint(int l, int m, int n);
	//�Ƿ����
	const bool if_exist(float p1, float p2, float p3);
	const bool if_exist(int l, int m, int n);
	//������Ϣ�𣿿��Ա�����棬������������ֻ������״̬����Ҫ���жϸտ�ʼ�仯���Ǹ�λ������
	//���ѣ�������̫��ʱ��ͻ�����
	const void savepoint(std::string filepath);

private:
	void buildBasepoint();

public:
	const int* xy_count;
	const int* z_count;

private:
	//���ǵ�һ����������
	const float x_pos, y_pos, z_pos; //����λ�ã�����������������ԭ���غϣ�z������
	const float x_size, y_size;
	const float z_size; //��С
	/*version 1 -��������������Ϣ���ܱ�����٣��豸���ܲ�����ֻ������ƽ����Ϣ��ѹ���洢*/
	std::array<std::bitset<6000 * 6000>*, 5000>* basepoint; //�洢�������Ŀռ���Ϣ
	//std::map<std::string, Cube*>* basepoint; //version 2
};


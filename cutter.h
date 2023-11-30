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
	//�����ƶ���Ĺ�������Ϣ
	void move(float dz, float dg);
	//���ʸ���λ�õĵ�Ԫ
	Square*	get_flatpoint(float x, float y);
	Square* get_flatpoint(int x, int y);
	//���浱ǰ�Ĺ�������Ϣ
	void saveWorkflat(std::string filepath);
	//���ù����沼����ϢΪ0
	void resetWorkflat();


private:
	//���ɳݹ����棬Ĭ�ϲ���ֵ��ϢΪ0
	void buildWorkflat();
	void transfertobit();

public:
	const float dia; //cutter diameter
	const int* square_count; //ÿ�л�ÿ�е�Ԫ��������һ
	unsigned short int const n; //ȫ��ͷ�����������
	unsigned short int const b; //�����ĵ������
	unsigned short int const bn; //���ڵ���ĳ����
	//ע�������i,j,��������ά�����xy��Ӧ�Ƕ�Ӧ��ϵ��i->z,j->x,0->y
	std::array<Square*, 2000 * 2000>* flatpoint; //�洢������Ĳ�����Ϣ

private:
	//�����ǵ������������꣬������Ҫע����ǣ���ʵ����ͷ�������Ѿ������ˣ�
	//������ת�ĽǶ��޷���һ�������ͬʱʵ�֣�����Ҫ������������ݾ����м�����ϵת����������������꣬
	//����˵������ĵ���������ϵ������һ�����������꣬��������һ���γ���һ��������������ͷ�����е�λ��
	//λ�ò���
	const float* r;
	const float* t;
	const float* h;
	//�������
	const float* alpha; //x��ת��
	const float* beta; //y��ת��
	const float* gamma; //z��ת��

};
#pragma once
#include <vector>
#include "cutter.h"
#include "geometris.h"

class Pdcbit
{
public:
	Pdcbit(unsigned short int blade, unsigned short int ccount, std::string filepath);
	~Pdcbit();
	//�趨�������
	void set_premeter(float rs, float ds, float d);
	//��ת�˶�
	void rotate();
	//���
	void drilling(float delt_gamma);

private:
	//�����ļ�������ͷ�ϸ����ݵ���Թ�ϵ
	void add_cutters(std::string filepath);
public:
	std::vector<Cutter*> all_c; //�������еĳ�

private:
	const unsigned short int blade; //������Ŀ
	const unsigned short int ccount; //�ݵ���Ŀ
	float rspeed; //ת��
	float dspeed; //����
	float doc; //�������
	//���ǵڶ�����ͷ����,��ʵ����ֻ��Ҫz��ֵ��ת�Ǿ����ˣ���Ϊ�������ȶ�û�в����ƶ�
	//λ�ò���
	float* x;
	float* y;
	float* z;
	//�������
	float* alpha; //x��ת��
	float* beta; //y��ת��
	float* gamma; //z��ת��
};

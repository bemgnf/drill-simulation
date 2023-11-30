#pragma once

#define CARTESION //ѡ��������ʽ

/*�������еĿռ��˶�λ�ڵ�һ������*/
/*
enum COO_FORMATE //������ʽ
{
	CARTESION,   //�ѿ���
	CYLINDRICAL, //������
	SPHERICAL    //������
};
*/
//����ľ�������Ϊ0.05f������ͬʱ��֤��ͼ���ٶ�û�м�����ٶȿ죬�ܹ�ͬʱ����
static float prs = 0.05f;//1.25f; //��С���־��ȣ�0.01mm��һ�㲻����0.01�ľ��ȣ�ʱ��ռ�Ļ���̫��������0.1��

#ifdef CARTESION
struct coo
{

	//λ�ò���
	float* x;
	float* y;
	float* z;
	//�������
	float* alpha; //x��ת��
	float* beta; //y��ת��
	float* gamma; //z��ת��
};
#endif // CARTESION

#ifdef CYLINDRICAL

struct coo
{
	//λ�ò���
	float* rou;
	float* theta;
	float* h;
	//�������
	float* alpha; //x��ת��
	float* beta; //y��ת��
	float* gamma; //z��ת��
};
#endif // CYLINDRICAL

#ifdef SPHERICAL

struct coo
{
	//λ�ò���
	float* rou;
	float* theta;
	float* phi;
	//�������
	float* alpha; //x��ת��
	float* beta; //y��ת��
	float* gamma; //z��ת��
};
#endif // SPHERICAL
#pragma once

//�ݹ�����ĵ�Ԫ������
//��λ���Ǵ���������������λ��
//�Կ���Բ������Ϊê��
class Square
{
public:
	Square(int i, int j);
	~Square();
	//����Ϊ������
	void work_on();
	//����Ϊ�ǹ�����
	void work_off();
	//�Ƿ��ڹ���
	const bool if_work();
	//��������λ������,��float��
	const float getRealpos(char a);
	//������ѧ�±�ο�,��int��
	const int getRefpos(char a);

public:
	float* bp1; //��Ԫ���ĵ���ͷx����
	float* bp2; //��Ԫ���ĵ���ͷy����
	float* bp3; //��Ԫ���ĵ���ͷz����
	float* sr; //��Ԫ���ĵ���ͷr����
	float* st; //��Ԫ���ĵ���ͷtheta����


	float* pgp1; //��Ԫ���ĵ���ͷx����
	float* pgp2; //��Ԫ���ĵ���ͷy����
	float* pgp3; //��Ԫ���ĵ���ͷz����

	float* gp1; //��Ԫ���ĵ�ȫ��x����
	float* gp2; //��Ԫ���ĵ�ȫ��y����
	float* gp3; //��Ԫ���ĵ�ȫ��z����

private:
	bool* is_work; //���汾��Ĺ���״̬��Ϣ
	const int* m; //��Ԫ���ĵ�x�±�
	const int* n; //��Ԫ���ĵ�y�±�
	const float* p1; //��Ԫ���ĵ�x����
	const float* p2; //��Ԫ���ĵ�y����

};

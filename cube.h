#pragma once

//��Ԫ����������ݴ洢�ṹ
class Cube
{
public:
	Cube(int i, int j, int k);
	~Cube();

public:
	//�Ƿ����
	const bool if_exist();
	//��������λ������
	const float* getRealpos();
	//������ѧ�±�ο�
	const int* getRefpos();
	//�ݾ�����ɾ����Ԫ
	void cube_del();
	//�ָ���Ԫ
	void cube_rep();

private:
	bool* is_exist; //�Ƿ����
	//float prs; //���־��ȣ�mm
	const int* l; //��Ԫ���ĵ�x�±�
	const int* m; //��Ԫ���ĵ�y�±�
	const int* n; //��Ԫ���ĵ�y�±�
	const float* p1; //��Ԫ���ĵ�x����
	const float* p2; //��Ԫ���ĵ�y����
	const float* p3; //��Ԫ���ĵ�y����
};

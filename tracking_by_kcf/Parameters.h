#pragma once

class Parameters
{
public:
	//Ԥ�������
	struct Preprocessing {
		double padding = 3;  //extra area surrounding the target
	} pre_processing;

	//�㷨����ʽ����������Ĳ���
	struct KCF
	{
		double lambda = 1e-4;  //regularization
	};

	//�����Ĳ���
	struct Feature
	{

	};

	//�˵Ĳ���
	struct Kernel
	{

	};
};

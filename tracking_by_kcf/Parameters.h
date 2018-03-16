#pragma once

class Parameters
{
public:
	//预处理参数
	struct Preprocessing {
		double padding = 3;  //extra area surrounding the target
	} pre_processing;

	//算法（公式）本身迭代的参数
	struct KCF
	{
		double lambda = 1e-4;  //regularization
	};

	//特征的参数
	struct Feature
	{

	};

	//核的参数
	struct Kernel
	{

	};
};

#pragma once
#include<iostream>
#include<string>
using namespace std;

class coststandard
{
public:
	double c_usage;  // ʹ������
	int c_type;   // ʹ������

	virtual double cal_price() = 0;
};
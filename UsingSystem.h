#pragma once
#include<iostream>
#include<string>
#include"UsingElectricity.h"
#include"UsingWater.h"
#include<fstream>
#define FILENAME1 "wetable.txt"
using namespace std;

class usingsystem
{
public:
	usingsystem();

	void m_save();  //������Ϣ
	bool m_file;    //�ļ��Ƿ����
	int get_num();  //��ȡ����
	void in_stu();

	int m_num;
	system1** m_arr1;

	void menu1();//��ʾ�˵�
	int is_exist(int id);//�ж��Ƿ����
	void show_stu();//��ʾ��Ϣ
	void add_info();//�����Ϣ
	void sear_price();//��ѯ����
	void sear_info();//��ѯ�ɷѼ�¼
	void not_pay();//��ѯδ�ɷ�����
	void exitsystem();//�˳�ϵͳ

	~usingsystem();
};
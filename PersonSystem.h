#pragma once
#include<iostream>
#include<string>
#include"Student.h"
#include"Teacher.h"
#include<fstream>
#include <vector>
#define FILENAME "persontable.txt"
using namespace std;

class personsystem
{
public:
	personsystem();

	void m_save();  // ������Ϣ
	bool m_file;    //�ļ��Ƿ����
	int get_num();  //��ȡ����
	vector<int> get_id();  //��ȡid

	void in_stu();

	int m_num;
	person** m_arr;
	//��ʾ�˵�
	void menu2();
	int is_exist(int id);  //�ж��Ƿ����
	int is_exist2(int roomNumber);
	void show_stu();       //��ʾ��Ϣ
	void add_info();       //�����Ϣ
	void mod_info();       //�޸���Ϣ
	void del_info();       //ɾ����Ϣ
	void exitsystem();     //�˳�ϵͳ

	~personsystem();
};
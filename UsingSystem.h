#pragma once
#include<iostream>
#include<string>
#include"UsingElectricity.h"
#include"UsingWater.h"
#include<fstream>
#define FILENAME1 "wetable.txt"
#include <ctime>
#include <map>

#include <time.h>
//�̲߳���ȫ����
#pragma warning( disable : 4996 )
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

	vector<int> get_time() {
		// ��ȡ��ǰʱ���time_t����ֵ
		time_t now = time(0);

		// ��time_tת��Ϊtm�ṹ���ʾ�ı���ʱ��
		tm* localTime = localtime(&now);

		// ����ꡢ�¡��ա�Сʱ�����Ӻ���
		vector<int> mytime;
		mytime.push_back(localTime->tm_year + 1900);
		mytime.push_back(localTime->tm_mon + 1);
		mytime.push_back(localTime->tm_mday);
		mytime.push_back(localTime->tm_hour);
		mytime.push_back(localTime->tm_min);
		mytime.push_back(localTime->tm_sec);

		return mytime;
	}
	string vtos(vector<int> vec) {
		string res= "";
		//��
		res += to_string(vec[0]);
		//�� �� ʱ �� ��
		for (int i = 1; i < 6; i++) {
			if (to_string(vec[i]).length() != 2) res += "0" + to_string(vec[i]);
			else res += to_string(vec[i]);
		}
		
		return res;
	}
	void time_format2(vector<int> timevec) {
		cout << timevec[0] << "��" \
			<< timevec[1] << "��" \
			<< timevec[2] << "��" \
			<< timevec[3] << "ʱ" \
			<< timevec[4] << "��" \
			<< timevec[5] << "��" << endl;
	}
};
#pragma once
#include<iostream>
#include<string>
#include <iomanip>
using namespace std;

class system1
{
public:
	int s_id;              // ������
	int s_roomnum;         // ����
	string s_ltime;         // �ϴγ���ʱ��
	string s_time;         // ���γ���ʱ��
	double s_ldegree;       // �ϴγ������
	double s_degree;       // ���γ������
	double s_price;        // �۸�
	int s_type;            // ˮ���ǵ��
	bool s_pay;            // �Ƿ��ѽɷ�

	void show_info00() {
		cout << "��ţ�" << s_id << endl;
		cout << "���ͣ�" << get_type() << endl;
		cout << "����ţ�" << s_roomnum << endl;
		cout << "�ϴγ���ʱ�䣺" << timeformat(s_ltime) << endl;
		cout << "���γ���ʱ�䣺" << timeformat(s_time) << endl;
		cout << "�ϴγ��������" << fixed << setprecision(2) << s_ldegree << get_unit() << endl;
		cout << "���γ��������" << fixed << setprecision(2) << s_degree << get_unit()<< endl;
		cout << "�۸�" << fixed << setprecision(2) << s_price << "��" << endl;
		cout << "֧��״̬��";
		if (s_pay) {
			cout << "��֧��" << endl;
		}
		else {
			cout << "δ֧��" << endl;
		}
	}
	string get_type() {
		if (s_type == 1) return string("���");
		else return string("ˮ��");
	}
	string timeformat(string time) {
		if (time.length() != 8) return "��ʽ������ο����룺2020101����ǰΪ��" + time;
		else return time.substr(0, 4) + "��" + time.substr(4, 2) + "��" + time.substr(6, 2) + "��";
	}
	string get_unit() {
		switch (s_type)
		{
		case 1:
			return "ǧ��ʱ";
			break;
		case 2:
			return "������";
			break;
		default:
			return "Error ��ʽ��������";
			break;
		}
		if (s_type == 1) return string("���");
		else return string("ˮ��");
	}

	void show_find_room_res() {
		cout << "��ţ�" << s_id << endl;
		cout << "���ͣ�" << get_type() << endl;
		cout << "ʹ�����ڣ�" << timeformat(s_ltime) << " - " << timeformat(s_time) << endl;
		cout << "ʹ������:" << fixed << setprecision(2) << (s_degree - s_ldegree) <<get_unit() << endl;
		cout << "Ӧ���۸�" << fixed << setprecision(2) << s_price << "��" << endl;
		cout << "֧��״̬��";
		if (s_pay) {
			cout << "��֧��" << endl;
		}
		else {
			cout << "δ֧��" << endl;
		}
	}

	void show_table() {
		cout << "|" << setw(7) << s_id << setw(8) << "|" << setw(16) << timeformat(s_ltime) << setw(3) << "|"  << setw(15) << timeformat(s_time) << setw(2) << "|" << setw(8) << s_degree - s_ldegree << setw(3) << "|" << setw(9) << s_price << setw(4) <<  "|" << endl;
	}
};
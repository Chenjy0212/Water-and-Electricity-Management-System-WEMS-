#include"Student.h"

student::student(string name, int id, int roomNumber, int UID) {
	this->m_name = name;
	this->m_id = id;
	this->m_roomNumber = roomNumber;
	this->m_UID = UID;
}
void student::show_info() {
	cout << "������" << m_name << endl;
	cout << "ѧ�ţ�" << m_id << endl;
	cout << "����ţ�" << m_roomNumber << endl;
	cout << "��ݣ�" << this->get_name() << endl;
}
string student::get_name()
{
	return string("ѧ��");
}

stucoststd::stucoststd(double usage, int type) {
	this->c_usage = usage;
	this->c_type = type;
}
double stucoststd::cal_price() {
	double price = 0;
	// ������õ�
	if (c_type == 1) {
		if (c_usage <= 50) {
			return price;
		}
		else {
			return ((c_usage - 50) * 1.2);
		}
	}
	// �������ˮ
	else if (c_type == 2) {
		if (c_usage <= 50) {
			return price;
		}
		else {
			return ((c_usage - 50) * 0.5);
		}
	}
}
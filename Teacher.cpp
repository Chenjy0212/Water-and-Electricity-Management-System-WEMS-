#include"Teacher.h"

teacher::teacher(string name, int id, int roomNumber, int UID) {
	this->m_name = name;
	this->m_id = id;
	this->m_roomNumber = roomNumber;
	this->m_UID = UID;
}
void teacher::show_info() {
	cout << "������" << m_name << endl;
	cout << "ѧ�ţ�" << m_id << endl;
	cout << "����ţ�" << m_roomNumber << endl;
	cout << "��ݣ�" << this->get_name() << endl;
}
string teacher::get_name()
{
	return string("��ʦ");
}

teccoststd::teccoststd(double usage, int type) {
	this->c_usage = usage;
	this->c_type = type;
}
double teccoststd::cal_price() {
	// ������õ�
	if (c_type == 1) {
		return (c_usage * 0.8);
	}
	// �������ˮ
	else if (c_type == 2) {
		return (c_usage * 0.3);
	}
}
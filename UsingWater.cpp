#include"usingwater.h"

usingwater::usingwater(int id, int roomnum, string ltime, string time, double ldegree, double degree, double price, int type, bool pay) {
	this->s_id = id;
	this->s_roomnum = roomnum;
	this->s_ltime = ltime;
	this->s_time = time;
	this->s_ldegree = ldegree;
	this->s_degree = degree;
	this->s_price = price;
	this->s_type = type;
	this->s_pay = pay;
}

//void usingwater::show_info00() {
//	cout << "��ţ�" << s_id << endl;
//	cout << "���ͣ�" << get_type() << endl;
//	cout << "����ţ�" << s_roomnum << endl;
//	cout << "�ϴγ���ʱ�䣺" << timeformat(s_ltime) << endl;
//	cout << "���γ���ʱ�䣺" << timeformat(s_time) << endl;
//	cout << "�ϴγ��������" << s_ldegree << endl;
//	cout << "���γ��������" << s_degree << endl;
//	cout << "�۸�" << s_price << endl;
//	if (s_pay) {
//		cout << "��֧��" << endl;
//	}
//	else {
//		cout << "δ֧��" << endl;
//	}
//}
//
//string usingwater::get_type() {
//	if (s_type == 1) return string("���");
//	else return string("ˮ��");
//}
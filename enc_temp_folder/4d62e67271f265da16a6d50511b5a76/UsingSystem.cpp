#include"UsingElectricity.h"
#include"PersonSystem.h"
#include"UsingSystem.h"
#include"UsingWater.h"
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

int g_var1 = 0;

// �������󷵻��������ڻ�����С�����ڡ�
string compareDate(vector<string>datavec, string type) {

	if (datavec.size() == 0)
		throw "��������Ϊ��";
	if (datavec[0].length() != 8 && datavec[0].length() != 12)
		throw "���ڸ�ʽ����";
	for (int i = 1; i < datavec.size(); i++) {
		if (datavec[0].length() != datavec[i].length()) {
			throw "���ڸ�ʽ����";
		}
	}

	string maxd = datavec[0];
	string mind = datavec[0];

	for (int i = 1; i < datavec.size(); i++) {
		for (int j = 0; j < datavec[i].length(); j++) {
			if (datavec[i][j] > maxd[j]) {
				maxd = datavec[i];
				break;
			}
			if (datavec[i][j] < mind[j]) {
				mind = datavec[i];
				break;
			}
		}
	}

	if (type == "max") {
		return maxd;
	}
	else if (type == "min") {
		return mind;
	}
}
// ��ȡ����ǰ��ʱ��
string get6month_ago(string data) {
	if (data.length() != 12 && data.length() != 8) {
		throw "ʱ���ʽ����ȷ";
	}
	if (data.length() == 12) {
		data = data.substr(0, 8);
	}
#	//���� 7 - 9��
	int mon = stoi(data.substr(4, 2));
	if (mon >= 7 && mon < 10) {
		mon -= 6;
		data[5] = mon + '0';
	}
	// ���ڵ���10��
	else if (mon >= 10) {
		mon -= 6;
		data[4] = '0';
		data[5] = mon + '0';
	}
	//С�� 7 ��
	else {
		int year = stoi(data.substr(0, 4));
		year -= 1;
		int mon = stoi(data.substr(4, 2));
		//С�ڵ���6�´���3��
		if (mon >3 && mon <= 6) {
			mon += 6 - 10;
			data[4] = '1';
			data[5] = mon + '0';
		}
		// С�ڵ���3��
		else if (mon <= 3) {
			mon += 6;
			data[5] = mon + '0';
		}
		data = to_string(year) + data.substr(4, 4);
	}

	return data;
}
// �ж������Ƿ��ڰ�����
bool in6mon(string date, string dateago) {
	bool res = false;
	for (int i = 0; i < 8; i++) {
		if (date[i] > dateago[i]) {
			res = true;
			break;
		}
	}
	return res;
}

usingsystem::usingsystem() {
	ifstream ifs;
	ifs.open(FILENAME1, ios::in);
	//�ļ������ڵ����
	if (!ifs.is_open()) {
		this->m_num = 0;//��ʼ������
		this->m_file = true;//��ʼ���ļ�Ϊ�ձ�־
		this->m_arr1 = NULL;//��ʼ������
		ifs.close();//�ر��ļ�
		return;
	}
	//�ļ�����,����Ϊ��
	char ch;
	ifs >> ch;//���ַ�
	if (ifs.eof()) {
		this->m_num = 0;
		this->m_file = true;
		this->m_arr1 = NULL;
		ifs.close();
		return;
	}
	//�ļ����ڣ������ݲ�Ϊ��
	int num = this->get_num();
	this->m_num = num;
	//���ٿռ�
	this->m_arr1 = new system1 * [this->m_num];
	//���ļ��е����ݴ浽������
	this->in_stu();
	//�������Զ�����
	g_var1 = this->m_arr1[this->m_num - 1]->s_id;
}
usingsystem::~usingsystem() {
	if (this->m_arr1 != NULL) {
		delete[]this->m_arr1;
		this->m_arr1 = NULL;
	}//�ͷŶ���������
}
void usingsystem::m_save() {
	ofstream ofs;
	ofs.open(FILENAME1, ios::out);
	//������д���ļ���
	for (int i = 0; i < this->m_num; i++)
	{
		ofs << this->m_arr1[i]->s_id << " "
			<< this->m_arr1[i]->s_roomnum << " "
			<< this->m_arr1[i]->s_ltime << " "
			<< this->m_arr1[i]->s_time << " "
			<< this->m_arr1[i]->s_ldegree << " "
			<< this->m_arr1[i]->s_degree << " "
			<< this->m_arr1[i]->s_price << " "
			<< this->m_arr1[i]->s_type << " "  
			<< this->m_arr1[i]->s_pay << " "
			<< this->m_arr1[i]->s_paytime << endl;
	}
	ofs.close();
}
//ͳ���ļ���¼���ݵ���Ŀ
int usingsystem::get_num() {
	ifstream ifs;
	ifs.open(FILENAME1, ios::in);

	int id;
	int roomnum;
	string ltime;
	string time;
	double ldegree;
	double degree;
	double price;
	int type;
	bool pay;
	string paytime;

	int num = 0;
	while (ifs >> id && ifs >> roomnum && ifs >> ltime && ifs >> time && ifs >> ldegree && ifs >> degree && ifs >> price && ifs >> type && ifs >> pay && ifs >> paytime) {
		num++;
	}
	ifs.close();
	return num;
}
void usingsystem::in_stu() {
	ifstream ifs;
	ifs.open(FILENAME1, ios::in);
	int id;
	int roomnum;
	string ltime;
	string time;
	double ldegree;
	double degree;
	double price;
	int type;
	bool pay;
	string paytime;

	int index = 0;
	while (ifs >> id && ifs >> roomnum && ifs >> ltime && ifs >> time && ifs >> ldegree && ifs >> degree && ifs >> price && ifs >> type && ifs >> pay && ifs >> paytime) {
		system1* system = NULL;
		if (type == 1) {
			system = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 1, pay, paytime);
		}
		if (type == 2) {
			system = new usingwater(id, roomnum, ltime, time, ldegree, degree, price, 2, pay, paytime);
		}
		this->m_arr1[index] = system;
		index++;
	}
}

//��ʾ������Ϣ
void usingsystem::show_stu() {
	// �ͱ������ͬ��
	this->in_stu();
	if (this->m_file) {
		cout << "�ļ�Ϊ��" << endl;
	}
	else {
		for (int i = 0; i < this->m_num; i++) {
			this->m_arr1[i]->show_info00();
			cout << endl;
		}
		cout << "��ǰ��ˮ�õ��¼�ܹ��� " << this->get_num() << " ��" << endl;
	}
	system("pause");
	system("cls");
}
//�����Ϣ
void usingsystem::add_info() {
	personsystem s;

	int newsize = this->m_num + 1;//�����¿ռ��С
	system1** newspace1 = new system1 * [newsize];//�ڶ��������¿ռ�
	if (this->m_arr1 != NULL) //��ԭ�ռ������ݷŵ��¿ռ���
	{
		for (int i = 0; i < this->m_num; i++)
		{
			newspace1[i] = this->m_arr1[i];
		}
	}
	//ѭ���������ᵼ�����ݵ�д���ӳ٣�û��Ҫ����
	int id;
	int roomnum;
	string time;
	string ltime = "20240101";
	double degree;
	double ldegree = 0;
	double price;
	bool pay = false;
	string paytime = "########";

	id = ++g_var1;
	cout << "�����뷿��ţ�" << endl;
	cin >> roomnum;
	int ret = s.is_exist2(roomnum);
	int quit_flag = 0;
	while (ret == -1) {
		cout << "����Ų���ȷ������������" << endl;
		cin >> roomnum;
		ret = s.is_exist2(roomnum);
		// �����������������Ѷ��
		++quit_flag;
		if (quit_flag == 10) break;
	}
	cout << "�����뵱ǰ�ĳ���ʱ��(eg��20240101)" << endl;
	cin >> time;
	cout << "���������1��ˮ��������2" << endl;
	int num;
	cin >> num;
	while (num != 1 && num != 2) {
		cout << "Error���������󡣵������1��ˮ������2" << endl;
		cin >> num;
	}
	switch (num)
	{
	case 1:
		cout << "�����뵱ǰ�õ�����" << endl;
		break;
	case 2:
		cout << "�����뵱ǰˮ��ʹ����" << endl;
		break;
	}
	cin >> degree;

	// �Զ���ȡ�ϴμ�¼ʱ���ʹ�õ���
	bool exite_flag = false;
	vector<string> datavec;
	for (int i = 0; i < this->m_num; i++)
	{
		// ���֮ǰ�м�¼�Ļ�
		if (this->m_arr1[i]->s_roomnum == roomnum && this->m_arr1[i]->s_type == num) {
			//�����ǲ�ͬ�ı��в�ͬ�Ľ��
			exite_flag = true;
			ldegree = max(m_arr1[i]->s_degree, ldegree);
			datavec.push_back(this->m_arr1[i]->s_time);
			//ltime = to_string(static_cast<int>(max(ceilf(stof(this->m_arr1[i]->s_time)), stof(ltime))));
		}
	}
	ltime = compareDate(datavec, "max");

	if (!exite_flag){ // ���û�м�¼,��ô��ʼ�������趨Ϊ�Ѿ�֧������Ϊû��ǰ��ʹ����Ϊ0
		ldegree = degree;
		ltime = time;
		pay = true;
	}

	system1* system1 = NULL;
	switch (num) {
	case 1: {
		if(s.m_arr[ret]->m_UID == 1){
			stucoststd* scs = new stucoststd(degree - ldegree, num);
			price = scs->cal_price();
			delete scs;
			system1 = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 1, pay, paytime);
			break;
		}
		else {
			teccoststd* tcs = new teccoststd(degree - ldegree, num);
			price = tcs->cal_price();
			delete tcs;
			system1 = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 1, pay, paytime);
			break;
		}
	}
	case 2: {
		if (s.m_arr[ret]->m_UID == 1) {
			stucoststd* scs = new stucoststd(degree - ldegree, num);
			price = scs->cal_price();
			delete scs;
			system1 = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 2, pay, paytime);
			break;
		}
		else {
			teccoststd* tcs = new teccoststd(degree - ldegree, num);
			price = tcs->cal_price();
			delete tcs;
			system1 = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 2, pay, paytime);
			break;
		}
	}
	}
	newspace1[this->m_num] = system1;
			
	
	delete[]this->m_arr1;      //�ͷ�ԭ���Ŀռ�
	this->m_arr1 = newspace1;  //�����¿ռ��ָ��
	this->m_num = newsize;     //�����µĸ���
	this->m_file = false;      //���²�Ϊ�ձ�־
	cout << "�ɹ����" << endl;
	this->m_save();

	system("pause");
	system("cls");
}
//�ж��Ƿ����
int usingsystem::is_exist(int roomnum) {
	int index = -1;
	int a = this->m_num;
	for (int i = 0; i < this->m_num; i++) {
		if (this->m_arr1[i]->s_roomnum == roomnum) {
			index = i;
			break;
		}
	}
	return index;
}
//��ѯ���ã��ɷ�
void usingsystem::sear_price() {
	// �ͱ������ͬ��
	this->in_stu();
	cout << "��������ķ����" << endl;
	int num;
	cin >> num;
	int ret;
	ret = is_exist(num);
	if (ret != -1) {
		cout << "��ѯȫ������������0����ѯ���������1����ѯˮ��������2" << endl;
		int a;
		cin >> a;
		while (a < 0 || a > 2) {
			cout << "Error���������󡣲�ѯȫ������������0����ѯ���������1����ѯˮ��������2" << endl;
			cin >> a;
		}
		int count = 0;
		int unpaid_count = 0;
		double due_payment = 0;
		double due_payment_part = 0;
		vector<int> id_list;
		vector<int> id_list_tmp;
		string tmp_num;
		char ypq;

		switch (a)
		{
		case 0:
			for (int i = 0; i < this->m_num; i++) {
				//�ж��ǲ��ǳ�ʼ�����ݣ�ͬһ���¼��ʹ����һ�����Ѿ��ɷ�
				if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay) continue;
				
				if (this->m_arr1[i]->s_roomnum == num) {
					++count;
					if (!this->m_arr1[i]->s_pay) {
						//ͳ������
						++unpaid_count;
						//ͳ��Ӧ�ɷ���
						due_payment += this->m_arr1[i]->s_price;
						//��¼���
						id_list.push_back(i);
					}
					this->m_arr1[i]->show_find_room_res();
					cout << endl;
				}
			}
			cout << "�ܹ� " << count << " �ʶ���, δ֧������ " << unpaid_count << " ��" << endl;
			cout << "Ӧ�ɷ��ܽ��Ϊ��" << due_payment << " ��" << endl;
			cout << "1. ȫ��֧���������롰a or A��" << endl;
			cout << "2. ѡ��֧���������롰p or P��,������Ҫ����ı�ź����롰y or Y��ȷ��" << endl;
			cout << "3. ȡ��֧��: �����롰q or Q��" << endl;
			char ypq;
			cin >> ypq;
			while (ypq != 'a' && ypq != 'A' && ypq != 'P' && ypq != 'p' && ypq != 'q' && ypq != 'Q') {
				cout << "Error����������ȫ��֧�������롰a or A����ѡ��֧�������롰p or P��ʹ�á�y or Y��������ȡ��֧�������롰q or Q����" << endl;
				cin >> ypq;
			}

			switch (ypq)
			{
			case 'a':case 'A':
				for (const auto& item : id_list) {
					if (!this->m_arr1[item]->s_pay) {
						this->m_arr1[item]->s_paytime = this->vtos(this->get_time()); //δ֧�������˵�����Ҫ���¸����ʱ��
					}
					this->m_arr1[item]->s_pay = true;
				}
				this->m_save();
				cout << "ȫ��֧���ɹ��������ɽ����Ϊ��" << due_payment << " ��" << endl;
				cout << "����ʱ��Ϊ��";
				this->time_format2(this->get_time());
				break;
			case 'p':case 'P':
				cout << "��������Ҫ֧���ı�� [ ";
				for (const auto& item : id_list) {
					cout << item + 1 << " ";
				}
				cout << "]" << endl;
				while (cin >> tmp_num) {
					if (tmp_num == "y" || tmp_num == "Y") break;
					
					auto it = find(id_list.begin(), id_list.end(), stoi(tmp_num) - 1);
					while (it == id_list.end()) {
						cout << "��������ȷ����Ҫ֧���Ķ������" << endl;
						cout << "������Ҫ֧���Ķ�����ţ�[ ";
						for (const auto& item : id_list) {
							cout << item + 1 << " ";
						}
						cout << "]" << endl;
						cin >> tmp_num;
						it = find(id_list.begin(), id_list.end(), stoi(tmp_num) - 1);
					}
					id_list_tmp.push_back(stoi(tmp_num) - 1);
				}
				for (const auto& item_tmp : id_list_tmp) {
					if (!this->m_arr1[item_tmp]->s_pay) {
						this->m_arr1[item_tmp]->s_paytime = this->vtos(this->get_time()); //δ֧�������˵�����Ҫ���¸����ʱ��
					}
					this->m_arr1[item_tmp]->s_pay = true;
					due_payment_part += this->m_arr1[item_tmp]->s_price;
				}
				this->m_save();
				cout << "����֧���ɹ��������ɽ����Ϊ��" << due_payment_part << " ��" << endl;
				cout << "����ʱ��Ϊ��";
				this->time_format2(this->get_time());
				break;
			case 'q':case 'Q':
				cout << "��ȡ��֧��������" << endl;
				break;
			} 
			break;
		case 1:
			for (int i = 0; i < this->m_num; i++) {
				if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay) continue;
				if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 1) {
					++count;
					if (!this->m_arr1[i]->s_pay) {
						++unpaid_count;
						due_payment += this->m_arr1[i]->s_price;
						id_list.push_back(i);
					}
					this->m_arr1[i]->show_find_room_res();
					cout << endl;
				}
			}
			cout << "�ܹ� " << count << " �ʶ���, δ֧������ " << unpaid_count << " ��" << endl;
			cout << "Ӧ�ɷ��ܽ��Ϊ��" << due_payment << " ��" << endl;
			cout << "1. ȫ��֧���������롰a or A��" << endl;
			cout << "2. ѡ��֧���������롰p or P��,������Ҫ����ı�ź����롰y or Y��ȷ��" << endl;
			cout << "3. ȡ��֧��: �����롰q or Q��" << endl;
			cin >> ypq;
			while (ypq != 'a' && ypq != 'A' && ypq != 'P' && ypq != 'p' && ypq != 'q' && ypq != 'Q') {
				cout << "Error����������ȫ��֧�������롰a or A����ѡ��֧�������롰p or P��ʹ�á�y or Y��������ȡ��֧�������롰q or Q����" << endl;
				cin >> ypq;
			}
			switch (ypq)
			{
			case 'a':case 'A':
				for (const auto& item : id_list) {
					if (!this->m_arr1[item]->s_pay) {
						this->m_arr1[item]->s_paytime = this->vtos(this->get_time()); //δ֧�������˵�����Ҫ���¸����ʱ��
					}
					this->m_arr1[item]->s_pay = true;
				}
				this->m_save();
				cout << "ȫ��֧���ɹ��������ɽ����Ϊ��" << due_payment << " ��" << endl;
				cout << "����ʱ��Ϊ��";
				this->time_format2(this->get_time());
				break;
			case 'p':case 'P':
				cout << "��������Ҫ֧���ı�� [ ";
				for (const auto& item : id_list) {
					cout << item + 1 << " ";
				}
				cout << "]" << endl;
				while (cin >> tmp_num) {
					if (tmp_num == "y" || tmp_num == "Y") break;
					auto it = find(id_list.begin(), id_list.end(), stoi(tmp_num) - 1);
					while (it == id_list.end()) {
						cout << "��������ȷ����Ҫ֧���Ķ������" << endl;
						cout << "������Ҫ֧���Ķ�����ţ�[ ";
						for (const auto& item : id_list) {
							cout << item + 1 << " ";
						}
						cout << "]" << endl;
						cin >> tmp_num;
						it = find(id_list.begin(), id_list.end(), stoi(tmp_num) - 1);
					}
					id_list_tmp.push_back(stoi(tmp_num) - 1);

				}
				for (const auto& item_tmp : id_list_tmp) {
					if (!this->m_arr1[item_tmp]->s_pay) {
						this->m_arr1[item_tmp]->s_paytime = this->vtos(this->get_time()); //δ֧�������˵�����Ҫ���¸����ʱ��
					}
					this->m_arr1[item_tmp]->s_pay = true;
					due_payment_part += this->m_arr1[item_tmp]->s_price;
				}
				this->m_save();
				cout << "����֧���ɹ��������ɽ����Ϊ��" << due_payment_part << " ��" << endl;
				cout << "����ʱ��Ϊ��";
				this->time_format2(this->get_time());
				break;
			case 'q':case 'Q':
				cout << "��ȡ��֧��������" << endl;
				break;
			}
			break;
		case 2:
			for (int i = 0; i < this->m_num; i++) {
				if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay) continue;
				if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 2) {
					++count;
					if (!this->m_arr1[i]->s_pay) {
						++unpaid_count;
						due_payment += this->m_arr1[i]->s_price;
						id_list.push_back(i);
					}
					this->m_arr1[i]->show_find_room_res();
					cout << endl;
				}
			}
			cout << "�ܹ� " << count << " �ʶ���, δ֧������ " << unpaid_count << " ��δ֧��" << endl;
			cout << "Ӧ�ɷ��ܽ��Ϊ��" << due_payment << " ��" << endl;
			cout << "1. ȫ��֧���������롰a or A��" << endl;
			cout << "2. ѡ��֧���������롰p or P��,������Ҫ����ı�ź����롰y or Y��ȷ��" << endl;
			cout << "3. ȡ��֧��: �����롰q or Q��" << endl;
			cin >> ypq;
			while (ypq != 'a' && ypq != 'A' && ypq != 'P' && ypq != 'p' && ypq != 'q' && ypq != 'Q') {
				cout << "Error����������ȫ��֧�������롰a or A����ѡ��֧�������롰p or P��ʹ�á�y or Y��������ȡ��֧�������롰q or Q����" << endl;
				cin >> ypq;
			}
			switch (ypq)
			{
			case 'a':case 'A':
				for (const auto& item : id_list) {
					if (!this->m_arr1[item]->s_pay) {
						this->m_arr1[item]->s_paytime = this->vtos(this->get_time()); //δ֧�������˵�����Ҫ���¸����ʱ��
					}
					this->m_arr1[item]->s_pay = true;
				}
				this->m_save();
				cout << "ȫ��֧���ɹ��������ɽ����Ϊ��" << due_payment << " ��" << endl;
				cout << "����ʱ��Ϊ��";
				this->time_format2(this->get_time());
				break;
			case 'p':case 'P':
				cout << "��������Ҫ֧���ı�� [ ";
				for (const auto& item : id_list) {
					cout << item + 1 << " ";
				}
				cout << "]" << endl;
				while (cin >> tmp_num) {
					if (tmp_num == "y" || tmp_num == "Y") break;
					auto it = find(id_list.begin(), id_list.end(), stoi(tmp_num) - 1);
					while (it == id_list.end()) {
						cout << "��������ȷ����Ҫ֧���Ķ������" << endl;
						cout << "������Ҫ֧���Ķ�����ţ�[ ";
						for (const auto& item : id_list) {
							cout << item + 1 << " ";
						}
						cout << "]" << endl;
						cin >> tmp_num;
						it = find(id_list.begin(), id_list.end(), stoi(tmp_num) - 1);
					}
					id_list_tmp.push_back(stoi(tmp_num) - 1);

				}
				for (const auto& item_tmp : id_list_tmp) {
					if (!this->m_arr1[item_tmp]->s_pay) {
						this->m_arr1[item_tmp]->s_paytime = this->vtos(this->get_time()); //δ֧�������˵�����Ҫ���¸����ʱ��
					}
					this->m_arr1[item_tmp]->s_pay = true;
					due_payment_part += this->m_arr1[item_tmp]->s_price;
				}
				this->m_save();
				cout << "����֧���ɹ��������ɽ����Ϊ��" << due_payment_part << " ��" << endl;
				cout << "����ʱ��Ϊ��";
				this->time_format2(this->get_time());
				break;
			case 'q':case 'Q':
				cout << "��ȡ��֧��������" << endl;
				break;
			}
			break;
		}
	}
	else {
		cout << "Error������ѯ����Ų����ڣ�" << endl;
	}
	system("pause");
}

//��ѯ�ɷѼ�¼
void usingsystem::sear_info()
{
	// �ͱ������ͬ��
	this->in_stu();
	cout << "��������ķ����" << endl;
	int num;
	cin >> num;
	cout << "�鿴����˵�������1���鿴ˮ���˵�������2" << endl;
	int choose;
	cin >> choose;
	while (choose != 1 && choose != 2) {
		cout << "Error���������󡣲鿴����˵�������1���鿴ˮ���˵�������2" << endl;
		cin >> choose;
	}
	int ret = is_exist(num);
	if (ret != -1 && choose == 1) {
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|                                  ��� kWh                                |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  δ֧�����  |  ��һ�μ�¼����  |  ���μ�¼����  |  ʹ����  |  Ӧ�����  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		
		int unpaid_count = 0;
		string une = "20230101";
		string unl = "20230101";
		double totalusage = 0;
		double totalprice = 0;
		vector<string> datavec1;
		for (int i = 0; i < this->m_num; i++) {
			if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_type == 1) {
				//une = this->m_arr1[i]->s_time;
				continue;
			}
			if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 1) {
				// δ֧����
				if (!this->m_arr1[i]->s_pay) {
					unpaid_count++;
					cout << setprecision(2) << fixed;
					this->m_arr1[i]->show_table();
					//unl = to_string(static_cast<int>(max(ceilf(stof(this->m_arr1[i]->s_time)), stof(unl))));
					datavec1.push_back(this->m_arr1[i]->s_time);
					totalusage += this->m_arr1[i]->s_degree - this->m_arr1[i]->s_ldegree;
					totalprice += this->m_arr1[i]->s_price;
				}
			}
		}
		

		if (unpaid_count == 0) {
			une = "########";
			unl = "########";
		}
		else {
			une = compareDate(datavec1, "min");
			unl = compareDate(datavec1, "max");
		}
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  �ܶ�����Ŀ  |   �����¼����   |  ���¼�¼����  |  ������  |  Ӧ���ܶ�  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|" << setw(7) << unpaid_count << setw(8) << "|" << setw(16) << this->m_arr1[0]->timeformat(une) << setw(3) << "|" << setw(15) << this->m_arr1[0]->timeformat(unl) << setw(2) << "|" << setw(8) << totalusage << setw(3) << "|" << setw(9) << totalprice << setw(4) << "|" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  ��֧�����  |          �����ڵĽɷ�ʱ��         |  ʹ����  |  �Ѹ����  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		
		int paid_count = 0;
		string ede = "20230101";
		string edl = "20230101";
		double totalusage2 = 0;
		double totalprice2 = 0;
		string currentdate;
		string cury = to_string(this->get_time()[0]);
		string curm = to_string(this->get_time()[1]);
		if (curm.length() != 2) curm = "0" + curm;
		string curd = to_string(this->get_time()[2]);
		if (curd.length() != 2) curd = "0" + curd;
		currentdate = cury + curm + curd;
		string halfyearago = get6month_ago(currentdate);
		vector<string> datavec2;
		for (int i = 0; i < this->m_num; i++) {
			if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay && this->m_arr1[i]->s_type == 1) {
				//ede = this->m_arr1[i]->s_time;
				continue;
			}

			if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 1) {
				// ֧����, ��ʱ���ڰ�����
				if (this->m_arr1[i]->s_pay && in6mon(this->m_arr1[i]->s_paytime, halfyearago)) {
					cout << setprecision(2) << fixed;
					this->m_arr1[i]->show_table2();
					paid_count++;
					//edl = to_string(static_cast<int>(max(ceilf(stof(this->m_arr1[i]->s_time)), stof(edl))));
					datavec2.push_back(this->m_arr1[i]->s_paytime.substr(0,8));
					totalusage2 += this->m_arr1[i]->s_degree - this->m_arr1[i]->s_ldegree;
					totalprice2 += this->m_arr1[i]->s_price;
				}
			}
		}
		if (paid_count == 0) {
			ede = "########";
			edl = "########";
		}
		else{
			edl = compareDate(datavec2, "max");
			ede = compareDate(datavec2, "min");
		}

		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  �ܶ�����Ŀ  |   ����ɷ�����   |  ���½ɷ�����  |  ������  |  �Ѹ��ܶ�  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|" << setw(7) << paid_count << setw(8) << "|" << setw(16) << this->m_arr1[0]->timeformat(ede) << setw(3) << "|" << setw(15) << this->m_arr1[0]->timeformat(edl) << setw(2) << "|" << setw(8) << totalusage2 << setw(3) << "|" << setw(9) << totalprice2 << setw(4) << "|" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
	}
	else if (ret != -1 && choose == 2) {
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|                                  ˮ�� m^3                                |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  δ֧�����  |  ��һ�μ�¼����  |  ���μ�¼����  |  ʹ����  |  Ӧ�����  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;

		int unpaid_count = 0;
		string une = "20230101";
		string unl = "20230101";
		double totalusage = 0;
		double totalprice = 0;
		vector<string> datavec1;
		for (int i = 0; i < this->m_num; i++) {
			if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_type == 2) {
				//une = this->m_arr1[i]->s_time;
				continue;
			}
			if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 2) {
				// δ֧����
				if (!this->m_arr1[i]->s_pay) {
					unpaid_count++;
					cout << setprecision(2) << fixed;
					this->m_arr1[i]->show_table();
					//unl = to_string(static_cast<int>(max(ceilf(stof(this->m_arr1[i]->s_time)),stof(unl))));
					datavec1.push_back(this->m_arr1[i]->s_time);
					totalusage += this->m_arr1[i]->s_degree - this->m_arr1[i]->s_ldegree;
					totalprice += this->m_arr1[i]->s_price;
				}
			}
		}

		if (unpaid_count == 0) {
			une = "########";
			unl = "########";
		}
		else {
			une = compareDate(datavec1, "min");
			unl = compareDate(datavec1, "max");
		}
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  �ܶ�����Ŀ  |   �����¼����   |  ���¼�¼����  |  ʹ����  |  Ӧ���ܶ�  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|" << setw(7) << unpaid_count << setw(8) << "|" << setw(16) << this->m_arr1[0]->timeformat(une) << setw(3) << "|" << setw(15) << this->m_arr1[0]->timeformat(unl) << setw(2) << "|" << setw(8) << totalusage << setw(3) << "|" << setw(9) << totalprice << setw(4) << "|" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  ��֧�����  |          �����ڵĽɷ�ʱ��         |  ������  |  �Ѹ����  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;

		int paid_count = 0;
		string ede = "20230101";
		string edl = "20230101";
		double totalusage2 = 0;
		double totalprice2 = 0;
		string currentdate;
		string cury = to_string(this->get_time()[0]);
		string curm = to_string(this->get_time()[1]);
		if (curm.length() != 2) curm = "0" + curm;
		string curd = to_string(this->get_time()[2]);
		if (curd.length() != 2) curd = "0" + curd;
		currentdate = cury + curm + curd;
		string halfyearago = get6month_ago(currentdate);
		vector<string> datavec2;
		for (int i = 0; i < this->m_num; i++) {
			if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay && this->m_arr1[i]->s_type == 2) {
				//ede = this->m_arr1[i]->s_time;
				continue;
			}

			if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 2) {
				// ֧����, ��ʱ���ڰ�����
				if (this->m_arr1[i]->s_pay && in6mon(this->m_arr1[i]->s_paytime, halfyearago)) {
					cout << setprecision(2) << fixed;
					this->m_arr1[i]->show_table2();
					paid_count++;
					//edl = to_string(static_cast<int>(max(ceilf(stof(this->m_arr1[i]->s_time)), stof(edl))));
					datavec2.push_back(this->m_arr1[i]->s_paytime.substr(0, 8));
					totalusage2 += this->m_arr1[i]->s_degree - this->m_arr1[i]->s_ldegree;
					totalprice2 += this->m_arr1[i]->s_price;
				}
			}
		}
		if (paid_count == 0) {
			ede = "########";
			edl = "########";
		}
		else {
			edl = compareDate(datavec2, "max");
			ede = compareDate(datavec2, "min");
		}
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  �ܶ�����Ŀ  |   ����ɷ�����   |  ���½ɷ�����  |  ������  |  �Ѹ��ܶ�  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|" << setw(7) << paid_count << setw(8) << "|" << setw(16) << this->m_arr1[0]->timeformat(ede) << setw(3) << "|" << setw(15) << this->m_arr1[0]->timeformat(edl) << setw(2) << "|" << setw(8) << totalusage2 << setw(3) << "|" << setw(9) << totalprice2 << setw(4) << "|" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
	}
	else {
		cout << "Error������ѯ����Ų����ڣ�" << endl;
	}

	system("pause");
}

//��ѯδ�ɷ�����
void usingsystem::not_pay() {
	// �ͱ������ͬ��
	this->in_stu();
	personsystem s;
	cout << "δ�ɷ�������" << endl;
	//��������������
	map<int, double> roommap;
	for (int i = 0; i < this->m_num; i++) {
		//δ�ɷѵķ���
		if (!this->m_arr1[i]->s_pay) {
			auto itr = roommap.find(this->m_arr1[i]->s_roomnum);  // ͳ������Ҫ������Ǯ
			if (itr != roommap.end()) {
				roommap[this->m_arr1[i]->s_roomnum] += this->m_arr1[i]->s_price;
			}
			else {
				roommap[this->m_arr1[i]->s_roomnum] = this->m_arr1[i]->s_price;
			}
		}
	}
	for (auto itr = roommap.begin(); itr != roommap.end(); ++itr) {
		cout << "����ţ�" << left<< setw(8) << itr->first << "   Ӧ�ɽ�" << itr->second << endl;
		for (int j = 0; j < s.m_num; j++) {
			if (s.m_arr[j]->m_roomNumber == itr->first) {
				cout << right << setw(6) << "->��" << s.m_arr[j]->m_name << endl;
			}
		}
	}

	
	system("pause");
}


void usingsystem::exitsystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(6);
}
void usingsystem::menu1() {
	cout << "****1�������ˮ����Ϣ**" << endl;
	cout << "****2����ѯ����********" << endl;
	cout << "****3����ѯ�ɷѼ�¼****" << endl;
	cout << "****4��չʾδ�ɷ�����**" << endl;
	cout << "****5, չʾ������Ϣ****" << endl;
	cout << "****6���������˵�******" << endl;
	cout << endl;
}
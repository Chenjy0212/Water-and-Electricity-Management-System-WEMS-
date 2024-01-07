#include"UsingElectricity.h"
#include"PersonSystem.h"
#include"UsingSystem.h"
#include"UsingWater.h"
#include <iostream>
#include <algorithm>
using namespace std;

int g_var1 = 0;

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
			<< this->m_arr1[i]->s_pay << endl;
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

	int num = 0;
	while (ifs >> id && ifs >> roomnum && ifs >> ltime && ifs >> time && ifs >> ldegree && ifs >> degree && ifs >> price && ifs >> type && ifs >> pay) {
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

	int index = 0;
	while (ifs >> id && ifs >> roomnum && ifs >> ltime && ifs >> time && ifs >> ldegree && ifs >> degree && ifs >> price && ifs >> type && ifs >> pay) {
		system1* system = NULL;
		if (type == 1) {
			system = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 1, pay);
		}
		if (type == 2) {
			system = new usingwater(id, roomnum, ltime, time, ldegree, degree, price, 2, pay);
		}
		this->m_arr1[index] = system;
		index++;
	}
}

//��ʾ������Ϣ
void usingsystem::show_stu() {
	if (this->m_file) {
		cout << "�ļ�Ϊ��" << endl;
	}
	else {
		cout << "��ǰˮ���¼�ܹ��� " << this->get_num() << " ��" << endl;
		for (int i = 0; i < this->m_num; i++) {
			this->m_arr1[i]->show_info00();
			cout << endl;
		}
	}
	system("pause");
	system("cls");
}
//�����Ϣ
void usingsystem::add_info() {
	personsystem s;

	cout << "��������Ҫ��ӵ�ˮ�����Ŀ" << endl;
	int addnum = 0;
	cin >> addnum;

	if (addnum > 0) {
		int newsize = this->m_num + addnum;//�����¿ռ��С
		system1** newspace1 = new system1 * [newsize];//�ڶ��������¿ռ�
		if (this->m_arr1 != NULL) //��ԭ�ռ������ݷŵ��¿ռ���
		{
			for (int i = 0; i < this->m_num; i++)
			{
				newspace1[i] = this->m_arr1[i];
			}
		}
		for (int i = 0; i < addnum; i++) {
			int id;
			int roomnum;
			string time;
			string ltime = "20230101";
			double degree;
			double ldegree = 0;
			double price;
			bool pay = false;
			if(i != 0){ 
				cout << endl; 
			}
			id = ++g_var1;
			cout << "������� " << i+1 << " �������" << endl;
			cin >> roomnum;
			int ret = s.is_exist2(roomnum);
			while (ret == -1) {
				cout << "����Ų���ȷ������������" << endl;
				cin >> roomnum;
				ret = s.is_exist2(roomnum);
			}
			cout << "�������" << i + 1 << "���ĳ���ʱ��(eg��20240101)" << endl;
			cin >> time;
			cout << "�������1��ˮ������2" << endl;
			int num;
			cin >> num;
			while (num != 1 && num != 2) {
				cout << "Error���������󡣵������1��ˮ������2" << endl;
				cin >> num;
			}
			switch (num)
			{
			case 1:
				cout << "�������" << i + 1 << "���ĵ�ǰ�õ����" << endl;
				break;
			case 2:
				cout << "�������" << i + 1 << "���ĵ�ǰˮ����" << endl;
				break;
			}
			cin >> degree;

			// �Զ���ȡ�ϴμ�¼ʱ���ʹ�õ���
			bool exite_flag = false;
			for (int i = 0; i < this->m_num; i++)
			{
				// ���֮ǰ�м�¼�Ļ�
				if (this->m_arr1[i]->s_roomnum == roomnum && this->m_arr1[i]->s_type == num) {
					//�����ǲ�ͬ�ı��в�ͬ�Ľ��
					exite_flag = true;
					ldegree = max(m_arr1[i]->s_degree, ldegree);
					ltime = to_string(static_cast<int>(max(stof(this->m_arr1[i]->s_time), stof(ltime))));
				}
			}
			if (!exite_flag){ // ���û�м�¼,��ô��ʼ�������趨Ϊ�Ѿ�֧��
				ldegree = degree;
				ltime = time;
				pay = true;
			}

			system1* system = NULL;
			switch (num) {
			case 1: {
				if(s.m_arr[ret]->m_UID == 1){
					stucoststd* scs = new stucoststd(degree - ldegree, num);
					price = scs->cal_price();
					delete scs;
					system = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 1, pay);
					break;
				}
				else {
					teccoststd* tcs = new teccoststd(degree - ldegree, num);
					price = tcs->cal_price();
					delete tcs;
					system = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 1, pay);
					break;
				}
			}
			case 2: {
				if (s.m_arr[ret]->m_UID == 1) {
					stucoststd* scs = new stucoststd(degree - ldegree, num);
					price = scs->cal_price();
					delete scs;
					system = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 2, pay);
					break;
				}
				else {
					teccoststd* tcs = new teccoststd(degree - ldegree, num);
					price = tcs->cal_price();
					delete tcs;
					system = new usingelectricity(id, roomnum, ltime, time, ldegree, degree, price, 2, pay);
					break;
				}
			}
			}
			newspace1[this->m_num + i] = system;
		}
	
		delete[]this->m_arr1;      //�ͷ�ԭ���Ŀռ�
		this->m_arr1 = newspace1;  //�����¿ռ��ָ��
		this->m_num = newsize;     //�����µĸ���
		this->m_file = false;      //���²�Ϊ�ձ�־
		cout << "�ɹ����" << endl;
		this->m_save();
		
	}
	else {
		cout << "��������" << endl;
	}
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
				if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay) continue;
				if (this->m_arr1[i]->s_roomnum == num) {
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
			cout << "ȫ��֧�������롰a or A����ѡ��֧�������롰p or P��ʹ�á�y or Y�������� ȡ��֧�������롰q or Q����" << endl;
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
					this->m_arr1[item-1]->s_pay = true;
				}
				this->m_save();
				cout << "ȫ��֧���ɹ��������ɽ����Ϊ��" << due_payment << " ��" << endl;
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
					this->m_arr1[item_tmp]->s_pay = true;
					due_payment_part += this->m_arr1[item_tmp]->s_price;
				}
				this->m_save();
				cout << "����֧���ɹ��������ɽ����Ϊ��" << due_payment_part << " ��" << endl;
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
			cout << "�ܹ� " << count << " �ʶ���, δ֧������ " << unpaid_count << " ��δ֧��" << endl;
			cout << "Ӧ�ɷ��ܽ��Ϊ��" << due_payment << " ��" << endl;
			cout << "ȫ��֧�������롰a or A����ѡ��֧�������롰p or P��ʹ�á�y or Y�������� ȡ��֧�������롰q or Q����" << endl;
	
			cin >> ypq;
			while (ypq != 'a' && ypq != 'A' && ypq != 'P' && ypq != 'p' && ypq != 'q' && ypq != 'Q') {
				cout << "Error����������ȫ��֧�������롰a or A����ѡ��֧�������롰p or P��ʹ�á�y or Y��������ȡ��֧�������롰q or Q����" << endl;
				cin >> ypq;
			}
			switch (ypq)
			{
			case 'a':case 'A':
				for (const auto& item : id_list) {
					this->m_arr1[item - 1]->s_pay = true;
				}
				this->m_save();
				cout << "ȫ��֧���ɹ��������ɽ����Ϊ��" << due_payment << " ��" << endl;
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
					this->m_arr1[item_tmp]->s_pay = true;
					due_payment_part += this->m_arr1[item_tmp]->s_price;
				}
				this->m_save();
				cout << "����֧���ɹ��������ɽ����Ϊ��" << due_payment_part << " ��" << endl;
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
			cout << "ȫ��֧�������롰a or A����ѡ��֧�������롰p or P��ʹ�á�y or Y�������� ȡ��֧�������롰q or Q����" << endl;
			cin >> ypq;
			while (ypq != 'a' && ypq != 'A' && ypq != 'P' && ypq != 'p' && ypq != 'q' && ypq != 'Q') {
				cout << "Error����������ȫ��֧�������롰a or A����ѡ��֧�������롰p or P��ʹ�á�y or Y��������ȡ��֧�������롰q or Q����" << endl;
				cin >> ypq;
			}
			switch (ypq)
			{
			case 'a':case 'A':
				for (const auto& item : id_list) {
					this->m_arr1[item - 1]->s_pay = true;
				}
				this->m_save();
				cout << "ȫ��֧���ɹ��������ɽ����Ϊ��" << due_payment << " ��" << endl;
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
					this->m_arr1[item_tmp]->s_pay = true;
					due_payment_part += this->m_arr1[item_tmp]->s_price;
				}
				this->m_save();
				cout << "����֧���ɹ��������ɽ����Ϊ��" << due_payment_part << " ��" << endl;
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
		for (int i = 0; i < this->m_num; i++) {
			if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay && this->m_arr1[i]->s_type == 1) {
				une = this->m_arr1[i]->s_time;
				continue;
			}
			if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 1) {
				// δ֧����
				if (!this->m_arr1[i]->s_pay) {
					unpaid_count++;
					cout << setprecision(2) << fixed;
					this->m_arr1[i]->show_table();
					unl = to_string(static_cast<int>(max(stof(this->m_arr1[i]->s_time), stof(unl))));
					totalusage += this->m_arr1[i]->s_degree - this->m_arr1[i]->s_ldegree;
					totalprice += this->m_arr1[i]->s_price;
				}
			}
		}
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  �ܶ�����Ŀ  |   �����¼����   |  ��ټ�¼����  |  ʹ����  |  Ӧ���ܶ�  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|" << setw(7) << unpaid_count << setw(8) << "|" << setw(16) << une.substr(0, 4) + "��" + une.substr(4, 2) + "��" + une.substr(6, 2) + "��" << setw(3) << "|" << setw(15) << unl.substr(0, 4) + "��" + unl.substr(4, 2) + "��" + unl.substr(6, 2) + "��" << setw(2) << "|" << setw(8) << totalusage << setw(3) << "|" << setw(9) << totalprice << setw(4) << "|" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  ��֧�����  |  ��һ�μ�¼����  |  ���μ�¼����  |  ������  |  �Ѹ����  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		
		int paid_count = 0;
		string ede = "20230101";
		string edl = "20230101";
		double totalusage2 = 0;
		double totalprice2 = 0;
		for (int i = 0; i < this->m_num; i++) {
			if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay && this->m_arr1[i]->s_type == 1) {
				ede = this->m_arr1[i]->s_time;
				continue;
			}
			if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 1) {
				// ֧����
				if (this->m_arr1[i]->s_pay) {
					cout << setprecision(2) << fixed;
					this->m_arr1[i]->show_table();
					paid_count++;
					edl = to_string(static_cast<int>(max(stof(this->m_arr1[i]->s_time), stof(edl))));
					totalusage2 += this->m_arr1[i]->s_degree - this->m_arr1[i]->s_ldegree;
					totalprice2 += this->m_arr1[i]->s_price;
				}
			}
		}
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|" << setw(7) << paid_count << setw(8) << "|" << setw(16) << ede.substr(0, 4) + "��" + ede.substr(4, 2) + "��" + ede.substr(6, 2) + "��" << setw(3) << "|" << setw(15) << edl.substr(0, 4) + "��" + edl.substr(4, 2) + "��" + edl.substr(6, 2) + "��" << setw(2) << "|" << setw(8) << totalusage2 << setw(3) << "|" << setw(9) << totalprice2 << setw(4) << "|" << endl;
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
		for (int i = 0; i < this->m_num; i++) {
			if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay && this->m_arr1[i]->s_type == 2) {
				une = this->m_arr1[i]->s_time;
				continue;
			}
			if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 2) {
				// δ֧����
				if (!this->m_arr1[i]->s_pay) {
					unpaid_count++;
					cout << setprecision(2) << fixed;
					this->m_arr1[i]->show_table();
					cout << this->m_arr1[i]->s_time << endl;
					unl = to_string(static_cast<int>(max(stof(this->m_arr1[i]->s_time),stof(unl))));
					totalusage += this->m_arr1[i]->s_degree - this->m_arr1[i]->s_ldegree;
					totalprice += this->m_arr1[i]->s_price;
				}
			}
		}

		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  �ܶ�����Ŀ  |   �����¼����   |  ��ټ�¼����  |  ʹ����  |  Ӧ���ܶ�  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|" << setw(7) << unpaid_count << setw(8) << "|" << setw(16) << une.substr(0, 4) + "��" + une.substr(4, 2) + "��" + une.substr(6, 2) + "��" << setw(3) << "|" << setw(15) << unl.substr(0, 4) + "��" + unl.substr(4, 2) + "��" + unl.substr(6, 2) + "��" << setw(2) << "|" << setw(8) << totalusage << setw(3) << "|" << setw(9) << totalprice << setw(4) << "|" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|  ��֧�����  |  ��һ�μ�¼����  |  ���μ�¼����  |  ������  |  �Ѹ����  |" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;

		int paid_count = 0;
		string ede = "20230101";
		string edl = "20230101";
		double totalusage2 = 0;
		double totalprice2 = 0;
		for (int i = 0; i < this->m_num; i++) {
			if (this->m_arr1[i]->s_ltime == this->m_arr1[i]->s_time && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay && this->m_arr1[i]->s_ldegree == this->m_arr1[i]->s_degree && this->m_arr1[i]->s_pay && this->m_arr1[i]->s_type == 2) {
				ede = this->m_arr1[i]->s_time;
				continue;
			}
			if (this->m_arr1[i]->s_roomnum == num && this->m_arr1[i]->s_type == 2) {
				// ֧����
				if (this->m_arr1[i]->s_pay) {
					cout << setprecision(2) << fixed;
					this->m_arr1[i]->show_table();
					paid_count++;
					edl = to_string(static_cast<int>(max(stof(this->m_arr1[i]->s_time), stof(edl))));
					totalusage2 += this->m_arr1[i]->s_degree - this->m_arr1[i]->s_ldegree;
					totalprice2 += this->m_arr1[i]->s_price;
				}
			}
		}

		cout << "+--------------------------------------------------------------------------+" << endl;
		cout << "|" << setw(7) << paid_count << setw(8) << "|" << setw(16) << ede.substr(0, 4) + "��" + ede.substr(4, 2) + "��" + ede.substr(6, 2) + "��" << setw(3) << "|" << setw(15) << edl.substr(0, 4) + "��" + edl.substr(4, 2) + "��" + edl.substr(6, 2) + "��" << setw(2) << "|" << setw(8) << totalusage2 << setw(3) << "|" << setw(9) << totalprice2 << setw(4) << "|" << endl;
		cout << "+--------------------------------------------------------------------------+" << endl;
	}
	else {
		cout << "Error������ѯ����Ų����ڣ�" << endl;
	}

	system("pause");
}

////��ѯδ�ɷ�����
void usingsystem::not_pay() {}
//	personsystem s;
//	cout << "δ�ɷ�������" << endl;
//	for (int i = 0; i < this->m_num; i++) {
//		if (this->m_arr1[i]->s_price != 0) {
//			for (int j = 0; j < s.m_num; j++) {
//				if (s.m_arr[j]->m_roomNumber = this->m_arr1[i]->s_id) {
//					cout << s.m_arr[j]->m_name << endl;
//				}
//			}
//		}
//	}
//}


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
	cout << "****5���������˵�******" << endl;
	cout << endl;
}
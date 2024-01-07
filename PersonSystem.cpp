#include"PersonSystem.h"
#include"Student.h"
#include"Person.h"
#include <iostream>

personsystem::personsystem() {

	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//�ļ������ڵ����
	if (!ifs.is_open()) {
		this->m_num = 0;      //��ʼ������
		this->m_file = true;  //��ʼ���ļ�Ϊ�ձ�־
		this->m_arr = NULL;   //��ʼ������
		ifs.close();          //�ر��ļ�
		return;
	}
	//�ļ�����,����Ϊ��
	char ch;
	ifs >> ch;  //���ַ�
	if (ifs.eof()) {
		this->m_num = 0;
		this->m_file = true;
		this->m_arr = NULL;
		ifs.close();
		return;
	}
	//�ļ����ڣ������ݲ�Ϊ��
	int num = this->get_num();
	this->m_num = num;
	//���ٿռ�
	this->m_arr = new person * [this->m_num];
	//���ļ��е����ݴ浽������
	this->in_stu();
}
personsystem::~personsystem() {
	if (this->m_arr != NULL) {
		delete[]this->m_arr;
		this->m_arr = NULL;
	}//�ͷŶ���������
}
void personsystem::m_save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	//��ÿ���˵�����д���ļ���
	for (int i = 0; i < this->m_num; i++)
	{
		ofs << this->m_arr[i]->m_name << " "
			<< this->m_arr[i]->m_id << " "
			<< this->m_arr[i]->m_roomNumber << " "
			<< this->m_arr[i]->m_UID << endl;
	}
	ofs.close();
}
//ͳ���ļ��е�����
int personsystem::get_num() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string name;
	int id;
	int roomnum;
	int UID;

	int num = 0;
	while (ifs >> name && ifs >> id && ifs >> roomnum && ifs >> UID) {
		num++;
	}
	ifs.close();
	return num;
}
//��ȡ�ļ��еı��
vector<int> personsystem::get_id() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string name;
	int id;
	int roomnum;
	int UID;

	vector<int> idv;
	while (ifs >> name && ifs >> id && ifs >> roomnum && ifs >> UID) {
		idv.push_back(id);
	}
	ifs.close();
	return idv;
}
void personsystem::in_stu() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	int roomNumber;
	string name;
	int UID;

	int index = 0;
	while (ifs >> name && ifs >> id && ifs >> roomNumber && ifs >> UID) {
		person* person = NULL;
		if (UID == 1) {
			person = new teacher(name, id, roomNumber, UID);
		}
		else {
			person = new student(name, id, roomNumber, UID);
		}

		this->m_arr[index] = person;
		index++;
	}
}

//��ʾ��Ϣ
void personsystem::show_stu() {
	if (this->m_file) {
		cout << "�ļ�Ϊ��" << endl;
	}
	else {
		cout << "��ǰ�û�������Ϊ�� " << this->get_num() << endl;
		for (int i = 0; i < m_num; i++) {
			this->m_arr[i]->show_info();
			cout << endl;

		}
	}
	system("pause");
	system("cls");
}

//�����Ϣ
void personsystem::add_info() {
	cout << "��������Ҫ��ӵ�����" << endl;
	int addnum = 0;
	cin >> addnum;

	if (addnum > 0) {
		int newsize = this->m_num + addnum;          //�����¿ռ��С
		person** newspace = new person * [newsize];  //�ڶ��������¿ռ�
		if (this->m_arr != NULL)                     //��ԭ�ռ������ݷŵ��¿ռ���
		{
			for (int i = 0; i < this->m_num; i++)
			{
				newspace[i] = this->m_arr[i];
			}
		}

		vector<int> idv = this->get_id();  //��ȡ��������ı��
		//for (auto i : idv) {
		//	cout << i << endl;
		//}
		for (int i = 0; i < addnum; i++) {
			int id;
			string name;
			int roomNumber;
			int num;

			cout << "�������" << i + 1 << "���˵�����" << endl;
			cin >> name;
			cout << "�������" << i + 1 << "���˵�ѧ����" << endl;
			cin >> id;
			auto it = find(idv.begin(), idv.end(), id);
			while (it != idv.end()) {
				cout << "ѧ�����Ѵ��ڣ�����������" << endl;
				cin >> id;
				it = find(idv.begin(), idv.end(), id);
			}
			cout << "�������" << i + 1 << "���˵ķ����" << endl;
			cin >> roomNumber;
			cout << "��ѡ�������ݣ���ʦ����1��ѧ������2" << endl;
			cin >> num;
			while (num != 1 && num != 2) {
				cout << "������������������" << endl;
				cin >> num;
			}
			person* person = NULL;
			switch (num) {
			case 1:
				person = new student(name, id, roomNumber, 1);
				break;
			case 2:
				person = new teacher(name, id, roomNumber, 2);
				break;
			default:
				break;
			}

			newspace[this->m_num + i] = person;
		}
		delete[]this->m_arr;//�ͷ�ԭ���Ŀռ�
		this->m_arr = newspace;//�����¿ռ��ָ��
		this->m_num = newsize;//�����µĸ���
		this->m_file = false;//����ְ����Ϊ�ձ�־
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
int personsystem::is_exist(int id) {
	int index = -1;
	for (int i = 0; i < this->m_num; i++) {
		if (this->m_arr[i]->m_id == id) {
			index = i;
			break;
		}
	}
	return index;
}
int personsystem::is_exist2(int roomNumber) {
	int index = -1;
	for (int i = 0; i < this->m_num; i++) {
		if (this->m_arr[i]->m_roomNumber == roomNumber) {
			index = i;
			break;
		}
	}
	return index;
}
//ɾ����Ϣ
void personsystem::del_info() {
	if (this->m_file) {
		cout << "�ļ�������" << endl;
	}
	else {
		cout << "��������ɾ�����˵ı��" << endl;
		int id;
		cin >> id;

		int index = this->is_exist(id);
		if (index != -1) {
			for (int i = index; i < this->m_num - 1; i++) {
				this->m_arr[i] = this->m_arr[i + 1];
			}
			this->m_num--;//���������м�¼����
			//ͬ�����ļ���
			this->m_save();
			cout << "ɾ���ɹ�" << endl;
		}
		else {
			cout << "ɾ��ʧ�ܣ�δ�ҵ�����" << endl;
		}
	}
	system("pause");
	system("cls");
}
//�޸���Ϣ
void personsystem::mod_info() {
	if (this->m_file) {
		cout << "�ļ�������" << endl;
	}
	else {
		cout << "��������" << endl;
		int id;
		cin >> id;

		int ret = this->is_exist(id);
		if (ret != -1) {
			delete this->m_arr[ret];
			int new_id = 0;
			string new_name;
			int new_roomNumber;
			int new_UID;
			cout << "�������������" << endl;
			cin >> new_id;
			cout << "���������ID" << endl;
			cin >> new_name;
			cout << "��������ķ����" << endl;
			cin >> new_roomNumber;
			cout << "��ѡ�������ݣ���ʦ����1��ѧ������2" << endl;
			cin >> new_UID;
			person* person = NULL;
			switch (new_UID) {
			case 1:
				person = new student(new_name, new_id, new_roomNumber, 1);
				break;
			case 2:
				person = new teacher(new_name, new_id, new_roomNumber, 2);
				break;
			default:
				break;
			}
			this->m_arr[ret] = person;
			cout << "�޸ĳɹ�" << endl;
			this->m_save();

		}
		else {
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}
void personsystem::exitsystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(5);
}
void personsystem::menu2() {
	cout << "��ӭʹ���û���Ϣ����ϵͳ" << endl;
	cout << "******1�������Ϣ******" << endl;
	cout << "******2��ɾ����Ϣ******" << endl;
	cout << "******3���޸���Ϣ******" << endl;
	cout << "******4����ʾ��Ϣ******" << endl;
	cout << "******5���������˵�****" << endl;
	cout << endl;
}
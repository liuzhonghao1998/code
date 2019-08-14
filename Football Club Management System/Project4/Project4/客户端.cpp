#include<winsock2.h>
#include<iostream>
#include<stdio.h>
#include<string>
#include<stack> 
#include<list>//ѡ��list��Ϊ����
#include<fstream>
#include<stdlib.h>

#pragma comment(lib,"ws2_32.lib")

static int NUM = 0; //���ڱ�����׺�ַ��� 
static int HUM = 0; //���ڿ���Ա���� 
static char behind[50] = { 0 }; //���ڴ��׺���ʽ  

using namespace std;

class People {
public:
	People();
	//People(const People& rhs){};
	string name;  //�����������Ϣ 
	int age;
	virtual void writemessage() {};
	virtual void changemessage(int a) {};
	virtual void readmessage() {};
	~People() {};
};

People::People() {};



class GovernmentP : public People {
public:
	GovernmentP();
	//GovernmentP(const GovernmentP& rhs){};
	virtual void writemessage();
	virtual void changemessage(int a);
	virtual void getmessagefromfile(fstream &F);

	string getstrength() {  //�õ�������Ա������ 
		return strength;
	}

	int getmoney() {
		return money;
	}

	virtual void readmessage() {
		cout << "������Ա������:" << name << endl;
		cout << "������Ա������:" << age << endl;
		cout << "������Ա������:\n" << strength << endl;
		cout << "������Ա����н(����Ϊ��λ):" << money << endl;
	}
	~GovernmentP() {};
private:
	string strength; //���� 
	int money; //��н
};

class SportsP : public People {
public:
	SportsP();
	//SportsP(const SportsP& rhs){};
	virtual void writemessage();
	virtual void readmessage();
	virtual void changemessage(int a);
	virtual void getmessagefromfile(fstream &F);
	string getstrength() {  //�õ���Ա������ 5
		return strength;
	}

	string getclub() { //6
		return club;
	}

	void putclub(string n) {
		club = n;
	}
	int getmessage(int a) {
		switch (a) {
		case 1:
			return money;
			break;
		case 2:
			return Transferfee;
			break;
		case 3:
			return kick;
			break;
		case 4:
			return experience;
			break;
		}
	}
	void getstrengthfromsever(string s) {
		strength = s;
	}
	void getmessageformsever(int count , int num) {
		switch (count) {
		case 4:
			money = num;
			break;
		case 5:
			Transferfee = num;
			break;
		case 6:
			kick = num;
			break;
		case 7:
			experience = num;
			break;
		}
	}
	~SportsP() {};
private:
	string strength; //���� 
	int money; //��н 
	int Transferfee; // ת���
	int kick; // ��������
	int experience; //�������� 
	string club; //�������ֲ� 
};

class Club {
public:
	Club();
	list<GovernmentP>lis1;
	list<SportsP>lis2;
	string putname();
	void getname(string n) {
		Cname = n;
	}
	void writename();
	void writein(int choose); //1.��Ա0.������Ա
	void readout();
	int deleteP(string l, int choose);
	void addG() { GHUM++; }
	void deG() { GHUM--; }
	void addS() { SHUM++; }
	void deS() { SHUM--; }
	int getGnum() {
		return GHUM;
	}
	int getSnum() {
		return SHUM;
	}
	void SNUM(int s) {
		SHUM = s;
	}
	void GNUM(int s) {
		GHUM = s;
	}
	void readmessage() {
		cout << "���ֲ���:" << Cname << endl;
		cout << "������Ա������:" << GHUM << endl;
		cout << "��Ա����:" << SHUM << endl;
	}
	~Club() {};
private:
	string Cname;
	int GHUM, SHUM;
};

void match(list<SportsP> lis);  // ���Һ��� 
void Fuzzysearch(string term, SportsP temp); //ģ������
int type(string a); // ���ڷ����������� 
int power(char b); //�ж��������Ȩ�� 
void change_experience(string term); //�ı�ɺ�׺���ʽ 
int changenum(stack<char> s); //�����Ӧ���� 
void Allist();
int  highmatch(string end);//����ĸ߼�����
void Searchlist();

GovernmentP::GovernmentP() {};

void GovernmentP::writemessage() {
	cout << "������������Ա������:" << endl;
	getline(cin, name);
	cout << "������������Ա������:" << endl;
	cin >> age;
	cout << "������������Ա������:" << endl;
	getchar();
	getline(cin, strength);
	cout << "������������Ա����н(����Ϊ��λ):" << endl;
	cin >> money;
};

void GovernmentP::changemessage(int a) {
	switch (a) {
	case 1:
		cout << "������Ҫ���ĵ�����:" << endl;
		getchar();
		break;
	case 2:
		cout << "������Ҫ���ĵ�����:" << endl;
		cin >> age;
		break;
	case 3:
		cout << "��������Ҫ���ĵ�������Ա����:" << endl;
		getline(cin, strength);
		break;
	case 4:
		cout << "��������Ҫ���ĵ���н(����Ϊ��λ):" << endl;
		cin >> money;
		break;
	}
};

void GovernmentP::getmessagefromfile(fstream &F) {
	string m, mes;
	stack<char> s;
	int i = 0; //�½Ǳ�
	int point = 0;  //���
	int count = 1; //��¼�ǵڼ�����Ϣ
	while (count != 5) {
		getline(F, m);
		while (m[i]) {
			if (m[i] == ':') point = 1, i++;
			if (count == 3) {
				getline(F, m);
				break;
			}
			else if (point == 1 && (count == 2 || count == 4)) {
				s.push(m[i]);
			}
			else if (point == 1) {
				mes += m[i];
			}
			i++;
		}
		switch (count) {
		case 1:
			name = mes;
			break;
		case 2:
			age = changenum(s);
			while (!s.empty()) s.pop();
			break;
		case 3:
			strength = mes;
			break;
		case 4:
			money = changenum(s);
			break;
		}
		count++; //���������һ
		point = 0; //��־����
		i = 0;
	}
}

static list<GovernmentP>::iterator Git;

SportsP::SportsP() {};

void SportsP::getmessagefromfile(fstream &F) {
	string m, mes;
	stack<char> s;
	int i = 0; //�½Ǳ�
	int point = 0;  //���
	int count = 1; //��¼�ǵڼ�����Ϣ
	while (count != 9) {
		getline(F, m);
		while (m[i]) {
			if (m[i] == ':') point = 1, i++;
			if (count == 3) {
				getline(F, mes);
				break;
			}
			else if (point == 1 && (count == 2 || count == 4 || count == 5 || count == 6 || count == 7)) {
				s.push(m[i]);
			}
			else if (point == 1) {
				mes += m[i];
			}
			i++;
		}
		switch (count) {
		case 1:
			name = mes;
			break;
		case 2:
			age = changenum(s);
			while (!s.empty()) s.pop();
			break;
		case 3:
			strength = mes;
			break;
		case 4:
			money = changenum(s);
			break;
		case 5:
			Transferfee = changenum(s);
			break;
		case 6:
			kick = changenum(s);
			break;
		case 7:
			experience = changenum(s);
			break;
		case 8:
			club = mes;
		}
		count++; //���������һ
		point = 0; //��־����
		while (!s.empty()) s.pop();
		mes.clear();
		i = 0;
	}
}

void SportsP::writemessage() {
	cout << "��������Ա������:" << endl;
	getline(cin, name);
	cout << "��������Ա������:" << endl;
	cin >> age;
	getchar();
	cout << "��������Ա������:" << endl;
	getline(cin, strength);
	cout << "��������Ա����н(����Ϊ��λ):" << endl;
	cin >> money;
	cout << "��������Ա��ת���(����Ϊ��λ):" << endl;
	cin >> Transferfee;
	cout << "��������Ա�Ľ�������(�Ը�Ϊ��λ):" << endl;
	cin >> kick;
	cout << "��������Ա�ķ�������(����Ϊ��λ):" << endl;
	cin >> experience;
	cout << "��������Ա�����ľ��ֲ�:" << endl;
	cin >> club;
	getchar();
}

void SportsP::readmessage() {
	cout << "��Ա������:" << name << endl;
	cout << "��Ա������:" << age << endl;
	cout << "��Ա������:\n" << strength << endl;
	cout << "��Ա����н(����Ϊ��λ):" << money << endl;
	cout << "��Ա��ת���(����Ϊ��λ):" << Transferfee << endl;
	cout << "��Ա�Ľ�������(�Ը�Ϊ��λ):" << kick << endl;
	cout << "��Ա�ķ�������(����Ϊ��λ):" << experience << endl;
	cout << "��Ա�����ľ��ֲ�:" << club << endl;
	cout << endl;
}

void SportsP::changemessage(int a) {
	switch (a) {
	case 1:
		cout << "������Ҫ���ĵ�����:" << endl;
		getline(cin, name);
		break;
	case 2:
		cout << "������Ҫ���ĵ�����:" << endl;
		cin >> age;
		break;
	case 3:
		cout << "��������Ҫ���ĵ���Ա����:" << endl;
		getline(cin, strength);
		break;
	case 4:
		cout << "��������Ҫ���ĵ���н(����Ϊ��λ):" << endl;
		cin >> money;
		break;
	case 5:
		cout << "��������Ҫ���ĵ���Ա��ת���(����Ϊ��λ):" << endl;
		cin >> Transferfee;
		break;
	case 6:
		cout << "��������Ҫ���ĵ���Ա�Ľ�������(�Ը�Ϊ��λ):" << endl;
		cin >> kick;
		break;
	case 7:
		cout << "������Ҫ���ĵ���Ա�ķ�������(����Ϊ��λ):" << endl;
		cin >> experience;
		break;
	case 8:
		cout << "������Ҫ���ĵ���Ա���������ֲ�:" << endl;
		cin >> club;
		break;
	}
}

Club::Club() {
	GHUM = 0;
	SHUM = 0;
};

void Club::writename() {
	getline(cin, Cname);
}

string Club::putname() {
	return Cname;
}


static list<SportsP>::iterator Sit;
static list<Club>::iterator Cit;  //���ڵ���
static GovernmentP G;
static SportsP S;


int Club::deleteP(string l, int choose) {
	int flag = 1;
	SportsP a;
	GovernmentP b;
	if (choose) {
		a = (*Cit).lis2.back();
		for (Sit = (*Cit).lis2.begin(); Sit != (*Cit).lis2.end(); Sit++) {
			S = *Sit;
			if (l == (S.name)) {
				if (l == a.name) {  //�ж��Ƿ�Ϊ���һ���ַ�
					(*Cit).lis2.pop_back();
					flag = 0;
					break;
				}
				else {
					Sit = (*Cit).lis2.erase(Sit);   //��������ͣ���ڱ�ɾ��Ԫ�ص���һ��λ�ã���ֱ�ӽ��в������ 
				}
				flag = 0;
				break;
			}
		}
	}
	else {
		b = (*Cit).lis1.back();
		for (Git = (*Cit).lis1.begin(); Git != (*Cit).lis1.end(); ) {
			G = *Git;
			if (l == (G.name)) {
				if (l == b.name) {
					(*Cit).lis1.pop_back();//�ж��Ƿ�Ϊ���һ���ַ�
					flag = 0;
				}
				else {
					Git = (*Cit).lis1.erase(Git);   //��������ͣ���ڱ�ɾ��Ԫ�ص���һ��λ�ã���ֱ�ӽ��в������ 
				}
				flag = 0;
				break;
			}
			Git++;
		}
	}
	if (flag) cout << "û���ҵ�����ɾ������Ļ��׵���\n";
	else cout << "�����ɹ�\n";
	return flag;
}

void Club::readout() {  //�����ڴ�
	fstream File;
	string Str;
	int a = 1;
	Str = Cname + "_G.txt";
	File.open(Str.c_str(), ios::in);
	if (!File)
	{
		cout << "fail to open the file" << endl;
		a = 0;//�����׳��쳣��
	}
	while (File.peek() != EOF) {
		if (a == 0)break;
		GovernmentP gtemp;
		gtemp.getmessagefromfile(File);
		lis1.push_back(gtemp);
	}
	File.close();
	Str.clear();
	Str = Cname + "_S.txt";
	File.open(Str.c_str(), ios::in);
	if (!File)
	{
		cout << "fail to open the file" << endl;
		a = 0;//�����׳��쳣��
	}
	while (File.peek() != EOF) {
		SportsP stemp;
		stemp.getmessagefromfile(File);
		lis2.push_back(stemp);
	}
	File.close();
}

void Club::writein(int choose) {  //д���ļ�
	fstream File;
	string Str;
	int a = 1, count = 1;
	if (choose) {
		Str = Cname + "_S.txt";
		File.open(Str.c_str(), ios::out);
		if (!File)
		{
			cout << "fail to open the file" << endl;
			a = 0;//�����׳��쳣��
		}
		for (Sit = lis2.begin(); Sit != lis2.end(); Sit++) {
			if (a == 0) break;
			S = *Sit;
			while (count != 9) {
				switch (count) {
				case 1:
					File << "name:" << S.name << endl;
					break;
				case 2:
					File << "age:" << S.age << endl;
					break;
				case 3:
					File << "strength:" << endl;
					File << S.getstrength() << endl;
					break;
				case 4:
					File << "money:" << S.getmessage(count - 3) << endl; //ת�������ƥ��
					break;
				case 5:
					File << "Transferfee:" << S.getmessage(count - 3) << endl;
					break;
				case 6:
					File << "kick:" << S.getmessage(count - 3) << endl;
					break;
				case 7:
					File << "experience:" << S.getmessage(count - 3) << endl;
					break;
				case 8:
					File << "club:" << S.getclub() << endl;
				}
				count++;
			}
			count = 0;
		}
	}
	else {
		Str = Cname + "_G.txt";
		File.open(Str.c_str(), ios::out);
		if (!File)
		{
			cout << "fail to open the file" << endl;
			a = 0;//�����׳��쳣��
		}
		for (Git = lis1.begin(); Git != lis1.end(); Git++) {
			if (a == 0) break;
			G = *Git;
			while (count != 4) {
				switch (count) {
				case 1:
					File << "name:" << G.name << endl;
					break;
				case 2:
					File << "age:" << G.age << endl;
					break;
				case 3:
					File << "strength:" << endl;
					File << G.getstrength() << endl;
					break;
				}
				count++;
			}
			count = 0;
		}
	}
	File.close();
}

static list<Club> lis;  //�������ֲ�����

class League {
public:
	League();
	int run();
	void Creadout();
	void Cwritein();
	void deletefile(string filename);
	~League() {};
};

League::League() {
}

void League::Creadout() {  //�����ڴ�
	string n;
	fstream F;
	stack<char> st; // ��������ת��
	Club ctemp;  //����д��
	int i = 0, A = 1, count = 0, a = 0;
	F.open("Clublist.txt", ios::in);
	if (!F)
	{
		cout << "fail to open the file" << endl;
		A = 0;//�����׳��쳣��
	}
	while (F.peek() != EOF) {
		if (A == 0) break;
		int  i = 0, flag = 0;
		getline(F, n);
		while (n[i]) {
			switch (count) {
			case 0:
				ctemp.getname(n);
				flag = 1;
				break;
			case 1:
				while (n[i]) {
					if (n[i] == ':') flag = 1, i++;
					if (flag) {
						st.push(n[i]);
					}
					i++;
				}
				a = changenum(st);
				ctemp.GNUM(a);
				while (!st.empty()) st.pop();
				break;
			case 2:
				while (n[i]) {
					if (n[i] == ':') flag = 1, i++;
					if (flag) {
						st.push(n[i]);
					}
					i++;
				}
				a = changenum(st);
				ctemp.SNUM(a);
				while (!st.empty()) st.pop();
				break;
			}
			if (flag) break;
		}
		if (count == 2) {
			ctemp.readout();
			lis.push_back(ctemp);
			ctemp.lis1.clear();
			ctemp.lis2.clear();
			count = 0;
		}
		else count++;
	}
	F.close();
}

void League::Cwritein() {   //д���ļ�
	fstream F;
	Club Ctemp;
	int a = 1;
	F.open("Clublist.txt", ios::out);
	if (!F)
	{
		cout << "fail to open the file" << endl;
		a = 0;//�����׳��쳣��
	}
	int count = 1;
	for (Cit = lis.begin(); Cit != lis.end(); Cit++) {
		if (a == 0)break;
		Ctemp = *Cit;
		while (count != 4) {
			switch (count) {
			case 1:
				F << Ctemp.putname() << endl;
				break;
			case 2:
				F << "GHUM:" << Ctemp.getGnum() << endl;
				break;
			case 3:
				F << "SHUM:" << Ctemp.getSnum() << endl;
				break;
			}
			count++;
		}
		count = 0;
	}
	F.close();
}

int League::run() {
	WSADATA wsaData;
	SOCKET sockClient;//�ͻ���Socket
	SOCKADDR_IN addrServer;//����˵�ַ
	WSAStartup(MAKEWORD(1, 1), &wsaData);
	//�½��ͻ���socket
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	//����Ҫ���ӵķ���˵�ַ

	addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//Ŀ��IP(127.0.0.1�ǻ��͵�ַ)
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);//���Ӷ˿�6000
									  //���ӵ������
	connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	char message[30] = {0};
	char receive[30] = {0};

	fstream file;
	Club C, c;  //���ڳ�ʼд�룬�����жϸ�ֵ
	GovernmentP Gtemp;  //���ڵ�����ֵ  
	SportsP Stemp;
	Club Ctemp;
	list<Club>::iterator cit; //���ڵ�����ֵ
	string n, N; //��ɾ������������ֲ� 
	string trem; //����Ҫ��
	string getl,fileS,fileG,NfileS,NfileG; //���ڽ��ܷ��Ͷ˷���������ת��
	int choose, Choose, option, fileNY , count = 1 , num; //����Ա����������Ա�������Ծ��ֲ����в������ǶԾ��ֲ��ڲ����в�����ʲô�������ļ�����,�����ļ�,�ƽ�������ת�� 
	int flag; //���ڸ��ֱ�ʶ 
	int gai;//����ĵ�ѡ��
	int Transfer_fee; //�ύ��ת��� 
	int  a;// ���ѡ��
	cout << "����֮ǰ�Ƿ��ù��˳���(1.�ù� 0.û�ù�):";
	cin >> fileNY;
	getchar();
	while (1) {
		if (fileNY == 1) {    //���ļ����г�ʼ��
			Creadout();
			cout << "��ʼ�����" << endl;
			fileNY = 0; //��ʼ�����
		}else {
				flag = 1;
				for (;;) {
					cout << "��������(1.�Ծ��ֲ����в��� 0.�Ծ��ֲ��ڲ����в���):";
					cin >> Choose;
					getchar();
					if (Choose == 1 || Choose == 0) break;
					else {
						cout << "���������������" << endl;
						cin.clear();    //�˴���cin.clear()����־��λ
						cin.ignore();   //ȡ�߸ղ����е��ַ�
					}
				}
				if (Choose) {
					Allist();
					for (;;) {
						cout << "����������еĲ���:";
						cin >> option;
						getchar();
						if (option == 1 || option == 2 || option == 3 || option == 4 || option == 5 || option == 6 || option == 7) break;
						else {
							cout << "���������������" << endl;
							cin.clear();    //�˴���cin.clear()����־��λ
							cin.ignore();   //ȡ�߸ղ����е��ַ�
						}
					}
					switch (option) {
					case 1:  //��
						cout << "����������ӵľ��ֲ�����:" << endl;
						C.writename();
						for (Cit = lis.begin(); Cit != lis.end(); Cit++) {
							Ctemp = *Cit;
							if (C.putname() == Ctemp.putname()) {
								cout << "�þ��ֲ��Ѿ�����������\n";
								C = *Cit;
								flag = 0;
								break;
							}
						}
						if (flag) {
							lis.push_back(C);
							fileS = C.putname() + "_S.txt";
							file.open(fileS.c_str(), ios::out); //fstream ֻ����ֻ��(out)������²Żᴴ�����ļ�
							file.close();
							fileG = C.putname() + "_G.txt";
							file.open(fileG.c_str(), ios::out);
							file.close();
							Cwritein();
						}
						break;
					case 2:  //ɾ
						cout << "��������ɾ���ľ��ֲ�����:" << endl;
						getline(cin, n);
						c = lis.back();
						for (Cit = lis.begin(); Cit != lis.end(); ) {
							Ctemp = *Cit;
							if (n == Ctemp.putname()) {
								fileS = Ctemp.putname() + "_S.txt";
								fileG = Ctemp.putname() + "_G.txt";
								remove(fileS.c_str());
								remove(fileG.c_str());
								Cwritein();  //ˢ��Clublist
								if (n == c.putname()) {
									lis.pop_back();
									flag = 0;
								}
								else {
									Cit = lis.erase(Cit);   //��������ͣ���ڱ�ɾ��Ԫ�ص���һ��λ�ã���ֱ�ӽ��в������ 
								}
								flag = 0;
								break;
							}
							Cit++;
						}
						if (flag) cout << "û���ҵ�����ɾ���ľ��ֲ�\n";
						break;
					case 3:  //��
						cout << "����������ľ��ֲ���Ϣ������:" << endl;
						getline(cin, n);
						for (Cit = lis.begin(); Cit != lis.end(); ) {
							Ctemp = *Cit;
							fileS = Ctemp.putname() + "_S.txt";
							fileG = Ctemp.putname() + "_G.txt";
							if (n == Ctemp.putname()) {
								flag = 0;
								cout << "����������ĵ�����" << endl;
								(*Cit).writename();
								cout << "���ĳɹ�!" << endl;
								NfileS = (*Cit).putname() + "_S.txt";
								NfileG = (*Cit).putname() + "_G.txt";
								rename(fileS.c_str(), NfileS.c_str());
								rename(fileG.c_str(), NfileG.c_str());
								Cwritein(); //ˢ��Clublist
								break;
							}
							Cit++;
						}
						if (flag) cout << "û���ҵ�������ĵľ��ֲ�\n";
						break;
					case 4:   //��
						for (Cit = lis.begin(); Cit != lis.end(); Cit++) {
							Ctemp = *Cit;
							if (n == (Ctemp.putname())) {
								cout << "�þ��ֲ��ڴ�������" << endl;
							}
							else cout << "�þ��ֲ����ڴ�������" << endl;
						}
						break;
					case 6: //���
						for (Cit = lis.begin(); Cit != lis.end(); Cit++) {
							Ctemp = *Cit;
							Ctemp.readmessage();
							cout << endl;
						}
						break;
					case 7:
						//�ر�socket
						closesocket(sockClient);
						WSACleanup();
						return 0;
						break;
					}
				}
				else {
					while (flag) {
						cout << "����������в����ľ��ֲ�����:" << endl;
						getline(cin, n);
						for (Cit = lis.begin(); Cit != lis.end(); Cit++) {
							Ctemp = *Cit;  //CitΪʵ��Ҫ������ֵ
							if (n == (Ctemp.putname())) {
								C = Ctemp;   //���ں�����������
								flag = 0;
								break;
							}
						}
						if (flag) cout << "�þ��ֲ����ڴ�������" << endl;
					}
					flag = 1;
					Allist();
					for (;;) {
						cout << "����������еĲ���:";
						cin >> option;
						getchar();
						if (option == 1 || option == 2 || option == 3 || option == 4 || option == 5 || option == 6 || option == 7) break;
						else {
							cout << "���������������" << endl;
							cin.clear();    //�˴���cin.clear()����־��λ
							cin.ignore();   //ȡ�߸ղ����е��ַ�
						}
					}
					for (;;) {
						cout << "����������еĲ�������(0:������Ա 1:��Ա):";
						cin >> choose;
						getchar();
						if (choose == 1 || choose == 0) break;
						else {
							cout << "���������������" << endl;
							cin.clear();    //�˴���cin.clear()����־��λ
							cin.ignore();   //ȡ�߸ղ����е��ַ�
						}
					}
					switch (option) {
					case 1:  //�� 
						if (choose) {
							S.writemessage();
							(*Cit).lis2.push_back(S);
							(*Cit).addS();
							(*Cit).writein(choose);
						}
						else {
							G.writemessage();
							(*Cit).lis1.push_back(G);
							(*Cit).addG();
							(*Cit).writein(choose);
						}
						Cwritein();
						break;
					case 2:  //ɾ 
						cout << "��������ɾ��������:";
						getline(cin, n);
						if (choose) {
							flag = (*Cit).deleteP(n, choose);
							if (flag == 0) {
								(*Cit).deS();
								(*Cit).writein(choose);
							}
						}
						else {
							flag = (*Cit).deleteP(n, choose);
							if (flag == 0) {
								(*Cit).deG();
								(*Cit).writein(choose);
							}
						}
						Cwritein();
						break;
					case 3:  //�� 
						if (choose) {
							cout << "�������������Ա��Ϣ������:" << endl;
							getline(cin, n);
							for (Sit = (*Cit).lis2.begin(); Sit != (*Cit).lis2.end(); ) {
								S = *Sit;
								if (n == (S.name)) {
									flag = 0;
									break;
								}
							}
							if (flag == 0) {
								cout << "����������ĵ���Ŀ(1.����2.����3.����4.��н5.ת���6.��������7.��������8.�������ֲ�)" << endl;
								cin >> gai;
								getchar();
								(*Sit).changemessage(gai);
								cout << "���ĳɹ�!" << endl;
								(*Cit).writein(choose);
							}
							else cout << "û���ҵ�����ɾ������Ļ��׵���\n";
						}
						else {
							cout << "��������Ҫ����������Ա������:" << endl;
							getline(cin, n);
							for (Git = (*Cit).lis1.begin(); Git != (*Cit).lis1.end(); ) {
								G = *Git;
								if (n == (G.name)) {
									flag = 0;
									break;
								}
							}
							if (flag == 0) {
								cout << "��������ĵ���Ŀ(1.����2.����3.����4.��н)" << endl;
								cin >> gai;
								getchar();
								(*Git).changemessage(gai);
								cout << "���ĳɹ�!" << endl;
								(*Cit).writein(choose);
							}
							else "û���ҵ�����ɾ������Ļ��׵���\n";
						}
						break;
					case 4: //��
						message[0] = '4';
						send(sockClient, message, strlen(message) + 1, 0);
						memset(message, 0, sizeof(message));
						Searchlist();
						cout << "��������Ҫ����������(��д��ʽ��ʹ���ĵ�������ϸ˵��):" << endl;
						cin >> trem;
						strcpy(message, trem.c_str());
						send(sockClient, message, sizeof(message) + 1, 0);
						memset(message, 0, sizeof(message));
						while (1) {
							recv(sockClient, receive, sizeof(receive) + 1, 0);
							getl = receive;
							memset(receive, 0, sizeof(receive));
							if (getl == "send is over") break;
							else {
								switch (count) {
								case 1:   
									cout << "��Ա������:" << getl << endl;
									break;
								case 2: 
									cout << "��Ա������:" << getl << endl;
									break;
								case 3: 
									cout << "��Ա������:\n" << getl << endl;
									break;
								case 4: 
									cout << "��Ա����н(����Ϊ��λ):" << getl << endl;
									break;
								case 5:
									cout << "��Ա��ת���(����Ϊ��λ):" << getl << endl;
									break;
								case 6:
									cout << "��Ա�Ľ�������(�Ը�Ϊ��λ):" << getl << endl;
									break;
								case 7:
									cout << "��Ա�ķ�������(����Ϊ��λ):" << getl << endl;
									break;
								case 8: 
									cout << "��Ա�����ľ��ֲ�:" << getl << endl;
									cout << endl;
									break;
								}
								count++;
								if (count == 9) count = 1;
							}
						}
						count = 1;
						for (Cit = lis.begin(); Cit != lis.end(); Cit++) {
							C = *Cit;
							HUM = C.getSnum();
							change_experience(trem);
							match(C.lis2);
						}
						break;
					case 5: //����
						message[0] = '5';
						send(sockClient, message, strlen(message) + 1, 0);
						memset(message, 0, sizeof(message));

						cout << "��������Ҫ�ӷ����������ľ��ֲ���:" << endl;
						getline(cin, N);
						strcpy(message, N.c_str());
						send(sockClient, message, sizeof(message) + 1, 0);
						memset(message, 0, sizeof(message));

						cout << "��������Ҫ��������Ա����:" << endl;
						getline(cin, n);
						strcpy(message, n.c_str());
						send(sockClient, message, sizeof(message) + 1, 0);
						memset(message, 0, sizeof(message));

						cout << "��������Ҫ�����ķ��ü۸�(����Ϊ��λ):" << endl;
						cin >> Transfer_fee;
						itoa(Transfer_fee, message, 10);
						send(sockClient, message, sizeof(message) + 1, 0);
						memset(message, 0,sizeof(message));

						while (1) {
							recv(sockClient, receive, sizeof(receive) + 1, 0);
							getl = receive;
							memset(receive, 0, sizeof(receive));
							if (getl == "fall to find club") {
								cout << "δ�ҵ�������н����ľ��ֲ�" << endl;
								break;
							}
							else if (getl == "fall to exchange") {
								cout << "������Ľ����ϸ���Ա��Ҫ������ת��ʧ��" << endl;
								break;
							}
							else {
								switch (count) {
								case 1: //name
									Stemp.name = getl;
									break;
								case 2:
									Stemp.age = atoi(getl.c_str());
									break;
								case 3:
									Stemp.getstrengthfromsever(getl);
									break;
								case 4:
								case 5:
								case 6:
								case 7:
									num = atoi(getl.c_str());
									Stemp.getmessageformsever(count , num);
									break;
								case 8:
									Stemp.putclub(getl);
									break;
								}
								count++;
								if (count == 9) break;
							}
						}
						(*Cit).lis2.push_back(Stemp);
						cout << "ת��ɹ�!" << endl;
						(*Cit).addS();
						(*Cit).writein(1);
						Cwritein();
						break;
					case 6: //��� 
						while (1) {
							cout << "��������Ҫ���������(1ȫ�����0.ѡ�����):";
							cin >> a;
							if (a == 1 || a == 0) break;
							else {
								cout << "���������������" << endl;
								cin.clear();    //�˴���cin.clear()����־��λ
								cin.ignore();   //ȡ�߸ղ����е��ַ�
							}
						}
						if (choose) {
							if (a) {
								for (Sit = C.lis2.begin(); Sit != C.lis2.end(); Sit++) {
									Stemp = *Sit;
									Stemp.readmessage();
									cout << endl;
								}
							}
							else {
								cout << "��������Ҫ�������Ա����:" << endl;
								cin >> n;
								for (Sit = C.lis2.begin(); Sit != C.lis2.end(); Sit++) {
									Stemp = *Sit;
									if (n == (Stemp.name)) {
										Stemp.readmessage();
										flag = 0;
										cout << endl;
										break;
									}
								}
								if (flag)cout << "û���ҵ������������\n";
							}
						}
						else {
							if (a) {
								for (Git = C.lis1.begin(); Git != C.lis1.end(); Git++) {
									Gtemp = *Git;
									Gtemp.readmessage();
									cout << endl;
								}
							}
							else {
								cout << "��������Ҫ�����������Ա������:" << endl;
								cin >> n;
								for (Git = C.lis1.begin(); Git != C.lis1.end(); Git++) {
									Gtemp = *Git;
									if (n == Gtemp.name) {
										Gtemp.readmessage();
										flag = 0;
										cout << endl;
										break;
									}
								}
								if (flag)cout << "û���ҵ������������\n";
							}
						}
						break;
					case 7: //�˳� 
							//�ر�socket
						closesocket(sockClient);
						WSACleanup();
						return 0;
						break;
					}
				}
			}
	}
	return 0;
}

void League::deletefile(string filename) {
	if (remove(filename.c_str()) == 0)
	{
		cout << "ɾ���ɹ�" << endl;
	}
	else
	{
		cout << "ɾ��ʧ��" << endl;
	}
}

int main(void)
{
	int end;
	League FIFA;
	end = FIFA.run();
	return end;

	//���������̣�ֱ���пͻ�����������Ϊֹ
	/*sockClient = accept(sockServer, (SOCKADDR*)&addrClient, &len);
	//���ղ���ӡ�ͻ�������
	recv(sockClient, recvBuf , 100, 0);
	cout<<recvBuf;*/


}

void Allist() {
	cout << "\t\t* * * * * * * * *" << endl;
	cout << "\t\t*1��\t\t*\n\t\t*2ɾ\t\t*\n\t\t*3��\t\t*\n\t\t*4��(�ͻ������)*\n\t\t*5����(�ͻ������)*\n\t\t*6���\t\t*\n\t\t*7�˳�ϵͳ\t*" << endl;
	cout << "\t\t* * * * * * * * *" << endl;
}

void Searchlist() {
	cout << "\t\t* * * * * * * * * * * * *" << endl;
	cout << "\t\t*����:name(����ʹ��)\t*\n\t\t*����:age\t\t*\n\t\t*��н:money\t\t*\n\t\t*ת���:transferfee\t*\n\t\t*��������:kick\t\t*\n\t\t*��������:experience\t*\n\t\t*���ֲ�:club\t\t*\n";
	cout << "\t\t* * * * * * * * * * * * *" << endl;
}

int type(string a) {
	if (a == "age") return 7;
	if (a == "money") return 1;
	if (a == "transferfee") return 2;
	if (a == "kick") return 3;
	if (a == "experience") return 4;
	if (a == "strength") return 5;
	if (a == "club") return 6;
	if (a == "name") return 8;
	return 0;
}

int changenum(stack<char> s) {
	int a, sum = 0, b = 1;
	while (!s.empty()) {
		a = s.top() - 48;
		sum += a*b;
		b *= 10;
		s.pop();
	}
	return sum;
}

int power(char b) {  //��Ӧ��������Ȩ�� 
	switch (b) {
	case '>':
	case '<':
	case '=':
		return 3;
		break;
	case '&':
	case '|':
		return 2;
		break;
	case '!':
	case '~':
		return 4;
		break;
	case '(':
		return 0;
	}
	return 0;
}

void Fuzzysearch(string term, SportsP temp) {
	size_t found = temp.name.find(term);
	if (found != string::npos) temp.readmessage();
}

void change_experience(string term) {  //��׺���ʽת������ 
	int i = 0;
	stack<char> s;
	NUM = 0;
	while (term[NUM]) {
		if (term[NUM] != '@') {
			if ((term[NUM] >= 'a'&&term[NUM] <= 'z') || (term[NUM] >= 'A'&&term[NUM] <= 'Z')) {
				behind[i++] = term[NUM];
			}
			else {
				if (term[NUM] >= '0'&&term[NUM] <= '9')behind[i++] = term[NUM];
				else {
					if (s.empty() && term[NUM] == term[NUM + 1]) {
						s.push(term[NUM]);
						NUM++;
					}
					else if (s.empty()) {
						s.push(term[NUM]);
					}
					else {
						if (term[NUM] == '(') {
							s.push(term[NUM]);
							if (term[NUM] == term[NUM + 1]) NUM++;
						}
						else if (term[NUM] == ')') {
							while (s.top() != '(') {
								behind[i++] = s.top();
								s.pop();
							}
							s.pop(); //����( 
						}
						else if (power(term[NUM])) {
							while (power(term[NUM]) <= power(s.top())) {
								behind[i++] = s.top();
								s.pop();
								if (s.empty()) break;
							}
							s.push(term[NUM]);
							if (term[NUM] == term[NUM + 1]) NUM++;
						}
					}
				}
			}
		}
		NUM++;
	}
	NUM = 0;  //��λ 
	while (!s.empty()) {
		behind[i++] = s.top();
		s.pop();
	}
}

void match(list<SportsP> lis2) {  //ƥ�� 
	SportsP Stemp;
	string end;//��������������ս��
	string st, St; // ���ڴ洢word ,���ڴ洢�ؼ���(club , ģ���ַ�)
	char op = '\0';  //���ڶ�ȡ�ַ�
	int num = 0, N = 0; //���ڴ����� ,���ֵĵ���
	stack<char> s; //���ڴ����� 
	int ex = 0;
	int count = 1;  //1.��������,0.ģ������
	list<SportsP>::iterator Sit;
	for (Sit = lis2.begin(); Sit != lis2.end(); Sit++) {
		Stemp = *Sit;
		while (behind[NUM]) {
			op = behind[NUM];
			if ((op >= 'a'&&op <= 'z') || (op >= 'A'&&op <= 'Z')) {
				if (st == "club") {
					St += op;
				}
				else st += op;
				NUM++;
			}
			else if (op >= '0'&&op <= '9') {
				s.push(op);
				NUM++;
			}
			else {
				switch (op) {
					//case ' ': 	
					//break;
				case '!': //!
					end += '!';
					break;
				case '&': //&
					end += '&';
					break;
				case '|': //|
					end += '|';
					break;
				case '>': //>
					num = changenum(s);
					ex = type(st);
					if (ex == 7) {
						if (Stemp.age > num) end += '1';
						else end += '0';
					}
					else {
						if (Stemp.getmessage(ex) > num) end += '1';
						else end += '0';
					}
					break;
				case '<'://<
					num = changenum(s);
					ex = type(st);
					if (ex == 7) {
						if (Stemp.age < num) end += '1';
						else end += '0';
					}
					else {
						if (Stemp.getmessage(ex) < num) end += '1';
						else end += '0';
					}
					break;
				case '=': //=
					num = changenum(s);
					ex = type(st);
					if (ex == 6) {  //���ֲ�
						if (Stemp.getclub() == St) end += '1';
						else end += '0';
					}
					else {
						if (ex == 7) {
							if (Stemp.age == num) end += '1';
							else end += '0';
						}
						else {
							if (Stemp.getmessage(ex) == num) end += '1';
							else end += '0';
						}
					}
					break;
				case '~':  //ֻ���ڲ����ֵ�ʱ��Ż��дιؼ���
					N = 0;
					while (st[N]) {
						if (St == "name") {
							St.clear();
						}
						else {
							St += st[N];
							N++;
						}
					}
					Fuzzysearch(St, Stemp);
					count = 0;  //��ʱ����ͳһ���
					St.clear();
					break;
				}
				while (!s.empty()) s.pop();
				st.clear();
				St.clear();
				ex = 0;
				NUM++;
			}
		}
		NUM = 0;
		if (count) {
			if (highmatch(end)) Stemp.readmessage();
			end.clear();
		}
	}
}

int highmatch(string end) {
	int i = 0, num1 = 0, num2 = 0, flag = 0;
	char op;
	string result;
	while (1) {
		if (end.length() == 1) return end[0] - 48;
		else {
			switch (end[i]) {
			case '0':
			case '1':
				if ((flag % 2) == 0) num1 = end[i] - 48, flag++;
				else if ((flag % 2) == 1)num2 = end[i] - 48, flag++;
				if (flag > 2)result += end[i - flag + 1];
				i++;
				break;
			case '&':
				num1 = num1*num2;
				op = (num1 + 48);
				result += op;
				i++;
				while (end[i]) {
					result += end[i];
					i++;
				}
				return highmatch(result);
				break;
			case'|':
				num1 = num1 + num2;
				if (num1 == 2) num1 = 1;
				else num1 = num1 % 2;
				op = (num1 + 48);
				result += op;
				i++;
				while (end[i]) {
					result += end[i];
					i++;
				}
				return highmatch(result);
				break;
			}
		}
	}
}


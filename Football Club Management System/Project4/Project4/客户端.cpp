#include<winsock2.h>
#include<iostream>
#include<stdio.h>
#include<string>
#include<stack> 
#include<list>//选用list作为容器
#include<fstream>
#include<stdlib.h>

#pragma comment(lib,"ws2_32.lib")

static int NUM = 0; //用于遍历后缀字符串 
static int HUM = 0; //用于看球员人数 
static char behind[50] = { 0 }; //用于存后缀表达式  

using namespace std;

class People {
public:
	People();
	//People(const People& rhs){};
	string name;  //人最基本的信息 
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

	string getstrength() {  //得到行政人员的能力 
		return strength;
	}

	int getmoney() {
		return money;
	}

	virtual void readmessage() {
		cout << "行政成员的姓名:" << name << endl;
		cout << "行政成员的年龄:" << age << endl;
		cout << "行政成员的能力:\n" << strength << endl;
		cout << "行政成员的年薪(以万为单位):" << money << endl;
	}
	~GovernmentP() {};
private:
	string strength; //能力 
	int money; //年薪
};

class SportsP : public People {
public:
	SportsP();
	//SportsP(const SportsP& rhs){};
	virtual void writemessage();
	virtual void readmessage();
	virtual void changemessage(int a);
	virtual void getmessagefromfile(fstream &F);
	string getstrength() {  //得到球员的能力 5
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
	string strength; //能力 
	int money; //年薪 
	int Transferfee; // 转会费
	int kick; // 进球总数
	int experience; //服役年限 
	string club; //所属俱乐部 
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
	void writein(int choose); //1.球员0.行政人员
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
		cout << "俱乐部名:" << Cname << endl;
		cout << "行政人员的人数:" << GHUM << endl;
		cout << "球员人数:" << SHUM << endl;
	}
	~Club() {};
private:
	string Cname;
	int GHUM, SHUM;
};

void match(list<SportsP> lis);  // 查找函数 
void Fuzzysearch(string term, SportsP temp); //模糊查找
int type(string a); // 用于返回条件代码 
int power(char b); //判断运算符的权重 
void change_experience(string term); //改变成后缀表达式 
int changenum(stack<char> s); //求出相应整数 
void Allist();
int  highmatch(string end);//含或的高级搜索
void Searchlist();

GovernmentP::GovernmentP() {};

void GovernmentP::writemessage() {
	cout << "请输入行政成员的姓名:" << endl;
	getline(cin, name);
	cout << "请输入行政成员的年龄:" << endl;
	cin >> age;
	cout << "请输入行政成员的能力:" << endl;
	getchar();
	getline(cin, strength);
	cout << "请输入行政成员的年薪(以万为单位):" << endl;
	cin >> money;
};

void GovernmentP::changemessage(int a) {
	switch (a) {
	case 1:
		cout << "请输入要更改的名字:" << endl;
		getchar();
		break;
	case 2:
		cout << "请输入要更改的年龄:" << endl;
		cin >> age;
		break;
	case 3:
		cout << "请输入想要更改的行政人员能力:" << endl;
		getline(cin, strength);
		break;
	case 4:
		cout << "请输入想要更改的年薪(以万为单位):" << endl;
		cin >> money;
		break;
	}
};

void GovernmentP::getmessagefromfile(fstream &F) {
	string m, mes;
	stack<char> s;
	int i = 0; //下角标
	int point = 0;  //标记
	int count = 1; //记录是第几个信息
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
		count++; //计数代码加一
		point = 0; //标志归零
		i = 0;
	}
}

static list<GovernmentP>::iterator Git;

SportsP::SportsP() {};

void SportsP::getmessagefromfile(fstream &F) {
	string m, mes;
	stack<char> s;
	int i = 0; //下角标
	int point = 0;  //标记
	int count = 1; //记录是第几个信息
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
		count++; //计数代码加一
		point = 0; //标志归零
		while (!s.empty()) s.pop();
		mes.clear();
		i = 0;
	}
}

void SportsP::writemessage() {
	cout << "请输入球员的姓名:" << endl;
	getline(cin, name);
	cout << "请输入球员的年龄:" << endl;
	cin >> age;
	getchar();
	cout << "请输入球员的能力:" << endl;
	getline(cin, strength);
	cout << "请输入球员的年薪(以万为单位):" << endl;
	cin >> money;
	cout << "请输入球员的转会费(以万为单位):" << endl;
	cin >> Transferfee;
	cout << "请输入球员的进球总数(以个为单位):" << endl;
	cin >> kick;
	cout << "请输入球员的服役年限(以年为单位):" << endl;
	cin >> experience;
	cout << "请输入球员所属的俱乐部:" << endl;
	cin >> club;
	getchar();
}

void SportsP::readmessage() {
	cout << "球员的姓名:" << name << endl;
	cout << "球员的年龄:" << age << endl;
	cout << "球员的能力:\n" << strength << endl;
	cout << "球员的年薪(以万为单位):" << money << endl;
	cout << "球员的转会费(以万为单位):" << Transferfee << endl;
	cout << "球员的进球总数(以个为单位):" << kick << endl;
	cout << "球员的服役年限(以年为单位):" << experience << endl;
	cout << "球员所属的俱乐部:" << club << endl;
	cout << endl;
}

void SportsP::changemessage(int a) {
	switch (a) {
	case 1:
		cout << "请输入要更改的名字:" << endl;
		getline(cin, name);
		break;
	case 2:
		cout << "请输入要更改的年龄:" << endl;
		cin >> age;
		break;
	case 3:
		cout << "请输入想要更改的球员能力:" << endl;
		getline(cin, strength);
		break;
	case 4:
		cout << "请输入想要更改的年薪(以万为单位):" << endl;
		cin >> money;
		break;
	case 5:
		cout << "请输入想要更改的球员的转会费(以万为单位):" << endl;
		cin >> Transferfee;
		break;
	case 6:
		cout << "请输入想要更改的球员的进球总数(以个为单位):" << endl;
		cin >> kick;
		break;
	case 7:
		cout << "输入想要更改的球员的服役年限(以年为单位):" << endl;
		cin >> experience;
		break;
	case 8:
		cout << "输入想要更改的球员的所属俱乐部:" << endl;
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
static list<Club>::iterator Cit;  //用于迭代
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
				if (l == a.name) {  //判断是否为最后一个字符
					(*Cit).lis2.pop_back();
					flag = 0;
					break;
				}
				else {
					Sit = (*Cit).lis2.erase(Sit);   //迭代器会停留在被删除元素的下一个位置，可直接进行插入操作 
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
					(*Cit).lis1.pop_back();//判断是否为最后一个字符
					flag = 0;
				}
				else {
					Git = (*Cit).lis1.erase(Git);   //迭代器会停留在被删除元素的下一个位置，可直接进行插入操作 
				}
				flag = 0;
				break;
			}
			Git++;
		}
	}
	if (flag) cout << "没有找到你想删除或更改或交易的人\n";
	else cout << "操作成功\n";
	return flag;
}

void Club::readout() {  //读入内存
	fstream File;
	string Str;
	int a = 1;
	Str = Cname + "_G.txt";
	File.open(Str.c_str(), ios::in);
	if (!File)
	{
		cout << "fail to open the file" << endl;
		a = 0;//或者抛出异常。
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
		a = 0;//或者抛出异常。
	}
	while (File.peek() != EOF) {
		SportsP stemp;
		stemp.getmessagefromfile(File);
		lis2.push_back(stemp);
	}
	File.close();
}

void Club::writein(int choose) {  //写入文件
	fstream File;
	string Str;
	int a = 1, count = 1;
	if (choose) {
		Str = Cname + "_S.txt";
		File.open(Str.c_str(), ios::out);
		if (!File)
		{
			cout << "fail to open the file" << endl;
			a = 0;//或者抛出异常。
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
					File << "money:" << S.getmessage(count - 3) << endl; //转换需进行匹配
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
			a = 0;//或者抛出异常。
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

static list<Club> lis;  //联赛俱乐部名单

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

void League::Creadout() {  //读入内存
	string n;
	fstream F;
	stack<char> st; // 用于字数转换
	Club ctemp;  //用于写入
	int i = 0, A = 1, count = 0, a = 0;
	F.open("Clublist.txt", ios::in);
	if (!F)
	{
		cout << "fail to open the file" << endl;
		A = 0;//或者抛出异常。
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

void League::Cwritein() {   //写入文件
	fstream F;
	Club Ctemp;
	int a = 1;
	F.open("Clublist.txt", ios::out);
	if (!F)
	{
		cout << "fail to open the file" << endl;
		a = 0;//或者抛出异常。
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
	SOCKET sockClient;//客户端Socket
	SOCKADDR_IN addrServer;//服务端地址
	WSAStartup(MAKEWORD(1, 1), &wsaData);
	//新建客户端socket
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	//定义要连接的服务端地址

	addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//目标IP(127.0.0.1是回送地址)
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);//连接端口6000
									  //连接到服务端
	connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	char message[30] = {0};
	char receive[30] = {0};

	fstream file;
	Club C, c;  //用于初始写入，用于判断赋值
	GovernmentP Gtemp;  //用于迭代赋值  
	SportsP Stemp;
	Club Ctemp;
	list<Club>::iterator cit; //用于迭代赋值
	string n, N; //想删除的人名或俱乐部 
	string trem; //查找要素
	string getl,fileS,fileG,NfileS,NfileG; //用于接受发送端发来的数据转化
	int choose, Choose, option, fileNY , count = 1 , num; //对球员还是行政人员操作，对俱乐部进行操作还是对俱乐部内部进行操作，什么操作，文件操作,接受文件,计接收数，转数 
	int flag; //用于各种标识 
	int gai;//想更改的选项
	int Transfer_fee; //提交的转会费 
	int  a;// 输出选项
	cout << "请问之前是否用过此程序(1.用过 0.没用过):";
	cin >> fileNY;
	getchar();
	while (1) {
		if (fileNY == 1) {    //用文件进行初始化
			Creadout();
			cout << "初始化完成" << endl;
			fileNY = 0; //初始化完成
		}else {
				flag = 1;
				for (;;) {
					cout << "请问是想(1.对俱乐部进行操作 0.对俱乐部内部进行操作):";
					cin >> Choose;
					getchar();
					if (Choose == 1 || Choose == 0) break;
					else {
						cout << "输入错误，请重输入" << endl;
						cin.clear();    //此处用cin.clear()流标志复位
						cin.ignore();   //取走刚才流中的字符
					}
				}
				if (Choose) {
					Allist();
					for (;;) {
						cout << "请输入想进行的操作:";
						cin >> option;
						getchar();
						if (option == 1 || option == 2 || option == 3 || option == 4 || option == 5 || option == 6 || option == 7) break;
						else {
							cout << "输入错误，请重输入" << endl;
							cin.clear();    //此处用cin.clear()流标志复位
							cin.ignore();   //取走刚才流中的字符
						}
					}
					switch (option) {
					case 1:  //增
						cout << "请输入想添加的俱乐部名字:" << endl;
						C.writename();
						for (Cit = lis.begin(); Cit != lis.end(); Cit++) {
							Ctemp = *Cit;
							if (C.putname() == Ctemp.putname()) {
								cout << "该俱乐部已经在联盟中了\n";
								C = *Cit;
								flag = 0;
								break;
							}
						}
						if (flag) {
							lis.push_back(C);
							fileS = C.putname() + "_S.txt";
							file.open(fileS.c_str(), ios::out); //fstream 只有在只读(out)的情况下才会创建空文件
							file.close();
							fileG = C.putname() + "_G.txt";
							file.open(fileG.c_str(), ios::out);
							file.close();
							Cwritein();
						}
						break;
					case 2:  //删
						cout << "请输入想删除的俱乐部名字:" << endl;
						getline(cin, n);
						c = lis.back();
						for (Cit = lis.begin(); Cit != lis.end(); ) {
							Ctemp = *Cit;
							if (n == Ctemp.putname()) {
								fileS = Ctemp.putname() + "_S.txt";
								fileG = Ctemp.putname() + "_G.txt";
								remove(fileS.c_str());
								remove(fileG.c_str());
								Cwritein();  //刷新Clublist
								if (n == c.putname()) {
									lis.pop_back();
									flag = 0;
								}
								else {
									Cit = lis.erase(Cit);   //迭代器会停留在被删除元素的下一个位置，可直接进行插入操作 
								}
								flag = 0;
								break;
							}
							Cit++;
						}
						if (flag) cout << "没有找到你想删除的俱乐部\n";
						break;
					case 3:  //改
						cout << "请输入想更改俱乐部信息的名字:" << endl;
						getline(cin, n);
						for (Cit = lis.begin(); Cit != lis.end(); ) {
							Ctemp = *Cit;
							fileS = Ctemp.putname() + "_S.txt";
							fileG = Ctemp.putname() + "_G.txt";
							if (n == Ctemp.putname()) {
								flag = 0;
								cout << "请输入想更改的名字" << endl;
								(*Cit).writename();
								cout << "更改成功!" << endl;
								NfileS = (*Cit).putname() + "_S.txt";
								NfileG = (*Cit).putname() + "_G.txt";
								rename(fileS.c_str(), NfileS.c_str());
								rename(fileG.c_str(), NfileG.c_str());
								Cwritein(); //刷新Clublist
								break;
							}
							Cit++;
						}
						if (flag) cout << "没有找到你想更改的俱乐部\n";
						break;
					case 4:   //查
						for (Cit = lis.begin(); Cit != lis.end(); Cit++) {
							Ctemp = *Cit;
							if (n == (Ctemp.putname())) {
								cout << "该俱乐部在此联赛中" << endl;
							}
							else cout << "该俱乐部不在此联赛中" << endl;
						}
						break;
					case 6: //输出
						for (Cit = lis.begin(); Cit != lis.end(); Cit++) {
							Ctemp = *Cit;
							Ctemp.readmessage();
							cout << endl;
						}
						break;
					case 7:
						//关闭socket
						closesocket(sockClient);
						WSACleanup();
						return 0;
						break;
					}
				}
				else {
					while (flag) {
						cout << "请输入想进行操作的俱乐部名字:" << endl;
						getline(cin, n);
						for (Cit = lis.begin(); Cit != lis.end(); Cit++) {
							Ctemp = *Cit;  //Cit为实际要操作的值
							if (n == (Ctemp.putname())) {
								C = Ctemp;   //用于后面做参数用
								flag = 0;
								break;
							}
						}
						if (flag) cout << "该俱乐部不在此联赛中" << endl;
					}
					flag = 1;
					Allist();
					for (;;) {
						cout << "请输入想进行的操作:";
						cin >> option;
						getchar();
						if (option == 1 || option == 2 || option == 3 || option == 4 || option == 5 || option == 6 || option == 7) break;
						else {
							cout << "输入错误，请重输入" << endl;
							cin.clear();    //此处用cin.clear()流标志复位
							cin.ignore();   //取走刚才流中的字符
						}
					}
					for (;;) {
						cout << "请输入想进行的操作对象(0:行政人员 1:球员):";
						cin >> choose;
						getchar();
						if (choose == 1 || choose == 0) break;
						else {
							cout << "输入错误，请重输入" << endl;
							cin.clear();    //此处用cin.clear()流标志复位
							cin.ignore();   //取走刚才流中的字符
						}
					}
					switch (option) {
					case 1:  //增 
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
					case 2:  //删 
						cout << "请输入想删除的人名:";
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
					case 3:  //改 
						if (choose) {
							cout << "请输入想更改球员信息的名字:" << endl;
							getline(cin, n);
							for (Sit = (*Cit).lis2.begin(); Sit != (*Cit).lis2.end(); ) {
								S = *Sit;
								if (n == (S.name)) {
									flag = 0;
									break;
								}
							}
							if (flag == 0) {
								cout << "请输入想更改的项目(1.名字2.年龄3.能力4.年薪5.转会费6.进球总数7.服役年限8.所属俱乐部)" << endl;
								cin >> gai;
								getchar();
								(*Sit).changemessage(gai);
								cout << "更改成功!" << endl;
								(*Cit).writein(choose);
							}
							else cout << "没有找到你想删除或更改或交易的人\n";
						}
						else {
							cout << "请输入想要更改行政人员的名字:" << endl;
							getline(cin, n);
							for (Git = (*Cit).lis1.begin(); Git != (*Cit).lis1.end(); ) {
								G = *Git;
								if (n == (G.name)) {
									flag = 0;
									break;
								}
							}
							if (flag == 0) {
								cout << "输入想更改的项目(1.名字2.年龄3.能力4.年薪)" << endl;
								cin >> gai;
								getchar();
								(*Git).changemessage(gai);
								cout << "更改成功!" << endl;
								(*Cit).writein(choose);
							}
							else "没有找到你想删除或更改或交易的人\n";
						}
						break;
					case 4: //查
						message[0] = '4';
						send(sockClient, message, strlen(message) + 1, 0);
						memset(message, 0, sizeof(message));
						Searchlist();
						cout << "请输入想要的限制条件(书写格式在使用文档中有详细说明):" << endl;
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
									cout << "球员的姓名:" << getl << endl;
									break;
								case 2: 
									cout << "球员的年龄:" << getl << endl;
									break;
								case 3: 
									cout << "球员的能力:\n" << getl << endl;
									break;
								case 4: 
									cout << "球员的年薪(以万为单位):" << getl << endl;
									break;
								case 5:
									cout << "球员的转会费(以万为单位):" << getl << endl;
									break;
								case 6:
									cout << "球员的进球总数(以个为单位):" << getl << endl;
									break;
								case 7:
									cout << "球员的服役年限(以年为单位):" << getl << endl;
									break;
								case 8: 
									cout << "球员所属的俱乐部:" << getl << endl;
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
					case 5: //交换
						message[0] = '5';
						send(sockClient, message, strlen(message) + 1, 0);
						memset(message, 0, sizeof(message));

						cout << "请输入想要从服务器交换的俱乐部名:" << endl;
						getline(cin, N);
						strcpy(message, N.c_str());
						send(sockClient, message, sizeof(message) + 1, 0);
						memset(message, 0, sizeof(message));

						cout << "请输入想要交换的球员姓名:" << endl;
						getline(cin, n);
						strcpy(message, n.c_str());
						send(sockClient, message, sizeof(message) + 1, 0);
						memset(message, 0, sizeof(message));

						cout << "请输入想要交换的费用价格(以万为单位):" << endl;
						cin >> Transfer_fee;
						itoa(Transfer_fee, message, 10);
						send(sockClient, message, sizeof(message) + 1, 0);
						memset(message, 0,sizeof(message));

						while (1) {
							recv(sockClient, receive, sizeof(receive) + 1, 0);
							getl = receive;
							memset(receive, 0, sizeof(receive));
							if (getl == "fall to find club") {
								cout << "未找到你想进行交换的俱乐部" << endl;
								break;
							}
							else if (getl == "fall to exchange") {
								cout << "你提出的金额不符合该球员的要求，所以转会失败" << endl;
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
						cout << "转会成功!" << endl;
						(*Cit).addS();
						(*Cit).writein(1);
						Cwritein();
						break;
					case 6: //输出 
						while (1) {
							cout << "请输入想要输出的类型(1全部输出0.选择输出):";
							cin >> a;
							if (a == 1 || a == 0) break;
							else {
								cout << "输入错误，请重输入" << endl;
								cin.clear();    //此处用cin.clear()流标志复位
								cin.ignore();   //取走刚才流中的字符
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
								cout << "请输入想要输出的球员姓名:" << endl;
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
								if (flag)cout << "没有找到你想输出的人\n";
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
								cout << "请输入想要输出的行政人员的姓名:" << endl;
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
								if (flag)cout << "没有找到你想输出的人\n";
							}
						}
						break;
					case 7: //退出 
							//关闭socket
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
		cout << "删除成功" << endl;
	}
	else
	{
		cout << "删除失败" << endl;
	}
}

int main(void)
{
	int end;
	League FIFA;
	end = FIFA.run();
	return end;

	//会阻塞进程，直到有客户端连接上来为止
	/*sockClient = accept(sockServer, (SOCKADDR*)&addrClient, &len);
	//接收并打印客户端数据
	recv(sockClient, recvBuf , 100, 0);
	cout<<recvBuf;*/


}

void Allist() {
	cout << "\t\t* * * * * * * * *" << endl;
	cout << "\t\t*1增\t\t*\n\t\t*2删\t\t*\n\t\t*3改\t\t*\n\t\t*4查(客户端提出)*\n\t\t*5交易(客户端提出)*\n\t\t*6输出\t\t*\n\t\t*7退出系统\t*" << endl;
	cout << "\t\t* * * * * * * * *" << endl;
}

void Searchlist() {
	cout << "\t\t* * * * * * * * * * * * *" << endl;
	cout << "\t\t*名字:name(单独使用)\t*\n\t\t*年龄:age\t\t*\n\t\t*年薪:money\t\t*\n\t\t*转会费:transferfee\t*\n\t\t*进球总数:kick\t\t*\n\t\t*服役年限:experience\t*\n\t\t*俱乐部:club\t\t*\n";
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

int power(char b) {  //相应操作符的权重 
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

void change_experience(string term) {  //后缀表达式转换函数 
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
							s.pop(); //弹出( 
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
	NUM = 0;  //复位 
	while (!s.empty()) {
		behind[i++] = s.top();
		s.pop();
	}
}

void match(list<SportsP> lis2) {  //匹配 
	SportsP Stemp;
	string end;//迭代用于算出最终结果
	string st, St; // 用于存储word ,用于存储关键字(club , 模糊字符)
	char op = '\0';  //用于读取字符
	int num = 0, N = 0; //用于存数字 ,名字的迭代
	stack<char> s; //用于存数字 
	int ex = 0;
	int count = 1;  //1.条件查找,0.模糊查找
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
					if (ex == 6) {  //俱乐部
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
				case '~':  //只有在查名字的时候才会有次关键字
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
					count = 0;  //此时无需统一输出
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


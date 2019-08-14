#include<iostream>
#include<stdio.h>
#include<string> 
#include<stack> 
#include<list>//选用list作为容器

#define P1 1 //增 ,年薪
#define P2 2 //删 ,转会费 
#define P3 3 //改 ,进球总数 
#define P4 4 //查 ,服役年限 
#define P5 5 //交易 ,能力 
#define P6 6 //输出 ,所属俱乐部 
#define P7 7 //退出 ,名字，年龄 
#define P8 8



static int NUM = 0; //用于遍历后缀字符串 
static int ZIF = 0; // 操作字符的下标 
static int STR = 0; //用于其他下标的加减 
static int HUM = 0; //用于看球员人数 
static char behind[50] = {0}; //用于存后缀表达式  

 
using namespace std;

class People{
	public:
		People();
		//People(const People& rhs){};
		string name;  //人最基本的信息 
		int age;
		virtual void writemessage(){};
		virtual void changemessage(int a){};
		virtual void readmessage(){};
		~People(){};	 
};

People::People(){};



class GovernmentP: public People{
	public:
		GovernmentP();
		//GovernmentP(const GovernmentP& rhs){};
		virtual void writemessage();
		virtual void changemessage(int a);
		
		string getstrength(){  //得到行政人员的能力 
			return strength;
		}
		
		int getmoney(){
			return money;
		}
		
		virtual void readmessage(){
			cout<<"行政成员的姓名:"<<name<<endl;
			cout<<"行政成员的年龄:"<<age<<endl;
			cout<<"行政成员的能力:\n"<<strength<<endl;
			cout<<"行政成员的年薪(以万为单位):"<<money<<endl; 
		}
		~GovernmentP(){};
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
	void writename();
	void getname(string n) {
		Cname = n;
	}
	string putname();
	int deleteP(string l , int choose);
	void addG() { GHUM++; }
	void deG() { GHUM--; }
	void addS() { SHUM++; }
	void deS() { SHUM--; }
	int getSnum() {
		return SHUM;
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

GovernmentP::GovernmentP() {};

void GovernmentP::writemessage(){
			cout<<"请输入行政成员的姓名:"<<endl;
			getline(cin , name);
			cout<<"请输入行政成员的年龄:"<<endl;
			cin>>age;
			cout<<"请输入行政成员的能力:"<<endl;
			getchar();
			getline(cin , strength);
			cout<<"请输入行政成员的年薪(以万为单位):"<<endl;
			cin>>money;
};

void GovernmentP::changemessage(int a){
	switch(a){
		case 1:
			cout<<"请输入要更改的名字:"<<endl;
			getchar();
		break;
		case 2:
			cout<<"请输入要更改的年龄:"<<endl;
			cin>>age;
		break;
		case 3:
			cout<<"请输入想要更改的行政人员能力:"<<endl;
			getline(cin , strength);
		break;
		case 4:
			cout<<"请输入想要更改的年薪(以万为单位):"<<endl;
			cin>>money;
		break;
	}
};

static list<GovernmentP>::iterator Git;

SportsP::SportsP(){};

void SportsP::writemessage(){
			cout<<"请输入球员的姓名:"<<endl;
			getline(cin , name);
			cout<<"请输入球员的年龄:"<<endl;
			cin>>age;
			getchar();
			cout<<"请输入球员的能力:"<<endl;
			getline(cin , strength);
			cout<<"请输入球员的年薪(以万为单位):"<<endl;
			cin>>money;
			cout<<"请输入球员的转会费(以万为单位):"<<endl;
			cin>>Transferfee;
			cout<<"请输入球员的进球总数(以个为单位):"<<endl;
			cin>>kick;
			cout<<"请输入球员的服役年限(以年为单位):"<<endl;
			cin>>experience;
			cout<<"请输入球员所属的俱乐部:"<<endl;
			cin>>club;
			getchar();
}

void SportsP::readmessage(){
			cout<<"球员的姓名:"<<name<<endl;
			cout<<"球员的年龄:"<<age<<endl;
			cout<<"球员的能力:\n"<<strength<<endl;
			cout<<"球员的年薪(以万为单位):"<<money<<endl;
			cout<<"球员的转会费(以万为单位):"<<Transferfee<<endl;
			cout<<"球员的进球总数(以个为单位):"<<kick<<endl;
			cout<<"球员的服役年限(以年为单位):"<<experience<<endl; 
			cout<<"球员所属的俱乐部:"<<club<<endl;
			cout << endl;
}

void SportsP::changemessage(int a){
			switch(a){
				case 1:
					cout<<"请输入要更改的名字:"<<endl;
					getline(cin , name);
				break;
				case 2:
					cout<<"请输入要更改的年龄:"<<endl;
					cin>>age;
				break;
				case 3:
					cout<<"请输入想要更改的球员能力:"<<endl;
					getline(cin , strength);
				break;
				case 4:
					cout<<"请输入想要更改的年薪(以万为单位):"<<endl;
					cin>>money;
				break;
				case 5:
					cout<<"请输入想要更改的球员的转会费(以万为单位):"<<endl;
					cin>>Transferfee;
				break;
				case 6:
					cout<<"请输入想要更改的球员的进球总数(以个为单位):"<<endl;
					cin>>kick;
				break;
				case 7:
					cout<<"输入想要更改的球员的服役年限(以年为单位):"<<endl;
					cin>>experience;
				break; 
				case 8:
					cout<<"输入想要更改的球员的所属俱乐部:"<<endl;
					cin>>club;
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


int Club::deleteP(string l , int choose){ 
	int flag = 1;
	SportsP a;
	GovernmentP b ;
	if (choose) {
		a = (*Cit).lis2.back();
		for (Sit = (*Cit).lis2.begin(); Sit != (*Cit).lis2.end(); Sit++) {
			S = *Sit;
			if (l == (S.name)){
				if (l == a.name){  //判断是否为最后一个字符
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
	if(flag) cout<<"没有找到你想删除或更改或交易的人\n";
	else cout << "操作成功\n";
	return flag;
}

void match(list<SportsP> lis2);  // 查找函数 
int type(string a); // 用于返回条件代码 
int power(char b); //判断运算符的权重 
void change_experience(string term); //改变成后缀表达式 
int changenum(stack<char> s); //求出相应整数 
void Allist();
static list<Club>lis;  //联赛俱乐部名单
void Searchlist();

int main(void){
	int choose,Choose,option; //对球员还是行政人员操作，对俱乐部进行操作还是对俱乐部内部进行操作，什么操作 
	Club C , c;  //用于初始写入，用于判断赋值
	GovernmentP Gtemp;  //用于迭代赋值  
	SportsP Stemp;
	Club Ctemp;
	list<Club>::iterator cit; //用于迭代赋值
	string n ,N; //想删除的人名或俱乐部 
	string trem; //查找要素 
	int gai;//想更改的选项
	int Transfer_fee; //提交的转会费 
	int  a;// 输出选项 
	while(1){
		int flag = 1;
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
		if(Choose){
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
			switch(option){
				case 1:
					cout<<"请输入想添加的俱乐部名字:"<<endl;
					getline(cin, n);
					for (Cit = lis.begin(); Cit != lis.end(); Cit++) {
						Ctemp = *Cit;
						if (n == Ctemp.putname()) {
							flag = 0;
							cout << "该俱乐部已经存在。" << endl;
							break;
						}
						}
					if(flag) C.getname(n) , lis.push_back(C);
				break;
				case 2:
					cout<<"请输入想删除的俱乐部名字:"<<endl;
					getline(cin , n);
					c = lis.back();
					for(Cit = lis.begin() ; Cit != lis.end() ; ){
						Ctemp = *Cit;
						if(n == Ctemp.putname()){
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
					if(flag) cout<<"没有找到你想删除的俱乐部\n";
				break;
				case 3:
					cout<<"请输入想更改俱乐部信息的名字:"<<endl;
					getline(cin , n);
					for(Cit = lis.begin() ; Cit != lis.end() ; ){
						Ctemp = *Cit;
						if(n == Ctemp.putname()){
							flag = 0;
							cout<<"请输入想更改的名字"<<endl;
							(*Cit).writename();
							cout<<"更改成功!"<<endl;
						break;
					}
						Cit++;
				}
				if(flag) cout<<"没有找到你想更改的俱乐部\n";
				break;
				case 4:
					for(Cit = lis.begin() ; Cit != lis.end() ; Cit++){
						Ctemp = *Cit;
						if(n == (Ctemp.putname())){
							cout<<"该俱乐部在此联赛中"<<endl; 
						}else cout<<"该俱乐部不在此联赛中"<<endl;
					} 
				break;
				case 6:
					for(Cit = lis.begin() ; Cit != lis.end() ; Cit++){
						Ctemp = *Cit;
						Ctemp.readmessage();
						cout << endl;
					}
				break;
				case 7:
					return 0;
				break;
		}
		}else{
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
			else{
				cout << "输入错误，请重输入" << endl;
				cin.clear();    //此处用cin.clear()流标志复位
				cin.ignore();   //取走刚才流中的字符
			}
		}
		for (;;) {
			cout << "请输入想进行的操作对象(0:行政人员 1:球员):";
			cin >> choose;
			getchar();
			if (choose == 1 || choose == 0 ) break;
			else {
				cout << "输入错误，请重输入" << endl;
				cin.clear();    //此处用cin.clear()流标志复位
				cin.ignore();   //取走刚才流中的字符
			}
		}
		switch(option){
			case 1:  //增 
				if(choose){
					S.writemessage();
					(*Cit).lis2.push_back(S);
					(*Cit).addS();
				}else{
					G.writemessage();
					(*Cit).lis1.push_back(G);
					(*Cit).addG();
				}
			break;
			case 2:  //删 
				cout << "请输入想删除的人名:";
				getline(cin , n);
				if(choose){
					flag = (*Cit).deleteP(n , choose);
					if(flag == 0) (*Cit).deS();
				}else{
					flag = (*Cit).deleteP(n, choose);
					if(flag == 0) (*Cit).deG();
				}
			break;
			case 3:  //改 
				if(choose){
					cout<<"请输入想更改球员信息的名字:"<<endl;
					getline(cin , n);
					for (Sit = (*Cit).lis2.begin(); Sit != (*Cit).lis2.end(); ) {
						S = *Sit;
						if (n == (S.name)) {
							flag = 0;
							break;
						}
					}
					if(flag == 0){
						cout<<"请输入想更改的项目(1.名字2.年龄3.能力4.年薪5.转会费6.进球总数7.服役年限8.所属俱乐部)"<<endl;
						cin>>gai;
						getchar();
						(*Sit).changemessage(gai);
						cout<<"更改成功!"<<endl;
					}else cout<< "没有找到你想删除或更改或交易的人\n";
				}else{
					cout<<"请输入想要更改行政人员的名字:"<<endl;
					getline(cin, n);
					for (Git = (*Cit).lis1.begin(); Git != (*Cit).lis1.end(); ) {
						G = *Git;
						if (n == (G.name)) {
							flag = 0;
							break;
						}
					}
					if(flag == 0){
						cout<<"输入想更改的项目(1.名字2.年龄3.能力4.年薪)"<<endl;
						cin>>gai;
						getchar();
						(*Git).changemessage(gai);
						cout<<"更改成功!"<<endl;
					}else "没有找到你想删除或更改或交易的人\n";
				}
			break;
			case 4: //查 
				Searchlist();
				cout<<"请输入想要的限制条件(书写格式在使用文档中有详细说明):"<<endl;
				cin>>trem;
				change_experience(trem);
				for (Cit = lis.begin(); Cit != lis.end(); Cit++) {
					C = *Cit;  //Cit为实际要操作的值
					HUM = C.getSnum();
					match(C.lis2);
					NUM = 0;
				}
			break;
			case 5: //交换
				cout<<"请输入想要交换到的俱乐部名:"<<endl;
				getline(cin , N);
				for(cit = lis.begin() ; cit != lis.end() ; cit++){
						Ctemp = *cit;
						if(N == (Ctemp.putname())){
							flag = 0;
							break;
					}
				}
				if (flag) {
					cout << "没有找到你想查找的俱乐部\n";
					break;
				}
				cout<<"请输入想要交换的球员姓名:"<<endl;
				getline(cin , n);
				flag = (*Cit).deleteP(n, choose);
				cout<<"请输入想要交换的费用价格(以万为单位):"<<endl;
				cin>>Transfer_fee;
				a = S.getmessage(2); 
				if(Transfer_fee>=a){
					S.putclub(N);
					(*cit).lis2.push_back(S);
					cout<<"转会成功!"<<endl;
				}else{
					cout<<"该俱乐部提出的金额不符合该球员的要求，所以转会失败"<<endl;
					(*Cit).lis2.insert(Sit , S); 
				} 
			break;
			case 6: //输出 
				cout<<"请输入想要输出的类型(1全部输出0.选择输出):";
				cin>>a;
				if(choose){
					if(a){
						for(Sit =C.lis2.begin() ; Sit != C.lis2.end() ; Sit++){
							Stemp = *Sit;
							Stemp.readmessage();
							cout<<endl;
						}
					}else{
						cout<<"请输入想要输出的球员姓名:"<<endl;
						cin>>n;
						for(Sit = C.lis2.begin() ; Sit != C.lis2.end() ; Sit++){
							Stemp = *Sit;
							if(n == (Stemp.name)){
								Stemp.readmessage();
								flag = 0;
								cout<<endl;
								break;
							}
						}	
						if(flag)cout<<"没有找到你想输出的人\n";
					} 
				}else{
					if(a){
						for(Git = C.lis1.begin() ; Git != C.lis1.end() ; Git++){
							Gtemp = *Git;
							Gtemp.readmessage();
							cout<<endl;
						}
					}else{
						cout<<"请输入想要输出的行政人员的姓名:"<<endl;
						cin>>n;
						for(Git = C.lis1.begin() ; Git != C.lis1.end() ; Git++){
							Gtemp = *Git;
							if(n == Gtemp.name){
								Gtemp.readmessage();
								flag = 0;
								cout<<endl;
								break;
							}
						}
						if(flag)cout<<"没有找到你想输出的人\n";
					} 
				}
			break;
			case 7: //退出 
				return 0;
			break;	 
			}
		}
	}	
	return 0;
}

void Allist(){
	cout<<"\t\t* * * * * * * * *"<<endl;
	cout<<"\t\t*1增\t\t*\n\t\t*2删\t\t*\n\t\t*3改\t\t*\n\t\t*4查(对所有球员)*\n\t\t*5交易(仅对球员)*\n\t\t*6输出\t\t*\n\t\t*7退出系统\t*"<<endl;
	cout<<"\t\t* * * * * * * * *"<<endl;
}

void Searchlist() {
	cout << "\t\t* * * * * * * * * * * * *" << endl;
	cout << "\t\t*年龄:age\t\t*\n\t\t*年薪:money\t\t*\n\t\t*转会费:transferfee\t*\n\t\t*进球总数:kick\t\t*\n\t\t*服役年限:experience\t*\n\t\t*俱乐部:club\t\t*\n";
	cout << "\t\t* * * * * * * * * * * * *" << endl;
}

int type(string a){
	if(a == "age") return 7;
	if(a == "money") return 1;
	if(a == "transferfee") return 2;
	if(a == "kick") return 3;
	if(a == "experience") return 4;
	if(a == "strength") return 5;
	if(a == "club") return 6;
	return 0;	
}

int changenum(stack<char> s){
	int a , sum=0 , b = 1;
	while(!s.empty()){
		a = s.top() - 48;
		sum+=a*b;
		b*=10;
		s.pop();
	}
	return sum;
}

int power(char b){  //相应操作符的权重 
	switch(b){
		case '>':
		case '<':
		case '=':
			return 3;
		break; 
		case '&':
			return 2;
			break;
		case '|':
			return 1;
		break;
		case '!':
			return 4;
		break;
		case '(':
		return 0;
	}
	return 0;
}

void change_experience(string term){  //后缀表达式转换函数 
	int i = 0;
	stack<char> s;
	NUM = 0;
	while(term[NUM]){
		if (term[NUM] != '@') {
			if ((term[NUM] >= 'a'&&term[NUM] <= 'z') || (term[NUM] >= 'A'&&term[NUM] <= 'Z')) {
				behind[i++] = term[NUM];
			}
			else {
				if (term[NUM] >= '0'&&term[NUM] <= '9')behind[i++] = term[NUM];
				else {
					if (s.empty()) s.push(term[NUM]);
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
	while(!s.empty()){
		behind[i++]=s.top();
		s.pop();
	}
}

void match(list<SportsP> lis2){  //匹配 
	SportsP Stemp;
	string st; // 用于存储word
	char op = '\0';  //用于读取字符
	int num = 0 , AND = 1 , flag = 0; //用于存数字,用于存与操作符的个数,用于存或操作符的个数 (初始化的不同是根据二者的特性来的)
	stack<char> s; //用于存数字 
	int good[20] = {0} ;//设一个球队球员最多20人 
	int ex = 0;
	list<SportsP>::iterator Sit;
	int i = 0;
	while(behind[NUM]){
		op = behind[NUM];
		if(op>='a'&&op<='z'){
			st+=op;
			NUM++;
		}else if(op>='0'&&op<='9'){
			s.push(op);
			NUM++;
		}else{
			switch(op){
				//case ' ': 	
				//break;
				case '!': //!
					for(int j=0 ; j<HUM ; j++){
						if((good[j] == AND && flag)||(good[i]==AND+1 && flag == 0)) good[j]--;
						else good[j]++;
					}
				break;
				case '&': //&
					AND++;
					flag = 1;
				break;
				case '>': //>
					num = changenum(s);
				    ex = type(st);
					if(ex == 7){
						for( Sit = lis2.begin() , i=0; Sit != lis2.end() ; Sit++ , i++ ){
							Stemp = *Sit;
							if(Stemp.age > num) good[i]++ ;
						}
					}else{
						for( Sit = lis2.begin() , i=0; Sit != lis2.end() ; Sit++ , i++ ){
							Stemp = *Sit;
							if(Stemp.getmessage(ex) > num) good[i]++ ;
					}
				}	
				break;
				case '<'://<
					num = changenum(s);
					ex  = type(st);
					if(ex == 7){
						for( Sit = lis2.begin() , i=0; Sit != lis2.end() ; Sit++ , i++ ){
							Stemp = *Sit;
							if(Stemp.age < num) good[i]++ ;
						}
					}else{
						for( Sit = lis2.begin() ,  i=0; Sit != lis2.end() ; Sit++ , i++ ){
							Stemp = *Sit;
							if(Stemp.getmessage(ex) < num) good[i]++ ;
					}
				}
				break;
				case '=': //=
					num = changenum(s);
					ex = type(st);
					if(ex == 7){
						for( Sit = lis2.begin() ,  i=0; Sit != lis2.end() ; Sit++ , i++ ){
							Stemp = *Sit;
							if(Stemp.age == num) good[i]++ ;
						}
					}else{
						for( Sit = lis2.begin() , i=0; Sit != lis2.end() ; Sit++ , i++ ){
							Stemp = *Sit;
							if(Stemp.getmessage(ex) == num) good[i]++ ;
					}
				}
				break; 
			}
			while (!s.empty()) s.pop();
			st.clear();
			ex = 0;
			NUM++;
		}
	}
	for( Sit = lis2.begin() , i=0; Sit != lis2.end() ; Sit++ , i++ ){
		Stemp = *Sit;
		if(good[i] == AND) Stemp.readmessage();
	}
}



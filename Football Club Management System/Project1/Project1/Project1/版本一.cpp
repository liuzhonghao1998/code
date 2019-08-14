#include<iostream>
#include<stdio.h>
#include<string> 
#include<stack> 
#include<list>//ѡ��list��Ϊ����

#define P1 1 //�� ,��н
#define P2 2 //ɾ ,ת��� 
#define P3 3 //�� ,�������� 
#define P4 4 //�� ,�������� 
#define P5 5 //���� ,���� 
#define P6 6 //��� ,�������ֲ� 
#define P7 7 //�˳� ,���֣����� 
#define P8 8



static int NUM = 0; //���ڱ�����׺�ַ��� 
static int ZIF = 0; // �����ַ����±� 
static int STR = 0; //���������±�ļӼ� 
static int HUM = 0; //���ڿ���Ա���� 
static char behind[50] = {0}; //���ڴ��׺���ʽ  

 
using namespace std;

class People{
	public:
		People();
		//People(const People& rhs){};
		string name;  //�����������Ϣ 
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
		
		string getstrength(){  //�õ�������Ա������ 
			return strength;
		}
		
		int getmoney(){
			return money;
		}
		
		virtual void readmessage(){
			cout<<"������Ա������:"<<name<<endl;
			cout<<"������Ա������:"<<age<<endl;
			cout<<"������Ա������:\n"<<strength<<endl;
			cout<<"������Ա����н(����Ϊ��λ):"<<money<<endl; 
		}
		~GovernmentP(){};
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
		cout << "���ֲ���:" << Cname << endl;
		cout << "������Ա������:" << GHUM << endl;
		cout << "��Ա����:" << SHUM << endl;
	}
	~Club() {};
private:
	string Cname;
	int GHUM, SHUM;
};

GovernmentP::GovernmentP() {};

void GovernmentP::writemessage(){
			cout<<"������������Ա������:"<<endl;
			getline(cin , name);
			cout<<"������������Ա������:"<<endl;
			cin>>age;
			cout<<"������������Ա������:"<<endl;
			getchar();
			getline(cin , strength);
			cout<<"������������Ա����н(����Ϊ��λ):"<<endl;
			cin>>money;
};

void GovernmentP::changemessage(int a){
	switch(a){
		case 1:
			cout<<"������Ҫ���ĵ�����:"<<endl;
			getchar();
		break;
		case 2:
			cout<<"������Ҫ���ĵ�����:"<<endl;
			cin>>age;
		break;
		case 3:
			cout<<"��������Ҫ���ĵ�������Ա����:"<<endl;
			getline(cin , strength);
		break;
		case 4:
			cout<<"��������Ҫ���ĵ���н(����Ϊ��λ):"<<endl;
			cin>>money;
		break;
	}
};

static list<GovernmentP>::iterator Git;

SportsP::SportsP(){};

void SportsP::writemessage(){
			cout<<"��������Ա������:"<<endl;
			getline(cin , name);
			cout<<"��������Ա������:"<<endl;
			cin>>age;
			getchar();
			cout<<"��������Ա������:"<<endl;
			getline(cin , strength);
			cout<<"��������Ա����н(����Ϊ��λ):"<<endl;
			cin>>money;
			cout<<"��������Ա��ת���(����Ϊ��λ):"<<endl;
			cin>>Transferfee;
			cout<<"��������Ա�Ľ�������(�Ը�Ϊ��λ):"<<endl;
			cin>>kick;
			cout<<"��������Ա�ķ�������(����Ϊ��λ):"<<endl;
			cin>>experience;
			cout<<"��������Ա�����ľ��ֲ�:"<<endl;
			cin>>club;
			getchar();
}

void SportsP::readmessage(){
			cout<<"��Ա������:"<<name<<endl;
			cout<<"��Ա������:"<<age<<endl;
			cout<<"��Ա������:\n"<<strength<<endl;
			cout<<"��Ա����н(����Ϊ��λ):"<<money<<endl;
			cout<<"��Ա��ת���(����Ϊ��λ):"<<Transferfee<<endl;
			cout<<"��Ա�Ľ�������(�Ը�Ϊ��λ):"<<kick<<endl;
			cout<<"��Ա�ķ�������(����Ϊ��λ):"<<experience<<endl; 
			cout<<"��Ա�����ľ��ֲ�:"<<club<<endl;
			cout << endl;
}

void SportsP::changemessage(int a){
			switch(a){
				case 1:
					cout<<"������Ҫ���ĵ�����:"<<endl;
					getline(cin , name);
				break;
				case 2:
					cout<<"������Ҫ���ĵ�����:"<<endl;
					cin>>age;
				break;
				case 3:
					cout<<"��������Ҫ���ĵ���Ա����:"<<endl;
					getline(cin , strength);
				break;
				case 4:
					cout<<"��������Ҫ���ĵ���н(����Ϊ��λ):"<<endl;
					cin>>money;
				break;
				case 5:
					cout<<"��������Ҫ���ĵ���Ա��ת���(����Ϊ��λ):"<<endl;
					cin>>Transferfee;
				break;
				case 6:
					cout<<"��������Ҫ���ĵ���Ա�Ľ�������(�Ը�Ϊ��λ):"<<endl;
					cin>>kick;
				break;
				case 7:
					cout<<"������Ҫ���ĵ���Ա�ķ�������(����Ϊ��λ):"<<endl;
					cin>>experience;
				break; 
				case 8:
					cout<<"������Ҫ���ĵ���Ա���������ֲ�:"<<endl;
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
static list<Club>::iterator Cit;  //���ڵ���
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
				if (l == a.name){  //�ж��Ƿ�Ϊ���һ���ַ�
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
	if(flag) cout<<"û���ҵ�����ɾ������Ļ��׵���\n";
	else cout << "�����ɹ�\n";
	return flag;
}

void match(list<SportsP> lis2);  // ���Һ��� 
int type(string a); // ���ڷ����������� 
int power(char b); //�ж��������Ȩ�� 
void change_experience(string term); //�ı�ɺ�׺���ʽ 
int changenum(stack<char> s); //�����Ӧ���� 
void Allist();
static list<Club>lis;  //�������ֲ�����
void Searchlist();

int main(void){
	int choose,Choose,option; //����Ա����������Ա�������Ծ��ֲ����в������ǶԾ��ֲ��ڲ����в�����ʲô���� 
	Club C , c;  //���ڳ�ʼд�룬�����жϸ�ֵ
	GovernmentP Gtemp;  //���ڵ�����ֵ  
	SportsP Stemp;
	Club Ctemp;
	list<Club>::iterator cit; //���ڵ�����ֵ
	string n ,N; //��ɾ������������ֲ� 
	string trem; //����Ҫ�� 
	int gai;//����ĵ�ѡ��
	int Transfer_fee; //�ύ��ת��� 
	int  a;// ���ѡ�� 
	while(1){
		int flag = 1;
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
		if(Choose){
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
			switch(option){
				case 1:
					cout<<"����������ӵľ��ֲ�����:"<<endl;
					getline(cin, n);
					for (Cit = lis.begin(); Cit != lis.end(); Cit++) {
						Ctemp = *Cit;
						if (n == Ctemp.putname()) {
							flag = 0;
							cout << "�þ��ֲ��Ѿ����ڡ�" << endl;
							break;
						}
						}
					if(flag) C.getname(n) , lis.push_back(C);
				break;
				case 2:
					cout<<"��������ɾ���ľ��ֲ�����:"<<endl;
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
								Cit = lis.erase(Cit);   //��������ͣ���ڱ�ɾ��Ԫ�ص���һ��λ�ã���ֱ�ӽ��в������ 
							}
							flag = 0;
							break;
					}
						Cit++;
				}
					if(flag) cout<<"û���ҵ�����ɾ���ľ��ֲ�\n";
				break;
				case 3:
					cout<<"����������ľ��ֲ���Ϣ������:"<<endl;
					getline(cin , n);
					for(Cit = lis.begin() ; Cit != lis.end() ; ){
						Ctemp = *Cit;
						if(n == Ctemp.putname()){
							flag = 0;
							cout<<"����������ĵ�����"<<endl;
							(*Cit).writename();
							cout<<"���ĳɹ�!"<<endl;
						break;
					}
						Cit++;
				}
				if(flag) cout<<"û���ҵ�������ĵľ��ֲ�\n";
				break;
				case 4:
					for(Cit = lis.begin() ; Cit != lis.end() ; Cit++){
						Ctemp = *Cit;
						if(n == (Ctemp.putname())){
							cout<<"�þ��ֲ��ڴ�������"<<endl; 
						}else cout<<"�þ��ֲ����ڴ�������"<<endl;
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
			else{
				cout << "���������������" << endl;
				cin.clear();    //�˴���cin.clear()����־��λ
				cin.ignore();   //ȡ�߸ղ����е��ַ�
			}
		}
		for (;;) {
			cout << "����������еĲ�������(0:������Ա 1:��Ա):";
			cin >> choose;
			getchar();
			if (choose == 1 || choose == 0 ) break;
			else {
				cout << "���������������" << endl;
				cin.clear();    //�˴���cin.clear()����־��λ
				cin.ignore();   //ȡ�߸ղ����е��ַ�
			}
		}
		switch(option){
			case 1:  //�� 
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
			case 2:  //ɾ 
				cout << "��������ɾ��������:";
				getline(cin , n);
				if(choose){
					flag = (*Cit).deleteP(n , choose);
					if(flag == 0) (*Cit).deS();
				}else{
					flag = (*Cit).deleteP(n, choose);
					if(flag == 0) (*Cit).deG();
				}
			break;
			case 3:  //�� 
				if(choose){
					cout<<"�������������Ա��Ϣ������:"<<endl;
					getline(cin , n);
					for (Sit = (*Cit).lis2.begin(); Sit != (*Cit).lis2.end(); ) {
						S = *Sit;
						if (n == (S.name)) {
							flag = 0;
							break;
						}
					}
					if(flag == 0){
						cout<<"����������ĵ���Ŀ(1.����2.����3.����4.��н5.ת���6.��������7.��������8.�������ֲ�)"<<endl;
						cin>>gai;
						getchar();
						(*Sit).changemessage(gai);
						cout<<"���ĳɹ�!"<<endl;
					}else cout<< "û���ҵ�����ɾ������Ļ��׵���\n";
				}else{
					cout<<"��������Ҫ����������Ա������:"<<endl;
					getline(cin, n);
					for (Git = (*Cit).lis1.begin(); Git != (*Cit).lis1.end(); ) {
						G = *Git;
						if (n == (G.name)) {
							flag = 0;
							break;
						}
					}
					if(flag == 0){
						cout<<"��������ĵ���Ŀ(1.����2.����3.����4.��н)"<<endl;
						cin>>gai;
						getchar();
						(*Git).changemessage(gai);
						cout<<"���ĳɹ�!"<<endl;
					}else "û���ҵ�����ɾ������Ļ��׵���\n";
				}
			break;
			case 4: //�� 
				Searchlist();
				cout<<"��������Ҫ����������(��д��ʽ��ʹ���ĵ�������ϸ˵��):"<<endl;
				cin>>trem;
				change_experience(trem);
				for (Cit = lis.begin(); Cit != lis.end(); Cit++) {
					C = *Cit;  //CitΪʵ��Ҫ������ֵ
					HUM = C.getSnum();
					match(C.lis2);
					NUM = 0;
				}
			break;
			case 5: //����
				cout<<"��������Ҫ�������ľ��ֲ���:"<<endl;
				getline(cin , N);
				for(cit = lis.begin() ; cit != lis.end() ; cit++){
						Ctemp = *cit;
						if(N == (Ctemp.putname())){
							flag = 0;
							break;
					}
				}
				if (flag) {
					cout << "û���ҵ�������ҵľ��ֲ�\n";
					break;
				}
				cout<<"��������Ҫ��������Ա����:"<<endl;
				getline(cin , n);
				flag = (*Cit).deleteP(n, choose);
				cout<<"��������Ҫ�����ķ��ü۸�(����Ϊ��λ):"<<endl;
				cin>>Transfer_fee;
				a = S.getmessage(2); 
				if(Transfer_fee>=a){
					S.putclub(N);
					(*cit).lis2.push_back(S);
					cout<<"ת��ɹ�!"<<endl;
				}else{
					cout<<"�þ��ֲ�����Ľ����ϸ���Ա��Ҫ������ת��ʧ��"<<endl;
					(*Cit).lis2.insert(Sit , S); 
				} 
			break;
			case 6: //��� 
				cout<<"��������Ҫ���������(1ȫ�����0.ѡ�����):";
				cin>>a;
				if(choose){
					if(a){
						for(Sit =C.lis2.begin() ; Sit != C.lis2.end() ; Sit++){
							Stemp = *Sit;
							Stemp.readmessage();
							cout<<endl;
						}
					}else{
						cout<<"��������Ҫ�������Ա����:"<<endl;
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
						if(flag)cout<<"û���ҵ������������\n";
					} 
				}else{
					if(a){
						for(Git = C.lis1.begin() ; Git != C.lis1.end() ; Git++){
							Gtemp = *Git;
							Gtemp.readmessage();
							cout<<endl;
						}
					}else{
						cout<<"��������Ҫ�����������Ա������:"<<endl;
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
						if(flag)cout<<"û���ҵ������������\n";
					} 
				}
			break;
			case 7: //�˳� 
				return 0;
			break;	 
			}
		}
	}	
	return 0;
}

void Allist(){
	cout<<"\t\t* * * * * * * * *"<<endl;
	cout<<"\t\t*1��\t\t*\n\t\t*2ɾ\t\t*\n\t\t*3��\t\t*\n\t\t*4��(��������Ա)*\n\t\t*5����(������Ա)*\n\t\t*6���\t\t*\n\t\t*7�˳�ϵͳ\t*"<<endl;
	cout<<"\t\t* * * * * * * * *"<<endl;
}

void Searchlist() {
	cout << "\t\t* * * * * * * * * * * * *" << endl;
	cout << "\t\t*����:age\t\t*\n\t\t*��н:money\t\t*\n\t\t*ת���:transferfee\t*\n\t\t*��������:kick\t\t*\n\t\t*��������:experience\t*\n\t\t*���ֲ�:club\t\t*\n";
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

int power(char b){  //��Ӧ��������Ȩ�� 
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

void change_experience(string term){  //��׺���ʽת������ 
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
	while(!s.empty()){
		behind[i++]=s.top();
		s.pop();
	}
}

void match(list<SportsP> lis2){  //ƥ�� 
	SportsP Stemp;
	string st; // ���ڴ洢word
	char op = '\0';  //���ڶ�ȡ�ַ�
	int num = 0 , AND = 1 , flag = 0; //���ڴ�����,���ڴ���������ĸ���,���ڴ��������ĸ��� (��ʼ���Ĳ�ͬ�Ǹ��ݶ��ߵ���������)
	stack<char> s; //���ڴ����� 
	int good[20] = {0} ;//��һ�������Ա���20�� 
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



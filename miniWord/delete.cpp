#include"struct.h"
int Whentostop( int Y , Row_node* R) 
{
	int b = 1;  //�ַ�������������һ��λ�� 
	int y = 0;  //�������ڵ����ļ���
	int flag = 0 , flag1=0;
	char* match;
	Data_node* D; //����Ѱ���ַ���
	y = 0;
	if(R->right!=NULL) D = R->right; //���������� 
	else return 0;
	while (D->right!=NULL) {
		D = D->right;
		b += 100;
		flag = 1;
	}
	if (!flag) b = 1; //ֻ��һ��
	match = D->data;
	while (b < MAX && *match != '\n') {
		if (*match == '\0'&&*(match+1)!='\0') {
			flag1 = 1;  //���ڽ��в�λ����
		}
		match++;
		b++;
	}
	if (!flag1) {
		if (b < MAX&&*(match + 1) == '\0') b++; //��һ�еĽ�β���ж�
		if (b == MAX && R->down != NULL&&*match != '\n') return 2;  //��һ��Ҳ���ˣ��Ҳ�Ϊ��β
		else if (*match == '\n') return 1;
		else if (b <= MAX&&R->down == NULL)return 0;   //����β��
	}
	else return -1;  //��һ�л��ڽ��в�λ
}

char backcover(Row_node* R, Data_node* D, int x, int Y, char* match1) 
{
	int flag1 = 0, flag2 = 0;
	char* match2;
	Data_node* D1;
	while (1) {
		if (x % 100 == 0 && D->right != NULL) {  //ȷ�����ĺ�һ���ַ�λ�� ���������ǰ�ƣ� 
			D1 = D;
			D = D->right;
			match2 = D->data;
			if (*match2 != '\0') {
				*match1 = *match2;
				*match2 = '\0';
				flag1 = 1;
				x++;
			}
			else return '\0';  //�൱��ɾ���˽�β�ַ�
		}
		else if (x % 100 == 0 && D->right == NULL) return '\0';
		else if (x % 100 != 0 && x<MAX) {
			if (flag1) {  //�����˿�����,����в���
				match1 = match2;
				*match1 = *(match1 + 1);
				match1++;
				*match1 = '\0';
				x++;
				flag1 = 0;
			}
			else if (flag2) {
				*match1 = *match2;
				match1 = match2;
				match2 = NULL;
				*match1 = '\0';
				flag2 = 0;
			}
			else {
				*match1 = *(match1 + 1);
				match1++;
				*match1 = '\0';
				x++;
			}
		}
		if (D->right == NULL && (Whentostop(Y ,R) == 0 || Whentostop(Y , R) == 1)) {return '\0'; }
		else if (x == MAX && Whentostop( Y ,R) == 2) {
			Y++;
			x = 1;  //��ֵΪ
			R = R->down;
			D = R->right;
			match2 = D->data;
			flag2 = 1;
		}
	}
	return '\0';
}

void Blockdelete() 
{
	int X = 0, Y = 0 ,flag=0;//�ж��ֽڵĸ���
	Row_node* R = pData_stack;
	Row_node* Rtemp;
	Data_node* last, *temp;
	last = R->right;
	while (R->down != NULL) {
		flag=0;
		while (last->right != NULL) {
			temp = last;
			last = last->right;
			X++;
		}
		if (last->data[0] == '\0') {
			if (X){
				delete temp->right;
				temp->right = NULL;
			}
			else {
				delete last;
				last = NULL;
				R->right = NULL;
				if (!Y) {
					pData_stack->down = R->down;
					delete R;
					R = pData_stack->down;
					last = R->right;
				}
				else {
					Rtemp->down = R->down;
					delete R;
					R = Rtemp->down;
					last = R->right;
				}
				flag = 1;
			}
		}
			if(!flag){
			Rtemp = R;
			R = R->down;
			last = R->right;
			Y++;
			X = 0;
		}
	}
	while (last->right != NULL) {   //���һ����еĴ���
		temp = last;
		last = last->right;
		X++;
	}
		if (last->data[0] == '\0') {
			if (X){
				delete temp->right;
				temp->right = NULL;
			}
			else {
				delete last;
				last = NULL;
				Rtemp->down = NULL;
				delete R;
				R = NULL;
			}
		}
}

char Rowbackspace( int Y) 
{
	int y = 0;  //����
	int x = 1, x1 = 0; //����ȷ����һ���ַ���λ��
	int flag = 2;
	Row_node* R = pData_stack, *R1;
	Data_node* D , *D1; //���ڱ�����Ƚ�����ȷ����һ�еĽ�β,����ȷ���� 
	Data_node* current_data = NULL;
	char* match1, *match2;
	while (y<Y) {  //ȷ���� 
		if (y == Y - 1 || Y == 1) R1 = R; //ȷ��������һ�У���һ���ǵ�һ�е����
		R = R->down;
		y++;
	}
	if(Y!=0) D = R1->right; //��һ�еĵ�һλ���˸�
	else return '\0';
	match1 = D->data;
	while (1) {   //ȷ����һ�еĽ�βmatch1
		if (*match1 == '\n') {
			*match1 = '\0';
			break;
		}
		else if (x == MAX) {
			*match1 = '\0';
			break;
		}
		else if (x % 100 == 0 && D->right != NULL) {
			D = D->right;
			match1 = D->data;
			x++;
		}
		else match1++, x++;
	}
	D1 = D;  //����������һ�еĽ�β��������ܻ�����
	D = R->right;
	match2 = D->data;
	while (x <= MAX && (*match2 != '\0')) {  //�˳��������������ˣ�����һ�в�����ȫ������
		*match1 = *match2;
		x++;
		*match2 = '\0';
		backcover(R, D, 1, Y, match2);
		if (x % 100 == 1 && x > 1) {
			current_data = (Data_node*)malloc(sizeof(Data_node));
			current_data->right = NULL;
			memset(current_data->data, '\0', 100);
			D1->right = current_data;
			D1 = D1->right;
			match1 = D1->data;
		}
		else  match1++;

	}
	return '\0';
}

char Rowdelete(Row_node* R, int x, int Y, char* match1) 
{
	char* match2;
	Row_node* R1;
	Data_node* D;
	Data_node* D1 = R->right;
	Data_node* current_data = NULL;
	Y++;//backcover����һ��
	if (R->down == NULL) return '\0';
	else {
		R1 = R->down;
		D = R1->right;
		match2 = D->data;
		while (x < MAX && (*match2 != '\0')) {  //�˳��������������ˣ�����һ�в�����ȫ������
			*match1 = *match2;
			x++;
			*match2 = '\0';
			backcover(R1, D, 1 , Y , match2);
			if (x % 100 == 0 && x > 0) {
				while (D1->right != NULL) D1 = D1->right; //ȷ����ӿ�
				current_data = (Data_node*)malloc(sizeof(Data_node));
				current_data->right = NULL;
				memset(current_data->data, '\0', 100);
				D1->right = current_data;
				D1 = D1->right;
				match1 = D1->data;
			}else  match1++;
		}
		return '\0';
	}
}

char Normal_bd(int X, int Y, int g) 
{
	int b, x;  //����ڵ���������λ�ã��ֽ������� 
	int y = 0;  //�������ڵ����ļ��� 
	char* match1=NULL , *match2=NULL;
	Row_node* R = pData_stack; 
	Data_node* D;
	x = X;
	b = X / 100;
	while (y<Y) {  //ȷ���� 
		R = R->down;
		y++;
	}
	y = 0;
	D = R->right;
	while (y<b) {  //ȷ���ֽ� 
		D = D->right;
		y++;
	}
	if (g == 0x08) {  //backspace 
		if (X == 0) {
			return Rowbackspace(Y);  //ֱ����������ɾ�в��� 
		}
		else {
			match1 = D->data;
			match1 += (x % 100 -1);
			*match1 = '\0';
		}
	}
	else {
		if (g == 0x53) {  //delete 
			match1 = D->data;
			match1 += x % 100;
			match2 = match1 + 1;
			*match1 = '\0';
			if (*match2 == '\0') return Rowdelete(R, x, Y, match1); //ɾ�����з�
			x++;
		}
	}
	return backcover(R, D, x, Y, match1);//xָ������һ���ַ�Ӧ���ڵ�λ��
}

void screen_bd(int ch,int x,int y) 
{
	char C = 'a';   //���ڼ���� 
 	C = Normal_bd(x, y, ch);
	Blockdelete();     //��Ҫ�������ļ���  
}


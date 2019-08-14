#include"struct.h"
int Whentostop( int Y , Row_node* R) 
{
	int b = 1;  //字符个数，具体下一个位置 
	int y = 0;  //行数，节点数的检索
	int flag = 0 , flag1=0;
	char* match;
	Data_node* D; //用于寻找字符和
	y = 0;
	if(R->right!=NULL) D = R->right; //进行行搜索 
	else return 0;
	while (D->right!=NULL) {
		D = D->right;
		b += 100;
		flag = 1;
	}
	if (!flag) b = 1; //只有一块
	match = D->data;
	while (b < MAX && *match != '\n') {
		if (*match == '\0'&&*(match+1)!='\0') {
			flag1 = 1;  //还在进行补位操作
		}
		match++;
		b++;
	}
	if (!flag1) {
		if (b < MAX&&*(match + 1) == '\0') b++; //在一行的结尾处判断
		if (b == MAX && R->down != NULL&&*match != '\n') return 2;  //这一行也满了，且不为结尾
		else if (*match == '\n') return 1;
		else if (b <= MAX&&R->down == NULL)return 0;   //到结尾了
	}
	else return -1;  //这一行还在进行补位
}

char backcover(Row_node* R, Data_node* D, int x, int Y, char* match1) 
{
	int flag1 = 0, flag2 = 0;
	char* match2;
	Data_node* D1;
	while (1) {
		if (x % 100 == 0 && D->right != NULL) {  //确定光标的后一个字符位置 （包括跨块前移） 
			D1 = D;
			D = D->right;
			match2 = D->data;
			if (*match2 != '\0') {
				*match1 = *match2;
				*match2 = '\0';
				flag1 = 1;
				x++;
			}
			else return '\0';  //相当于删除了结尾字符
		}
		else if (x % 100 == 0 && D->right == NULL) return '\0';
		else if (x % 100 != 0 && x<MAX) {
			if (flag1) {  //经过了跨块操作,或跨行操作
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
			x = 1;  //初值为
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
	int X = 0, Y = 0 ,flag=0;//判断字节的个数
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
	while (last->right != NULL) {   //最后一或二行的处理
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
	int y = 0;  //行数
	int x = 1, x1 = 0; //用于确定下一个字符的位置
	int flag = 2;
	Row_node* R = pData_stack, *R1;
	Data_node* D , *D1; //用于保留与比较用于确定上一行的结尾,用于确定行 
	Data_node* current_data = NULL;
	char* match1, *match2;
	while (y<Y) {  //确定行 
		if (y == Y - 1 || Y == 1) R1 = R; //确定他的上一行，上一行是第一行的情况
		R = R->down;
		y++;
	}
	if(Y!=0) D = R1->right; //第一行的第一位按退格
	else return '\0';
	match1 = D->data;
	while (1) {   //确定上一行的结尾match1
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
	D1 = D;  //继续保留上一行的结尾，后面可能还有用
	D = R->right;
	match2 = D->data;
	while (x <= MAX && (*match2 != '\0')) {  //退出条件，这行满了，或下一行不够，全部移上
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
	Y++;//backcover是下一行
	if (R->down == NULL) return '\0';
	else {
		R1 = R->down;
		D = R1->right;
		match2 = D->data;
		while (x < MAX && (*match2 != '\0')) {  //退出条件，这行满了，或下一行不够，全部移上
			*match1 = *match2;
			x++;
			*match2 = '\0';
			backcover(R1, D, 1 , Y , match2);
			if (x % 100 == 0 && x > 0) {
				while (D1->right != NULL) D1 = D1->right; //确定后接块
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
	int b, x;  //具体节点数，具体位置，字节总数。 
	int y = 0;  //行数，节点数的检索 
	char* match1=NULL , *match2=NULL;
	Row_node* R = pData_stack; 
	Data_node* D;
	x = X;
	b = X / 100;
	while (y<Y) {  //确定行 
		R = R->down;
		y++;
	}
	y = 0;
	D = R->right;
	while (y<b) {  //确定字节 
		D = D->right;
		y++;
	}
	if (g == 0x08) {  //backspace 
		if (X == 0) {
			return Rowbackspace(Y);  //直接跳到进行删行操作 
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
			if (*match2 == '\0') return Rowdelete(R, x, Y, match1); //删除换行符
			x++;
		}
	}
	return backcover(R, D, x, Y, match1);//x指的是下一个字符应该在的位置
}

void screen_bd(int ch,int x,int y) 
{
	char C = 'a';   //用于检测用 
 	C = Normal_bd(x, y, ch);
	Blockdelete();     //主要用于最后的检索  
}


#include"struct.h"
void Addchar(char ch,int x,int y)
{
	Row_node* pRow=NULL;
	Data_node* pData=NULL;
	Data_node* pNew=NULL;
	Row_node* pNewrow=NULL;
	Data_node* pChar=NULL;
	char cLast='\0';
	int i=0,j=0,k=0;
	if(pData_stack==NULL)
	{
		pData_stack=(Row_node*)malloc(sizeof(Row_node));
		pData_stack->down=NULL;
		pData_stack->right=NULL;
		pNew=(Data_node*)malloc(sizeof(Data_node));
		pNew->right=NULL;
		memset(pNew->data,'\0',100);
		pData_stack->right=pNew;
	}
	pRow=pData_stack;
	for(i=0;i<y;i++)
	{
		if(pRow->down==NULL)
		{
			pNewrow=(Row_node*)malloc(sizeof(Row_node));
			pNewrow->down=pRow->down;
			pNewrow->right=NULL;
			pRow->down=pNewrow;
			pNew=(Data_node*)malloc(sizeof(Data_node));
			pNew->right=NULL;
			memset(pNew->data,'\0',100);
			pNewrow->right=pNew;
		}
		pRow=pRow->down;
	}
	pData=pRow->right;
	for(i=0;i<x/100;i++)
	{
		if(pData->right==NULL)
		{
			pNew=(Data_node*)malloc(sizeof(Data_node));
			pNew->right=NULL;
			memset(pNew->data,'\0',100);
			pData->right=pNew;
		}
		pData=pData->right;
	}
	i=x%100;
	j=i;
	
	if(ch=='\r'||ch=='\n')
	{
		pChar=pData;
		k=x;
		while(pData!=NULL&&pData->data[j]!='\0')
		{
			Addchar('\0',k,y);
			if(j==99)
			{
				pData=pData->right;
				j=0;
			}
			else
			{
				j++;
			}
			k++;
		}
		pChar->data[i]='\n';
		pChar->right=NULL;
		return;
	}
	
	while(pData->data[j]!='\0'&&j<=99)
	{
		j++;
	}
	
	if(x/100<(MAX-1)/100)
	{
		if(j<=99)
		{
			while(j>i)
			{
				pData->data[j]=pData->data[j-1];
				j--;
			}
			pData->data[i]=ch;
		}
		else
		{
			j--;
			cLast=pData->data[j];
			while(j>i)
			{
				pData->data[j]=pData->data[j-1];
				j--;
			}
			pData->data[i]=ch;
			if(pData->right==NULL)
			{
				pNew=(Data_node*)malloc(sizeof(Data_node));
				pNew->right=NULL;
				memset(pNew->data,'\0',100);
				pData->right=pNew;
			}
			Addchar(cLast,(x/100+1)*100,y);			
		}
	}
	else
	{
		if(j<=(MAX-1)%100)
		{
			while(j>i)
			{
				pData->data[j]=pData->data[j-1];
				j--;
			}
			pData->data[i]=ch;			
		}
		else
		{
			j--;
			cLast=pData->data[j];
			while(j>i)
			{
				pData->data[j]=pData->data[j-1];
				j--;
			}
			pData->data[i]=ch;
			if(pRow->down==NULL)
			{
				pNewrow=(Row_node*)malloc(sizeof(Row_node));
				pNewrow->down=pRow->down;
				pNewrow->right=NULL;
				pRow->down=pNewrow;
				pNew=(Data_node*)malloc(sizeof(Data_node));
				pNew->right=NULL;
				memset(pNew->data,'\0',100);
				pNewrow->right=pNew;
			}
			Addchar(cLast,0,y+1);			
		}
	}
	return;
}


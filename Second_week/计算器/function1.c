#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"D:/qg作业/计算器/function1.h"
//把运算符对应到优先级表的索引 
int Char2Index(char ch)
{
	switch(ch)
	{
		case'+':return 0;
		case'-':return 1;
		case'*':return 2;
		case'/':return 3;
	}
}

//双目运算 若除数为0则返回0 
Status Calculate(ElemType a,ElemType b,char oprt,ElemType *ans)
{
	switch(oprt)
	{
		case'+':*ans=a+b;break;
		case'-':*ans=a-b;break;
		case'*':*ans=a*b;break;
		case'/':
			{
				if(fabs(b-0.0)<=1e-9)
				{
				 printf("除数不能为0\n");
				 return ERROR;
				}
				else *ans=a/b;
				break;
			}
	}
	return SUCCESS;
} 
int isError(char*c)
{
	int i,count40=0,count41=0;
	for(i=0;c[i];i++)
	{	if(!isdig(c[0])&&c[0]!=40&&c[0]!=41)return 1;
		if(!isdig(c[i])&&c[i]!=40&&c[i]!=41&&c[i]!='#'&&c[i]!='+'&&c[i]!='-'&&c[i]!='*'&&c[i]!='/')return 1;
		if(c[i]=='#'&&c[i+1]!=0)return 1;
		if(c[i]=='+'||c[i]=='-'||c[i]=='*'||c[i]=='/')
		  if(c[i+1]==0||c[i+1]=='+'||c[i+1]=='*'||c[i+1]=='/'||c[i+1]==41||c[i-1]==40&&c[i]!='-'||c[i+1]=='#')
		  return 1;
		  if(c[i]==40)count40++;
		  else if (c[i]==41)count41++;
		if(c[i]=='.')
		{
			int j;
			for(j=i+1;c[j];j++)
			{
				if(c[j]=='.')return 1;
				else if(!isdig(c[j]))break;
			}
		}
	
	}
	if(count40!=count41)return 1;
	if(c[i-1]!='#')return 1;
	return 0;
}

int isdig(char c)
{
	if(c>='0'&&c<='9'||c=='.')return 1;
	return 0;
}

 //得到栈顶元素
Status getTopLStack(LinkStack *s,ElemType *e) 
{	
	if(s==NULL)
	{
	 return ERROR;
	}
	if(s->count==0)
	{
		return ERROR; 
	}
	*e = s->top->data;
	return SUCCESS;
}

Status getTopOLStack(OLinkStack *s,char *e) 
{	
	if(s==NULL)
	{
	 return ERROR;
	}
	if(s->count==0)
	{
		return ERROR; 
	}
	*e = s->top->data;
	return SUCCESS;
}
//入栈
Status pushLStack(LinkStack *s,ElemType data) 
{
	if(s==NULL)
	{
	 return ERROR;
	}
	StackNode*p = (StackNode*)malloc(sizeof(StackNode));
	p->next = s->top;p->data=data;
	s->top=p;s->count++;
	return SUCCESS;
}
Status pushOLStack(OLinkStack *s,char data) 
{
	if(s==NULL)
	{
	 return ERROR;
	}
	OStackNode*p = (OStackNode*)malloc(sizeof(OStackNode));
	p->next = s->top;p->data=data;
	s->top=p;s->count++;
	return SUCCESS;
}

//出栈
Status popLStack(LinkStack *s,ElemType *data)   
{
	if(s==NULL)
	{
	 return ERROR;
	}
	if(s->count==0)
	{
		return ERROR; 
	}
	StackNode *p = s->top;
	*data=p->data;
	s->top = s->top->next;
	free(p);
	s->count--;
}
Status popOLStack(OLinkStack *s,char *data)   
{
	if(s==NULL)
	{
	 return ERROR;
	}
	if(s->count==0)
	{
		return ERROR; 
	}
	OStackNode *p = s->top;
	*data=p->data;
	s->top = s->top->next;
	free(p);
	s->count--;
}


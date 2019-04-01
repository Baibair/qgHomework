#include <stdio.h>
#include <stdlib.h>
#include"D:/qg作业/计算器/function1.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*
40-> '('    41->')'    pOer->操作符栈指针    pnum->操作数栈指针 
flag1->该数前有负号  flag2->该数有小数点 

*/ 				//利用二维数组构建优先级比较表
int main(int argc, char *argv[]) 
{				// + - *  /
	int cmp[4][4]={0,0,-1,-1,// +
				   0,0,-1,-1,// -
				   1,1,0,0,// *
				   1,1,0,0};// /
	char question[20];
				   
	LinkStack numStack = {NULL,0};double num = 0,term = 1;
	LinkStack *pnum = &numStack;int flag1=0,flag2=0,i;
	OLinkStack Oper = {NULL,0};
	OLinkStack *pOper = &Oper;
	while(1)
{
	printf("请输入要计算的表达式,末尾加#\n");
	scanf("%s",question);
	while(isError(question))
	{
		printf("输入错误\n");
		printf("请输入要计算的表达式，末尾加#\n");
		scanf("%s",question);
	}
	
	
	for( i=0;question[i];i++)
	{
		if(question[i]=='-'&&(i==0||i>0&&!isdig(question[i-1])))//区分负号和减号 
		{
			flag1=1;
			continue;
		}
		
		if(isdig(question[i])&&question[i]!='.')
		num=10*num+question[i]-'0';
		
		if(flag2&&isdig(question[i]))term*=10;
		if(question[i]=='.')flag2=1;
			
		if(!isdig(question[i]))
			{	
				if(i>0&&isdig(question[i-1])&&!isdig(question[i]))
			  {							
				flag1?pushLStack(pnum,-num/term):pushLStack(pnum,num/term);
				flag1=flag2=0;term=1;
				num=0;
			  }
				if(question[i]==40)pushOLStack(pOper,question[i]);
				else if(pOper->count==0)pushOLStack(pOper,question[i]);
				else if(question[i]==41)
				{
					char opertop;
					getTopOLStack(pOper,&opertop);
					while(opertop!=40)
					{
						popOLStack(pOper,&opertop);
						ElemType a,b,c;
						popLStack(pnum,&b);
						popLStack(pnum,&a);
						if(Calculate(a,b,opertop,&c)==ERROR)
							{
								system("pause");
								return 0;
							}
						 pushLStack(pnum,c); 
						 getTopOLStack(pOper,&opertop);	
					}
					popOLStack(pOper,&opertop);					
				}
				else if(question[i]!='#')//除了结尾的其他情况 
				{
					char opertop;
					getTopOLStack(pOper,&opertop);
					while(opertop!=40&&cmp[ Char2Index(opertop) ][ Char2Index(question[i]) ] ==1&&pOper->count>0)
					{
						popOLStack(pOper,&opertop);//若操作符栈顶元素优先级大于改操作符 出栈立即计算再入操作数栈 
						ElemType a,b,c;
						popLStack(pnum,&b);
						popLStack(pnum,&a);
						if(Calculate(a,b,opertop,&c)==ERROR)
							{
								system("pause");
								return 0;
							} 
						pushLStack(pnum,c);
						getTopOLStack(pOper,&opertop);
					}
					pushOLStack(pOper,question[i]);
				}
			}
	}
	 char opertop;
	while(pOper->count>0)//把运算符栈全部出栈 
	{	char ch;getTopOLStack(pOper,&ch);
		if(ch=='#'&&pOper->count==1)break;
		popOLStack(pOper,&opertop);
						ElemType a,b,c;
						popLStack(pnum,&b);
						popLStack(pnum,&a);
						if(Calculate(a,b,opertop,&c)==ERROR)
							{
								system("pause");
								return 0;
							} 
						pushLStack(pnum,c);
	}
	ElemType ans;popLStack(pnum,&ans);
	printf("The answer is %lf\n",ans);
}
	return 0;
}

#ifndef _function1_h
#define _function1_h

typedef enum Status
{
	ERROR=0,
	SUCCESS=1
}Status;

typedef double ElemType;

typedef  struct StackNode
{
	ElemType data;
	struct StackNode *next;
}StackNode, *LinkStackPtr;

typedef  struct OStackNode
{
	char data;
	struct OStackNode *next;
}OStackNode, *OLinkStackPtr;



typedef  struct  LinkStack{
	LinkStackPtr top;
	int	count;
}LinkStack;

typedef  struct  OLinkStack{
	OLinkStackPtr top;
	int	count;
}OLinkStack;



int Char2Index(char ch);
Status Calculate(ElemType a,ElemType b,char oprt,ElemType *ans);
int isError(char *c);
int isdig(char c);
Status getTopLStack(LinkStack *s,ElemType *e);
Status pushLStack(LinkStack *s,ElemType data);
Status popLStack(LinkStack *s,ElemType *data);
Status getTopOLStack(OLinkStack *s,char *e);
Status pushOLStack(OLinkStack *s,char data);
Status popOLStack(OLinkStack *s,char *data);

#endif

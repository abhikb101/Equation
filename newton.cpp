/*
the program works in the following way:
it contains a class ex which is used for creating individual expressions:
	data members:
	1)fn is used for storing coefficient and power/coeff. of angle
	2)type is used to store the type of expression
	3)exp to save +,-
	member functions:
	1)input  : for storing the expression
	2)print  : for displaying the expression
	3)dvt    : for finding the derivative of the expression
	4)solve  : for solving for any value of  x
	5)tp & ch: returns the type and exp
	6)md     : chnages exp
the program inputs any equation using a linked list of epressions and the finding its derivative
functions:
pt :used for printing equation
fx :used for input of equation
dt :used for derivative of equation
sol:used for solving the equation for given value of x

the program uses newton method for finding the solution
newton method uses any random value of x, preferable if near solution
and the moves towards the solution by a jump of h
h=f(x)/f`(x)
this is done untill h starts repeating its value or f(x)-->0 i.e. h<<<<0
*/
#include<iostream.h>
#include<conio.h>
#include<iomanip.h>
#include<math.h>
class ex
{
	private:
	double fn[2][2];
	char type[2],exp[2];
	public:
	ex* next;
	char input()
	{
		cin>>fn[0][0]>>type[0]>>fn[0][1]>>exp[0];
		if(type[0]=='y')
			type[0]='x';
		return exp[0];
	}
	void mod(char i)
	{
		exp[1]=i;
	}
	char print(double i)
	{
		cout<<fn[i][0]<<type[i]<<fn[i][1]<<" "<<exp[i]<<" ";
		return exp[i];
	}
	char ch(double i)
	{
		return exp[i];
	}
	char tp()
	{
		return type[0];
	}

	void dvt()
	{
		exp[1]=exp[0];
		fn[1][0]=fn[0][0]*fn[0][1];
		fn[1][1]=fn[0][1];
		type[1]=type[0];
		if(type[0]=='x')
		{
			fn[1][1]=fn[0][1]-1;
		}
		else if(type[0]=='s')
		{
			type[1]='c';
		}
		else if(type[0]=='c')
		{
			type[1]='s';
		}
		else if(type[0]=='e');
	}
	double solve(double x, double i)
	{
		       if(type[0]=='x')
		       {
			    if(x==0)
			     return 0;
			    else
			    {	if(fn[i][1]==0)
					return fn[i][0];
				else if(fn[i][1]<0)
					return fn[i][0]*1/pow(x,fn[i][1]);
				else
					return fn[i][0]*pow(x,fn[i][1]);
			     }
		       }
		       else if(type[i]=='s')
		       {
			    return fn[i][0]*sin(fn[i][1]*x);
		       }
		       else if(type[i]=='c')
		       {
			    return fn[i][0]*cos(fn[i][1]*x);
		       }
		      else if(type[0]=='e')
		      {
				return pow(2.718,fn[i][1])*fn[i][0];
		       }
		       return 0;
	}

};
ex* fx(ex* n)
{
	ex* nd;
	n=nd=new ex;
	char expn;
	while(expn!='.')
	{
		expn=nd->input();
		nd->next=new ex;
		nd=nd->next;
	}
	return n;
}
void pt(ex* n)
{
	ex* nd;
	nd=n;
	char expn;
	expn=n->ch(0);
	do
	{
		expn=nd->print(0);
		nd=nd->next;
	}while(expn!='.');
}
void dt(ex* n)
{
	ex* nd;
	ex* c;
	nd=n;
	char expn;
	do
	{
		c=nd->next;
		nd->dvt();
		if(expn!='.')
			if(c->tp()=='c')
			    {
				if(nd->ch(0)=='+')
					nd->mod('-');
				else if(nd->ch(0)=='-')
					nd->mod('+');
			    }

		expn=nd->print(1);
		nd=nd->next;
	}while(expn!='.');
}
double sol(ex* n, double x, double i)
{
	char expn;
	expn=n->ch(i);
	if(expn=='+')
		return n->solve(x,i)+sol(n->next,x,i);
	else if(expn=='-')
		return n->solve(x,i)-sol(n->next,x,i);
	else if(expn=='.')
		return n->solve(x,i);
	return 0;
}
void newton(ex* n)
{
	double x0=3,h=1;
	double flag;
	h=sol(n,x0,0)/sol(n,x0,1);
	do
	{       h=h/pow(10,4);
		flag=h;
		h=sol(n,x0,0)/sol(n,x0,1);
		x0=x0-h;
		if(flag==h)
			break;
		h=h*pow(10,4);
	}while(abs(h)>0.01);
	cout<<"Ans found"<<x0<<"::"<<sol(n,x0,0);

}
void main()
{
	clrscr();
	ex* n;
	cout<<"Enter the exp:";
	n=fx(n);
	pt(n);
	cout<<"\n";
	dt(n);
	cout<<sol(n,2,0)<<":"<<sol(n,2,1)<<endl;
	newton(n);
	getch();

}

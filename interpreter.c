#include <stdio.h>
#include <math.h>
#include "calc3.h"
#include "calc3.tab.h"
#define pi 3.141592654

int tag[26] = {0};

double factorial(double num)
{
	if (num == 0 || num == 1)
		return 1;
	else
		return num * factorial(num-1);
}

void ftob(double a)
{
	long b = (long)a;
	int neg_flag = 0;
	if (a < 0)
	{
		b *= -1;
		neg_flag = 1;
	}
	int c[32];
	char d[32];
	int i, j;
	for (i = 0; b > 0; i++, b /= 2)
		c[i] = b % 2;
	i--;
	for (j = 0;i >= 0; i--,j++)
	{
		if (c[i] == 1) d[j] = '1';
		else d[j] = '0';
	}
	d[j] = '\0';
	if (neg_flag)
		printf("-bx%-32s", d);
	else
		printf("bx%-33s", d);
}

void ftoo(double a)
{
	long b = (long)a;
	int neg_flag = 0;
	if (a < 0)
	{
		b *= -1;
		neg_flag = 1;
	}
	int c[12];
	char d[12];
	int i, j;
	for (i = 0; b > 0; i++, b /= 8)
		c[i] = b % 8;
	i--;
	for (j = 0;i >= 0; i--,j++)
	{
		switch (c[i])
		{
			case 0:	d[j] = '0'; break;
			case 1:	d[j] = '1'; break;
			case 2:	d[j] = '2'; break;
			case 3:	d[j] = '3'; break;
			case 4:	d[j] = '4'; break;
			case 5:	d[j] = '5'; break;
			case 6:	d[j] = '6'; break;
			case 7:	d[j] = '7'; break;
		}
	}
	d[j] = '\0';
	if (neg_flag)
		printf("-ox%-12s", d);
	else
		printf("ox%-13s", d);
}

void ftoh(double a)
{
	long b = (long)a;
	int neg_flag = 0;
	if (a < 0)
	{
		b *= -1;
		neg_flag = 1;
	}
	int c[8];
	char d[8];
	int i, j;
	for (i = 0; b > 0; i++, b /= 16)
		c[i] = b % 16;
	i--;
	for (j = 0;i >= 0; i--,j++)
	{
		switch (c[i])
		{
			case 0:	d[j] = '0'; break;
			case 1:	d[j] = '1'; break;
			case 2:	d[j] = '2'; break;
			case 3:	d[j] = '3'; break;
			case 4:	d[j] = '4'; break;
			case 5:	d[j] = '5'; break;
			case 6:	d[j] = '6'; break;
			case 7:	d[j] = '7'; break;
			case 8:	d[j] = '8'; break;
			case 9:	d[j] = '9'; break;
			case 10: d[j] = 'A'; break;
			case 11: d[j] = 'B'; break;
			case 12: d[j] = 'C'; break;
			case 13: d[j] = 'D'; break;
			case 14: d[j] = 'E'; break;
			case 15: d[j] = 'F'; break;
		}
	}
	d[j] = '\0';
	if (neg_flag)
		printf("-hx%-8s", d);
	else
		printf("hx%-9s", d);
}

void printall(void)
{
	int i, flag = 1;
	printf("\tOutput:\n");
	for (i = 0; i < 26; i++)
	{
		if (tag[i] == 1)
		{
			printf("\t\t%c = %lf\n", 'a' + i, sym[i]);
			flag = 0;
		}
	}
	if (flag)
		printf("\t\tNo data found\n");
}

void printallf(void)
{
	int i, flag = 1;
	printf("\tOutput:\n");
	for (i = 0; i < 26; i++)
	{
		if (tag[i] == 1)
		{
			printf("\t%c = %-10.2lf", 'a' + i, sym[i]);
			printf(" "); ftoh(sym[i]);
			printf(" "); ftoo(sym[i]);
			printf(" "); ftob(sym[i]);
			printf("\n");
			flag = 0;
		}
			
	}
	if (flag)
		printf("\t\tNo data\n");
}

void reset(void)
{
	int i;
	for (i = 0; i < 26; i++)
	{
		sym[i] = 0;
		tag[i] = 0;
	}
}

double cube(double num)
{
	return num * num * num;
}

double ex(nodeType *p)
{
	if (!p) return 0;
	switch (p->type)
	{
		case typeCon:		return p->con.value;
		case typeId:		return sym[p->id.i];
		case typeOpr:
		switch (p->opr.oper)
		{
			case WHILE:		while(ex(p->opr.op[0]))
								ex(p->opr.op[1]);
							return 0;
			case IF:		if (ex(p->opr.op[0]))
								ex(p->opr.op[1]);
							else if (p->opr.nops > 2)
								ex(p->opr.op[2]);
							return 0;
			case PRINT:		printf("\t\tOutput: %lf\n", ex(p->opr.op[0]));
							return 0;
			case V:			printallf();
							return 0;
			case W:			printall();
							return 0;
			case X:			printf("\t\tOutput: ");
							ftob(ex(p->opr.op[0]));
							printf("\n");
							return 0;
			case Y:			printf("\t\tOutput: ");
							ftoo(ex(p->opr.op[0]));
							printf("\n");
							return 0;
			case Z:			printf("\t\tOutput: ");
							ftoh(ex(p->opr.op[0]));
							printf("\n");
							return 0;
			case RESET:		reset();
							printf("\t\tAll varaibles cleared\n");
							return 0;
			case ABS:		if (ex(p->opr.op[0]) >= 0)
								return ex(p->opr.op[0]);
							else
								return -ex((p->opr.op[0]));
			case SIN:		return sin(ex(p->opr.op[0]) * pi / 180);
			case COS:		return cos(ex(p->opr.op[0]) * pi / 180);
			case TAN:		return tan(ex(p->opr.op[0]) * pi / 180);
			case ';':		ex(p->opr.op[0]);
							return ex(p->opr.op[1]);
			case '=':		tag[p->opr.op[0]->id.i] = 1;
							return sym[p->opr.op[0]->id.i] = ex(p->opr.op[1]);
			case UMINUS:	return -ex(p->opr.op[0]);
			case '+':		return ex(p->opr.op[0]) + ex(p->opr.op[1]);
			case '-':		return ex(p->opr.op[0]) - ex(p->opr.op[1]);
			case '*':		return ex(p->opr.op[0]) * ex(p->opr.op[1]);
			case '/':		if (ex(p->opr.op[1]) == 0)
							{
								printf("\t\tError: Connot divide by 0\n");
								return 0;
							}
							else
								return ex(p->opr.op[0]) / ex(p->opr.op[1]);
			case '<':		return ex(p->opr.op[0]) < ex(p->opr.op[1]);
			case '>':		return ex(p->opr.op[0]) > ex(p->opr.op[1]);
			case GE:		return ex(p->opr.op[0]) >= ex(p->opr.op[1]);
			case LE:		return ex(p->opr.op[0]) <= ex(p->opr.op[1]);
			case NE:		return ex(p->opr.op[0]) != ex(p->opr.op[1]);
			case EQ:		return ex(p->opr.op[0]) == ex(p->opr.op[1]);
			case '!':		if (ex(p->opr.op[0]) - (int)ex(p->opr.op[0]) != 0)
							{
								printf("\t\tError: Must be an integer\n");
								return 0;
							}
							else
								return factorial(ex(p->opr.op[0]));
			case POW:		return pow(ex(p->opr.op[0]),ex(p->opr.op[1]));
			case MOD:		if ((ex(p->opr.op[0]) - (int)ex(p->opr.op[0]) != 0) ||
								(ex(p->opr.op[1]) - (int)ex(p->opr.op[1]) != 0))
							{
								printf("\t\tError: Operand must be an integer\n");
								return 0;
							}
							else
								return ((int)(ex(p->opr.op[0])) % ((int)ex(p->opr.op[1])));
			case EXP:		return exp(ex(p->opr.op[0]));
			case LOG:		if (ex(p->opr.op[0]) <= 0)
							{
								printf("\t\tError: Must be a positive number\n");
								return 0;
							}
							else
								return log10(ex(p->opr.op[0]));
			case LN:		if (ex(p->opr.op[0]) <= 0)
							{
								printf("\t\tError: Must be a positive number\n");
								return 0;
							}
							else
								return log(ex(p->opr.op[0]));
			case SQRT:		if (ex(p->opr.op[0]) < 0)
							{
								printf("\t\tError: Must be a non-negative number\n");
								return 0;
							}
							else
								return sqrt(ex(p->opr.op[0]));
			case CUBE:		return cube(ex(p->opr.op[0]));
			case INCR:		return ex(p->opr.op[0]) + 1;
			case DECR:		return ex(p->opr.op[0]) - 1;
			case CEIL:		return ceil(ex(p->opr.op[0]));
			case FLOOR:		return floor(ex(p->opr.op[0]));
		}
	}
	return 0;
}


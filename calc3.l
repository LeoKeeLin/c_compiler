%{
	#include <stdlib.h>
	#include <string.h>
	#include "calc3.h"
	#include "calc3.tab.h"
	#define MAX 2147483647
	#define MIN -2147483648
	void yyerror(char *);
	int check_overflow(double);
	double btof(char [], int);
	double otof(char [], int);
	double htof(char [], int);
	double value;
	int size;

%}


%%

[a-z]		{
				yylval.sIndex = *yytext - 'a';
				return VARIABLE;
			}

0			{
				yylval.iValue = atof(yytext);
				return DOUBLE;
			}

[0-9]+(\.[0-9]+)?	{
				size = strlen(yytext);
				value = atof(yytext);
				if (check_overflow(value))
					yylval.iValue = value;
				else
				{
					yylval.iValue = 0;
					yyerror("\t\tWarning: Overflow, value ignored");
				}
				return DOUBLE;
			}

PI 			{
				yylval.iValue = 3.141592654;
				return DOUBLE;
			}

E 			{
				yylval.iValue = 2.718281828;
				return DOUBLE;
			}

b(0|1)+		{
				size = strlen(yytext);
				value = btof(yytext, size);
				if (check_overflow(value))
					yylval.iValue = value;
				else
				{
					yylval.iValue = 0;
					yyerror("\t\tWarning: Overflow, value ignored");
				}
				return DOUBLE;
			}

o[0-7]+		{
				size = strlen(yytext);
				value = otof(yytext, size);
				if (check_overflow(value))
					yylval.iValue = value;
				else
				{
					yylval.iValue = 0;
					yyerror("\t\tWarning: Overflow, value ignored");
				}
				return DOUBLE;
			}

h[0-9A-F]+	{
				size = strlen(yytext);
				value = htof(yytext, size);
				if (check_overflow(value))
					yylval.iValue = value;
				else
				{
					yylval.iValue = 0;
					yyerror("\t\tWarning: Overflow, value ignored");
				}
				return DOUBLE;
			}

"++"   				return INCR;
"--"				return DECR;

[-()<>=+*/!;{}.]	return *yytext;

">="				return GE;
"<="				return LE;
"=="				return EQ;
"!="				return NE;
"while"				return WHILE;
"if"				return IF;
"else"				return ELSE;
"print"				return PRINT;
"abs"				return ABS;
"exit"				return EXIT;
"sin"				return SIN;
"cos"				return COS;
"tan"				return TAN;
"print_all"			return W;
"print_bin"			return X;
"print_oct"			return Y;
"print_hex"			return Z;
"print_allf"		return V;
"reset"				return RESET;
"sqrt"|"SQRT"       return SQRT;
"^"					return POW;
"%"					return MOD;
"exp"|"EXP"			return EXP;
"cube"				return CUBE;
"log"|"LOG" 		return LOG;
"ln"|"LN"  			return LN;
"ceil"				return CEIL;
"floor"				return FLOOR;

[ \t\n]+			;	/* ignore whitespace */

.					yyerror("\t\tWarning: Unknown character");

%%

double btof(char c[], int s)
{
	int i, j;
	double temp = 1;
	double result = 0;
	for (i = s-2; i >= 0; i--)
	{
		if (c[s-i-1] == '1')
		{
			for (j = 0; j < i; j++) temp *= 2;
			result += temp;
			temp = 1;
		}
	}
	return result;
}

double otof(char c[], int s)
{
	int i, j, k;
	double temp = 1;
	double result = 0;
	for (i = s-2; i >= 0; i--)
	{
		switch (c[s-i-1])
		{
			case '0':	k = 0; break;
			case '1':	k = 1; break;
			case '2':	k = 2; break;
			case '3':	k = 3; break;
			case '4':	k = 4; break;
			case '5':	k = 5; break;
			case '6':	k = 6; break;
			case '7':	k = 7; break;
			default: break;
		}
		for (j = 0; j < i; j++) temp *= 8;
		result += k * temp;
		temp = 1;
	}
	return result;
}

double htof(char c[], int s)
{
	int i, j, k;
	double temp = 1;
	double result = 0;
	for (i = s-2; i >= 0; i--)
	{
		switch (c[s-i-1])
		{
			case '0':	k = 0; break;
			case '1':	k = 1; break;
			case '2':	k = 2; break;
			case '3':	k = 3; break;
			case '4':	k = 4; break;
			case '5':	k = 5; break;
			case '6':	k = 6; break;
			case '7':	k = 7; break;
			case '8':	k = 8; break;
			case '9':	k = 9; break;
			case 'A':	k = 10; break;
			case 'B':	k = 11; break;
			case 'C':	k = 12; break;
			case 'D':	k = 13; break;
			case 'E':	k = 14; break;
			case 'F':	k = 15; break;
			default: break;
		}
		for (j = 0; j < i; j++) temp *= 16;
		result += k * temp;
		temp = 1;
	}
	return result;
}

int check_overflow(double a)
{
	if (a > MAX || a < MIN)
		return 0;
	else
		return 1;
}

int yywrap(void)
{
	return 1;
}
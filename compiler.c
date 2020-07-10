#include <stdio.h>
#include "calc3.h"
#include "calc3.tab.h"

static int lbl;

double ex(nodeType *p)
{
	int lbl1, lbl2;

	if (!p) return 0;
	switch (p->type)
	{ 
		case typeCon:		printf("\tpush\t%lf\n", p->con.value);
							break;
		case typeId:		printf("\tpush\t%c\n", p->id.i + 'a');
							break;
		case typeOpr:
		switch(p->opr.oper)
		{ 
			case WHILE:
				printf("L%03d:\n", lbl1 = lbl++);
				ex(p->opr.op[0]);
				printf("\tjz\tL%03d\n", lbl2 = lbl++);
				ex(p->opr.op[1]);
				printf("\tjmp\tL%03d\n", lbl1);
				printf("L%03d:\n", lbl2);
				break;
			case IF:
				ex(p->opr.op[0]);
				if (p->opr.nops > 2)
				{
					/* if else */
					printf("\tjz\tL%03d\n", lbl1 = lbl++);
					ex(p->opr.op[1]);
					printf("\tjmp\tL%03d\n", lbl2 = lbl++);
					printf("L%03d:\n", lbl1);
					ex(p->opr.op[2]);
					printf("L%03d:\n", lbl2);
				}
				else
				{
					/* if */
					printf("\tjz\tL%03d\n", lbl1 = lbl++);
					ex(p->opr.op[1]);
					printf("L%03d:\n", lbl1);
				}
				break;
			case PRINT:
				ex(p->opr.op[0]);
				printf("\tprint\n");
				break;
			case V:
				printf("\tprint_all\n");
				break;
			case W:
				printf("\tprint_all_form\n");
				break;
			case X:
				ex(p->opr.op[0]);
				printf("\tprint_bin\n");
				break;
			case Y:
				ex(p->opr.op[0]);
				printf("\tprint_oct\n");
				break;
			case Z:
				ex(p->opr.op[0]);
				printf("\tprint_hex\n");
				break;
			case RESET:
				printf("\tAll varaibles cleared\n");
				break;
			case ABS:
				ex(p->opr.op[0]);
				printf("\tABS\n");
				break;
			case SIN:
				ex(p->opr.op[0]);
				printf("\tSIN\n");
				break;
			case COS:
				ex(p->opr.op[0]);
				printf("\tCOS\n");
				break;
			case TAN:
				ex(p->opr.op[0]);
				printf("\tTAN\n");
				break;
			case '=':
				ex(p->opr.op[1]);
				printf("\tpop\t%c\n", p->opr.op[0]->id.i + 'a');
				break;
			case UMINUS:
				ex(p->opr.op[0]);
				printf("\tneg\n");
				break;
			case '!':
				ex(p->opr.op[0]);
				printf("\tfactorial\n");
				break;
			case EXP:
				ex(p->opr.op[0]);
				printf("\tEXP\n");
				break;
			case SQRT:
				ex(p->opr.op[0]);
				printf("\tSQRT\n");
				break;
			case CUBE:
				ex(p->opr.op[0]);
				printf("\tCUBE\n");
				break;
			case LOG:
				ex(p->opr.op[0]);
				printf("\tLOG\n");
				break;
			case LN:
				ex(p->opr.op[0]);
				printf("\tLN\n");
				break;
			case INCR:
				ex(p->opr.op[0]);
				printf("\tpush\t%lf\n", 1.0);
				printf("\tadd\n");
				break;
			case DECR:
				ex(p->opr.op[0]);
				printf("\tpush\t%lf\n", 1.0);
				printf("\tsub\n");
				break;
			case CEIL:
				ex(p->opr.op[0]);
				printf("\tCEIL\n");
				break;
			case FLOOR:
				ex(p->opr.op[0]);
				printf("\tFLOOR\n");
				break;
			default:
				ex(p->opr.op[0]);
				ex(p->opr.op[1]);
				switch (p->opr.oper)
				{
					case '+':	printf("\tadd\n"); break;
					case '-':	printf("\tsub\n"); break;
					case '*':	printf("\tmul\n"); break;
					case '/':	printf("\tdiv\n"); break;
					case '<':	printf("\tcompLT\n"); break;
					case '>':	printf("\tcompGT\n"); break;
					case GE:	printf("\tcompGE\n"); break;
					case LE:	printf("\tcompLE\n"); break;
					case NE:	printf("\tcompNE\n"); break;
					case EQ:	printf("\tcompEQ\n"); break;
					case POW:	printf("\tpow\n"); break;
					case MOD:	printf("\tmod\n"); break;
				}
		}
	} 
	return 0;
}
         
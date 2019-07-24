#include	<stdio.h>
#include	<stdlib.h>
#include	"define.h"
#include	"scanner.h"
#include	"parser.h"
#include	"error.h"

/* 次の字句を先読みするための変数 */
static token_t	nextsym;

static int
parse_term(void);

static int
parse_number(void);

void
parser_init(void)
{
	nextsym = scanner_get_next_sym();
}

/* E ::= T { ( + | - ) T } ; */
int
parser_parse_expression(void)
{
	int		r = 0;
	int 	s;
	int 	mp_value = 1; // 1 == plus, -1 == minus
	int s_n;
	fprintf(stderr, "PUSHI 0\n");

	while (nextsym.sym != SYM_SEMICOLON && nextsym.sym != SYM_RPAREN){
		if (nextsym.sym == SYM_PLUS){
			nextsym = scanner_get_next_sym();
		} else if (nextsym.sym == SYM_MINUS){
			nextsym = scanner_get_next_sym();
			mp_value *= -1;
		}else{
			printf("( ");
			s = parse_term();
			while (nextsym.sym == SYM_ASTERISK || nextsym.sym == SYM_SLASH  || nextsym.sym == SYM_CONSTANT_INT ){
				if (nextsym.sym == SYM_ASTERISK){
					nextsym = scanner_get_next_sym();
					printf("* ");
					s_n = parse_term();
					s *= s_n;
					fprintf(stderr, "MUL\n");
				} else if (nextsym.sym == SYM_SLASH){
					nextsym = scanner_get_next_sym();
					printf("/ ");
					s /= parse_term();
					fprintf(stderr, "DIV\n");
				}
			}
			printf(") ");
			printf("+ (? %d) ",mp_value);
			r += mp_value * s;
			mp_value = 1;
			fprintf(stderr, "ADD\n");
		}
	}

	return (r);
}

/* T ::= N */
int
parse_term(void)
{
	int	r;

	r = parse_number();
	return (r);
}

int
parse_number(void)
{
	int	r;

	if (nextsym.sym == SYM_CONSTANT_INT){
		r = nextsym.integer;
		printf("%d ",r);
		fprintf(stderr, "PUSHI %d\n",r);
		nextsym = scanner_get_next_sym();
	}else if (nextsym.sym == SYM_LPAREN){
		nextsym = scanner_get_next_sym();
		printf("[ ");
		r = parser_parse_expression();
		printf("] ");
		nextsym = scanner_get_next_sym();
	}else{
		ERROR("<N> が必要です");
	}
	return (r);
}


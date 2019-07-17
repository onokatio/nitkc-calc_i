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

	while (nextsym.sym != SYM_SEMICOLON && nextsym.sym != SYM_RPAREN){
		if (nextsym.sym == SYM_PLUS){
			nextsym = scanner_get_next_sym();
		} else if (nextsym.sym == SYM_MINUS){
			nextsym = scanner_get_next_sym();
			mp_value *= -1;
		}else{
			s = parse_term();
			while (nextsym.sym == SYM_ASTERISK || nextsym.sym == SYM_SLASH  || nextsym.sym == SYM_CONSTANT_INT ){
				if (nextsym.sym == SYM_ASTERISK){
					nextsym = scanner_get_next_sym();
					s *= parse_term();
				} else if (nextsym.sym == SYM_SLASH){
					nextsym = scanner_get_next_sym();
					s /= parse_term();
				}
			}
			r += mp_value * s;
			mp_value = 1;
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
		nextsym = scanner_get_next_sym();
	}else if (nextsym.sym == SYM_LPAREN){
		nextsym = scanner_get_next_sym();
		r = parser_parse_expression();
		nextsym = scanner_get_next_sym();
	}else{
		ERROR("<N> が必要です");
	}
	return (r);
}


#include	<stdio.h>
#include	"define.h"
#include	"scanner.h"
#include	"parser.h"

int main(void)
{
	printf("式: ");
	scanner_init(stdin);
	parser_init();

	fprintf(stderr, "        .globl main\n");
	fprintf(stderr, "        .type main @function\n");
	fprintf(stderr, "main:\n");
	fprintf(stderr, "        pushq %rbp\n");
	fprintf(stderr, "        movq %rsp, %rbp\n");
	printf("答え: %d\n",parser_parse_expression());
	fprintf(stderr, "        popq %rax\n");
	fprintf(stderr, "        popq %rbp\n");
	fprintf(stderr, "        ret\n");
	return 0;
}

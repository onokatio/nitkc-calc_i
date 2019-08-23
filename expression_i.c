#include	<stdio.h>
#include	"define.h"
#include	"scanner.h"
#include	"parser.h"

int main(void)
{
	printf("式: ");
	scanner_init(stdin);
	parser_init();

	fprintf(stderr, "        .text\n");
	fprintf(stderr, "        .global func\n");
	fprintf(stderr, "        .type func,@function\n");
	fprintf(stderr, "func:\n");
	fprintf(stderr, "        r5 = r10\n");
	printf("答え: %d\n",parser_parse_expression());
	fprintf(stderr, "        r1 = *(u32 *)(r5 - 0)\n");
	fprintf(stderr, "        exit\n");
	fprintf(stderr, ".Lfunc_end0:\n");
        fprintf(stderr, ".size   func, .Lfunc_end0-func\n");
        fprintf(stderr, ".section        .BTF,\"\",@progbits\n");
        fprintf(stderr, ".short  60319\n");
        fprintf(stderr, ".byte   1\n");
        fprintf(stderr, ".byte   0\n");
        fprintf(stderr, "        .long   24\n");
        fprintf(stderr, "        .long   0\n");
        fprintf(stderr, "        .long   0\n");
        fprintf(stderr, "        .long   0\n");
        fprintf(stderr, "        .long   1\n");
        fprintf(stderr, ".byte   0\n");
        fprintf(stderr, ".section        .BTF.ext,\"\",@progbits\n");
        fprintf(stderr, ".short  60319\n");
        fprintf(stderr, ".byte   1\n");
        fprintf(stderr, ".byte   0\n");
        fprintf(stderr, "        .long   24\n");
        fprintf(stderr, "        .long   0\n");
        fprintf(stderr, "        .long   4\n");
        fprintf(stderr, "        .long   4\n");
        fprintf(stderr, "        .long   4\n");
        fprintf(stderr, "        .long   8\n");
        fprintf(stderr, "        .long   16\n");
        fprintf(stderr, ".addrsig\n");

	return 0;
}

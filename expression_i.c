#include	<stdio.h>
#include	"define.h"
#include	"scanner.h"
#include	"parser.h"

main(void)
{
	printf("式: ");
	scanner_init(stdin);
	parser_init();

	fprintf(stderr, "main:\n");
	fprintf(stderr, "ENTER\n");
	printf("答え: %d\n",parser_parse_expression());
	fprintf(stderr, "WR\n");
	fprintf(stderr, "WRLN\n");
	fprintf(stderr, "LEAVE\n");
	fprintf(stderr, "RET\n");
}

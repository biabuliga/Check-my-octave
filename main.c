#include <stdio.h>
#include <stdlib.h>
#include "memory_matrix.h"

int main(void)
{
	matrix_t *colectie = NULL;
	int nr = 0;
	char cmd;

	while (1) {
		if (scanf(" %c", &cmd) != 1)
			break;

		if (cmd == 'Q') {
			cmd_quit(&colectie, &nr);
			break;
		} else if (cmd == 'L') {
			cmd_load(&colectie, &nr);
		} else if (cmd == 'P') {
			cmd_print(colectie, nr);
		} else if (cmd == 'D') {
			cmd_dim(colectie, nr);
		} else if (cmd == 'T') {
			cmd_transpose(colectie, nr);
		} else if (cmd == 'M') {
			cmd_multiply(&colectie, &nr);
		} else if (cmd == 'F') {
			cmd_free(&colectie, &nr);
		} else if (cmd == 'O') {
			cmd_sort(colectie, nr);
		} else if (cmd == 'C') {
			cmd_crop(colectie, nr);
		} else if (cmd == 'S') {
			int indx1, indx2;
			scanf("%d %d", &indx1, &indx2);
			/* placeholder S */
		} else {
			printf("Unrecognized command\n");
		}
	}
	return 0;
}

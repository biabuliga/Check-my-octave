#ifndef MEMORY_MATRIX_H
#define MEMORY_MATRIX_H

typedef struct {
	int rows;
	int cols;
	int **data;
} matrix_t;

void create_matrix(matrix_t *matrix, int m, int n);
void add_data(matrix_t *matrix);
void cmd_load(matrix_t **col, int *nr);
void cmd_print(matrix_t *col, int nr);
void cmd_dim(matrix_t *col, int nr);
void cmd_transpose(matrix_t *col, int nr);
void cmd_multiply(matrix_t **col, int *nr);
void cmd_free(matrix_t **col, int *nr);
void cmd_sort(matrix_t *col, int nr);
void cmd_crop(matrix_t *col, int nr);
void cmd_quit(matrix_t **col, int *nr);

#endif

#include <stdlib.h>
#include <stdio.h>
#include "memory_matrix.h"

void create_matrix(matrix_t *matrix, int m, int n)
{
	matrix->rows = m;
	matrix->cols = n;
	matrix->data = (int **)malloc(m * sizeof(int *));
	for (int i = 0; i < m; i++)
		matrix->data[i] = (int *)malloc(n * sizeof(int));
}

void add_data(matrix_t *matrix)
{
	for (int i = 0; i < matrix->rows; i++) {
		for (int j = 0; j < matrix->cols; j++)
			scanf("%d", &matrix->data[i][j]);
	}
}

void cmd_quit(matrix_t **col, int *nr)
{
	for (int i = 0; i < *nr; i++) {
		for (int j = 0; j < (*col)[i].rows; j++)
			free((*col)[i].data[j]);
		free((*col)[i].data);
	}
	free(*col);
}

void cmd_load(matrix_t **col, int *nr)
{
	int m, n;
	scanf("%d %d", &m, &n);
	(*nr)++;
	*col = (matrix_t *)realloc(*col, (*nr) * sizeof(matrix_t));
	create_matrix(&(*col)[*nr - 1], m, n);
	add_data(&(*col)[*nr - 1]);
}

void cmd_print(matrix_t *col, int nr)
{
	int index;
	scanf("%d", &index);
	if (index >= 0 && index < nr) {
		for (int i = 0; i < col[index].rows; i++) {
			for (int j = 0; j < col[index].cols; j++)
				printf("%d ", col[index].data[i][j]);
			printf("\n");
		}
	} else {
		printf("No matrix with the given index\n");
	}
}

void cmd_dim(matrix_t *col, int nr)
{
	int index;
	scanf("%d", &index);
	if (index < 0 || index >= nr)
		printf("No matrix with the given index\n");
	else
		printf("%d %d\n", col[index].rows, col[index].cols);
}

void cmd_transpose(matrix_t *col, int nr)
{
	int index;
	scanf("%d", &index);
	if (index < 0 || index >= nr) {
		printf("No matrix with the given index\n");
	} else {
		matrix_t *mat = &col[index];
		int **temp = (int **)malloc(mat->cols * sizeof(int *));

		for (int i = 0; i < mat->cols; i++)
			temp[i] = (int *)malloc(mat->rows * sizeof(int));

		for (int i = 0; i < mat->rows; i++) {
			for (int j = 0; j < mat->cols; j++)
				temp[j][i] = mat->data[i][j];
		}

		for (int i = 0; i < mat->rows; i++)
			free(mat->data[i]);
		free(mat->data);

		mat->data = temp;
		int aux = mat->rows;
		mat->rows = mat->cols;
		mat->cols = aux;
	}
}

void cmd_multiply(matrix_t **col, int *nr)
{
	int idx1, idx2;
	scanf("%d %d", &idx1, &idx2);
	if (idx1 < 0 || idx1 >= *nr || idx2 < 0 || idx2 >= *nr) {
		printf("No matrix with the given index\n");
	} else {
		matrix_t *a = &(*col)[idx1];
		matrix_t *b = &(*col)[idx2];
		if (a->cols != b->rows) {
			printf("Cannot perform matrix multiplication\n");
		} else {
			int m = a->rows;
			int n = b->cols;
			int p = a->cols;

			int **res = (int **)malloc(m * sizeof(int *));
			for (int i = 0; i < m; i++) {
				res[i] = (int *)malloc(n * sizeof(int));
				for (int j = 0; j < n; j++) {
					long long sum = 0;
					for (int k = 0; k < p; k++) {
						long long prod = (1LL * a->data[i][k] *
								  b->data[k][j]) % 10007;
						sum = (sum + prod) % 10007;
					}
					if (sum < 0)
						sum += 10007;
					res[i][j] = (int)sum;
				}
			}

			(*nr)++;
			*col = (matrix_t *)realloc(*col, (*nr) * sizeof(matrix_t));
			(*col)[*nr - 1].rows = m;
			(*col)[*nr - 1].cols = n;
			(*col)[*nr - 1].data = res;
		}
	}
}

void cmd_free(matrix_t **col, int *nr)
{
	int index;
	scanf("%d", &index);
	if (index < 0 || index >= *nr) {
		printf("No matrix with the given index\n");
	} else {
		matrix_t *mat = &(*col)[index];
		for (int i = 0; i < mat->rows; i++)
			free(mat->data[i]);
		free(mat->data);

		for (int i = index; i < *nr - 1; i++)
			(*col)[i] = (*col)[i + 1];
		(*nr)--;

		if (*nr > 0) {
			*col = (matrix_t *)realloc(*col, (*nr) * sizeof(matrix_t));
		} else {
			free(*col);
			*col = NULL;
		}
	}
}

void cmd_sort(matrix_t *col, int nr)
{
	int *sum = (int *)malloc(nr * sizeof(int));
	for (int index = 0; index < nr; index++) {
		long long current_sum = 0;
		for (int i = 0; i < col[index].rows; i++) {
			for (int j = 0; j < col[index].cols; j++) {
				current_sum = (current_sum +
					       col[index].data[i][j]) % 10007;
			}
		}
		if (current_sum < 0)
			current_sum += 10007;
		sum[index] = (int)current_sum;
	}

	for (int i = 0; i < nr - 1; i++) {
		for (int j = 0; j < nr - i - 1; j++) {
			if (sum[j] > sum[j + 1]) {
				int aux = sum[j];
				sum[j] = sum[j + 1];
				sum[j + 1] = aux;

				matrix_t auxm = col[j];
				col[j] = col[j + 1];
				col[j + 1] = auxm;
			}
		}
	}
	free(sum);
}

void cmd_crop(matrix_t *col, int nr)
{
	int index, l, c;
	scanf("%d", &index);
	if (index < 0 || index >= nr) {
		printf("No matrix with the given index\n");
		scanf("%d", &l);
		for (int i = 0; i < l; i++) {
			int junk;
			scanf("%d", &junk);
		}
		scanf("%d", &c);
		for (int i = 0; i < c; i++) {
			int junk;
			scanf("%d", &junk);
		}
	} else {
		matrix_t *mat_old = &col[index];
		scanf("%d", &l);
		int vector_lines[l];
		for (int i = 0; i < l; i++)
			scanf("%d", &vector_lines[i]);

		scanf("%d", &c);
		int vector_cols[c];
		for (int i = 0; i < c; i++)
			scanf("%d", &vector_cols[i]);

		int **temp = (int **)malloc(l * sizeof(int *));
		for (int i = 0; i < l; i++) {
			temp[i] = (int *)malloc(c * sizeof(int));
			for (int j = 0; j < c; j++)
				temp[i][j] = mat_old->data[vector_lines[i]][vector_cols[j]];
		}

		for (int i = 0; i < mat_old->rows; i++)
			free(mat_old->data[i]);
		free(mat_old->data);

		mat_old->data = temp;
		mat_old->rows = l;
		mat_old->cols = c;
	}
}

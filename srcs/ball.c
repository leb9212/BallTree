/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ball.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <elee@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 10:45:02 by elee              #+#    #+#             */
/*   Updated: 2017/06/28 12:14:52 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	swap(double *arr, int i1, int i2)
{
	double	tmp;
	
	tmp = arr[i1];
	arr[i1] = arr[i2];
	arr[i2] = tmp;
}

void	dual_swap(double *darr, int *iarr, int i1, int i2)
{
	double	dtmp;
	int		itmp;

	dtmp = darr[i1];
	darr[i1] = darr[i2];
	darr[i2] = dtmp;
	itmp = iarr[i1];
	iarr[i1] = iarr[i2];
	iarr[i2] = itmp;
}

int		arr_2d_len(double **arr)
{
	int	len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}

int		arr_1d_len(double *arr)
{
	int	len;

	len = 0;
	while (arr[len] != NAN)
		len++;
	return (len);
}

void	btree_zero(t_btree *b)
{
	b->data = NULL;
	b->idx_array = NULL;
	b->node_data = NULL;
	b->node_bounds = NULL;

	b->leaf_size = 0;
	b->n_levels = 0;
	b->n_nodes = 0;

	b->n_trims = 0;
	b->n_leaves = 0;
	b->n_splits = 0;
	b->n_calls = 0;
}

t_btree	*btree_init(double **data, int leaf_size)
{
	t_btree	*b;
	int		i, j;

	b = (t_btree*)malloc(sizeof(t_btree));
	btree_zero(b);

	b->data = data;
	b->leaf_size = leaf_size;
	
	if (arr_2d_len(data) == 0)
	{
		printf("data is an empty array\n");
		exit(-1);
	}
	if (leaf_size < 1)
	{
		printf("leaf_size must be greater than or equal to 1\n");
		exit(-1);
	}

	b->n_samples = arr_2d_len(data);
	b->n_features = arr_1d_len(data[0]);

	b->n_levels = log2(fmax(1, (b->n_samples - 1) / b->leaf_size)) + 1;
	b->n_nodes = pow(2.0, b->n_levels) - 1;

	b->idx_array = (int*)malloc(sizeof(int) * b->n_samples);
	b->node_data = (t_nodedata*)calloc(b->n_nodes, sizeof(t_nodedata));
	b->node_bounds = (double***)malloc(sizeof(double**));
	b->node_bounds[0] = (double**)malloc(sizeof(double*) * b->n_nodes);
	for (i = 0; i < b->n_nodes; i++)
	{
		b->node_bounds[0][i] = (double*)malloc(sizeof(double) * b->n_features);
		for (j = 0; j < b->n_features; j++)
			b->node_bounds[0][i][j] = 0.0;
	}
	recursive_build(0, 0, b->n_samples);
	return (b);
}

int		*query(t_binarytree *tree, double *x, int k)
{
}

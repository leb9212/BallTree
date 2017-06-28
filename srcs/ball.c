/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ball.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <elee@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 10:45:02 by elee              #+#    #+#             */
/*   Updated: 2017/06/28 13:28:57 by elee             ###   ########.fr       */
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

int		init_node(t_btree *b, int i_node, int idx_start, int idx_end)
{
	int		n_features
	int		n_points;
	
	int		i, j;
	double	radius;

	double	*centroid;

	n_features = b->n_features;
	n_points = idx_end - idx_start;
	
	data = b->data[0];
	centroid = b->node_bounds[0][i_node];

	for (j = 0; j < n_features; j++)
		centroid[j] = 0.0;

	for (i = idx_start; i < idx_end; i++)
		for (j = 0 ; j < n_features; j++)
			centroid[j] += b->data[i][j];

	for (j = 0; j < n_features; j++)
		centroid[j] /= n_points;

	radius = 0.0;
	for (i = idx_start; i < idx_end; i++)
		radius = fmax(radius, manhattan_dist(centroid, b->data[i], n_features);

	b->node_data[i_node].radius = radius;
	b->node_data.idx_start = idx_start;
	b->node_data.idx_end = idx_end;
	return (0);
}

int		find_node_split_dim(double **data, int *node_indices, int n_features, int n_points)
{
	double	min_val, max_val, val, spread, max_spread;
	int		i, j, j_max;

	j_max = 0;
	max_spread = 0;
	for (j = 0; j < n_features; j++)
	{
		max_val = data[node_indices[0]][j];
		min_val = max_val;
		for (i = 1; i < n_points; i++)
		{
			val = data[node_indices[i]][j];
			max_val = fmax(max_val, val);
			min_val = fmin(min_val, val);
		}
		spread = max_val - min_val;
		if (spread > max_spread)
		{
			max_spread = spread;
			j_max = j;
		}
	}
	return (j_max);
}

int		partition_node_indices(double **data, int *node_indices, int split_dim, int split_index,
								int n_features, int n_points)
{
	int		left, right, midindex, i;
	double	d1, d2;

	left = 0;
	right = n_points - 1;

	while (TRUE)
	{
		midindex = left;
		for (i = left; i < right; i++)
		{
			d1 = data[node_indices[i]][split_dim];
			d2 = data[node_indices[right]][split_dim];
			if (d1 < d2)
			{
				swap(node_indices, i, midindex)
				midindex += 1;
			}
		}
		swap(node_indices, midindex, right);
		if (midindex == split_index)
			break ;
		else if (midindex < split_index)
			left = midindex + 1;
		else
			right = midindex - 1;
	}
	return (0);
}

int		recursive_build(t_btree *b, int i_node, int idx_start, int idx_end)
{
	int	imax;
	int	n_features;
	int	n_points;
	int	n_mid;

	n_features = b->n_features;
	n_points = idx_end - idx_start;
	n_mid = n_points / 2;

	//initialize the node data
	init_node(b, i_node, idx_start, idx_end);

	if (2 * i_node + 1 >= b->n_nodes)
	{
		b->node_data[i_node].is_leaf = TRUE;
		if (idx_end - idx_start > 2 * b->leaf_size)
			printf("Memory layout is flawed: not enough nodes allocated");
	}
	else if (idx_end - idx_start < 2)
	{
		printf("Memory layout is flawed: too many nodes allocated");
		b->node_data[i_node].is_leaf = TRUE;
	}
	else
	{
		b->node_data[i_node].is_leaf = FALSE;
		i_max = find_node_split_dim(b->data, b->idx_array, n_features, n_points);
		partition_node_indices(b->data, b->idx_array, i_max, n_mid, n_features, n_points);
		recursive_build(b, 2 * i_node + 1, idx_start, idx_start + n_mid);
		recursive_build(b, 2 * i_node + 2, idx_start + n_mid, idx_end);
	}
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
	recursive_build(b, 0, 0, b->n_samples);
	return (b);
}

int		*btree_query(t_btree *tree, double *x, int k)
{

}

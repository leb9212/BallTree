/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neighbors_heap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <elee@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 10:45:06 by elee              #+#    #+#             */
/*   Updated: 2017/06/28 14:48:43 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ball.h"

t_nheap	*nheap_init(int n_pts, int n_nbrs)
{
	t_nheap	*h;
	int		i, j;

	h = (t_nheap*)malloc(sizeof(t_nheap));
	h->n_pts = n_pts;
	h->n_nbrs = n_nbrs;
	h->distances = (double**)malloc(sizeof(double*) * n_pts);
	for (i = 0; i < n_pts; i++)
	{
		h->distances[i] = (double*)malloc(sizeof(double) * n_nbrs);
		for (j = 0; j < n_nbrs; j++)
			h->distances[i][j] = INFINITY;
	}
	h->indices = (int**)malloc(sizeof(int*) * n_pts);
	for (i = 0; i < n_pts; i++)
		h->indices[i] = (int*)calloc(sizeof(int), n_nbrs);
	return (h);
}

double	nheap_largest(t_nheap *h, int row)
{
	return (h->distances[row][0]);
}

int		nheap_push(t_nheap *h, int row, double val, int i_val)
{
	int		i, ic1, ic2, i_swap;
	int		size;
	double	*dist_arr;
	int		*ind_arr;

	size = h->n_nbrs;
	dist_arr = h->distances[row];
	ind_arr = h->indices[row];

	// if distance is already greater than the furthest element, don't push
	if (val > dist_arr[0])
		return (0);

	// insert the values at position 0
	dist_arr[0] = val;
	ind_arr[0] = i_val;

	// descend the heap, swapping values until the max heap criterion is met
	i = 0;
	while (TRUE)
	{
		ic1 = 2 * i + 1;
		ic2 = ic1 + 1;

		if (ic1 >= size)
			break ;
		else if (ic2 >= size)
		{
			if (dist_arr[ic2] > val)
				i_swap = ic1;
			else
				break ;
		}
		else if (dist_arr[ic1] >= dist_arr[ic2])
		{
			if (val < dist_arr[ic1])
				i_swap = ic1;
			else
				break ;
		}
		else
		{
			if (val < dist_arr[ic2])
				i_swap = ic2;
			else
				break ;
		}
		dist_arr[i] = dist_arr[i_swap];
		ind_arr[i] = ind_arr[i_swap];
		i = i_swap;
	}

	dist_arr[i] = val;
	ind_arr[i] = i_val;

	return (0);
}

double	**copy_double(double **arr, int row, int col)
{
	double	**copy;
	int		i, j;

	copy = (double**)malloc(sizeof(double*) * row);
	for (i = 0; i < row; i++)
	{
		copy[i] = (double*)malloc(sizeof(double) * col);
		for (j = 0; j < col; j++)
			copy[i][j] = arr[i][j];
	}
	return (copy);
}

int		**copy_int(int **arr, int row, int col)
{
	int		**copy;
	int		i, j;

	copy = (int**)malloc(sizeof(int*) * row);
	for (i = 0; i < row; i++)
	{
		copy[i] = (int*)malloc(sizeof(int) * col);
		for (j = 0; j < col; j++)
			copy[i][j] = arr[i][j];
	}
	return (copy);
}

t_knn	nheap_get_arrays(t_nheap *h)
{
	t_knn	output;

	output.distances = copy_double(h->distances, h->n_pts, h->n_nbrs);
	output.indices = copy_int(h->indices, h->n_pts, h->n_nbrs);
	return (output);
}

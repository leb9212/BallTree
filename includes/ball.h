/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ball.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <elee@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 10:55:27 by elee              #+#    #+#             */
/*   Updated: 2017/06/28 10:55:27 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BALL_H
# define BALL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <math.h>
# include <float.h>

# define HEAP_INITIAL_SIZE 8

typedef struct	s_heap
{
	int			size;
	int			count;
	double		*heapparr;
}				t_heap;

typedef	struct	s_nodedata
{
	int			idx_start;
	int			idx_end;
	int			is_leaf;
	double		radius;
}				t_nodedata;

typedef struct	s_binarytree
{
	double		*data_arr;
	int			*idx_array_arr;
	double		*node_data_arr;
	double		*node_bounds_arr;

	int			leaf_size;
	int			n_levels;
	int			n_nodes;
	//dist metric is always going to be manhattan distance
	int			n_trims;
	int			n_leaves;
	int			n_splits;
	int			n_calls;
}				t_binarytree;


double	manhattan_dist(double *x1, double *x2, int size);

#endif

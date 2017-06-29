/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <elee@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 14:49:03 by elee              #+#    #+#             */
/*   Updated: 2017/06/28 17:21:55 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ball.h"

int		main(void)
{
	double	**points = (double**)malloc(sizeof(double*) * 4);
	
	for (int i = 0; i < 4; i++)
		points[i] = (double*)malloc(sizeof(double) * 3);

	points[0][0] = 1.0;
	points[0][1] = 1.0;
	points[0][2] = 1.0;

	points[1][0] = 2.0;
	points[1][1] = 2.0;
	points[1][2] = 2.0;

	points[2][0] = 3.0;
	points[2][1] = 3.0;
	points[2][2] = 3.0;
	
	points[3][0] = 4.0;
	points[3][1] = 4.0;
	points[3][2] = 4.0;

	t_btree *tree = btree_init(points, 4, 3, 1);

	double	**query_points = (double**)malloc(sizeof(double*) * 2);

	for (int i = 0; i < 2; i++)
		query_points[i] = (double*)malloc(sizeof(double*) * 3);

	query_points[0][0] = 1.4;
	query_points[0][1] = 1.4;
	query_points[0][2] = 1.4;

	query_points[1][0] = 2.0;
	query_points[1][1] = 2.0;
	query_points[1][2] = 2.0;


	t_knn	knn = btree_query(tree, query_points, 2, 3, 2);
	printf("distance: %lf\n", knn.distances[0][0]);
	printf("index: %d\n", knn.indices[0][0]);

	printf("distance: %lf\n", knn.distances[1][0]);
	printf("index: %d\n", knn.indices[1][0]);

	return (0);
}

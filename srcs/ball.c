/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ball.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <elee@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 10:45:02 by elee              #+#    #+#             */
/*   Updated: 2017/06/28 10:45:53 by elee             ###   ########.fr       */
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

int		arr_len(double *data)
{
	int	len = 0;

	while (data[len] != NAN)
		len++;
	return (len);
}

t_tree	*build_balltree(double *data, int size, int n_leaf)
{
}

int		*query(t_binarytree *tree, double *x, int k)
{
}

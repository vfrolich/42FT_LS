/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 11:40:24 by vfrolich          #+#    #+#             */
/*   Updated: 2016/11/17 11:41:15 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_range(int min, int max)
{
	int *range;
	int i;

	i = 0;
	if (min >= max)
		return (0);
	if ((max - min) > 0)
		range = (int *)malloc(sizeof(int) * (max - min));
	else
		range = (int *)malloc(sizeof(int) * ((max - min) * -1));
	if (range == NULL)
		return (0);
	while ((min + i) < max)
	{
		range[i] = min + i;
		i++;
	}
	return (range);
}

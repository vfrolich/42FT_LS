/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 14:31:44 by vfrolich          #+#    #+#             */
/*   Updated: 2016/11/17 19:11:14 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_count_n(int n)
{
	int count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		count++;
	}
	while (n >= 1)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	char	*dst;
	int		count;

	count = ft_count_n(n);
	dst = (char *)malloc(sizeof(char) * (count + 1));
	if (dst == NULL)
		return (NULL);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		dst[0] = '-';
		n = n * -1;
	}
	dst[count] = '\0';
	if (n == 0)
		dst[count - 1] = '0';
	while (n > 0)
	{
		dst[count - 1] = (n % 10) + '0';
		n = n / 10;
		count--;
	}
	return (dst);
}

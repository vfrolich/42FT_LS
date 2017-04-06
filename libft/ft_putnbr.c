/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:30:26 by vfrolich          #+#    #+#             */
/*   Updated: 2016/11/16 16:36:31 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n)
{
	long puis;

	puis = 1;
	if (n < 0)
		n = n * -1;
	while (puis <= n)
		puis = puis * 10;
	puis = puis / 10;
	return (puis);
}

void		ft_putnbr(int n)
{
	unsigned int puis;

	puis = ft_count_digits(n);
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else if (n == 2147483647)
		ft_putstr("2147483647");
	else
	{
		if (n < 0)
		{
			ft_putchar('-');
			n = n * -1;
		}
		if (n == 0)
			ft_putchar('0');
		while (puis >= 1)
		{
			ft_putchar(((n / puis) % 10) + '0');
			puis = puis / 10;
		}
	}
}

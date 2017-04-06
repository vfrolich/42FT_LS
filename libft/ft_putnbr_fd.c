/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 12:45:04 by vfrolich          #+#    #+#             */
/*   Updated: 2016/11/16 18:07:12 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	long	ft_count_digits(int n)
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

void			ft_putnbr_fd(int n, int fd)
{
	int puis;

	puis = ft_count_digits(n);
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n == 2147483647)
		ft_putstr_fd("2147483647", fd);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n = n * -1;
		}
		if (n == 0)
			ft_putchar_fd('0', fd);
		while (puis >= 1)
		{
			ft_putchar_fd(((n / puis) % 10) + '0', fd);
			puis = puis / 10;
		}
	}
}

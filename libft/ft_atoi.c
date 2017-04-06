/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 15:04:58 by vfrolich          #+#    #+#             */
/*   Updated: 2016/11/24 13:35:56 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcheck(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]) == 0)
	{
		if ((str[i] == '-' || str[i] == '+') && ft_isdigit(str[i + 1]) != 0)
			i++;
		else if (str[i] == '\v' || str[i] == '\t' || str[i] == '\f'	\
			|| str[i] == '\r' || str[i] == '\n' || str[i] == ' ')
			i++;
		else
			return (-1);
	}
	return (0);
}

static int	ft_getnbr(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) != 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_signchecker(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]) == 0)
	{
		if (ft_isdigit(str[i]) != 0 && str[i - 1] == '-')
			return (1);
		i++;
	}
	if (ft_isdigit(str[i]) != 0 && str[i - 1] == '-')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int result;
	int i;

	i = ft_getnbr(str);
	if (ft_strcheck(str) == -1)
		return (0);
	result = 0;
	while (ft_isdigit(str[i]) != 0)
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (ft_signchecker(str) == 1)
		return (result * -1);
	return (result);
}

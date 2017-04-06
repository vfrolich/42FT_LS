/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 19:38:30 by vfrolich          #+#    #+#             */
/*   Updated: 2016/11/17 19:22:44 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_check_strim(char const *s, int i)
{
	while (s[i] != '\0')
	{
		if (s[i] != '\t' && s[i] != '\n' && s[i] != 32)
			return (1);
		i++;
	}
	return (0);
}

static	int		ft_count_c(char const *s)
{
	int n;
	int i;

	i = 0;
	n = 0;
	while ((s[i] != '\0') && (s[i] == 32 || s[i] == '\n' || s[i] == '\t'))
		i++;
	while (s[i] != '\0' && ft_check_strim(s, i) != 0)
	{
		i++;
		n++;
	}
	return (n);
}

static	char	*ft_realstrim(char const *s, int i, char *dest)
{
	int j;

	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != '\t' || s[i] != '\n' || s[i] != 32)
		{
			if (ft_check_strim(s, i) == 0)
			{
				dest[j] = '\0';
				return (dest);
			}
		}
		dest[j] = s[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char			*ft_strtrim(char const *s)
{
	int		i;
	char	*dest;
	int		size;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] == 32 || s[i] == '\n' || s[i] == '\t')
		i++;
	size = ft_count_c(s) + 1;
	dest = (char *)malloc(sizeof(char) * size);
	if (dest == NULL)
		return (NULL);
	dest = ft_realstrim(s, i, dest);
	return (dest);
}

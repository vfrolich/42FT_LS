/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 21:02:35 by vfrolich          #+#    #+#             */
/*   Updated: 2016/11/15 14:30:06 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_count_words(char const *s, char c)
{
	int i;
	int nb_w;

	i = 0;
	nb_w = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			nb_w++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (nb_w + 1);
}

static	int		ft_count_char(char const *s, char c, int i)
{
	int nb_c;

	nb_c = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		nb_c++;
	}
	return (nb_c + 1);
}

static	char	**ft_fill_tab(char const *s, char c, char **dest)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			k = 0;
			while (s[i] != c && s[i] != '\0')
			{
				dest[j][k] = s[i];
				k++;
				i++;
			}
			dest[j][k] = '\0';
			j++;
		}
		else
			i++;
	}
	dest[j] = NULL;
	return (dest);
}

static	char	**ft_malloc_tab(char const *s, char c)
{
	int		i;
	int		j;
	char	**dest;

	i = 0;
	j = 0;
	dest = (char **)malloc(sizeof(char *) * ft_count_words(s, c));
	if (dest == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			dest[j] = (char *)malloc(sizeof(char) * ft_count_char(s, c, i));
			if (dest[j] == NULL)
				return (NULL);
			while (s[i] != c && s[i] != '\0')
				i++;
			j++;
		}
		else
			i++;
	}
	return (dest);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**dest;

	if (c < 0 || c > 127 || s == NULL)
		return (NULL);
	dest = ft_malloc_tab(s, c);
	if (dest)
	{
		dest = ft_fill_tab(s, c, dest);
		return (dest);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 13:55:30 by vfrolich          #+#    #+#             */
/*   Updated: 2017/02/22 11:01:43 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_str_cut(t_mstr *mstr, char **line)
{
	char *tmp;

	tmp = ft_strdup(mstr->str);
	if (*tmp == '\n')
	{
		*line = ft_strnew(0);
		return ;
	}
	*line = tmp;
	if (ft_strchr(tmp, '\n'))
		*(ft_strchr(tmp, '\n')) = '\0';
}

char	*join_free(t_mstr *mstr)
{
	char	*dst;

	if (!mstr->str || !mstr->buff)
		return (NULL);
	dst = ft_strnew(ft_strlen(mstr->str) + ft_strlen(mstr->buff));
	if (!dst)
		return (NULL);
	dst = ft_strcpy(dst, mstr->str);
	free(mstr->str - mstr->diff);
	dst = ft_strcat(dst, mstr->buff);
	ft_strdel(&mstr->buff);
	return (dst);
}

int		return_line(char **line, t_mstr *mstr, int ret)
{
	if (ft_strchr(mstr->str, '\n'))
	{
		ft_str_cut(mstr, line);
		if ((ft_strchr(mstr->str, '\n') + 1))
		{
			mstr->diff = (ft_strchr(mstr->str, '\n') + 1) - mstr->str;
			mstr->str = ft_strchr(mstr->str, '\n') + 1;
		}
		return (1);
	}
	if (!ret)
	{
		ft_str_cut(mstr, line);
		mstr->flag = 0;
		return (1);
	}
	mstr->diff = 0;
	return (0);
}

int		ft_return(t_mstr *mstr, int ret, char **line)
{
	if (ret == -1 || !mstr->str)
	{
		mstr->diff = 0;
		mstr->flag = 1;
		if (mstr->str)
			ft_strdel(&mstr->str);
		*line = ft_strnew(0);
		return (-1);
	}
	if (!mstr->flag && ft_strlen(mstr->str))
	{
		mstr->str = ft_strnew(0);
		return (1);
	}
	if (!mstr->flag)
	{
		mstr->diff = 0;
		mstr->flag = 1;
		ft_strdel(&mstr->str);
		*line = ft_strnew(0);
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static t_mstr	mstr;
	int				ret;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	ret = 1;
	if (!mstr.str)
	{
		mstr.str = ft_strnew(0);
		mstr.flag = 1;
		mstr.diff = 0;
	}
	while (ret && mstr.flag)
	{
		mstr.buff = ft_strnew(BUFF_SIZE);
		if ((ret = read(fd, mstr.buff, BUFF_SIZE)) < 0)
			return (ft_return(&mstr, ret, line));
		mstr.buff[ret] = '\0';
		mstr.str = join_free(&mstr);
		if ((return_line(line, &mstr, ret)))
			return (ft_return(&mstr, ret, line));
	}
	return (ft_return(&mstr, ret, line));
}

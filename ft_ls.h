/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 10:26:22 by vfrolich          #+#    #+#             */
/*   Updated: 2017/05/13 15:10:38 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <dirent.h>
# include <errno.h>
# include <time.h>
# define RED "[31m"
# define CYAN "[36m"
# define RESET "[39m"

typedef	struct			s_file
{
	char				*name;
	char				*path;
	struct stat			*infos;
	struct s_file		*next;
	struct s_file		*dir;
	int					erref;
}						t_file;

typedef struct			s_opt
{
	int					all;
	int					recurs;
	int					list;
	int					reverse;
	int					t;
	int					color;
}						t_opt;

typedef	struct			s_padding
{
	size_t				user;
	size_t				links;
	size_t				group;
	size_t				size;
	size_t				maj;
	size_t				min;
}						t_padd;

t_file					*ft_listnew(char *name);
void					lst_add(t_file *new, t_file **start);
t_file					*ft_create_lst(DIR *dirp, t_file *lst,
						char *base_dir, t_opt *opt);
t_file					*arg_to_lst(char **argv);
char					ft_get_type(struct stat *filestat);
char					*ft_get_rights(struct stat *filestat);
char					*time_check(struct stat *filestat, char *str);
int						get_total_size(t_file *lst, t_opt *opt);
t_file					*check_for_opt(char *name, t_opt *opt,
						char *base_dir, t_file *lst);
t_file					*ft_fill_info(t_file *lst, char *base_dir, t_opt *opt);
t_file					*fill_file(t_file *lst, t_opt *opt);
t_file					*fill_dir(t_file *lst, DIR *dirptr, t_opt *opt);
t_file					*rd_dir(DIR *dirptr);
int						fill_stats(t_file *lst);
void					ft_print_lst(t_file *lst);
char					*listed_display(struct stat *filestat, t_padd *padding);
void					read_link_path(t_file *lst);
void					ft_print_recursive(t_file *lst);
void					print_listed(t_file *lst, t_opt *opt);
void					recursive_listed(t_file	*lst, t_opt *opt);
void					print_errors(t_file *lst, t_opt *opt);
void					ft_print_dir(t_file *lst, t_opt *opt, t_file *start);
void					ft_print_dir_r(t_file *lst, t_opt *opt);
void					print_dir_one(t_file *lst, t_opt *opt);
void					print_list(t_file *lst, t_opt *opt);
int						check_for_empty(t_file *lst, t_opt *opt);
int						last_dir(t_file *lst);
int						count_files(t_file *lst);
char					*ft_get_path(t_file *lst, t_file *dir, char *base_dir);
size_t					get_largest_links(t_file *lst);
size_t					get_largest_user(t_file *lst);
size_t					get_largest_group(t_file *lst);
size_t					get_largest_size(t_file *lst);
size_t					get_largest_maj(t_file *lst);
size_t					get_largest_min(t_file *lst);
char					*get_min_maj(struct stat *filestat, t_padd *padd);
char					*padd_it(char *str, int max);
char					*padd_it_left(char	*str, int max);
int						sorted_list(t_file *lst);
int						sorted_r_list(t_file *lst);
t_file					*sort_list(t_file *lst);
t_file					*sort_r_list(t_file *lst);
t_file					*swap_data(t_file *lst, t_file *lst2);
int						sorted_list_t(t_file *lst);
t_file					*sort_list_t(t_file *lst);
int						sorted_r_list_t(t_file *lst);
t_file					*sort_r_list_t(t_file *lst);
void					arg_handle(int argc, char **argv);
void					simple_ft_ls();
void					current_ls(t_opt *opt);
t_file					*get_files(DIR *dirp, char *base_dir);
void					lst_free_one(t_file *lst);
void					free_lst(t_file *lst);
t_opt					*opt_fill(char *argv, t_opt *options);
t_opt					*opt_init(void);
int						opt_check(char *av);
void					vanilla_ls(t_file *lst, t_opt *opt);
t_padd					*padding_init(t_file *lst);
t_padd					*get_padding(t_file *lst, t_padd *padd);
t_file					*sort_handle(t_file *lst, t_opt *opt);
void					display_infos(t_file *lst, t_padd *padd, t_opt *opt);
void					display_line(t_file *lst, t_opt *opt, t_padd *padd);
int						recursable(t_file *lst, t_opt *opt);
void					color(char *color, char *target, int fd);
#endif

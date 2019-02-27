/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:19:11 by aulopez           #+#    #+#             */
/*   Updated: 2019/02/27 18:57:14 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** --- Headers -----------------------------------------------------------------
*/

/*
** # include <sys/sysmacros.h> //major/minor, for linux
** libft for libft (duh)
** errno to get error msg, ls_error
** stdlib for malloc/free
** dirent, /sys/stat, time for structure
** grp, pwd for getpwuid getgrgid
** sys/xattr for major/minor
** sys/acl for bonus : acl
** unistd for readlink
*/

# include <libft.h>
# include <errno.h>
# include <stdlib.h>
# include <dirent.h>
# include <grp.h>
# include <time.h>
# include <pwd.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/ioctl.h>
# include <unistd.h>

/*
** --- Define ------------------------------------------------------------------
*/

/*
** LSO_1 to LSO_P are used for ft_ls flags
** LSO_1STFILE to LSO_ERROPEN are used to handle special cases
*/

# define LSO_1 1
# define LSO_L 2
# define LSO_RR 4
# define LSO_A 8
# define LSO_R 16
# define LSO_T 32
# define LSO_S 64
# define LSO_TT 128
# define LSO_U 256
# define LSO_O 512
# define LSO_F 1024
# define LSO_GG 2048
# define LSO_AA 4096
# define LSO_P 8192
# define LSO_CC 16384
# define LSO_1STFILE 32768
# define LSO_ARGC 65536
# define LSO_ERROPEN 131072
# define LSO_ERROR 262144
# define LS_SIX_MONTH 15552000

/*
** --- Enum & structure --------------------------------------------------------
*/

enum {LSERR_USAGE, LSERR_MALLOC, LSERR_OTHER, LSERR_OPENFILE, LSERR_OPENDIR};
typedef struct stat		t_stat;
typedef struct dirent	t_dirent;

typedef struct			s_file
{
	t_stat				stat;
	char				name[NAME_MAX];
	struct s_file		*prev;
	struct s_file		*next;
}						t_file;

typedef struct			s_ls
{
	t_file				*file;
	t_file				*curr_file;
	size_t				numfile;
	t_list				*directory;
	t_list				*curr_dir;
	int					flags;
}						t_ls;

/*
** --- Prototypes --------------------------------------------------------------
*/

int						ls_parsing(int ac, char **av, int *flags);
int						ls_print_error(char *str, int errflag, t_ls *ls);
int						ls_print_error_argc(char *str, int errflag, t_ls *ls);
int						load_info_from_directory(t_ls *ls);
int						load_info_from_argument(t_ls *ls, int argc,
						char **argv);
int						handle_dev_fd(t_ls *ls, char *pathname);
int						create_first_directory(t_ls *ls, int option_ac);
int						create_directory(t_ls *ls, int option_ac);
void					create_directory_from_arg_loop(t_ls *ls);
void					sort_ascii(t_file *current, t_file *last);
void					sort_time(t_file *current, t_file *last);
void					print_ls(t_ls *liste1);
void					print_basic(t_ls *ls, int first);
void					print_column_loop(t_ls *ls, int block_size,
						int str_size);
void					print_detailed(t_ls *ls, int non_first);
void					set_colors(t_file *file, t_ls *ls);
void					set_detailed_list_length(t_ls *ls, long long (*s)[12]);
void					load_attribute(t_file *file, t_ls *ls,
						char (*attr)[12]);
int						load_file_link(t_ls *ls);

#endif

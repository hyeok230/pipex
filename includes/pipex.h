/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junylee <junylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 14:29:41 by junylee           #+#    #+#             */
/*   Updated: 2021/09/26 18:07:48 by junylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*
** =============================================================================
** Dependencies
** =============================================================================
*/

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>

/*
** =============================================================================
** Struct Type Definitions
** =============================================================================
*/

typedef struct s_info
{
	int		input_fd;
	int		output_fd;
	char	*full_cmd[2];
	char	**cmd[2];
	char	**envp;
}	t_info;

/*
** =============================================================================
** Macros
** =============================================================================
*/

# define SUCCESS 1
# define ERROR -1

/*
** =============================================================================
** Utils
** =============================================================================
*/

void	ft_fail(char **ret);
int		ft_isdeli(char c, char deli);
int		ft_count(char *s, char c);
char	*ft_cpy(char *s, char c, int *offset, int i);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
int		ft_strlen(const char *str);
void	*ft_memset(void *ptr, int value, size_t size);
void	redirect_in(t_info info);
void	redirect_out(t_info info);
char	**ret_path(char **envp);
int		excute_cmd(t_info info, int num);
void	dup_pipe(int fd[2], int io);
void	check_files(char *input, char *output, t_info *info);
int		check_path(char *cmd);
int		make_path(t_info *info, int num);
int		check_cmd(char *cmd, t_info *info, int num);
void	init_args(char **argv, char **envp, t_info *info);
void	child(t_info info, int fd[2]);
void	parent(t_info info, int fd[2]);
int		main(int argc, char **argv, char **envp);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:59:21 by junylee           #+#    #+#             */
/*   Updated: 2021/09/26 18:06:03 by junylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(t_info info, int fd[2])
{
	int	num;

	num = 0;
	redirect_in(info);
	dup_pipe(fd, STDOUT_FILENO);
	if (excute_cmd(info, num) == ERROR)
	{
		perror(info.cmd[num][0]);
		exit(1);
	}
}

void	parent(t_info info, int fd[2])
{
	int	num;

	num = 1;
	redirect_out(info);
	dup_pipe(fd, STDIN_FILENO);
	if (excute_cmd(info, num) == ERROR)
	{	
		perror(info.cmd[num][0]);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	pid;
	t_info	info;

	if (argc != 5)
		return (1);
	ft_memset(&info, 0, sizeof(t_info));
	init_args(argv, envp, &info);
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[STDIN_FILENO]);
		close(fd[STDOUT_FILENO]);
	}
	if (pid == 0)
		child(info, fd);
	else
	{
		waitpid(pid, &status, WNOWAIT);
		parent(info, fd);
	}
	return (0);
}

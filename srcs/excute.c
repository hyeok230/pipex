/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junylee <junylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:05:02 by junylee           #+#    #+#             */
/*   Updated: 2021/09/26 18:06:32 by junylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect_in(t_info info)
{
	dup2(info.input_fd, STDIN_FILENO);
	close(info.input_fd);
}

void	redirect_out(t_info info)
{
	dup2(info.output_fd, STDOUT_FILENO);
	close(info.output_fd);
}

char	**ret_path(char **envp)
{
	int		i;
	char	*all_path;
	char	**path;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			all_path = ft_strdup(envp[i] + 5);
			path = ft_split(all_path, ':');
			return (path);
		}
	}
	return (NULL);
}

int	excute_cmd(t_info info, int num)
{
	if (execve(info.full_cmd[num], info.cmd[num], info.envp) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	dup_pipe(int fd[2], int io)
{
	dup2(fd[io], io);
	close(fd[STDIN_FILENO]);
	close(fd[STDOUT_FILENO]);
}

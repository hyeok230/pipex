/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junylee <junylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:02:05 by junylee           #+#    #+#             */
/*   Updated: 2021/09/26 18:06:20 by junylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_files(char *input, char *output, t_info *info)
{
	if (access(input, F_OK | R_OK))
	{
		perror("File is not existing\n");
		exit (1);
	}
	info->input_fd = open(input, O_RDONLY);
	if (info->input_fd < 0)
	{
		perror(input);
		exit (1);
	}
	info->output_fd = open(output, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (info->output_fd < 0)
	{
		perror(output);
		exit (1);
	}
}

int	check_path(char *cmd)
{
	if (ft_strncmp(cmd, "/", 1) == 0
		|| ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../", 3) == 0)
		return (1);
	return (-1);
}

int	make_path(t_info *info, int num)
{
	int		i;
	char	**path;
	char	*temp_path;
	char	*full_cmd;

	i = 0;
	path = ret_path(info->envp);
	while (path[i])
	{
		temp_path = ft_strjoin(path[i], "/");
		full_cmd = ft_strjoin(temp_path, info->cmd[num][0]);
		if (access(full_cmd, F_OK) == 0)
		{
			info->full_cmd[num] = ft_strdup(full_cmd);
			free(temp_path);
			free(full_cmd);
			return (SUCCESS);
		}
		free(temp_path);
		free(full_cmd);
		i++;
	}
	return (ERROR);
}

int	check_cmd(char *cmd, t_info *info, int num)
{
	int	i;

	i = 0;
	info->cmd[num] = ft_split(cmd, ' ');
	if (check_path(info->cmd[num][0]) == -1)
	{
		if (make_path(info, num) == ERROR)
			return (ERROR);
		return (SUCCESS);
	}
	else
	{
		info->full_cmd[num] = info->cmd[num][0];
		if (access(info->full_cmd[num], F_OK) == 0)
			return (SUCCESS);
		return (ERROR);
	}
}

void	init_args(char **argv, char **envp, t_info *info)
{
	int	num;

	num = 0;
	check_files(argv[1], argv[4], info);
	info->envp = envp;
	if (check_cmd(argv[2], info, num) == ERROR)
		perror(argv[2]);
	num = 1;
	if (check_cmd(argv[3], info, num) == ERROR)
		perror(argv[3]);
}

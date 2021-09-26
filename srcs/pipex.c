/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:59:21 by junylee           #+#    #+#             */
/*   Updated: 2021/09/26 15:46:29 by junylee          ###   ########.fr       */
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
	int i;
	char *all_path;
	char **path;

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

void dup_pipe(int fd[2], int io)
{
	dup2(fd[io], io);
	close(fd[STDIN_FILENO]);
	close(fd[STDOUT_FILENO]);
}

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
	int i;
	char **path;
	char *temp_path;
	char *full_cmd;

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
	int i;

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
	int num;

	num = 0;
	check_files(argv[1], argv[4], info);
	info->envp = envp;
	if (check_cmd(argv[2], info, num) == ERROR)
	{
		perror(argv[2]);
		exit(1);
	}
	num = 1;
	if (check_cmd(argv[3], info, num) == ERROR)
	{
		perror(argv[3]);
		exit(1);
	}
}

int main(int argc, char **argv, char **envp)
{
	int fd[2];
	int num;
	int status;
	pid_t	pid;
	t_info	info;

	if (argc != 5)
	{
		perror("Not exact arguments\n");
		return (1);
	}
	ft_memset(&info, 0, sizeof(t_info));
	init_args(argv, envp, &info);
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		//fork fail
		close(fd[STDIN_FILENO]);
		close(fd[STDOUT_FILENO]);		
	}
	if (pid == 0)
	{
		//parent process
		num = 1;
		waitpid(pid, &status, 0);
		redirect_out(info);
		dup_pipe(fd, STDIN_FILENO);
		if (excute_cmd(info, num) == ERROR)
		{	
			perror(info.cmd[num][0]);
			exit(1);
		}
	}
	else
	{
		//child process
		num = 0;
		redirect_in(info);
		dup_pipe(fd, STDOUT_FILENO);
		if (excute_cmd(info, num) == ERROR)
		{
			perror(info.cmd[num][0]);
			exit(1);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:59:21 by junylee           #+#    #+#             */
/*   Updated: 2021/09/15 15:53:40 by junylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect_in(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redirect_out(const char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
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

void	excute_cmd(char *argv, char **envp)
{	
	int i;
	char **path;
	char **cmd;
	char *full_cmd;

	i = 0;
	cmd = ft_split(argv, ' ');
	path = ret_path(envp);
	while (path[i])
	{
		full_cmd = ft_strjoin(path[i], "/");
		full_cmd = ft_strjoin(full_cmd, argv);
		execve(full_cmd, cmd, NULL);
		free(full_cmd);
		i++;
	}
	perror(cmd[0]);
}

void dup_pipe(int fd[2], int io)
{
	dup2(fd[io], io);
	close(fd[STDIN_FILENO]);
	close(fd[STDOUT_FILENO]);
}

int main(int argc, char **argv, char **envp)
{
	int fd[2];
	int status;
	pid_t	pid;

	if (argc != 5)
		return (1);
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
		waitpid(pid, &status, 0);
		redirect_out(argv[4]);
		dup_pipe(fd, STDIN_FILENO);
		excute_cmd(argv[3], envp);
	}
	else
	{
		//child process
		if (access(argv[1], F_OK | R_OK))
		{	
			perror("File is not existing\n");
			return (1); // exit or return?
		}
		redirect_in(argv[1]);
		dup_pipe(fd, STDOUT_FILENO);
		excute_cmd(argv[2], envp);
	}
	return (0);
}

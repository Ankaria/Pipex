/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elerika <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:55:15 by elerika           #+#    #+#             */
/*   Updated: 2022/01/14 22:55:18 by elerika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_search_path(char **path, char **commands, char **env)
{
	char	*slash;
	char	*str;

	while (*path)
	{
		slash = ft_strjoin(*path, "/");
		str = ft_strjoin(slash, *commands);
		path++;
		free(slash);
		if (access(str, F_OK) == 0)
		{
			if (execve(str, commands, env) == -1)
			{
				ft_putstr_fd("Oh no, error execve!\n", 2);
				exit(1);
			}
		}
		free(str);
	}
}

void	run_process(char *argv, char **env)
{
	int		i;
	char	*path;
	char	**commands;
	char	**split_path;

	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (ft_strnstr(env[i], "PATH=", 5))
	{
		path = ft_strnstr(env[i], "PATH=", 5) + 5;
		commands = ft_split(argv, ' ');
		split_path = ft_split(path, ':');
		ft_search_path(split_path, commands, env);
	}
}

static void	child_process(char **argv, int	*pip_fd, char **env)
{
	int	in;

	in = open(argv[1], O_RDONLY);
	dup2(in, 0);
	dup2(pip_fd[1], STDOUT_FILENO);
	close(pip_fd[0]);
	close(pip_fd[1]);
	close(in);
	run_process(argv[2], env);
	exit(1);
}

static void	parent_process(char **argv, int *pip_fd, char **env)
{
	int	out;

	out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	dup2(out, STDOUT_FILENO);
	dup2(pip_fd[0], 0);
	close(pip_fd[1]);
	close(pip_fd[0]);
	close(out);
	run_process(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int	pip_fd[2];
	int	pid;

	if (argc == 5)
	{
		if (open(argv[1], O_RDONLY) == -1 || open(argv[4], \
			O_WRONLY | O_CREAT | O_TRUNC, 0777) == -1)
			ft_error("Oh no, wrong file!\n");
		if (pipe(pip_fd) == -1)
			ft_error("Oh no, pipe not created!\n");
		pid = fork();
		if (pid == -1)
		{
			ft_error("Oh no, fork error!\n");
			exit(1);
		}
		if (pid == 0)
			child_process(argv, pip_fd, env);
		else
			parent_process(argv, pip_fd, env);
	}
	else
		ft_error("Oh no, we don't have 5 arguments!\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:36:13 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/18 11:39:55 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char	*get_path(char *cmd)
{
	t_argv	*path;
	char	**tmp;
	char	*str;

	if (!ft_strncmp("/", cmd, 1) || !ft_strncmp("./", cmd, 2)
		|| !ft_strncmp("../", cmd, 3))
		return (ft_strdup(cmd));
	if (!ft_strncmp("~", cmd, 1))
		return (str3join(ft_strdup(getenv("$HOME")), ft_strdup("/"),
				ft_strdup(cmd + 1)));
	str = get_env(ft_strdup("$PATH"));
	if (!*str)
	{
		free(str);
		return (NULL);
	}
	tmp = ft_split(str, ':');
	free(str);
	path = argv_new((void **)tmp, NULL);
	return (accessable(path, cmd));
}

int	exec_this(t_argv *cmd)
{
	char	*path;
	t_argv	*env;
	int		i;

	folder_operations(cmd);
	if (is_builtin(cmd))
		return (builtin_exec(cmd));
	path = get_path(cmd->array[0]);
	if (!path)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", cmd->array[0]);
		exit(127);
	}
	env = g_et->array[0];
	i = execve(path, (char **)cmd->array, (char **)env->array);
	if (i == -1)
	{
		perror(cmd->array[0]);
		exit(127);
	}
	return (0);
}

int	wait_all(int pid, int max)
{
	int	i;
	int	st;
	int	last_pid;

	i = 0;
	while (i < max)
	{
		if (waitpid(0, &st, 0) == pid)
			last_pid = st;
		i++;
	}
	return (last_pid >> 8);
}

void	pre_exec(t_argv *trgt, t_info info)
{
	if (info.i != 0)
	{
		dup2(info.fd, 0);
		close(info.fd);
	}
	if (info.i != info.max_proc - 1)
		dup2(info.io[1], 1);
	close(info.io[0]);
	close(info.io[1]);
	exit(exec_this(trgt));
}

int	exec_all(t_argv *exec, int max_proc)
{
	int		pid;
	int		fd;
	int		i;
	int		io[2];
	t_argv	*trgt;

	i = 0;
	fd = 0;
	while (i < max_proc)
	{
		trgt = get_trgt(exec);
		pipe(io);
		pid = fork();
		if (pid == 0)
			pre_exec(trgt, (t_info){i, fd, io, max_proc});
		argv_destroy(trgt, (void (*)(void *))free);
		if (i != 0)
			close(fd);
		close(io[1]);
		fd = io[0];
		if (i == max_proc - 1)
			close(fd);
		++i;
	}
	return (wait_all(pid, max_proc));
}

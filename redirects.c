/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:32:21 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/18 16:34:41 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	infile_op(t_argv *cmd, int io[])
{
	char	*str;
	char	*tmp;

	tmp = NULL;
	str = (char *)cmd->array[cmd->try_index + 1];
	if (str[0] == '~')
		tmp = ft_strjoin(get_env(ft_strdup("$HOME")), tmp + 1);
	else
		tmp = ft_strdup(str);
	(io)[0] = open(tmp, O_RDONLY);
	free(tmp);
	if ((io)[0] == -1)
	{
		ft_fprintf(2, "minishell: %s: No such file or directory",
			cmd->array[cmd->try_index + 1]);
		exit(127);
	}
	dup2((io)[0], STDIN_FILENO);
	close((io)[0]);
	argv_del_one(cmd, cmd->try_index, free);
	argv_del_one(cmd, cmd->try_index, free);
}

void	outfile_op(t_argv *cmd, int io[])
{
	char	*str;
	char	*tmp;

	tmp = NULL;
	str = (char *)cmd->array[cmd->try_index + 1];
	if (str[0] == '~')
		tmp = ft_strjoin(get_env(ft_strdup("$HOME")), tmp + 1);
	else
		tmp = ft_strdup(str);
	(io)[1] = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(tmp);
	if ((io)[1] == -1)
	{
		ft_fprintf(2, "minishell: %s: No such file or directory\n",
			cmd->array[cmd->try_index + 1]);
		exit(127);
	}
	dup2((io)[1], STDOUT_FILENO);
	close((io)[1]);
	argv_del_one(cmd, cmd->try_index, free);
	argv_del_one(cmd, cmd->try_index, free);
}

void	append_op(t_argv *cmd, int io[])
{
	char	*str;
	char	*tmp;

	tmp = NULL;
	str = (char *)cmd->array[cmd->try_index + 1];
	if (str[0] == '~')
		tmp = ft_strjoin(get_env(ft_strdup("$HOME")), tmp + 1);
	else
		tmp = ft_strdup(str);
	(io)[1] = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(tmp);
	if ((io)[1] == -1)
	{
		ft_fprintf(2, "minishell: %s: No such file or directory\n",
			cmd->array[cmd->try_index + 1]);
		exit(127);
	}
	dup2((io)[1], STDOUT_FILENO);
	close((io)[1]);
	argv_del_one(cmd, cmd->try_index, free);
	argv_del_one(cmd, cmd->try_index, free);
}

void	heredoc_op(t_argv *cmd, int io[])
{
	pipe((io));
	write((io)[1], cmd->array[cmd->try_index + 1],
		ft_strlen(cmd->array[cmd->try_index + 1]));
	close((io)[1]);
	dup2((io)[0], 0);
	close((io)[0]);
	argv_del_one(cmd, cmd->try_index, free);
	argv_del_one(cmd, cmd->try_index, free);
}

void	folder_operations(t_argv *cmd)
{
	int		io[2];
	size_t	i;

	i = 0;
	while (i < cmd->len)
	{
		cmd->try_index = 0;
		if (argv_try(cmd, "<", cmd->try_index, (int (*)(void *,
					void *))ft_strcmp) == 0)
			infile_op(cmd, io);
		else if (argv_try(cmd, ">", cmd->try_index, (int (*)(void *,
					void *))ft_strcmp) == 0)
			outfile_op(cmd, io);
		else if (argv_try(cmd, ">>", cmd->try_index, (int (*)(void *,
					void *))ft_strcmp) == 0)
			append_op(cmd, io);
		else if (argv_try(cmd, "<<", cmd->try_index, (int (*)(void *,
					void *))ft_strcmp) == 0)
			heredoc_op(cmd, io);
		else
			i++;
	}
}

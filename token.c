/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:03:45 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/18 12:31:19 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	is_token(char *line)
{
	if (ft_strchr("|<>", *line))
		return (1);
	return (0);
}

char	*lexer_token(t_argv *cmd, char *line)
{
	char	*str;

	str = NULL;
	if (is_token(line))
	{
		if (!ft_strncmp("<<", line, 2))
			str = ft_strdup("<<");
		else if (!ft_strncmp(">>", line, 2))
			str = ft_strdup(">>");
		else if (!ft_strncmp("|", line, 1))
			str = ft_strdup("|");
		else if (!ft_strncmp(">", line, 1))
			str = ft_strdup(">");
		else if (!ft_strncmp("<", line, 1))
			str = ft_strdup("<");
		argv_push(cmd, str);
		line += ft_strlen(str);
	}
	return (line);
}

char	*heredoc_operation(char *line)
{
	char	*str;
	char	*read;
	int		save;

	save = dup(0);
	str = ft_strdup("");
	if (!line || !*line)
		return (str);
	while (1)
	{
		signal(SIGINT, (void (*)(int))signal_handler);
		signal(SIGQUIT, SIG_IGN);
		read = readline("> ");
		if (!read)
			break ;
		if (!ft_strcmp(line, read))
			break ;
		str = str3join(str, read, ft_strdup("\n"));
	}
	if (read)
		free(read);
	dup2(save, 0);
	close(save);
	return (str);
}

int	heredoc_check(t_argv *cmd)
{
	char	*tmp;

	cmd->try_index = 0;
	while (argv_try(cmd, "<<", cmd->try_index, (int (*)(void *,
				void *))ft_strcmp) == 0)
	{
		tmp = heredoc_operation(cmd->array[cmd->try_index + 1]);
		argv_del_one(cmd, cmd->try_index + 1, free);
		argv_insert(cmd, cmd->try_index + 1, tmp);
		cmd->try_index++;
	}
	return (0);
}

int	lexer(t_argv *cmd, char *line, int status)
{

	while (line && *line)
	{
		line = lexer_token(cmd, line);
		while (ft_isspace(*line))
			line++;
		line = lexer_word_plus_quote(cmd, line, status);
		if (line == NULL)
			return (-1);
		while (ft_isspace(*line))
			line++;
	}
	return (0);
}

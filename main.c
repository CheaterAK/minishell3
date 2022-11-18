/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:32:26 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/18 16:40:03 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "minishell.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int		argv_try(t_argv *argv, void *addr, size_t index, int (*fptr)(void *,
				void *));

void	signal_handler(int sig)
{
	(void)sig;
	g_et->try_index = 1;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

t_argv	*quote_err(char *line, t_argv *cmd, int *status)
{
	free(line);
	argv_destroy(cmd, free);
	ft_fprintf(2,
		"minishell: syntax error detected an unclosed quote(s)\n");
	*status = 258;
	return (NULL);
}

t_argv	*get_cmd(char *line, int *status)
{
	t_argv	*cmd;
	char	*str;

	if (line[0] == '\0' || check_line(line))
	{
		free(line);
		return (NULL);
	}
	cmd = argv_new(NULL, NULL);
	add_history(line);
	if (lexer(cmd, line, *status))
		return (quote_err(line, cmd, status));
	free(line);
	str = check_token(cmd);
	if (str || heredoc_check(cmd))
	{
		printf("minishell: syntax error near unexpected token `%s'\n", str);
		if (str)
			free(str);
		*status = 258;
		argv_destroy(cmd, free);
		return (NULL);
	}
	return (cmd);
}

void	minishell(int *status)
{
	char	*line;
	t_argv	*cmd;

	while (1)
	{
		signal(SIGINT, (void (*)(int))signal_handler);
		signal(SIGQUIT, SIG_IGN);
		if (g_et->try_index != 0)
		{
			*status = g_et->try_index;
			g_et->try_index = 0;
		}
		line = readline("$> ");
		if (line == NULL)
			break ;
		cmd = get_cmd(line, status);
		if (cmd == NULL)
			continue ;
		else if (argv_try(cmd, "|", 0, (int (*)(void *, void *))ft_strcmp) != 0
				&& is_builtin(cmd))
			*status = builtin_op(cmd);
		else
			*status = exec_all(cmd, find_procces_size(cmd));
		argv_destroy(cmd, free);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	t_argv	*env;

	g_et = argv_new(NULL, NULL);
	argv_push(g_et, argv_new((void **)envp, (void *(*)(void *))ft_strdup));
	argv_push(g_et, argv_new(NULL, NULL));
	env = g_et->array[0];
	status = 0;
	(void)argc;
	(void)argv;
	minishell(&status);
	return (0);
}

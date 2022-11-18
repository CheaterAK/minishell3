/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:32:42 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/18 16:30:06 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>

int	ft_env(void)
{
	t_argv	*env;
	size_t	i;

	i = 0;
	env = g_et->array[0];
	while (i < env->len)
		ft_printf("%s\n", env->array[i++]);
	return (0);
}

int	ft_exit(t_argv *cmd)
{
	if (cmd->len == 1)
		exit(0);
	else if (cmd->len >= 2)
	{
		if (argv_is(cmd, 1, (int (*)(int))ft_isdigit) == 1)
		{
			if (cmd->len > 2)
			{
				ft_fprintf(2, "exit: too many arguments\n");
				return (1);
			}
			exit(ft_atoi(cmd->array[1]) % 256);
		}
		else
		{
			ft_fprintf(2, "exit: %s: numeric argument required\n",
				(char *)cmd->array[1]);
			exit(2);
		}
	}
	exit(0);
}

int	is_valid_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		++i;
	while (str[i])
	{
		if (str[i] == 'n')
			++i;
		else
			return (0);
	}
	return (1);
}

void	check_n(size_t *i, int *n, t_argv *cmd)
{
	while (*i < cmd->len)
	{
		if (is_valid_n(cmd->array[*i]))
		{
			(*n) = 1;
			++(*i);
		}
		else
			break ;
	}
}

int	ft_echo(t_argv *cmd)
{
	size_t	i;
	int		n;

	i = 1;
	n = 0;
	if (cmd->len == 1)
		ft_printf("\n");
	else
	{
		check_n(&i, &n, cmd);
		while (i < cmd->len)
		{
			ft_printf("%s", cmd->array[i]);
			if (i < cmd->len - 1)
				ft_printf(" ");
			i++;
		}
		if (n == 0)
			ft_printf("\n");
	}
	return (0);
}

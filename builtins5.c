/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:32:32 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/18 16:32:30 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>

int	compare_env(char *s1, char *s2)
{
	int		res;
	char	*tmp;

	tmp = ft_strjoin(s2, "=");
	res = ft_strncmp(s1, tmp, ft_strlen(tmp));
	free(tmp);
	return (res);
}

int	compare_exp(char *s1, char *s2)
{
	int		res;
	char	*tmp;

	tmp = ft_strjoin(s1, "=");
	res = ft_strncmp(s2, tmp, ft_strlen(tmp));
	free(tmp);
	return (res);
}

int	unset(char *tmp, t_argv *cmd, int status, int i)
{
	t_argv	*env;
	t_argv	*exp;

	env = g_et->array[0];
	exp = g_et->array[1];
	tmp = NULL;
	if (ft_isstring(cmd->array[i]))
	{
		tmp = ft_strjoin(cmd->array[i], "=");
		if (argv_try(exp, cmd->array[i], 0, (int (*)(void *,
					void *))ft_strcmp) == 0)
			argv_del_one(exp, exp->try_index, free);
		else if (argv_try(env, tmp, env->try_index, (int (*)(void *,
					void *))compare_this) == 0)
			argv_del_one(env, env->try_index, free);
	}
	else
	{
		ft_fprintf(2, "minishell: unset: `%s': not a valid identifier\n",
			cmd->array[i++]);
		status = 1;
	}
	if (tmp)
		free(tmp);
	return (status);
}

int	ft_unset(t_argv *cmd)
{
	t_argv	*env;
	size_t	i;
	int		status;
	char	*tmp;

	tmp = NULL;
	i = 1;
	status = 0;
	env = g_et->array[0];
	while (i < cmd->len)
	{
		env->try_index = 0;
		status = unset(tmp, cmd, status, i);
		++i;
	}
	return (status);
}

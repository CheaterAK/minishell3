/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:32:36 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/18 16:31:25 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>

char	*get_env(char *str)
{
	t_argv	*env;
	char	*tmp;
	char	*ret;

	env = g_et->array[0];
	tmp = ft_strjoin(str + 1, "=");
	free(str);
	if (argv_try(env, tmp, 0, (int (*)(void *, void *))env_cmp) == 0)
	{
		ret = ft_substr(env->array[env->try_index], ft_strlen(tmp),
				ft_strlen(env->array[env->try_index]) - ft_strlen(tmp));
		free(tmp);
		return (ret);
	}
	else
	{
		free(tmp);
		return (ft_strdup(""));
	}
}

int	compare_this(char *s1, char *s2)
{
	int		res;
	char	*tmp;

	tmp = ft_strchr(s2, '=');
	res = ft_strncmp(s2, s1, tmp - s2 + 1);
	return (res);
}

void	exp_push(t_argv *cmd, int i)
{
	t_argv	*env;
	t_argv	*exp;

	env = g_et->array[0];
	exp = g_et->array[1];
	if (argv_try(exp, cmd->array[i], 0, (int (*)(void *, void *))ft_strcmp)
		&& argv_try(env, cmd->array[i], 0, (int (*)(void *,
					void *))compare_env))
		argv_push(exp, ft_strdup(cmd->array[i]));
}

int	env_push(t_argv *cmd, t_argv *exp, int i, int status)
{
	t_argv	*env;

	env = g_et->array[0];
	if (argv_try(exp, cmd->array[i], 0, (int (*)(void *,
				void *))compare_exp) == 0)
	{
		argv_del_one(exp, exp->try_index, free);
		argv_push(env, ft_strdup(cmd->array[i]));
	}
	else if ((argv_try(env, cmd->array[i], 0, (int (*)(void *, void *)) \
	compare_this) == 0) && ft_is_valid_env(cmd->array[i]))
	{
		argv_del_one(env, env->try_index, free);
		argv_insert(env, env->try_index, ft_strdup(cmd->array[i]));
	}
	else if ((argv_try(env, cmd->array[i], 0, (int (*)(void *, void *)) \
	compare_this) != 0 && ft_is_valid_env(cmd->array[i])))
		argv_push(env, ft_strdup(cmd->array[i]));
	else
		status = ft_fprintf(2, "minishell: export: `%s': not a\
 valid identifier\n", cmd->array[i]);
	return (status && 1);
}

int	ft_export(t_argv *cmd)
{
	t_argv	*exp;
	t_argv	*env;
	size_t	i;
	int		status;

	i = 1;
	status = 0;
	exp = g_et->array[1];
	env = g_et->array[0];
	if (cmd->len == 1)
		env_print(env);
	while (i < cmd->len)
	{
		env->try_index = 0;
		exp->try_index = 0;
		if (ft_isstring(cmd->array[i]))
			exp_push(cmd, i);
		else
			status = env_push(cmd, exp, i, status);
		++i;
	}
	return (status && 1);
}

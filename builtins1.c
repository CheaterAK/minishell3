/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:32:45 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/18 16:28:10 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static char	*get_path(char *tmp, t_argv *cmd)
{
	char	*path;

	if (tmp[0] == '~' || cmd->len == 1)
	{
		path = str3join(get_env(ft_strdup("$HOME")), ft_strdup(""),
				ft_strdup(tmp + 1));
		free(tmp);
	}
	else
		path = tmp;
	return (path);
}

int	cd_err(char *path)
{
	if (!access(path, F_OK))
	{
		ft_fprintf(2, "minishell: cd: %s: Not a directory\n", path);
		free(path);
		return (1);
	}
	else
	{
		ft_fprintf(2, "minishell: cd: %s: No such file or directory\n", path);
		free(path);
		return (1);
	}
}

int	change_directory(char *path)
{
	t_argv	*env;
	char	*pwd;
	char	cwd[512];

	env = g_et->array[0];
	free(path);
	env->try_index = 0;
	getcwd(cwd, 512);
	if (argv_try(env, "OLDPWD=", 0, (int (*)(void *, void *))env_cmp) == 0)
	{
		pwd = get_env(ft_strdup("$PWD"));
		argv_del_one(env, env->try_index, free);
		argv_insert(env, env->try_index, ft_strjoin("OLDPWD=", pwd));
		free(pwd);
	}
	env->try_index = 0;
	if (argv_try(env, "PWD=", 0, (int (*)(void *, void *))env_cmp) == 0)
		argv_del_one(env, env->try_index, (void (*)(void *))free);
	argv_insert(env, env->try_index, ft_strjoin("PWD=", cwd));
	return (0);
}

int	ft_cd(t_argv *cmd)
{
	char	*path;
	char	*tmp;

	tmp = ft_strdup(cmd->array[1]);
	path = get_path(tmp, cmd);
	if (0 == chdir(path))
		change_directory(path);
	else
		return (cd_err(path));
	return (0);
}

int	ft_pwd(void)
{
	char	path[512];

	getcwd(path, 512);
	ft_printf("%s\n", path);
	return (0);
}

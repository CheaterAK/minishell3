/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:11:17 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/18 15:11:18 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "minishell.h"
#include <fcntl.h>

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

char	*check_token(t_argv *cmd)
{
	size_t	i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (i < cmd->len)
	{
		tmp = (char *)cmd->array[i];
		if (ft_strchr("<>|", tmp[0]) && *tmp)
		{
			tmp2 = cmd->array[++i];
			if (!tmp2 || *tmp2 == '\0')
			{
				if (cmd->array[i + 1] == NULL || cmd->len < i + 1)
					return (ft_strdup("newline"));
				tmp = cmd->array[++i];
				if (ft_strchr("<>|", tmp[0]) || !tmp)
					return (ft_strdup(tmp));
				else if (!tmp || *tmp == '\0')
					return (ft_strdup("newline"));
			}
		}
		i++;
	}
	return (NULL);
}

int	check_line(char *line)
{
	while (line && *line)
	{
		if (ft_isspace(*line))
			line++;
		else
			return (0);
	}
	return (1);
}

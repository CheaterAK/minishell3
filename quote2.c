/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:38:13 by akocabas          #+#    #+#             */
/*   Updated: 2022/11/18 12:38:14 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "minishell.h"
#include <fcntl.h>

char	*jump_to_double_quote(char *line)
{
	char	*len;

	len = ft_strchr(line + 1, '\"');
	if (len == 0)
		return (NULL);
	else
		len = len - line + (char *)1;
	return (ft_substr(line, 0, (size_t)len));
}

char	*jump_to_single_quote(char *line)
{
	char	*len;

	len = ft_strchr(line + 1, '\'');
	if (len == 0)
		return (0);
	else
		len = len - line + (char *)1;
	return (ft_substr(line, 0, (size_t)len));
}

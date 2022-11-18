/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akocabas <akocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:28:32 by akocabas          #+#    #+#             */
/*   Updated: 2022/01/19 12:36:32 by akocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*n_lst;

	n_lst = malloc(sizeof(t_list));
	if (!n_lst)
		return (NULL);
	n_lst -> content = content;
	n_lst -> next = NULL;
	return (n_lst);
}

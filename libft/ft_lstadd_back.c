/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 08:42:25 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/11/07 14:16:41 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*buf;

	buf = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (buf->next != NULL)
			buf = buf->next;
		buf->next = new;
	}
}

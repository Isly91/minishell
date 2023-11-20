/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 08:44:49 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/11/08 13:00:40 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del) (void *))
{
	t_list	*buf;

	while (*lst)
	{
		buf = *lst;
		*lst = (*lst)->next;
		del(buf->content);
		free(buf);
	}
	*lst = NULL;
}

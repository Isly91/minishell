/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 08:46:53 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/11/08 17:00:27 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*mfree(t_list **lst, void (*del) (void *))
{
	t_list	*buf;

	while (*lst)
	{
		buf = *lst;
		*lst = (*lst)->next;
		del(buf->content);
		free(buf);
	}
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f) (void *), void (*del) (void *))
{
	t_list	*newlist;
	t_list	*head;

	if (!lst)
		return (NULL);
	newlist = malloc(sizeof(t_list));
	if (!newlist)
		return (NULL);
	newlist->content = f(lst->content);
	head = newlist;
	lst = lst->next;
	while (lst)
	{
		newlist->next = malloc(sizeof(t_list));
		if (!newlist->next)
			return (mfree(&head, del));
		newlist->next->content = f(lst->content);
		newlist = newlist->next;
		lst = lst->next;
	}
	newlist->next = NULL;
	return (head);
}

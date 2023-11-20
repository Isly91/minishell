/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 08:45:58 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/11/07 14:54:56 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f) (void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

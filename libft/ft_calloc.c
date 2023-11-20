/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 18:46:57 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/11/07 10:08:26 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*am;

	am = malloc (count * size);
	if (!am)
		return (NULL);
	ft_bzero(am, count * size);
	return (am);
}

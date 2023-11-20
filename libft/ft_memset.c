/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 14:39:31 by jvorstma      #+#    #+#                 */
/*   Updated: 2022/11/07 10:11:43 by jvorstma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*d;

	d = b;
	while (len > 0)
	{
		*d = (unsigned char) c;
		len--;
		d++;
	}
	return (b);
}

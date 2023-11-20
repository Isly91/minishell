/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvorstma <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/07 18:16:21 by jvorstma      #+#    #+#                 */
/*   Updated: 2023/10/11 18:17:44 by jvorstma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_two_d_arr_len(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_executable_path_size(char **executable_path)
{
	int	i;

	i = 0;
	while (executable_path && executable_path[i])
		i++;
	return (i);
}

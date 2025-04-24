/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chdir_command.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 19:00:30 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/07 16:33:42 by ibehluli      ########   odam.nl         */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 18:59:22 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/08 10:51:18 by ibehluli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo_command(t_main *main, char **cmd)
{
	int		i;

	i = 1;
	if (!main || !cmd)
		return ;
	if (!ft_strcmp(cmd[i], "-n"))
		i++;
	while (cmd[i])
	{
		if (!ft_print_fd(cmd[i], main->fd[1]))
			return ;
		if (cmd[i + 1] && !ft_print_fd(" ", main->fd[1]))
			return ;
		i++;
	}
	if (ft_strcmp(cmd[1], "-n"))
	{
		if (ft_print_fd("\n", main->fd[1]) == 0)
			return ;
	}
}

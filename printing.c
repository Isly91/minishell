/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printing.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 14:08:20 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/13 11:11:55 by ibehluli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_fd(char *str, int fd)
{
	if (write(fd, str, ft_strlen(str)) < 0)
		return (0);
	return (1);
}

void	ft_print_list(t_env *env_parameters, int size, t_main *main)
{
	int	i;
	int	x;

	i = 0;
	x = 1;
	if (!main)
		return ;
	if (!env_parameters)
		ft_exit_code_change(main, 130);
	while (i < size && env_parameters)
	{
		x *= ft_print_fd(env_parameters->key, main->fd[1]);
		x *= ft_print_fd("=", main->fd[1]);
		x *= ft_print_fd(env_parameters->value, main->fd[1]);
		x *= ft_print_fd("\n", main->fd[1]);
		env_parameters = env_parameters->next;
		i++;
	}
	if (x == 0)
		ft_exit_code_change(main, 6);
}

void	ft_print_char_double(t_main *main, char **env_parameters)
{
	int	i;
	int	x;

	i = 0;
	x = 1;
	if (!main)
		return ;
	if (!env_parameters)
		ft_exit_code_change(main, 130);
	while (env_parameters[i])
	{
		x *= ft_print_fd(env_parameters[i], main->fd[1]);
		x *= ft_print_fd("\n", main->fd[1]);
		i++;
	}
	if (x == 0)
		ft_exit_code_change(main, 6);
}

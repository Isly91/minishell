/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 18:53:08 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/17 10:29:00 by ibehluli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	other_command_status(t_main *main, int status)
{
	if (!main)
		main->exit_code = 1;
	else if (status + 128 == 130)
	{
		main->exit_code = status + 128;
		ft_print_fd("\n", 2);
	}
	else if (status == 131)
		main->exit_code = status;
	else
		main->exit_code = WEXITSTATUS(status);
}

void	ft_exit_code_change(t_main *main, int x)
{
	if (!main)
		return ;
	if (main->exit_code == 0)
		main->exit_code = x;
}

static int	ft_is_valid_code(char *str)
{
	int				i;
	unsigned long	num;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (!ft_strcmp(&str[i], "-9223372036854775808"))
		return (1);
	if ((str[i] == '-' || str[i] == '+'))
		i++;
	num = 0;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - 48);
		if (num > LONG_MAX)
			return (0);
		i++;
	}
	if (str[i])
		return (0);
	else
		return (1);
}

void	ft_exit_command(t_main *main, char **cmd)
{
	if (main && cmd && cmd[0] && cmd[1] && ft_is_valid_code(cmd[1]) && cmd[2])
	{
		ft_print_fd("exit\nminishell: exit: too many arguments\n", 2);
		return (ft_exit_code_change(main, 1));
	}
	else if (main && cmd && cmd[0] && cmd[1])
	{
		ft_print_fd("exit\n", 1);
		if (ft_is_valid_code(cmd[1]) && !cmd[2])
			ft_exit_code_change(main, (ft_atoi(cmd[1]) % 256));
		else if (!ft_is_valid_code(cmd[1]))
		{
			ft_print_fd(" exit: ", 2);
			ft_print_fd(cmd[1], 2);
			ft_print_fd(": numeric argument required\n", 2);
			ft_exit_code_change(main, 2);
		}
	}
	else
	{
		if (main->old_exit_code != 0)
			ft_exit_code_change(main, main->old_exit_code);
		ft_print_fd("exit\n", 1);
	}
	exit(main->exit_code);
}

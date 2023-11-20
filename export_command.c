/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_command.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 18:57:50 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/13 10:30:53 by ibehluli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if not, error message: -bash: export: '1=a': not a valid identifier 

static void	ft_print_export_only(t_main *main)
{
	t_env	*current;
	int		i;

	if (!main)
		return (ft_exit_code_change(main, 1));
	current = *main->env_parameters;
	while (current)
	{
		i = ft_print_fd("declare -x ", main->fd[1]);
		i *= ft_print_fd(current->key, main->fd[1]);
		i *= ft_print_fd("=", main->fd[1]);
		i *= ft_print_fd(current->value, main->fd[1]);
		i *= ft_print_fd("\n", main->fd[1]);
		if (i == 0)
			return (ft_exit_code_change(main, 6));
		current = current->next;
	}
}

static void	ft_make_new_struct(t_main *main, char **key_val)
{
	t_env	*new_struct;

	if (!main || !key_val)
		return (ft_exit_code_change(main, 1));
	if (!ft_valid_key_name(key_val[0]))
		return (ft_exit_code_change(main, 20));
	new_struct = malloc(sizeof(t_env));
	if (!new_struct)
		return (ft_exit_code_change(main, 3));
	new_struct->next = NULL;
	new_struct->key = ft_strdup(key_val[0]);
	new_struct->value = ft_strdup(key_val[1]);
	ft_add_env_var(main, new_struct);
}

static	void	making_key(t_main *main, char	**key_val)
{
	int		x;

	x = ft_check_if_key_exist(main, key_val[0], key_val[1]);
	if (x == 1)
		ft_update_env_key(main, key_val);
	else if (x != 2)
		ft_make_new_struct(main, key_val);
	else
		ft_exit_code_change(main, 1);
}

static void	ft_export_utils(t_main *main, char *str)
{
	char	**key_val;

	if (!main || !str)
		return (ft_exit_code_change(main, 1));
	if (!str[0] || str[0] == '=')
	{
		ft_print_fd(" not a valid identifier\n", 2);
		main->exit_code = 1;
		return ;
	}
	key_val = ft_split(str, '=');
	if (!key_val)
		return (ft_exit_code_change(main, 1));
	if (ft_valid_key_name(key_val[0]) == 0)
	{
		ft_print_fd(" not a valid identifier\n", 2);
		main->exit_code = 1;
	}
	else
		making_key(main, key_val);
	ft_free_double_array(key_val);
}

void	ft_export_command(t_main *main, char **cmd)
{
	int			i;

	if (!main || !cmd)
		return (ft_exit_code_change(main, 1));
	i = 1;
	while (cmd && cmd[i])
	{
		if (ft_equal_in_a_str(cmd[i]) == 1)
			ft_export_utils(main, cmd[i]);
		else if (ft_valid_key_name(cmd[i]) == 0)
		{
			ft_print_fd(" not a valid identifier\n", 2);
			main->exit_code = 1;
		}
		i++;
	}
	if (!cmd[i] && i == 1)
		ft_print_export_only(main);
}

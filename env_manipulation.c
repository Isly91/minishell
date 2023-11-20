/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_manipulation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/09 09:32:31 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/13 12:47:45 by ibehluli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_key_value(t_main *main, char *key)
{
	t_env	*current;
	char	*value;

	if (!key || !main)
		return (ft_exit_code_change(main, 1), NULL);
	current = *main->env_parameters;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			value = current->value;
			break ;
		}
		else
			value = NULL;
		current = current->next;
	}
	return (value);
}

void	ft_update_env_key(t_main *main, char **keys_values)
{
	t_env	*current;

	if (!main || !keys_values)
		return (ft_exit_code_change(main, 1));
	current = *(main->env_parameters);
	while (current)
	{
		if (ft_strcmp(current->key, keys_values[0]) == 0)
		{
			ft_free_single_array(current->value);
			current->value = ft_strdup(keys_values[1]);
			break ;
		}
		current = current->next;
	}
}

int	ft_valid_key_name(char *key)
{
	int	i;

	i = 0;
	if (!key)
		return (0);
	while (key && key[i])
	{
		if (key[i] == '_')
			i++;
		else if (ft_isalpha(key[i]) == 1)
			i++;
		else if (ft_isdigit(key[i]) == 1 && i != 0)
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_update_env_value(t_main *main, char *key, char *new_value)
{
	t_env	*current;

	if (!main || !key || !new_value)
		return (ft_exit_code_change(main, 1));
	current = *(main->env_parameters);
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			ft_free_single_array(current->value);
			current->value = ft_strdup(new_value);
			break ;
		}
		current = current->next;
	}
}

void	ft_add_env_var(t_main *main, t_env *new_struct)
{
	t_env	*current;
	int		i;

	if (!main || !new_struct)
		return (ft_exit_code_change(main, 1));
	i = 0;
	main->env_size++;
	current = *main->env_parameters;
	while (i < main->env_size - 2)
	{
		current = current->next;
		i++;
	}
	current->next = new_struct;
}

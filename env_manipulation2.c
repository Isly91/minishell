/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_manipulation2.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 19:16:31 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/08/25 19:18:26 by ibehluli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_key_value(t_main *main, char *value)
{
	t_env	*current;

	if (!main || !main->env_parameters)
		return (0);
	current = *(main->env_parameters);
	while (current)
	{
		if (ft_strcmp(current->value, value) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

int	ft_check_if_key_exist(t_main *main, char *key, char *value)
{
	t_env	*current;

	if (!main && main->env_parameters)
		return (0);
	current = *(main->env_parameters);
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (1 + ft_check_key_value(main, value));
		current = current->next;
	}
	return (0);
}

void	ft_search_remove_key_value(t_main *main, char *key)
{
	t_env	*current;
	t_env	*previous;

	if (!key || !main)
		return (ft_exit_code_change(main, 1));
	current = *(main->env_parameters);
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				*(main->env_parameters) = current->next;
			ft_free_single_array(current->key);
			ft_free_single_array(current->value);
			if (current)
				free(current);
			main->env_size--;
			break ;
		}
		previous = current;
		current = current->next;
	}
}

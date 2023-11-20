/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handling.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/18 12:16:40 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/13 12:40:42 by ibehluli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_on = 0;

static void	ft_signal_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		g_signal_on = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	*ft_signal_buf(t_main *main)
{
	char	*buf;

	if (g_signal_on == 1)
	{
		buf = ft_itoa(130);
		g_signal_on = 0;
	}
	else
		buf = ft_itoa(main->old_exit_code);
	return (buf);
}

void	ft_signal(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

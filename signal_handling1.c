/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handling1.c                                 :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: ibehluli <ibehluli@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/13 12:37:01 by ibehluli      #+#    #+#                 */
/*   Updated: 2023/11/15 16:05:04 by jvorstma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_signal_here_doc(int sig_num)
{
	if (sig_num == SIGINT)
	{
		printf("\n");
		exit(130);
	}
}

void	ft_child_signal(void)
{
	signal(SIGINT, ft_signal_here_doc);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_sigign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

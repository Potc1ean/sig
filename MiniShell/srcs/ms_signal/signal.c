#include "../../includes/minishell.h"

void exec_signal(int signal)
{
	if (!kill(ft_getpid(), signal))
	{
		if (signal == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
		}
		else if (signal == SIGINT)
		{
			ft_putstr_fd("\n", 1);
		}
	}
	else if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		// et il me faut le prompt
	}
}

void handler_signal(int signal)
{
    if (signal == SIGINT)
    {
        ft_putstr_fd("\nminishel$\b", 1);
    }
}
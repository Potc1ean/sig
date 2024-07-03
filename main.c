/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichpakov <ichpakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:52:31 by njeanbou          #+#    #+#             */
/*   Updated: 2024/07/03 14:08:03 by ichpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_data(t_params **para, t_put **put, t_data **data)
{
	*para = (t_params *)malloc (sizeof(t_params));
	*put = (t_put *) malloc (sizeof(t_put));
	*data = NULL;
	*data = malloc(sizeof(t_data));
	(*data)->fd_in = -2;
	(*put)->input = NULL;
	(*put)->output = NULL;
}

void	loop_shell(t_params *para, t_env *lstenv, t_put *put, t_data *data)
{
	int		error;
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (input != NULL)
		{
			init_data(&para, &put, &data);
			if (ft_strstr(input, "<<") == NULL)
				add_history(input);
			error = set_para(&para, input, &lstenv, &put);
			if (error == 0 && para->com[0] != NULL)
				add_status(&lstenv, ms_exec_loop(data, &para, put, &lstenv));
			if (error != 0)
			{
				print_error(error, input);
				free_error(&para, &put, &data);
			}
			else
				free_all(&para, &put, &data);
		}
		else if (isatty(STDIN_FILENO) == 0)
			exit(EXIT_FAILURE);
	}
}

static void	incr_shlvl(t_env **env)
{
	t_env	*head;
	int		lvl;

	head = *env;
	while (head != NULL)
	{
		if (ft_strequal(head->env_name, "SHLVL") == 0)
		{
			lvl = ft_atoi(head->env_value);
			lvl++;
			free(head->env_value);
			head->env_value = ft_itoa(lvl);
		}
		head = head->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_params	*para;
	t_env		*lstenv;
	t_put		*put;
	t_data		*data;

	para = NULL;
	put = NULL;
	data = NULL;
	if (argc < 1 || argv[1] != NULL)
		exit(EXIT_FAILURE);
	lstenv = set_env(env);
	incr_shlvl(&lstenv);
	signal(SIGINT, handler_signal);
	loop_shell(para, lstenv, put, data);
	return (0);
}

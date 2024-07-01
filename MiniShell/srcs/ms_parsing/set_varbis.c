/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_varbis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:32:47 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/19 16:43:57 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	var_count(char *var, int len)
{
	int	i;

	i = 0;
	if (len == 0)
	{
		while (var[len] != '\0')
		{
			if (var[len] == '=')
				return (len);
			len++;
		}
	}
	else
	{
		while (var[len] != '\0')
		{
			len++;
			i++;
		}
	}
	return (i - 1);
}

static char	**var_split(char *var)
{
	int		len;
	int		i;
	char	**line;

	i = 0;
	line = (char **)malloc (3 * sizeof(char *));
	len = var_count(var, 0);
	line[0] = (char *)malloc ((len + 1) * sizeof(char));
	while (var[i] != '=' && var[i] != '\0')
	{
		line[0][i] = var[i];
		i++;
	}
	line[0][i] = '\0';
	i++;
	len = var_count(var, len);
	line[1] = (char *)malloc ((len + 1) * sizeof(char));
	len = 0;
	while (var[i] != '\0')
		line[1][len++] = var[i++];
	line[1][len] = '\0';
	line[2] = NULL;
	return (line);
}

static void	varbis(char *var, t_env **env)
{
	t_env	*head;
	t_env	*new;
	char	**line;
	bool	new_var;

	head = *env;
	new_var = false;
	line = var_split(var);
	while (head != NULL)
	{
		if (ft_strequal(head->env_name, line[0]) == 0)
		{
			free(head->env_value);
			head->env_value = ft_strdup(line[1]);
			new_var = true;
		}
		head = head->next;
	}
	if (new_var == false)
	{
		new = new_node(line[0], line[1], false);
		ft_lstadd_back_env(env, new);
	}
	ft_free_tab(line);
}

void	set_varbis(t_params **para, t_env **env)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while ((*para)->com[z] != NULL && (*para)->com[z][0] != '\0')
	{
		if (ft_strstr((*para)->com[z], "=") == NULL)
			break ;
		if ((*para)->com[z + 1] == NULL && (*para)->com[z][0] == '=')
			return ;
		while ((*para)->com[z] != NULL && (*para)->com[z][i] != '\0')
		{
			if ((*para)->com[z][i] == '=')
			{
				varbis((*para)->com[z], env);
				free((*para)->com[z]);
				(*para)->com[z] = NULL;
				break ;
			}
			i++;
		}
		z++;
	}
	return ;
}

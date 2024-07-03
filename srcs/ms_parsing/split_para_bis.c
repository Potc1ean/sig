/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_para_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:58:31 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/05 17:34:13 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				return (-1);
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"' && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				return (-1);
		}
		i++;
	}
	return (0);
}

int	count_quote(char *str, int *i)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'')
			(*i)++;
		return (1);
	}
	if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] != '\"')
			(*i)++;
		return (1);
	}
	return (0);
}

int	count_red(char *str, int *i)
{
	if (str[*i] == '<')
	{
		(*i)++;
		while (str[*i] == '<')
			(*i)++;
		return (1);
	}
	if (str[*i] == '>')
	{
		(*i)++;
		while (str[*i] == '>')
			(*i)++;
		return (1);
	}
	if (str[*i] == '|')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	red_len(char *str, int *i)
{
	int	len;

	len = 0;
	if (str[*i] == '<')
	{
		while (str[*i] == '<')
		{
			len++;
			(*i)++;
		}
		return (len);
	}
	else if (str[*i] == '>')
	{
		while (str[*i] == '>')
		{
			len++;
			(*i)++;
		}
		return (len);
	}
	return (len);
}

int	quote_len(char *str, int *i)
{
	int	len;

	len = 0;
	if (str[*i] == '\'')
	{
		(*i)++;
		len++;
		while (str[*i] != '\0' && str[*i] != '\'')
		{
			(*i)++;
			len++;
		}
	}
	else if (str[*i] == '\"')
	{
		(*i)++;
		len++;
		while (str[*i] != '\0' && str[*i] != '\"')
		{
			(*i)++;
			len++;
		}
	}
	(*i)++;
	return (len + 1);
}

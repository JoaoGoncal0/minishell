/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:12 by jomendes          #+#    #+#             */
/*   Updated: 2024/07/10 15:34:48 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_env(char **env, t_vars *mini)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	mini->env = malloc(sizeof(char *) * (i + 1));
	if (!mini->env)
		return ;
	mini->env_len = i;
	i = 0;
	while (i < mini->env_len)
	{
		mini->env[i] = ft_strdup(env[i]);
		i++;
	}
	mini->env[i] = NULL;
}

int	env_builtin(t_vars *mini)
{
	int	i;

	i = -1;
	while (++i < mini->env_len)
		printf("%s\n", mini->env[i]);
	return (0);
}

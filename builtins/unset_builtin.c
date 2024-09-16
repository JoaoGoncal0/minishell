/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:09:04 by jomendes          #+#    #+#             */
/*   Updated: 2024/09/16 18:04:11 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var(t_vars *mini, char *var)
{
	int i;
	int j;
	int u;
	char *str;

	i = 0;
	u = 0;
	j = 0;
	str = NULL;
	
	while (i < mini->env_len)
	{
		printf("var = %s\n", var);
		if (ft_strncmp(mini->env[i], var, ft_strlen(var)) == 0)
		{
			
			if (ft_strlen(mini->env[i]) == ft_strlen(var))
			{
				str[j] = mini->env[i][j];
				j = 0;
				i = 0;
			}
			printf("str = %s\n", str);
			// while (str[j] == var[u] && str[j] != '=' && var[u] != '\0')
			// while ( != '\0')
			// {
			// 	str[j] =
            //     j++;
            //     u++;
            // }
		}
		i++;
	}
	return (str);
}

int	unset_builtin(t_vars *mini)
{
	char	**split;
	char 	*str;
	int		i;
	int		j;
	
	i = 0;
	j = 1;
	if (ft_strncmp(mini->input, "unset\0", ft_strlen(mini->input)) == 0)
		return (1);
	split = ft_split(mini->input, ' ');
	printf("split = %s\n", split[j]);
	str = get_var(mini, split[1]);
	while (split[i] != NULL)
	{
		echo_dollar_finish(split[i], 0, mini);
		i++;
	}
	return (0);
}

// dois string joins para juntar o PATH (split[1]) com "=" e 
// depois com o que vier do echo dollar finish
// atualizar o valor do env com o strdup de todas as strings menos aquela ou aquelas
//  que damos unset
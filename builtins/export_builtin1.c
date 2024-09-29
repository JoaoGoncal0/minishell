/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:46:26 by jomendes          #+#    #+#             */
/*   Updated: 2024/09/28 22:14:52 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// verificar o numero de argumentos e o formato dos mesmos
// só aceito letras ou o _ 
// seguidas de letras minus Maius ou numeros ou _
// adicionar ao export

int     export_check(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') || 
        (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_')))
        {
            printf("export: `%c': not a valid identifier\n", str[i]);
            return (1);
        }
        i++;
    }
    return (0);
}

void    export_var(t_vars *mini)
{
    int     i;
    char    **split;
    //int     len;

    i = 1;
    split = ft_split(mini->input, ' ');
    while (split[i]) 
    {
        if (export_check(split[i]) == 0)
        {
            export_update(mini, split[i]);   
            //len = export_lenght(mini);
            // printf("split = %s\n", split[i]);
            //printf("mini->export[len + 1] antes = %s\n", mini->export[len + 1]);
            //mini->export[len + 1] = ft_strdup(split[i]);
            //printf("mini->export[len + 1] depois = %s\n", mini->export[len + 1]);
        }
        i++;
    }
    sorting_export(mini);
}

void	export_update(t_vars *mini, char *str)
{
	int	i;
	int k;
    int len;
    int done;
    
	i = 0;
	k = 0;
    done = 0;
    len = export_len(mini->export);
    printf("valor do len %d\n", len);
	while (k < len)
	{
		if (mini->new_export[k])
		{
			free(mini->new_export[k]);
			mini->new_export[k] = NULL;
		}
		k++;
	}
	while (i < len)
	{
        //if (ft_strncmp(mini->export[i], str, ft_strlen(str) == 0))
        //    i++;
		if (!mini->export[i + 1] && done == 0)
		{
            done = 1;
            mini->new_export[i] = ft_strdup(str);
			i++;
		}
		if (mini->export[i])
		{
			mini->new_export[i] = ft_strdup(mini->export[i]);
			i++;
		}    
	}
	mini->new_export[i] = NULL;
	export_update1(mini);
}

void	export_update1(t_vars *mini)
{
	int i;
	int j;
	char **temp;
    int s;
    int len;

	i = 0;
	j = 0;
    len = export_len(mini->new_export);
    printf("valor do lennnnn %d\n", len);
    printf("\n\n----- UPDATED EXPORT ------\n\n\n");
	s = -1;
	while (++s < len)
		printf("declare -x: %s\n", mini->new_export[s]);
    printf("declare -x: %s\n", mini->new_export[s + 1]);
	while (i < len)
	{
		if (mini->export[i])
		{
			free(mini->export[i]);
			mini->export[i] = NULL;
		}
		i++;
	}
	i = 0;
	temp = realloc(mini->export, sizeof(char *) * (len + 1));
	if (!temp)
		return;
	mini->export = temp;
	while (j < len)
	{
		if (mini->new_export[j])
        {
            printf("mini->new_export = %s\n", mini->new_export[j]);
            mini->export[j] = ft_strdup(mini->new_export[j]);
        }
		else
			mini->export[j] = NULL;
		j++;
	}
	mini->export[j] = NULL;
}
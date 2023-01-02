/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 17:31:06 by ntan-wan          #+#    #+#             */
/*   Updated: 2022/12/31 18:39:48 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# define MAX_TOKEN_LEN 100

# include "../libft/libft.h"
# include <stdio.h>
# include <stdbool.h>

typedef enum e_token_type
{
	COMMAND,
	ARGUMENT,
	REDIRECTION,
	PIPE,
	UNKNOWN
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			value[MAX_TOKEN_LEN];
	struct s_token	*next;
}	t_token;

// t_list	*ms_tokenize(char *input);
void	ms_tokens_free(t_list **tokens);
void	ms_token_value_print(void *tokens);
void	ms_token_list_value_print(t_list *tokens);
#endif
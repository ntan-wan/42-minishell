/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:19:48 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/08 11:20:39 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "node.h"
# include "libft.h"

typedef struct  s_btree
{
	void	*content;
	struct	s_btree	*left;
	struct	s_btree	*right;
}			t_btree;

t_node	*ms_parser(char **tokens_arr);
#endif
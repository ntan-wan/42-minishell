/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:21:26 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/03/09 10:56:41 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
    @brief Check for pattern [ <and_or> ';' <command_line> ]
 */
t_ast	*cmd_line_pattern_1_andor_cmdline(t_sh *sh)
{
	t_ast	*and_or_node;
	t_ast	*cmd_line_node;
	t_ast	*seq_node;

    // sh->and_or_ast = NULL;
	parse_and_or(sh);
	and_or_node = sh->and_or_ast;
	if (and_or_node)
	{
        if (s_match_and_consume_token(SEMICOLON, sh->scanner))
		{
			cmd_line_node = parse_cmdline(sh);
			if (cmd_line_node)
			{
				seq_node = ft_calloc(1, sizeof(t_ast));
				ast_settype(seq_node, AST_SEQ);
				ast_attach(seq_node, and_or_node, cmd_line_node);
				return (seq_node);
			}
		}
		ast_delete(&and_or_node);
	}
	return (NULL);
}

/* 
    @brief Check for pattern [ <and_or> ';' ]
 */
t_ast	*cmd_line_pattern_2_andor_seq(t_sh *sh)
{
	t_ast	*and_or_node;
	t_ast	*seq_node;

	// *and_or_ast(NULL) = NULL;
	parse_and_or(sh);
	and_or_node = sh->and_or_ast;
	if (and_or_node)
	{
		// if (s_token_type_matches(SEMICOLON, s))
        if (s_match_and_consume_token(SEMICOLON, sh->scanner))
		{
			seq_node = ft_calloc(1, sizeof(t_ast));
			ast_settype(seq_node, AST_SEQ);
			ast_attach(seq_node, and_or_node, NULL);
			return (seq_node);
		}
		ast_delete(&and_or_node);
	}
	return (NULL);
}
/* 
    @brief Check for pattern [ <and_or> ]
 */
t_ast	*cmd_line_pattern_3_andor(t_sh *sh)
{
	t_ast	*and_or_node;

	// and_or_node = NULL;
	// *and_or_ast(NULL) = NULL
	parse_and_or(sh);
	// and_or_node = sh->and_or_ast;
	// if (and_or_node == NULL)
		// return (NULL);
	// return (and_or_node);
    return (sh->and_or_ast);
}

/*
	@return Return an array of functions that
	@return check for cmdline matching pattern.
    @note Must search the patterns in the following order.
 */
t_ast *(**cmdline_pattern_array(void))(t_sh *)
{
	static t_ast *(*pattern_func[])(t_sh *) = {
        cmd_line_pattern_1_andor_cmdline,
        cmd_line_pattern_2_andor_seq,
        cmd_line_pattern_3_andor,
		NULL
	};

return (pattern_func);

}

/* 
	@return t_ast * is returned upon success, else return NULL.
 */
t_ast	*parse_cmdline(t_sh *sh)
{
	return (pattern_searcher(cmdline_pattern_array(), sh));
}
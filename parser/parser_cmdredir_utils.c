/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmdredir_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:35:07 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/12 17:37:06 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_words(t_list *portion)
{
	if (((t_words *)portion->content)->token != TOK_WORD
		&& ((t_words *)portion->content)->token != TOK_OTHER_SPAC
		&& ((t_words *)portion->content)->token != TOK_FILE)
		return (1);
	return (0);
}

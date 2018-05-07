/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 11:54:18 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/06 18:22:08 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
**	Main for initial testing purposes, not required for dynamic library
*/

int		main(int argc, char **argv)
{
	int32_t		i;
	void		*testing;

	i = 1;
	if (argc < 2)
		ft_printf("Please include byte amounts as arguments\n");
	else
	{
		while (argv[i])
		{
			testing = ft_malloc(ft_atoi(argv[i]));
#ifdef DEBUG
			if (testing)
				ft_printf("Success\n");
#endif
			i++;
		}
//		ft_free((void *)1);
		ft_free(testing);
	}
}

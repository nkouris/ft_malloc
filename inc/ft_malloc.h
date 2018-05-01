/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 11:51:12 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/01 15:17:00 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdint.h>
# include <sys/mman.h>
# include <errno.h>
# include "libft.h"

# define TINY 128
# define SMALL 1024
# define NORM 1
# define LARGE 1025

# define RED 0x1
# define BLACK 0x2

# define EMPTYSEGS 0
# define PAGEMAPS 1

extern void			*g_tracksegs[2];

typedef struct	s_hdc
{
	void		*next;
	uint16_t	nummap;
	uint16_t	segcount;
}				t_hdc;

typedef struct	s_mtag
{
	void		*pghead;
	void		*parent;
	void		*left;
	void		*right;
	uint64_t	size;
}				t_mtag;

typedef struct	s_rbsentinel
{
	uint8_t		color;
	void		*left;
	void		*right;
}				t_rbsentinel;

/*
**	ft_malloc.c
*/

void	*ft_malloc(size_t size);

/*
**	mtag.c
*/

void	pagemeta_init(void *head, size_t nummap, size_t size);

#endif

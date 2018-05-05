/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 11:51:12 by nkouris           #+#    #+#             */
/*   Updated: 2018/05/05 11:24:11 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdint.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <errno.h>
# include "libft.h"

# define TINY 128
# define SMALL 1024
# define NORM 1
# define LARGE 1025

# define RED 0x1
# define BLACK 0x2
# define USED 0x04
# define UNUSED 0x08

# define EMPTYSEGS 0
# define PAGEMAPS 1

# define HTAG ((t_hdc *)tag)
# define MTAG ((t_mtag *)tag)

extern void		*g_tracksegs[2];

typedef struct	s_hdc
{
	void		*next;
	uint16_t	nummap;
	uint16_t	segcount;
}				t_hdc;

typedef struct	s_mtag
{
	void		*map_head;
	void		*parent;
	void		*left;
	void		*right;
	uint64_t	size;
	uint8_t		color;
	uint8_t		condition;
}				t_mtag;

typedef struct	s_rbnode
{
	void		*pad;
	void		*parent;
	void		*left;
	void		*right;
	uint64_t	content;
	uint8_t		color;
}				t_rbnode;

typedef struct		s_rbtree
{
	t_rbnode		*root;
}					t_rbtree;

/*
**	ft_malloc.c
*/

void	*ft_malloc(size_t size);

/*
**	mtag.c
*/

void	pagemeta_init(void *head, size_t nummap, size_t size);

/*
**	rbtree logic
*/

void		ft_rbdelete(t_rbtree *tree, t_rbnode *node);

void		ft_rbdelete_rot(t_rbtree *tree, t_rbnode *move);

int			ft_rbinsert(t_rbtree *tree, t_rbnode *new);

void		ft_rbsubtransfer(t_rbtree *tree, t_rbnode *node, t_rbnode *temp);
t_rbnode	*ft_bstminnode(t_rbnode *node);
void		ft_leftrot(t_rbnode *node, t_rbtree *tree);
void		ft_rightrot(t_rbnode *node, t_rbtree *tree);
t_rbnode	*ft_rbnewnode(int content);

#endif

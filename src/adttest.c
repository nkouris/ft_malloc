#include <stdint.h>

enum rb_color
{
	RED,
	BLACK
};

typedef struct	s_rb
{
	struct s_rb	*children[2];
	int			data;
	uint8_t		rb_color;
}				t_rb;

/* insert */

t_rb	*rb_insert(t_rb *tree, int data)
{
	t_rb	*new;
	t_rb	*temp;

	temp = tree;
	new = (t_rb *)malloc(sizeof(t_rb));
	new->data = data;
	while (temp->children
}

#pragma once
#include <stdio.h>
/*
Red Black Trees
(C) 1999  Andrea Arcangeli <andrea@suse.de>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

linux/include/linux/rbtree.h

To use rbtrees you'll have to implement your own insert and search cores.
This will avoid us to use callbacks and to drop drammatically performances.
I know it's not the cleaner way,  but in C (not in C++) to get
performances and genericity...

See Documentation/rbtree.txt for documentation and samples.
*/

#define offset(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define	 rb_entry(ptr, type, member)  ((type *)(void *)((char *)(ptr) - offset(type, member)))

#define	RB_RED		0
#define	RB_BLACK	1

struct rb_node {
    unsigned long  rb_parent_color;
    struct rb_node *rb_right;
    struct rb_node *rb_left;
};

struct rb_root {
    struct rb_node *rb_node;
};

#define rb_parent(r)   ((struct rb_node *)((r)->rb_parent_color & ~3))
#define rb_color(r)   ((r)->rb_parent_color & 1)
#define rb_is_red(r)   (!rb_color(r))
#define rb_is_black(r) rb_color(r)
#define rb_set_red(r)  do { (r)->rb_parent_color &= ~1; } while (0)
#define rb_set_black(r) do { (r)->rb_parent_color |= 1; } while (0)
#define RB_ROOT	(struct rb_root) { NULL, }
#define RB_EMPTY_ROOT(root) ((root)->rb_node == NULL)

static inline void rb_set_parent(struct rb_node *rb, struct rb_node *p)
{
    rb->rb_parent_color = (rb->rb_parent_color & 3) | (unsigned long)p;
}
static inline void rb_set_color(struct rb_node *rb, int color)
{
    rb->rb_parent_color = (rb->rb_parent_color & ~1) | color;
}

/* 'empty' nodes are nodes that are known not to be inserted in an rbtree */
#define RB_EMPTY_NODE(node)  \
	((node)->rb_parent_color == (unsigned long)(node))
#define RB_CLEAR_NODE(node)  \
	((node)->rb_parent_color = (unsigned long)(node))

void rb_insert_color(struct rb_node *, struct rb_root *);
void rb_erase(struct rb_node *, struct rb_root *);

/* Find logical next and previous nodes in a tree */
struct rb_node *rb_next(const struct rb_node *);
struct rb_node *rb_prev(const struct rb_node *);
struct rb_node *rb_first(const struct rb_root *);
struct rb_node *rb_last(const struct rb_root *);

/* Postorder iteration - always visit the parent after its children */
struct rb_node *rb_first_postorder(const struct rb_root *);
struct rb_node *rb_next_postorder(const struct rb_node *);

static inline void rb_link_node(struct rb_node *node, struct rb_node *parent,
                                                   struct rb_node **rb_link)
{
    node->rb_parent_color = (unsigned long)parent;
    node->rb_left = node->rb_right = NULL;

    *rb_link = node;
}

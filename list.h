/*
 * Copyright (C) 2002 Free Software Foundation, Inc.
 * (originally part of the GNU C Library and Userspace RCU)
 * Contributed by Ulrich Drepper <drepper@redhat.com>, 2002.
 *
 * Copyright (C) 2009 Pierre-Marc Fournier
 * Conversion to RCU list.
 * Copyright (C) 2010 Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see
 * <http://www.gnu.org/licenses/>.
 */

/**
 *
 *  Copyright (C) <31,May,2023>  <Antony Lian>

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.

**/

#ifndef HASHTABLE_LIST_H
#define HASHTABLE_LIST_H

#include <stddef.h>

struct list_head
{
    struct list_head *prev;
    struct list_head *next;
};

static inline void list_init(struct list_head *head)
{
    head->prev = head;
    head->next = head;
}

static inline void list_add_tail(struct list_head *newp, struct list_head *head)
{
    newp->prev = head->prev;
    newp->next = head;
    head->prev->next = newp;
    head->prev = newp;
}

static inline void __list_del(struct list_head *prev, struct list_head *next)
{
    prev->next = next;
    next->prev = prev;
}

static inline void list_del(struct list_head *target)
{
    __list_del(target->prev, target->next);
}

/* 避免与<stddef>中的offsetof重定义 */
#undef offsetof
/* 计算偏移量 */
#define offsetof(type, member) ((size_t) & ((type *)0)->member)

#undef container_of
/* 计算结构体的地址 */
#define container_of(ptr, type, member) \
    (type *)((char *)(ptr)-offsetof(type, member))

/* 头节点不挂载任何数据结构 */
#define list_for_each_entry(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

static inline void list_replace(struct list_head *old, struct list_head *newp)
{
    newp->next = old->next;
    newp->prev = old->prev;
    old->next->prev = newp;
    old->prev->next = newp;
}

#endif // HASHTABLE_LIST_H

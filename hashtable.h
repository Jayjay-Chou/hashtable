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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-stack-address"
#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include "list.h"
#include "hashfunc.h"
#include "stdlib.h"

#define HASH_TABLE_SIZE 10

static inline struct list_head *hash_head()
{
    struct list_head *hash_table = (struct list_head *)malloc(HASH_TABLE_SIZE * sizeof(struct list_head));
    return hash_table;
}

static void hash_init(struct list_head *hash_table)
{
    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        list_init(&hash_table[i]);
    }
}

static inline void hash_add_ele(struct list_head *newp, struct list_head *name, int key)
{
    list_add_tail(newp, &name[key]);
}

/**
 * @ pos为位置指针
 * @ table_head 为哈希表头
 * @ hash_num 为需要遍历的哈希表下标
 *
 * */

/* 哈希表中不挂载任何数据结构 所有的数据全部挂载在头节点之后 */
#define hash_for_each(pos, table_head, hash_num) \
    list_for_each_entry(pos, &table_head[hash_num])

/* 判断哈希表中某位置是否只有头节点 */
#define HASH_EMPTY(head) (head) == ((head)->next) ? 1 : 0

/* 判断哈希表中某位置是否只有头节点 */
#define HASH_EMPTY_SAFE(head, addr) HASH_EMPTY((head[addr]))

static inline int hash_node_empty(struct list_head head)
{
    return &head == head.next;
}

static inline void hash_del(struct list_head *target)
{
    list_del(target);
}

static inline void hash_replace(struct list_head *old, struct list_head *newp)
{
    list_init(newp);
    list_replace(old, newp);
}

#endif // HASHTABLE_HASHTABLE_H

#pragma clang diagnostic pop

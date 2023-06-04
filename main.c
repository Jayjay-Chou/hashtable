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

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "hashtable.h"

//#define HASH_TABLE_SIZE 10

/**
 * @ 如何使用hashtable和list
 *   首先，需要定义一个需要挂载的结构体
 *   比如，有一个struct结构如下：
 *   struct demo{
 *      member1;
 *      member2;
 *      ...
 *      struct list_head node;
 *   }
 *   在使用时，先要对demo结构进行初始化
 *   struct demo demo1;
 *   demo1.member1 = value1;
 *   demo1.member2 = value2;
 *   ...
 *
 *   在初始化完成后，编译器将为demo分配内存空间，这样才能初始化节点
 *   否则就会出现错误，因为只声明不初始化，demo在内存中并不存在
 *
 * @ 初始化完成后，可以选择对demo中的节点进行初始化
 *   list_init(&demo1.node)
 *   也可以直接进行挂载
 *   hash_add_ele(&demo1.node,hash_head(),addr)
 *   然后可以用container_of宏进行访问
 *   container_of宏返回一个demo类型的指针
 *   然后就可以用container_of返回的指针来访问节点成员
 *
 * */

struct user {
    int member;
    struct list_head node;
};

int main() {
    struct user test;
    test.member = 100;
    list_init(&test.node);
    struct user *p = container_of(&test.node, struct user, node);
    printf("%d\n", p->member);

    struct list_head *hashtable = hash_head();
    hash_init(hashtable);
    hash_add_ele(&test.node, hashtable, 2);
    struct user *q = container_of(hashtable[2].next, struct user, node);
    printf("%d\n%d\n", q->member, test.member);

    struct user *pointer = (struct user*) malloc(sizeof (struct user));
    pointer->member = 50;
    hash_add_ele(&(pointer->node), hashtable, 2);
    struct user *tar = container_of((hashtable[2].next)->next,struct user,node);
    printf("%d\n",tar->member);


    struct list_head *pos = NULL;
    list_for_each_entry(pos,&hashtable[2]){
        //printf("%d\n",co)
        struct user *newNode = container_of(pos,struct user,node);
        //if (newNode->member == 50){
            //hash_del(&(newNode->node));
            //free(newNode);
            //newNode = NULL;
        //}
        printf("%d\n",newNode->member);
    }
    pos = NULL;
    list_for_each_entry(pos,&hashtable[2]){
        struct user *newNode = container_of(pos,struct user,node);
        printf("\n\n%d\n",newNode->member);
    }


    pos = NULL;
    hash_for_each(pos,hashtable,2){
        struct user *ptr = container_of(pos,struct user,node);
        printf("\n\n\n%d\n",ptr->member);
    }


    printf("-----------------\n");
    char name[] = "who";
    hash_int size =  hash_func(name);
    printf("%d\n",size);

    printf("**************\n");
    int bool = HASH_EMPTY(&hashtable[0]);
    printf("%d\n",bool);



    printf("**************\n");
    int newBool = HASH_EMPTY_SAFE(&hashtable,0);
    printf("%d\n",newBool);

    struct user newp;
    newp.member = 800;
    pos = NULL;
    hash_for_each(pos,hashtable,2){
        struct user *ptr = container_of(pos,struct user,node);
        if (ptr->member == 50){
            hash_replace(&(ptr->node),&newp.node);
        }
    }

    pos = NULL;
    hash_for_each(pos,hashtable,2){
        struct user *ptr = container_of(pos,struct user,node);
        printf("\n%d\n",ptr->member);
    }

    return 0;
}


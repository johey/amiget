#include "list.h"

#include <stdio.h>
#include <stdlib.h>

list_t *list_init() {
    list_t *list = (list_t *)malloc(sizeof(list_t));
    node_t *first = (node_t *)malloc(sizeof(node_t));
    node_t *last = (node_t *)malloc(sizeof(node_t));
    first->next = last;
    last->prev = first;
    first->prev = NULL;
    last->next = NULL;
    list->first = first;
    list->last = last;
    list->count = 0;
    list->active = NULL;

    return list;
}

void list_destruct(list_t *list) {
    free(list->first);
    free(list->last);
    list->first = list->last = NULL;
    free(list);
}

void list_push_back(list_t *list, void *data, char set_active) {
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = data;
    node->prev = list->last->prev;
    node->next = list->last;
    list->last->prev->next = node;
    list->last->prev = node;
    list->count++;

    if (set_active) list->active = node;
}

node_t *list_remove_at(list_t *list, unsigned char pos, active_transfer transfer) {
    node_t *prev = list->first;
    node_t *node = prev->next;

    if (node == list->last) return NULL;

    for (unsigned char i = 0; i < pos; i++) {
        prev = node;
        if ((node = node->next) == (list->last)) return NULL;
    }
    prev->next = node->next;
    prev->next->prev = prev;

    list->count--;

    if (list->active != node)
        return node;

    switch(transfer) {
        case active_null:
            list->active = NULL;
            break;
        case active_prev:
            list->active = node->prev;
            break;
        case active_next:
            list->active = node->next;
            break;
    }
    if (transfer == active_null || list->count == 0) 
        list->active = NULL;
    else if (transfer == active_next && list->active == list->last)
        list->active = node->prev;
    else if (transfer == active_prev && list->active == list->first)
        list->active = node->next;

    return node;
}

node_t *list_get_at(list_t *list, unsigned char pos) {
    node_t *node = list->first->next;

    for (unsigned char i = 0; i < pos; i++) {
        if ((node = node->next) == NULL) return NULL;
    }

    if (node == list->last) return NULL;

    return node;
}

unsigned char list_count(list_t *list) {
    return list->count;
}

void list_active_next(list_t *list) {
    if (!(list->active))
        return;

    list->active = list->active->next;
    if (list->active == list->last)
        list->active = list->first->next;
}

void list_active_prev(list_t *list) {
    if (!(list->active))
        return;

    list->active = list->active->prev;
    if (list->active == list->first)
        list->active = list->last->prev;
}


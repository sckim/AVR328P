#include <os.h>

/*------------------------------------------------------------------------------
 * List APIs
 *----------------------------------------------------------------------------*/
struct list *list_init(struct list *list)
{
    list->link.next = &list->link;
    list->link.prev = &list->link;
    list->link.item = NULL;
    list->link.list = NULL;
    list->count     = 0;

    return list;
}

void list_put(struct list *list, struct link *link)
{
    if (link->list)
        return;

    link->next = &list->link;
    link->prev = list->link.prev;
    link->list = list;

    list->link.prev->next = link;
    list->link.prev = link;
    list->count++;
}

void list_put_first(struct list *list, struct link *link)
{
    if (link->list)
        return;

    link->next = list->link.next;
    link->prev = &list->link;
    link->list = list;

    list->link.next->prev = link;
    list->link.next = link;
    list->count++;
}

void *list_get(struct list *list)
{
    void    *item = NULL;

    if (list->count)
    {
        struct link  *link = list->link.next;
        item = link->item;
        list->link.next = link->next;
        link->next->prev = &list->link;
        list->count--;
        link->list = NULL;
    }

    return item;
}

void *list_rotate(struct list *list)
{
    if (list->count == 0)
        return NULL;

    if (list->count == 1)
        return list->link.next->item;

    struct link  *link = list->link.next;

    list->link.next = link->next;
    link->next->prev = &list->link;

    link->next = &list->link;
    link->prev = list->link.prev;
    list->link.prev->next = link;
    list->link.prev = link;

    return list->link.next->item;
}

void *list_peek(struct list *list)
{
    return list->link.next->item;
}

uint8_t list_count(struct list *list)
{
    return list->count;
}

bool list_empty(struct list *list)
{
    return !(list->count);
}

/*------------------------------------------------------------------------------
 * Link APIs
 *----------------------------------------------------------------------------*/
struct link *link_init(void *item, struct link *link)
{
    link->next = NULL;
    link->prev = NULL;
    link->list = NULL;
    link->item = item;

    return link;
}

void *link_insert(struct link *old_link, struct link *new_link)
{
    if (old_link->list == NULL || new_link->list)
        return NULL;

    new_link->next = old_link;
    new_link->prev = old_link->prev;
    new_link->list = old_link->list;

    old_link->prev->next = new_link;
    old_link->prev = new_link;

    old_link->list->count++;

    return new_link->item;
}

void *link_remove(struct link *link)
{
    void *item = NULL;

    if (link && link->list)
    {
        link->prev->next = link->next;
        link->next->prev = link->prev;
        link->list->count--;
        link->list = NULL;
        item = link->item;
    }

    return item;
}

void *link_prev(struct link *link)
{
    return link->prev->item;
}

void *link_next(struct link *link)
{
    return link->next->item;
}


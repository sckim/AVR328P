
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <board.h>
#include <arch.h>

/*------------------------------------------------------------------------------
 * Base types and Macros
 *----------------------------------------------------------------------------*/
typedef uint8_t     bool;
enum
{
    false,
    true
};
 
/*------------------------------------------------------------------------------
 * Double linked list
 *----------------------------------------------------------------------------*/
struct link
{
    struct link     *next,
                    *prev;
    void            *item;
    struct list     *list;
};
 
struct list
{
    struct link     link;
    uint8_t         count;
};

#define OS_NR_PRIORITIES            8
#define OS_MIN_PRIORITY             (OS_NR_PRIORITIES - 1)
#define OS_MAX_PRIORITY             0
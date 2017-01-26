#include "calculus.h"

int stackFree (stack_t **s)
{
        stack_t         *item = *s;
        stack_t         *next;
        int             progress = 0;

        while (item)
        {
                next = item->next;
                if (item->value != NULL)
                        free ((void*)item->value);
                item->type = 0xBADC0DE;
                free (item);
                progress++;
                item = next;
        }

        return progress;
}

unsigned int stackTop (stack_t *s)
{
        return s->type;
}

int stackPush (stack_t **s, void *value, unsigned int type)
{
        stack_t         *item;

        item = (stack_t*) calloc (1, sizeof(stack_t));
        if (!item)
        {
                _d ("%s\n", strerror (errno));
                return -1;
        }

        item->value = value;
        item->type = type;
        item->next = *s;

        *s = item;

        return 0;
}

void *stackPop (stack_t **s)
{
        stack_t         *item = *s;
        void            *value = item->value;

        *s = item->next;
        free (item);
        return value;
}

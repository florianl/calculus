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

int bin2dez(char *t)
{
        int             value = 0;
        int             power = 1;
        int             len = strlen(t);
        int             i = 0;

        if (len<2)
                return -1;

        for (i=len-1; i>=1; i--)
        {
                if (t[i] == '1')
                {
                        value += power;
                }
                power <<= 1;
        }

        return value;
}


int uni2dez(char *t, int multi)
{
        int             value = 0;
        int             power = 1;
        int             len = strlen(t);
        int             i = 0;

        if (len<2)
                return -1;

        for (i=len-1; i>=1; i--)
        {
                value += (t[i] - 48) * power;
                power *= multi;
        }

        return value;
}

int hex2dez(char *t)
{
        int             value = 0;
        int             power = 1;
        int             len = strlen(t);
        int             i = 0;
        int             element = 0;


        if (len<2)
                return -1;

        for (i=len-1; i>=1; i--)
        {
                if ( t[i] <= 57 && t[i] >= 48)
                        /*      numbers                 */
                        element = t[i] - 48;
                else if ( t[i] <= 70 && t[i] >= 65)
                        /*      uppercase letters       */
                        element = t[i] - 55;
                else if ( t[i] <= 102 && t[i] >= 97)
                        /*      lowercase letters       */
                        element = t[i] - 87;
                else
                        break;
                value += element * power;
                power *= 16;
        }

        return value;
}

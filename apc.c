#include "apc.h"

int store_operand(Dlist **head, Dlist **tail, char *str)
{
    int i = 0;

    if (str[0] == '\0')
        return 1;

    while (str[i] != '\0')
    {
        if (!isdigit((unsigned char)str[i]))
            return 1;

        if (insert_last(head, tail, str[i] - '0'))
            return 1;

        i++;
    }

    return 0;
}

int addition(Dlist *tail1, Dlist *tail2,
             Dlist **result_head, Dlist **result_tail)
{
    int sum, carry = 0, digit;

    while (tail1 != NULL || tail2 != NULL || carry != 0)
    {
        sum = carry;

        if (tail1 != NULL)
        {
            sum += tail1->data;
            tail1 = tail1->prev;
        }

        if (tail2 != NULL)
        {
            sum += tail2->data;
            tail2 = tail2->prev;
        }

        digit = sum % 10;
        carry = sum / 10;

        if (insert_first(result_head, result_tail, digit))
            return 1;
    }

    return 0;
}
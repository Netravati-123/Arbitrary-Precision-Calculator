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

int compare_lists(Dlist *head1, Dlist *head2)
{
    int count1 = 0, count2 = 0;
    Dlist *temp1 = head1;
    Dlist *temp2 = head2;

    while (temp1 != NULL && temp1->data == 0 &&
           temp1->next != NULL)
    {
        temp1 = temp1->next;
    }

    while (temp2 != NULL && temp2->data == 0 &&
           temp2->next != NULL)
    {
        temp2 = temp2->next;
    }

    while (temp1 != NULL)
    {
        count1++;
        temp1 = temp1->next;
    }

    while (temp2 != NULL)
    {
        count2++;
        temp2 = temp2->next;
    }

    if (count1 > count2)
        return 1;

    if (count1 < count2)
        return -1;

    temp1 = head1;
    temp2 = head2;

    while (temp1 != NULL && temp1->data == 0 &&
           temp1->next != NULL)
    {
        temp1 = temp1->next;
    }

    while (temp2 != NULL && temp2->data == 0 &&
           temp2->next != NULL)
    {
        temp2 = temp2->next;
    }

    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->data > temp2->data)
            return 1;

        if (temp1->data < temp2->data)
            return -1;

        temp1 = temp1->next;
        temp2 = temp2->next;
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

int subtraction(Dlist *tail1, Dlist *tail2,
                Dlist **result_head, Dlist **result_tail)
{
    int diff, borrow = 0;

    while (tail1 != NULL)
    {
        diff = tail1->data - borrow;
        borrow = 0;

        if (tail2 != NULL)
        {
            diff = diff - tail2->data;
            tail2 = tail2->prev;
        }

        if (diff < 0)
        {
            diff = diff + 10;
            borrow = 1;
        }

        if (insert_first(result_head, result_tail, diff))
            return 1;

        tail1 = tail1->prev;
    }

    return 0;
}

    int multiplication(Dlist *tail1, Dlist *tail2,
                   Dlist **result_head, Dlist **result_tail)
{
    Dlist *list1_head = NULL, *list1_tail = NULL;
    Dlist *list2_head = NULL, *list2_tail = NULL;
    Dlist *list3_head = NULL, *list3_tail = NULL;

    Dlist *temp1, *temp2;

    int carry, product, digit, shift = 0;

    insert_last(&list3_head, &list3_tail, 0);

    temp2 = tail2;

    while (temp2 != NULL)
    {
        digit = temp2->data;
        temp1 = tail1;
        carry = 0;

        while (temp1 != NULL || carry != 0)
        {
            product = carry;

            if (temp1 != NULL)
            {
                product += temp1->data * digit;
                temp1 = temp1->prev;
            }

            carry = product / 10;
            product = product % 10;

            if (insert_first(&list1_head, &list1_tail, product))
                goto error;
        }

        for (int i = 0; i < shift; i++)
        {
            if (insert_last(&list1_head, &list1_tail, 0))
                goto error;
        }

        if (addition(list3_tail, list1_tail,
                     &list2_head, &list2_tail))
            goto error;

        delete_list(&list3_head, &list3_tail);
        delete_list(&list1_head, &list1_tail);

        list3_head = list2_head;
        list3_tail = list2_tail;

        list2_head = NULL;
        list2_tail = NULL;

        shift++;
        temp2 = temp2->prev;
    }

    *result_head = list3_head;
    *result_tail = list3_tail;

    return 0;

error:
    delete_list(&list1_head, &list1_tail);
    delete_list(&list2_head, &list2_tail);
    delete_list(&list3_head, &list3_tail);

    return 1;
}

     int is_zero(Dlist *head)
{
    while (head != NULL)
    {
        if (head->data != 0)
            return 0;

        head = head->next;
    }

    return 1;
}

static void remove_leading_zeros(Dlist **head, Dlist **tail)
{
    while (*head != NULL && (*head)->data == 0 &&
           (*head)->next != NULL)
    {
        Dlist *temp = *head;

        *head = (*head)->next;
        (*head)->prev = NULL;

        free(temp);
    }

    if (*head == NULL)
        *tail = NULL;
}

int division(Dlist *head1, Dlist *head2,
             Dlist **result_head, Dlist **result_tail)
{
    Dlist *rem_head = NULL, *rem_tail = NULL;
    Dlist *temp_head = NULL, *temp_tail = NULL;
    Dlist *divisor_tail = head2;
    Dlist *digit = head1;

    int count;

    if (head1 == NULL || head2 == NULL || is_zero(head2))
        return 2;

    while (divisor_tail->next != NULL)
        divisor_tail = divisor_tail->next;

    while (digit != NULL)
    {
        // Bring down the next digit
        if (insert_last(&rem_head, &rem_tail, digit->data))
            goto memory_error;

        remove_leading_zeros(&rem_head, &rem_tail);

        count = 0;

        // Subtract divisor until remainder is smaller
        while (compare_lists(rem_head, head2) >= 0)
        {
            if (subtraction(rem_tail, divisor_tail,
                            &temp_head, &temp_tail) != 0)
                goto memory_error;

            delete_list(&rem_head, &rem_tail);

            rem_head = temp_head;
            rem_tail = temp_tail;

            temp_head = NULL;
            temp_tail = NULL;

            remove_leading_zeros(&rem_head, &rem_tail);

            count++;
        }

        // Store quotient digit
        if (insert_last(result_head, result_tail, count))
            goto memory_error;

        digit = digit->next;
    }

    remove_leading_zeros(result_head, result_tail);

    delete_list(&rem_head, &rem_tail);

    return 0;

memory_error:
    delete_list(&rem_head, &rem_tail);
    delete_list(&temp_head, &temp_tail);
    delete_list(result_head, result_tail);

    return 1;
}

#include "apc.h"

int main(int argc, char *argv[])
{
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *result_head = NULL, *result_tail = NULL;

    int cmp, negative = 0, status = 0;

    if (argc != 4)
    {
        printf("Usage: ./a.out operand1 operator operand2\n");
        return 1;
    }

    if (argv[2][1] != '\0' ||
        (argv[2][0] != '+' &&
         argv[2][0] != '-' &&
         argv[2][0] != '*'))
    {
        printf("Invalid operator. Use +, - or * only.\n");
        return 1;
    }

    if (store_operand(&head1, &tail1, argv[1]) != 0 ||
        store_operand(&head2, &tail2, argv[3]) != 0)
    {
        printf("Invalid operand or memory allocation failed\n");
        status = 1;
        goto cleanup;
    }

    if (argv[2][0] == '+')
    {
        status = addition(tail1, tail2,&result_head, &result_tail);
    }
    else if (argv[2][0] == '-')
    {
        cmp = compare_list(head1, head2);

        if (cmp >= 0)
        {
            status = subtraction(tail1, tail2,&result_head, &result_tail);
        }
        else
        {
            negative = 1;

            status = subtraction(tail2, tail1,&result_head, &result_tail);
        }
    }
    else
    {
        status = multiplication(tail1, tail2,&result_head, &result_tail);
    }

    if (status != 0)
    {
        printf("Memory allocation failed\n");
        goto cleanup;
    }

    printf("First operand: ");
    print_list(head1);

    printf("Second operand: ");
    print_list(head2);

    printf("Result: ");

    if (negative)
    {
        Dlist *temp = result_head;

        while (temp != NULL && temp->data == 0 &&
               temp->next != NULL)
        {
            temp = temp->next;
        }

        if (temp != NULL && temp->data != 0)
            printf("-");
    }

    print_list(result_head);

cleanup:
    delete_list(&head1, &tail1);
    delete_list(&head2, &tail2);
    delete_list(&result_head, &result_tail);

    return status;
}
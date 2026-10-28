#include "apc.h"

int main(int argc, char *argv[])
{
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *result_head = NULL, *result_tail = NULL;

    if (argc != 4)
    {
        printf("Usage: ./a.out operand1 + operand2\n");
        return 1;
    }

    if (argv[2][0] != '+' || argv[2][1] != '\0')
    {
        printf("Invalid operator. Use + only.\n");
        return 1;
    }

    if (store_operand(&head1, &tail1, argv[1]) != 0 ||
        store_operand(&head2, &tail2, argv[3]) != 0)
    {
        printf("Invalid operand or memory allocation failed\n");

        delete_list(&head1, &tail1);
        delete_list(&head2, &tail2);

        return 1;
    }

    if (addition(tail1, tail2,
                 &result_head, &result_tail) != 0)
    {
        printf("Memory allocation failed\n");

        delete_list(&head1, &tail1);
        delete_list(&head2, &tail2);
        delete_list(&result_head, &result_tail);

        return 1;
    }

    printf("First operand: ");
    print_list(head1);

    printf("Second operand: ");
    print_list(head2);

    printf("Result: ");
    print_list(result_head);

    delete_list(&head1, &tail1);
    delete_list(&head2, &tail2);
    delete_list(&result_head, &result_tail);

    return 0;
}
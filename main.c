#include "apc.h"

int main(int argc, char *argv[])
{
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *result_head = NULL, *result_tail = NULL;

    int sign1 = 1, sign2 = 1;
    int cmp, negative = 0, status = 0;
    int op_sign;

    char *operand1, *operand2;

    if (argc != 4)
    {
        printf("Usage: ./APC.out operand1 operator operand2\n");
        return 1;
    }

    // Validate operator
    if (argv[2][1] != '\0' ||
        (argv[2][0] != '+' &&
         argv[2][0] != '-' &&
         argv[2][0] != 'x' &&
         argv[2][0] != 'X' &&
         argv[2][0] != '/'))
    {
        printf("Invalid operator\n");
        return 1;
    }

    operand1 = argv[1];
    operand2 = argv[3];

    // Extract sign of first operand
    if (*operand1 == '+' || *operand1 == '-')
    {
        if (*operand1 == '-')
            sign1 = -1;

        operand1++;
    }

    // Extract sign of second operand
    if (*operand2 == '+' || *operand2 == '-')
    {
        if (*operand2 == '-')
            sign2 = -1;

        operand2++;
    }

    // Check empty operands
    if (*operand1 == '\0' || *operand2 == '\0')
    {
        printf("Invalid operand\n");
        return 1;
    }

    // Store only digits
    if (store_operand(&head1, &tail1, operand1) != 0 ||
        store_operand(&head2, &tail2, operand2) != 0)
    {
        printf("Invalid operand\n");
        status = 1;
        goto cleanup;
    }

    // Addition
    if (argv[2][0] == '+' || argv[2][0] == '-')
    {
        op_sign = sign2;

        // For subtraction, reverse second operand sign
        if (argv[2][0] == '-')
            op_sign = -op_sign;

        if (sign1 == op_sign)
        {
            status = addition(tail1, tail2,
                              &result_head, &result_tail);

            if (sign1 == -1)
                negative = 1;
        }
        else
        {
            cmp = compare_lists(head1, head2);

            if (cmp >= 0)
            {
                status = subtraction(tail1, tail2,
                                     &result_head, &result_tail);

                if (sign1 == -1)
                    negative = 1;
            }
            else
            {
                status = subtraction(tail2, tail1,
                                     &result_head, &result_tail);

                if (op_sign == -1)
                    negative = 1;
            }
        }
    }

    // Multiplication
    else if (argv[2][0] == 'x' || argv[2][0] == 'X')
    {
        status = multiplication(tail1, tail2,
                                &result_head, &result_tail);

        if (sign1 != sign2)
            negative = 1;
    }

    // Division
    else if (argv[2][0] == '/')
    {
        if (is_zero(head2))
        {
            printf("Division by zero is not possible\n");
            status = 1;
            goto cleanup;
        }

        status = division(head1, head2,
                          &result_head, &result_tail);

        if (sign1 != sign2)
            negative = 1;
    }

    if (status != 0)
    {
        if (status != 1)
            printf("Operation failed\n");
        else
            printf("Memory allocation failed\n");

        goto cleanup;
    }

    printf("First operand: ");
    if (sign1 == -1 && !is_zero(head1))
        printf("-");
    print_list(head1);

    printf("Second operand: ");
    if (sign2 == -1 && !is_zero(head2))
        printf("-");
    print_list(head2);

    printf("Result: ");

    if (negative && !is_zero(result_head))
        printf("-");

    print_list(result_head);

cleanup:
    delete_list(&head1, &tail1);
    delete_list(&head2, &tail2);
    delete_list(&result_head, &result_tail);

    return status;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int low;
    int high;
    int state;
} Node;

void merge(int a[], int low, int mid, int high) {
    int i = low;
    int j = mid + 1;
    int k = 0;

    int *temp = (int *)malloc((high - low + 1) * sizeof(int));

    while (i <= mid && j <= high) {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= high)
        temp[k++] = a[j++];

    for (i = low, k = 0; i <= high; i++, k++)
        a[i] = temp[k];

    free(temp);
}

void mergeSort(int a[], int n) {
    Node *stack = (Node *)malloc(2 * n * sizeof(Node));
    int top = -1;

    // Push complete array
    stack[++top] = (Node){0, n - 1, 0};

    while (top >= 0) {
        Node current = stack[top--];

        int low = current.low;
        int high = current.high;

        if (low >= high)
            continue;

        int mid = low + (high - low) / 2;

        if (current.state == 0) {

            // Push merge operation
            stack[++top] = (Node){low, high, 1};

            // Push right half
            stack[++top] = (Node){mid + 1, high, 0};

            // Push left half
            stack[++top] = (Node){low, mid, 0};

        } else {
            // Merge two sorted halves
            merge(a, low, mid, high);
        }
    }

    free(stack);
}

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    mergeSort(a, n);

    printf("Sorted array: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    free(a);

    return 0;
}

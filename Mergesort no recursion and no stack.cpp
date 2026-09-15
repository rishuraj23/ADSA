#include <stdio.h>
#include <stdlib.h>

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

    for (i = low, k = 0; i <= high; i++, k++) {
        a[i] = temp[k];
    }

    free(temp);
}

void mergeSort(int a[], int n) {
    int size, left, mid, right;

    // Start with subarrays of size 1
    for (size = 1; size < n; size = size * 2) {

        for (left = 0; left < n - 1; left = left + 2 * size) {

            mid = left + size - 1;
            right = left + 2 * size - 1;

            // If right exceeds array
            if (right >= n)
                right = n - 1;

            // If there is a second subarray
            if (mid < right)
                merge(a, left, mid, right);
        }
    }
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

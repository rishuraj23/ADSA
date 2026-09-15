#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 1000

void printArray(int a[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void copyArray(int src[], int dest[], int n) {
    int i;
    for (i = 0; i < n; i++)
        dest[i] = src[i];
}
void swap(int *x , int *y){
	int temp = *x;
	*x=*y;
	*y=temp;
}

/* 1. Insertion Sort */
void insertionSort(int a[], int n) {
    int i, j, key;

    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

/* 2. Bubble Sort */
void bubbleSort(int a[], int n) {
    int i, j, temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

/* 3. Selection Sort */
void selectionSort(int a[], int n) {
    int i, j, minIndex, temp;

    for (i = 0; i < n - 1; i++) {
        minIndex = i;

        for (j = i + 1; j < n; j++) {
            if (a[j] < a[minIndex])
                minIndex = j;
        }

        temp = a[i];
        a[i] = a[minIndex];
        a[minIndex] = temp;
    }
}

/* 4. Shell Sort */
void shellSort(int a[], int n) {
    int gap, i, j, temp;

    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = a[i];

            for (j = i; j >= gap && a[j - gap] > temp; j -= gap)
                a[j] = a[j - gap];

            a[j] = temp;
        }
    }
}

/* Quick Sort */
int partition(int arr[], int low, int high) {

    // Initialize pivot to be the first element
    int p = arr[low];
    int i = low;
    int j = high;

    while (i < j) {
        while (arr[i] <= p && i <= high - 1) {
            i++;
        }
        while (arr[j] > p && j >= low + 1) {
            j--;
        }
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[low], &arr[j]);
    return j;
}


/* 5. Quick Sort */
void quickSort(int a[], int low, int high) {
    int p;

    if (low < high) {
        p = partition(a, low, high);

        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

/* Merge Sort */
void merge(int a[], int low, int mid, int high) {
    int temp[MAX];
    int i = low;
    int j = mid + 1;
    int k = low;

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

    for (i = low; i <= high; i++)
        a[i] = temp[i];
}

/* 6. Merge Sort */
void mergeSort(int a[], int low, int high) {
    int mid;

    if (low < high) {
        mid = low + (high - low) / 2;

        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

/* Heapify */
void heapify(int a[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int temp;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i) {
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        heapify(a, n, largest);
    }
}

/* 7. Heap Sort */
void heapSort(int a[], int n) {
    int i, temp;

    for (i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for (i = n - 1; i > 0; i--) {
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        heapify(a, i, 0);
    }
}

/* 8. Radix Sort */
int getMax(int a[], int n) {
    int i, max = a[0];

    for (i = 1; i < n; i++) {
        if (a[i] > max)
            max = a[i];
    }

    return max;
}

void countingSortRadix(int a[], int n, int exp) {
    int output[MAX];
    int count[10] = {0};
    int i;

    for (i = 0; i < n; i++)
        count[(a[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        a[i] = output[i];
}

/* 8. Radix Sort - non-negative integers */
void radixSort(int a[], int n) {
    int max, exp;

    max = getMax(a, n);

    for (exp = 1; max / exp > 0; exp *= 10)
        countingSortRadix(a, n, exp);
}

/* 9. Counting Sort */
void countingSort(int a[], int n) {
    int min = a[0];
    int max = a[0];
    int range;
    int *count;
    int i, j, k = 0;

    for (i = 1; i < n; i++) {
        if (a[i] < min)
            min = a[i];

        if (a[i] > max)
            max = a[i];
    }

    range = max - min + 1;

    count = (int *)calloc(range, sizeof(int));

    if (count == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    for (i = 0; i < n; i++)
        count[a[i] - min]++;

    for (i = 0; i < range; i++) {
        for (j = 0; j < count[i]; j++)
            a[k++] = i + min;
    }

    free(count);
}

/* 10. Bucket Sort */
void bucketSort(int a[], int n) {
    int i, j, k;
    int min = a[0], max = a[0];
    int bucketCount;
    int *bucket;

    for (i = 1; i < n; i++) {
        if (a[i] < min)
            min = a[i];

        if (a[i] > max)
            max = a[i];
    }

    bucketCount = (int)sqrt(n) + 1;

    bucket = (int *)calloc(bucketCount, sizeof(int));

    if (bucket == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    /*
     * For integer data, use a simple bucket distribution
     * based on the value range.
     */
    int **buckets = (int **)malloc(bucketCount * sizeof(int *));
    int *sizes = (int *)calloc(bucketCount, sizeof(int));

    if (buckets == NULL || sizes == NULL) {
        printf("Memory allocation failed.\n");
        free(bucket);
        free(buckets);
        free(sizes);
        return;
    }

    for (i = 0; i < bucketCount; i++)
        buckets[i] = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        int index;

        if (max == min)
            index = 0;
        else
            index = (int)(((long long)(a[i] - min) * bucketCount) /
                          (max - min + 1));

        if (index >= bucketCount)
            index = bucketCount - 1;

        buckets[index][sizes[index]++] = a[i];
    }

    for (i = 0; i < bucketCount; i++)
        insertionSort(buckets[i], sizes[i]);

    k = 0;

    for (i = 0; i < bucketCount; i++) {
        for (j = 0; j < sizes[i]; j++)
            a[k++] = buckets[i][j];

        free(buckets[i]);
    }

    free(buckets);
    free(sizes);
    free(bucket);
}

/* 11. Radix Exchange Sort */
void radixExchangeSort(int a[], int left, int right, int bit) {
    int i, j, temp;

    if (left >= right || bit < 0)
        return;

    i = left;
    j = right;

    while (i <= j) {
        while (i <= right && ((a[i] >> bit) & 1) == 0)
            i++;

        while (j >= left && ((a[j] >> bit) & 1) == 1)
            j--;

        if (i < j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }

    radixExchangeSort(a, left, j, bit - 1);
    radixExchangeSort(a, i, right, bit - 1);
}

/* 11. Wrapper for Radix Exchange Sort */
void radixExchange(int a[], int n) {
    int max, bit = 0;

    max = getMax(a, n);

    while ((max >> bit) > 1)
        bit++;

    radixExchangeSort(a, 0, n - 1, bit);
}

/* 12. Address Calculation Sort */
void addressCalculationSort(int a[], int n) {
    int min = a[0];
    int max = a[0];
    int range;
    int i, j, k = 0;
    int *count;
    int *output;

    /*
     * Address calculation sort is implemented using
     * calculated positions from the value range.
     */

    for (i = 1; i < n; i++) {
        if (a[i] < min)
            min = a[i];

        if (a[i] > max)
            max = a[i];
    }

    range = max - min + 1;

    count = (int *)calloc(range, sizeof(int));
    output = (int *)malloc(n * sizeof(int));

    if (count == NULL || output == NULL) {
        printf("Memory allocation failed.\n");
        free(count);
        free(output);
        return;
    }

    for (i = 0; i < n; i++)
        count[a[i] - min]++;

    for (i = 1; i < range; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        int address = a[i] - min;

        output[count[address] - 1] = a[i];
        count[address]--;
    }

    for (i = 0; i < n; i++)
        a[i] = output[i];

    free(count);
    free(output);
}

int main() {
    int original[MAX];
    int a[MAX];
    int n, choice, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter %d elements: ", n);

    for (i = 0; i < n; i++)
        scanf("%d", &original[i]);

    printf("\nOriginal array: ");
    printArray(original, n);

    printf("\n SORTING MENU \n");
    printf("1.  Insertion Sort\n");
    printf("2.  Bubble Sort\n");
    printf("3.  Selection Sort\n");
    printf("4.  Shell Sort\n");
    printf("5.  Quick Sort\n");
    printf("6.  Merge Sort\n");
    printf("7.  Heap Sort\n");
    printf("8.  Radix Sort\n");
    printf("9.  Counting Sort\n");
    printf("10. Bucket Sort\n");
    printf("11. Radix Exchange Sort\n");
    printf("12. Address Calculation Sort\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    copyArray(original, a, n);

    switch (choice) {
        case 1:
            insertionSort(a, n);
            break;

        case 2:
            bubbleSort(a, n);
            break;

        case 3:
            selectionSort(a, n);
            break;

        case 4:
            shellSort(a, n);
            break;

        case 5:
            quickSort(a, 0, n - 1);
            break;

        case 6:
            mergeSort(a, 0, n - 1);
            break;

        case 7:
            heapSort(a, n);
            break;

        case 8:
            radixSort(a, n);
            break;

        case 9:
            countingSort(a, n);
            break;

        case 10:
            bucketSort(a, n);
            break;

        case 11:
            radixExchange(a, n);
            break;

        case 12:
            addressCalculationSort(a, n);
            break;

        default:
            printf("Invalid choice.\n");
            return 1;
    }

    printf("\nSorted array: ");
    printArray(a, n);

    return 0;
}

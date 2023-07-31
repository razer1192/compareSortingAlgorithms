#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;
int swap(int *array, int pos1, int pos2){
    int tmp = array[pos1];
    array[pos1] = array[pos2];
    array[pos2] = tmp;

}
void merge(int arr[], int l, int m, int r)
{
    int i;
	int j;
	int k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    //create temp arrays 
    int *L = (int*) malloc(n1*sizeof(int));
    int *R = (int*) malloc(n2*sizeof(int));

    //copy the data to temp arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    
    i = 0; // index of first subarray
    j = 0; // index of second subarray
    k = l; // index of merged subarray
    while (i < n1 && j < n2){

        if (L[i] <= R[j]){

            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    //copies the remainders of 1st array
    while (i < n1){

        arr[k] = L[i];
        i++;
        k++;
    }

    //copies the remainders of the 2nd array
    while (j < n2){

        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}
// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if (l < r){

        int m = (l+r)/2;
        mergeSort(pData, l, m);
        mergeSort(pData, m+1, r);
        merge(pData, l, m, r);
    }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int i;
	int item;
	int j;
    for (i = 1; i < n; i++){

         item = pData[i];

		//this part sorts the numbers
          for(j=i-1; j>=0; j--){

              if(pData[j]>item){
                pData[j+1] = pData[j];
                    }
              else{
                break;
              }
          }
          pData[j+1] = item;
    }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	
    for(int i = 0; i < n; i++){
        
        int tmp  = 0;
       
        for(int j = 0; j < n - i - 1; j++){
            if(pData[j] > pData[j+1]){
                swap(pData,j,j+1);
                tmp++;
            }


        }
        
        
    }
    printf("\n");
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int i;
	int j;
	int min_idx;
	int temp;
	
	for (i = 0; i < n-1; i++)
	{
	    
		
		min_idx = i;
		for (j = i+1; j < n; j++)
		if (pData[j] < pData[min_idx]){
			min_idx = j;
		   }
		temp = pData[i];
		pData[i] = pData[min_idx];
		pData[min_idx] = temp;

		
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	/*
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
	}
	
	return dataSz;
	*/

	FILE* inFile = fopen(inputFileName,"r");
    int numInputs;
    int value;
    fscanf(inFile, " %d\n", &numInputs);
    int* numArray = NULL;
    numArray = (int *) malloc(numInputs * sizeof(int));
    //*ppData = (int *) malloc(numInputs * sizeof(int));
    
    for(int i = 0; i < numInputs; i++){
        fscanf(inFile," %d", &value);
		//ppData[i] = value;
        numArray[i] = value;
    }
    /*for(int i = 0; i < numInputs; i++){
			//printf("%d ", ppData[i]);
			printf("%d ", numArray[i]);
		}*/
    *ppData = numArray;
    for(int i = 0; i < numInputs; i++){
			//printf("%d ", *ppData[i]);
			//printf("%d ", numArray[i]);
		}
    //free(numArray);
  //  printArray(*ppData, numInputs);
    return numInputs;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)//!!!!!!remember to set this to 3
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}
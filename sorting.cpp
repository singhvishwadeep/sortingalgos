//============================================================================
// Name        : sorting.cpp
// Author      : Vishwadeep Singh
// Version     :
// Copyright   : GNU License
// Description : bubble sort, insertion sort, merge sort
//		 selection sort, shell sort, quick sort
//============================================================================

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define SIZE 15
#define SETSIZE 1000
#define debug 0
#define tempdebug 0
#define timedebug 1
#define errdebug 1

using namespace std;

struct timeval t0,t1;
double elapsedTime;

struct timeval t0in,t1in;
double elapsedTimein;

void starttime () {
	gettimeofday(&t0, NULL);
}

double endtime (const string str) {
	gettimeofday(&t1, NULL);
	elapsedTime = (t1.tv_sec - t0.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (t1.tv_usec - t0.tv_usec) / 1000.0;   // us to ms
	if (timedebug)
		cout << "elapsed " << elapsedTime << " ms. " << str << endl;
	return elapsedTime;
}

void starttimein () {
	gettimeofday(&t0in, NULL);
}

double endtimein (const string str) {
	gettimeofday(&t1in, NULL);
	elapsedTimein = (t1in.tv_sec - t0in.tv_sec) * 1000.0;      // sec to ms
	elapsedTimein += (t1in.tv_usec - t0in.tv_usec) / 1000.0;   // us to ms
	if (timedebug)
		cout << "elapsed " << elapsedTimein << " ms. " << str << endl;
	return elapsedTimein;
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) {
	if (l < r) {
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l+(r-l)/2;
		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);
		merge(arr, l, m, r);
    }
}


void quicksort(int *x,int first,int last){
    int pivot,j,temp,i;

     if(first<last){
         pivot=first;
         i=first;
         j=last;

         while(i<j){
             while(x[i]<=x[pivot]&&i<last)
                 i++;
             while(x[j]>x[pivot])
                 j--;
             if(i<j){
                 temp=x[i];
                  x[i]=x[j];
                  x[j]=temp;
             }
         }
         temp=x[pivot];
         x[pivot]=x[j];
         x[j]=temp;
         quicksort(x,first,j-1);
         quicksort(x,j+1,last);
    }
}

void shellsort(int *arr, int num)
{
    int i, j, k, tmp;
    for (i = num / 2; i > 0; i = i / 2)
    {
        for (j = i; j < num; j++)
        {
            for(k = j - i; k >= 0; k = k - i)
            {
                if (arr[k+i] >= arr[k])
                    break;
                else
                {
                    tmp = arr[k];
                    arr[k] = arr[k+i];
                    arr[k+i] = tmp;
                }
            }
        }
    }
}

int validatesort (int *arr, int size) {
	int prev = arr[0];
	for (int i = 0; i < size; i++) {
		if (prev > arr[i]) {
			return 1;
		}
		prev = arr[i];
	}
	return 0;
}

int main() {

	// variables
	int generate_stats = SIZE;
	int *sample_size = new int [SIZE];
	int **data = new int*[generate_stats];
	int **backupdata = new int*[generate_stats];
	srand(time(NULL));

	starttime();
	// generating data
	for (int i = 0; i < generate_stats; i++) {
		int max = (i+1)*SETSIZE;
		int min = (i)*SETSIZE;
		sample_size[i] = rand()%(max-min + 1) + min;
		if (debug)
			cout << "generated " << sample_size[i] << " sample size of " << i << endl;

		data[i] = new int[sample_size[i]];
		backupdata[i] = new int[sample_size[i]];
		for (int j = 0; j < sample_size[i]; j++) {
			data[i][j] = rand()%100;
			backupdata[i][j] = data[i][j];
			if (debug)
				cout << "data[" << i << "][" << j << "] = " << data[i][j] << endl;
		}
	}
	endtime("collecting data finished");

	starttime();
	for (int i = 0; i < generate_stats; i++) {
		if (debug)
			cout << "sorting ";
		for (int j = 0; j < sample_size[i]; j++) {
			if (debug)
				cout << data[i][j] << " ";
		}
		if (debug)
			cout << endl;
		starttimein();
		// bubble sort
		for (int j = 0 ; j < ( sample_size[i] - 1 ); j++) {
			for (int d = 0 ; d < sample_size[i] - j - 1; d++) {
				if (data[i][d] > data[i][d+1]) {
					int swap       = data[i][d];
					data[i][d]   = data[i][d+1];
					data[i][d+1] = swap;
				}
			}

			if (tempdebug)
				cout << "sorting temp ";
			for (int te = 0; te < sample_size[i]; te++) {
				if (tempdebug)
					cout << data[i][te] << " ";
			}
			if (tempdebug)
				cout << endl;

		}
		if (debug)
			cout << "sorting ";
		for (int j = 0; j < sample_size[i]; j++) {
			if (debug)
				cout << data[i][j] << " ";
		}
		if (debug)
			cout << endl;

		if (timedebug)
			cout << "data size = " << sample_size[i] << " ";
		endtimein("single bubble sort finished");
	}
	endtime("bubble sort finished");

	for (int i = 0; i < generate_stats; i++) {
		if (validatesort(data[i],sample_size[i])) {
			cout << "Error while validating results for bubble sort, data size: " << sample_size[i] << endl;
			if (errdebug) {
				for (int j = 0; j < sample_size[i]; j++) {
					cout << data[i][j] << " ";
				}
				cout << endl;
			}
		}
	}

	// reverting back;
	for (int i = 0; i < generate_stats; i++) {
		for (int j = 0; j < sample_size[i]; j++) {
			data[i][j] = backupdata[i][j];
		}
	}

	starttime();
	for (int i = 0; i < generate_stats; i++) {
		if (debug)
			cout << "sorting ";
		for (int j = 0; j < sample_size[i]; j++) {
			if (debug)
				cout << data[i][j] << " ";
		}
		if (debug)
			cout << endl;
		starttimein();
		// insertion sort
		for (int j = 1 ; j < ( sample_size[i] ); j++) {
		    int d = j;
		    while ( d > 0 && data[i][d] < data[i][d-1]) {
		      int t          = data[i][d];
		      data[i][d]   = data[i][d-1];
		      data[i][d-1] = t;
		      d--;
		    }

			if (tempdebug)
				cout << "sorting temp ";
			for (int te = 0; te < sample_size[i]; te++) {
				if (tempdebug)
					cout << data[i][te] << " ";
			}
			if (tempdebug)
				cout << endl;

		}
		if (debug)
			cout << "sorting ";
		for (int j = 0; j < sample_size[i]; j++) {
			if (debug)
				cout << data[i][j] << " ";
		}
		if (debug)
			cout << endl;

		if (timedebug)
			cout << "data size = " << sample_size[i] << " ";
		endtimein("single insertion sort finished");
	}
	endtime("insertion sort finished");

	for (int i = 0; i < generate_stats; i++) {
		if (validatesort(data[i],sample_size[i])) {
			cout << "Error while validating results for insertion sort, data size: " << sample_size[i] << endl;
			if (errdebug) {
				for (int j = 0; j < sample_size[i]; j++) {
					cout << data[i][j] << " ";
				}
				cout << endl;
			}
		}
	}

	// reverting back;
	for (int i = 0; i < generate_stats; i++) {
		for (int j = 0; j < sample_size[i]; j++) {
			data[i][j] = backupdata[i][j];
		}
	}

	starttime();
	for (int i = 0; i < generate_stats; i++) {
		if (debug)
			cout << "sorting ";
		for (int j = 0; j < sample_size[i]; j++) {
			if (debug)
				cout << data[i][j] << " ";
		}
		if (debug)
			cout << endl;
		starttimein();
		// merge sort
		mergeSort(data[i], 0, sample_size[i]-1);
		if (debug)
			cout << "sorting ";
		for (int j = 0; j < sample_size[i]; j++) {
			if (debug)
				cout << data[i][j] << " ";
		}
		if (debug)
			cout << endl;

		if (timedebug)
			cout << "data size = " << sample_size[i] << " ";
		endtimein("single merge sort finished");
	}
	endtime("merge sort finished");

	for (int i = 0; i < generate_stats; i++) {
		if (validatesort(data[i],sample_size[i])) {
			cout << "Error while validating results for merge sort, data size: " << sample_size[i] << endl;
			if (errdebug) {
				for (int j = 0; j < sample_size[i]; j++) {
					cout << data[i][j] << " ";
				}
				cout << endl;
			}
		}
	}

	// reverting back;
	for (int i = 0; i < generate_stats; i++) {
		for (int j = 0; j < sample_size[i]; j++) {
			data[i][j] = backupdata[i][j];
		}
	}

	starttime();
	for (int i = 0; i < generate_stats; i++) {
		if (debug)
			cout << "sorting ";
		for (int j = 0; j < sample_size[i]; j++) {
			if (debug)
				cout << data[i][j] << " ";
		}
		if (debug)
			cout << endl;
		starttimein();
		// quicksort
		quicksort(data[i],0,sample_size[i]-1);
		if (debug)
			cout << "sorting ";
		for (int j = 0; j < sample_size[i]; j++) {
			if (debug)
				cout << data[i][j] << " ";
		}
		if (debug)
			cout << endl;

		if (timedebug)
			cout << "data size = " << sample_size[i] << " ";
		endtimein("single quick sort finished");
	}
	endtime("quick sort finished");

	for (int i = 0; i < generate_stats; i++) {
		if (validatesort(data[i],sample_size[i])) {
			cout << "Error while validating results for quick sort, data size: " << sample_size[i] << endl;
			if (errdebug) {
				for (int j = 0; j < sample_size[i]; j++) {
					cout << data[i][j] << " ";
				}
				cout << endl;
			}
		}
	}

	// reverting back;
	for (int i = 0; i < generate_stats; i++) {
		for (int j = 0; j < sample_size[i]; j++) {
			data[i][j] = backupdata[i][j];
		}
	}

	starttime();
	for (int i = 0; i < generate_stats; i++) {
		if (debug)
			cout << "sorting ";
		for (int j = 0; j < sample_size[i]; j++) {
			if (debug)
				cout << data[i][j] << " ";
		}
		if (debug)
			cout << endl;
		starttimein();
		int n = sample_size[i];
		// selection sort
		for (int c = 0 ; c < ( n - 1 ) ; c++ ) {
		  int position = c;

		  for (int d = c + 1 ; d < n ; d++ ) {
			 if ( data[i][position] > data[i][d] )
				position = d;
		  }
		  if ( position != c ) {
			 int swap = data[i][c];
			 data[i][c] = data[i][position];
			 data[i][position] = swap;
		  }
		}

		if (debug)
			cout << "sorting ";
		for (int j = 0; j < sample_size[i]; j++) {
			if (debug)
				cout << data[i][j] << " ";
		}
		if (debug)
			cout << endl;

		if (timedebug)
			cout << "data size = " << sample_size[i] << " ";
		endtimein("single selection sort finished");
	}
	endtime("selection sort finished");

	for (int i = 0; i < generate_stats; i++) {
		if (validatesort(data[i],sample_size[i])) {
			cout << "Error while validating results for selection sort, data size: " << sample_size[i] << endl;
			if (errdebug) {
				for (int j = 0; j < sample_size[i]; j++) {
					cout << data[i][j] << " ";
				}
				cout << endl;
			}
		}
	}

	// reverting back;
	for (int i = 0; i < generate_stats; i++) {
		for (int j = 0; j < sample_size[i]; j++) {
			data[i][j] = backupdata[i][j];
		}
	}

	starttime();
	for (int i = 0; i < generate_stats; i++) {
		if (debug)
			cout << "sorting ";
		for (int j = 0; j < sample_size[i]; j++) {
			if (debug)
				cout << data[i][j] << " ";
		}
		if (debug)
			cout << endl;
		starttimein();
		// shell sort
		shellsort(data[i],sample_size[i]);
		if (debug)
			cout << "sorting ";
		for (int j = 0; j < sample_size[i]; j++) {
			if (debug)
				cout << data[i][j] << " ";
		}
		if (debug)
			cout << endl;

		if (timedebug)
			cout << "data size = " << sample_size[i] << " ";
		endtimein("single shell sort finished");
	}
	endtime("shell sort finished");

	for (int i = 0; i < generate_stats; i++) {
		if (validatesort(data[i],sample_size[i])) {
			cout << "Error while validating results for shell sort, data size: " << sample_size[i] << endl;
			if (errdebug) {
				for (int j = 0; j < sample_size[i]; j++) {
					cout << data[i][j] << " ";
				}
				cout << endl;
			}
		}
	}

	cout << "Analysis completed." << endl;
	return 0;
}

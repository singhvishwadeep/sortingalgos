//============================================================================
// Name        : cppexplorer.cpp
// Author      : Vishwadeep Singh
// Version     :
// Copyright   : GNU License
// Description : bubble sort, insertion sort, merge sort
//				selection sort, shell sort, quick sort
//============================================================================

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define SIZE 5
#define SETSIZE 10000
#define debug 0
#define tempdebug 0
#define timedebug 1

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

void merge(int *arr,int min,int mid,int max)
{
	if (debug)
		cout << "checking again ";
	for (int j = 0; j < max; j++) {
		if (debug)
			cout << arr[j] << " ";
	}
	if (debug)
		cout << endl;
  int tmp[max+1];
  int i,j,k,m;
  j=min;
  m=mid+1;
  for(i=min; j<=mid && m<=max ; i++)
  {
     if(arr[j]<=arr[m])
     {
         tmp[i]=arr[j];
         j++;
     }
     else
     {
         tmp[i]=arr[m];
         m++;
     }
  }
  if(j>mid)
  {
     for(k=m; k<=max; k++)
     {
         tmp[i]=arr[k];
         i++;
     }
  }
  else
  {
     for(k=j; k<=mid; k++)
     {
        tmp[i]=arr[k];
        i++;
     }
  }
  for(k=min; k<=max; k++)
     arr[k]=tmp[k];
}

void part(int *arr,int min,int max)
{
	if (debug)
		cout << "checking ";
	for (int j = 0; j < max; j++) {
		if (debug)
			cout << arr[j] << " ";
	}
	if (debug)
		cout << endl;
 int mid;
 if(min<max)
 {
   mid=(min+max)/2;
   part(arr,min,mid);
   part(arr,mid+1,max);
   merge(arr,min,mid,max);
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
		for (int j = 1 ; j < ( sample_size[i] - 1 ); j++) {
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
		part(data[i],0,sample_size[i]-1);
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


	cout << "Analysis completed." << endl;
	return 0;
}

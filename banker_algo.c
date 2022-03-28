#include <stdio.h>

 void matrix(int *m,int *n,int allocation[][*n],int max[][*n],int avail[][*n],int need[][*n]);
 void display(int *m,int *n,int allocation[][*n],int max[][*n],int avail[][*n],int need[][*n]);
 void safety_algo(int *m,int *n,int allocation[][*n],int avail[][*n],int need[][*n]);
 void resource_rqst_algo(int *m,int *n,int allocation[][*n],int avail[][*n],int need[][*n]);

 int main() {
 	int m,n,mark_a,mark_b;
 	char choice;

 	mark_b :
	printf("\nEnter the number of processes\t:\t");
	scanf("%d",&m); 
	printf("\nEnter the number of resource type\t:\t");
	scanf("%d",&n);
	int allocation[m][n];int max[m][n];int need[m][n];int avail[1][n];
 	matrix(&m,&n,allocation,max,avail,need);
 	display(&m,&n,allocation,max,avail,need);

 	mark_a :
 	printf("\nDo you want to check whether the system is in safe state or not?\npress Y || N\n");
 	scanf("%*c%c",&choice);
 	if(choice=='y' || choice=='Y') {
 		safety_algo(&m,&n,allocation,avail,need);
 		printf("\nDo you want to request to add a particular resource instance or not?\npress Y || N\n");
 		scanf("%*c%c",&choice);
 		if(choice=='y' || choice=='Y') {
	 		resource_rqst_algo(&m,&n,allocation,avail,need);
	 		display(&m,&n,allocation,max,avail,need);
	 		goto mark_a;
	 	}
 	}
 	printf("\nDo you want to create another table or not?\npress Y || N\n");
 	scanf("%*c%c",&choice);
 	if(choice=='y' || choice=='Y') {
 		goto mark_b;
 	}
 	return 0;
 }

//this function will take input from user
//creation of available vector of size m
//creation of m*n max matrix
//creation of m*n allocation matrix
//creation of m*n need matrix
void matrix(int *m,int *n,int allocation[][*n],int max[][*n],int avail[][*n],int need[][*n]) {
	int i,j;
 	for(i = 0; i < *m; i++) {
 		for(j = 0; j < *n; j++) {
 			printf("\nEnter the instances of allocation matrix for process p%d\t:\t",i);
 			scanf("%d",&allocation[i][j]);
 		}
 		printf("\n"); 		
    }
    for(i = 0; i < *m; i++) {
 		for(j = 0; j < *n; j++) {
 			printf("\nEnter the maximum instances of resource matrix for process p%d\t:\t",i);
 			scanf("%d",&max[i][j]);
 		}
 		printf("\n");
 	}
 	for(i = 0; i < *n; i++) {
 		printf("\nEnter the available instances of resource type\t:\t");
 		scanf("%d",&avail[0][i]);
 	}
 	for(i = 0; i < *m; i++) {
 		for (j = 0; j < *n; j++) {
 			need[i][j]=max[i][j]-allocation[i][j];
 		}
 	}
}

//Banker's Algorithm Implementation
void safety_algo(int *m,int *n,int allocation[][*n],int avail[][*n],int need[][*n]) {
	int i,j,k,flag,x=0;
	int work[1][*n];int finish[*m];int ans[*m];

	for(i = 0; i < *n; i++)
		work[0][i]=avail[0][i];
	for(i = 0; i < *m; i++)
		finish[i]=0;

	for(k = 0; k < *m; k++) {
		for(i = 0; i < *m; i++) {
			if(finish[i]==0) {
				flag=1;
				for(j = 0; j < *n; j++) {
					if(need[i][j]>work[0][j])
						flag=0;
				}
				if(flag==1 && finish[i]==0) {
					for(j=0; j < *n; j++) {
						work[0][j]+=allocation[i][j];
					}
					ans[x++]=i;
					finish[i]=1;
				}
			}
		}
	}
	for (i=0;i<*m;i++) {
		if(finish[i]==0) {
			printf("\nThe system is not in safe state");
			flag=0;
			break;
		}
	}
	if(flag!=0) {
		printf("\nThe following safe sequnce is : ");
		for(i=0;i<*m;i++) {
			printf("p%d\t",ans[i]);
		}
		printf("\n");
	}	
}

//Resource Request Algorithm Implementation
void resource_rqst_algo(int *m,int *n,int allocation[][*n],int avail[][*n],int need[][*n]) {
	int i,j,pno;
	int rqst[1][*n];

	printf("\nEnter the process number : ");
	scanf("%d",&pno);
	for (i = 0; i < *n; i++) {
		printf("\nEnter the required instances of request : ");
		scanf("%d",&rqst[0][i]);
	}
	for(i = 0; i < *n; i++) {
		if(rqst[0][i]>avail[0][i]) {
			printf("\nRequest cannot be processed : Unavailable resource instance");
			return;
		}
	}
	for(i = 0; i < *n; i++) {
		if(rqst[0][i]>need[pno][i]) {
			printf("\nRequest cannot be processed");
			return;
		}
	}
	for(i = 0; i < *n; i++) {
		printf("\nRequest can be processed\n");
		need[pno][i] -= rqst[0][i];
		avail[0][i] -= rqst[0][i];
		allocation[pno][i] += rqst[0][i];
	}
}

//to view the entered data
void display(int *m,int *n,int allocation[][*n],int max[][*n],int avail[][*n],int need[][*n]) {
	int i,j;
	printf("\nProcess\t\tAllocation\tMax\tAvailabe\tNeed");
	for(i = 0; i < *m; i++) {
		printf("\np%d\t\t",i);
		for(j=0;j<*n;j++) {
			printf("%d ",allocation[i][j]);
		}
		printf("\t\t");
		for(j = 0; j < *n; j++) {
			printf("%d ",max[i][j]);
		}
		printf("\t");
		if(i==0) {
			for(j = 0; j < *n; j++)
				printf("%d ",avail[0][j]);
		}
		printf("\t\t");
		for(j = 0; j < *n; j++) {
			printf("%d ",need[i][j]);
		}
	}
	printf("\n");
}
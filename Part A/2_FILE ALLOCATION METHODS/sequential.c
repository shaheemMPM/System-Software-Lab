#include<stdio.h>
#include<string.h>

struct file{
  int sAddr;
  int len;
  char file[10];
  int isAlloc;
};

void clearScreen();

int main(){

  struct file files[10];
	int n, nb, nf, status[100], visit[100], flag;
	char block[100], tempStatus[15];

  clearScreen();
  printf("\nSequential File Allocation\n--------------------------\n\n");

	printf("Enter Number of blocks : ");
	scanf("%d", &nb);
	printf("Enter Number of files : ");
	scanf("%d", &nf);


	for(int i = 0; i < nb; i++){
		block[i] = '0';
		status[i] = 1;
	}

	for (int i = 0; i < nf; i++){
		printf("\n\nEnter Starting Address of File %d : ", i+1);
		scanf("%d", &files[i].sAddr);
		printf("Enter Length of File %d : ", i+1);
		scanf("%d", &files[i].len);
		printf("Enter Content of File %d : ", i+1);
		scanf("%s", files[i].file);
    files[i].isAlloc = 0;
	}

  printf("\nEnter Number of Blocks to Visit : ");
  scanf("%d", &n);
  printf("Enter Block Numbers : ");
  for (int i = 0; i < n; i++){
    scanf("%d", &visit[i]);
  }

	for (int i = 0; i < nf; i++){
		flag = -1;
		for(int j = files[i].sAddr-1; j < (files[i].sAddr+files[i].len-1); j++){
			if(status[j] != 1){
				flag = 1;
				break;
			}
      if (j >= nb) {
        flag = 1;
        break;
      }
		}
		if (flag == -1){
      files[i].isAlloc = 1;
      for(int j = files[i].sAddr-1, k = 0; j < (files[i].sAddr+files[i].len-1); j++, k++){
        block[j] = files[i].file[k];
        status[j] = 0;
  		}
    }
	}

  clearScreen();
  printf("\nOutputs\n=======\n\n");
  printf("Request's Starting Address      Status\n--------------------------------------\n");
  for (int i = 0; i < nf; i++){
    if (files[i].isAlloc == 0) {
      strcpy(tempStatus , "Not Allocated");
    }else{
      strcpy(tempStatus , "Allocated");
    }
    printf("             %d                  %s\n", files[i].sAddr, tempStatus);
  }
  printf("\n\n\nStatus of Memory Blocks\n-----------------------\n");
  for (int i = 0; i < nb; i++){
    if (status[i] == 1) {
      strcpy(tempStatus , "Free");
    }else{
      strcpy(tempStatus , "Occupied");
    }
    printf("%d    %s\n", i+1, tempStatus);
  }
  printf("\n\n\nBlocks      Contents\n--------------------\n");
  for (int i = 0; i < n; i++){
    printf("  %d           %c\n", visit[i], block[visit[i]-1]);
  }
  printf("\n\n\n");
  return 0;
}

void clearScreen(){
  printf("\e[1;1H\e[2J");
}

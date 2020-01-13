#include<stdio.h>

struct file {
  int len;
  int index;
  char content[10];
  int isAlloc;
  int space[10];
};

void clearScreen();

int main(){
  struct file files[10];
  int nb, nf, status[100], top = 1, k, tTop;
  char blocks[100];

  printf("Enter Number of blocks : ");
	scanf("%d", &nb);
	printf("Enter Number of files : ");
	scanf("%d", &nf);

  for (int i = 0; i < nb; i++){
    status[i] = 1;
    blocks[i] = '0';
  }

  for (int i = 0; i < nf; i++){
		printf("\n\nEnter Length of File %d : ", i+1);
		scanf("%d", &files[i].len);
    printf("Enter Index Node of File %d : ", i+1);
    scanf("%d", &files[i].index);
		printf("Enter Content of File %d : ", i+1);
		scanf("%s", files[i].content);
    files[i].isAlloc = 0;
	}

/*

  for(int i = 0; i < nf; i++){
    if (status[files[i].index] == 1 && top <= nb) {
      status[files[i].index] = 0;
      tTop = top;
      for (int j = 0; j < files[i].len; j++){
        k = 0;
        while (1) {
          if (top > nb) {
            break;
          }
          if (status[top] == 1) {
            files[i].space[k++] = top++;
            break;
          }else{
            top++;
          }
        }
      }
      top = tTop;
      if (k != files[i].len){
        status[files[i].index] = 1;
      }else{
        for (int j = 0; j < files[i].len; j++){
          while (1) {
            if (status[top] == 1) {
              status[top] = 0;
              blocks[top++] = files[i].content[j];
              break;
            }else{
              top++;
            }
          }
        }
        files[i].isAlloc = 1;
      }
    }
  }

  for (int i = 0; i < nf; i++){
    printf("%d\t\t", files[i].index);
    if (files[i].isAlloc == 1) {
      for (int j = 0; j < files[i].len; j++){
        printf("%d, ", files[i].space[j]);
      }
      printf("\t\tAllocated\n");
    }else{
      printf("\t\t\t\tNot Allocated\n");
    }
  }
*/
  return 0;
}

void clearScreen(){
  printf("\e[1;1H\e[2J");
}

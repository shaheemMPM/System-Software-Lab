#include<stdio.h>

struct process{
  int index;
  char pid[5];
  int bt;
  int at;
  int pt;
  int tt;
  int wt;
  int done;
} pr[10];

void clearScreen();
void readProcess(int);
void sortByAt(int);
void sortByIndex(int);
void printPorcess(int);
void fcfs(int);
void sjf(int);
void roundRobin(int, int);
void priority(int);

int main(){
  int n, qt;
  clearScreen();
  printf("\n\nCPU Scheduling Algorithms\n");
  printf("=========================\n\n");
  printf("Enter Number of Process : ");
  scanf("%d", &n);
  printf("\nEnter Time Quantum for Round Robin : ");
  scanf("%d", &qt);
  readProcess(n);
  clearScreen();
  printPorcess(n);
  fcfs(n);
  sjf(n);
  roundRobin(n, qt);
  priority(n);
  printf("\n\n\n");
  return 0;
}

void clearScreen(){
  printf("\e[1;1H\e[2J");
}

void readProcess(int n){
  for (int i = 0; i < n; i++){
    pr[i].index = i;
    printf("\n\nEnter Process Name : ");
    scanf("%s", pr[i].pid);
    printf("Enter Arrival Time (AT) of %s : ", pr[i].pid);
    scanf("%d", &pr[i].at);
    printf("Enter Burst Time (BT) of %s : ", pr[i].pid);
    scanf("%d", &pr[i].bt);
    printf("Enter Priority of %s : ", pr[i].pid);
    scanf("%d", &pr[i].pt);
    pr[i].wt = 0;
    pr[i].tt = 0;
  }
}

void sortByAt(int n){
  int sm;
  struct process tempProc;
  for (int i = 0; i < n-1; i++){
    sm = i;
    for (int j = i+1; j < n; j++){
      if (pr[j].at < pr[sm].at) {
        sm = j;
      }
    }
    if (sm != i) {
      tempProc = pr[i];
      pr[i] = pr[sm];
      pr[sm] = tempProc;
    }
  }
}

void sortByIndex(int n){
  int sm;
  struct process tempProc;
  for (int i = 0; i < n-1; i++){
    sm = i;
    for (int j = i+1; j < n; j++){
      if (pr[j].index < pr[sm].index) {
        sm = j;
      }
    }
    if (sm != i) {
      tempProc = pr[i];
      pr[i] = pr[sm];
      pr[sm] = tempProc;
    }
  }
}

void printPorcess(int n){
  sortByIndex(n);
  printf("\n\nProcess      AT      BT      Priority\n");
  printf("-------------------------------------");
  for (int i = 0; i < n; i++){
    printf("\n  %s          %d      %d          %d", pr[i].pid, pr[i].at, pr[i].bt, pr[i].pt);
  }
}

void fcfs(int n) {
  sortByAt(n);
  int st = pr[0].at;   //service time (total time processor worked)
  for (int i = 0; i < n; i++){
    pr[i].wt = st - pr[i].at;
    st += pr[i].bt;
    pr[i].tt = st - pr[i].at;
  }
  sortByIndex(n);
  printf("\n\n\n\nOutput (FCFS)\n");
  printf("-------------");
  printf("\nProcess      TAT      WT\n");
  for (int i = 0; i < n; i++){
    printf("\n  %s          %d       %d", pr[i].pid, pr[i].tt, pr[i].wt);
  }
}

void sjf(int n){
  sortByAt(n);
  int st, top=-1, sm, tIndex;
  struct process tempChart[10], tempProc;
  for (int i = 0; i < n; i++){
    pr[i].done = 0;
  }
  st = pr[0].at;
  for (int k = 0; k < n; k++){
    // finds all the processes which are currently arrived at the processor
    for (int i = 0; i < n; i++){
      if (pr[i].at <= st && pr[i].done != 1) {
        tempChart[++top] = pr[i];
      }
    }
    // sort tempChart by BT
    for (int i = 0; i < top; i++){
      sm = i;
      for (int j = i+1; j <= top; j++){
        if (tempChart[j].bt < tempChart[sm].bt) {
          sm = j;
        }
      }
      if (sm != i) {
        tempProc = tempChart[i];
        tempChart[i] = tempChart[sm];
        tempChart[sm] = tempProc;
      }
    }
    // finds WT and TAT of currently arrived smallest process
    tIndex = tempChart[0].index;
    for (int i = 0; i < n; i++){
      if (pr[i].index == tIndex) {
        pr[i].wt = st - pr[i].at;
        st += pr[i].bt;
        pr[i].tt = st - pr[i].at;
        pr[i].done = 1;
        break;
      }
    }
    top = -1;
  }
  sortByIndex(n);
  printf("\n\n\n\nOutput (SJF)\n");
  printf("------------");
  printf("\nProcess      TAT      WT\n");
  for (int i = 0; i < n; i++){
    printf("\n  %s          %d       %d", pr[i].pid, pr[i].tt, pr[i].wt);
  }
}

void roundRobin(int n, int qTime){
  struct process rr[100];
  int rear = n-1, st, tIndex;
  sortByAt(n);
  for (int i = 0; i < n; i++){
    rr[i] = pr[i];
  }
  st = rr[0].at;
  for (int i = 0; i <= rear; i++){
    if (rr[i].at <= st && rr[i].bt > 0) {
      if (rr[i].bt >= qTime) {
        rr[i].bt -= qTime;
        st += qTime;
      }else{
        st += rr[i].bt;
        rr[i].bt = 0;
      }
    }
    if (rr[i].bt > 0) {
      rr[++rear] = rr[i];
    }else{
      tIndex = rr[i].index;
      for (int j = 0; j < n; j++){
        if (pr[j].index == tIndex) {
          pr[j].wt = st - pr[j].at - pr[j].bt;
          pr[j].tt = st - pr[j].at;
          break;
        }
      }
    }
  }
  sortByIndex(n);
  printf("\n\n\n\nOutput (Round Robin)\n");
  printf("--------------------");
  printf("\nProcess      TAT      WT\n");
  for (int i = 0; i < n; i++){
    printf("\n  %s          %d       %d", pr[i].pid, pr[i].tt, pr[i].wt);
  }
}

void priority(int n){
  sortByAt(n);
  int st, top=-1, sm, tIndex;
  struct process tempChart[10], tempProc;
  for (int i = 0; i < n; i++){
    pr[i].done = 0;
  }
  st = pr[0].at;
  for (int k = 0; k < n; k++){
    // finds all the processes which are currently arrived at the processor
    for (int i = 0; i < n; i++){
      if (pr[i].at <= st && pr[i].done != 1) {
        tempChart[++top] = pr[i];
      }
    }
    // sort tempChart by Priority
    for (int i = 0; i < top; i++){
      sm = i;
      for (int j = i+1; j <= top; j++){
        if (tempChart[j].pt < tempChart[sm].pt) {
          sm = j;
        }
      }
      if (sm != i) {
        tempProc = tempChart[i];
        tempChart[i] = tempChart[sm];
        tempChart[sm] = tempProc;
      }
    }
    // finds WT and TAT of currently arrived highest priority
    tIndex = tempChart[0].index;
    for (int i = 0; i < n; i++){
      if (pr[i].index == tIndex) {
        pr[i].wt = st - pr[i].at;
        st += pr[i].bt;
        pr[i].tt = st - pr[i].at;
        pr[i].done = 1;
        break;
      }
    }
    top = -1;
  }
  sortByIndex(n);
  printf("\n\n\n\nOutput (Priority)\n");
  printf("-----------------");
  printf("\nProcess      TAT      WT\n");
  for (int i = 0; i < n; i++){
    printf("\n  %s          %d       %d", pr[i].pid, pr[i].tt, pr[i].wt);
  }
}

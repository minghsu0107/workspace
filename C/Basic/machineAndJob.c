#include <stdio.h>
#define MAX_NUM_JOBS 500
#define MAX_NUM_MACH 500
#define MAX_NUM_TASKS 500
int machReadyTime[MAX_NUM_MACH];
int taskSeq[MAX_NUM_JOBS][MAX_NUM_TASKS][2];
int numJobTasks[MAX_NUM_JOBS];
int nextTaskPos[MAX_NUM_JOBS]; // number of completed tasks in each job
int lastTaskCompTime[MAX_NUM_JOBS];
 
int main(){
  int N, M;
  int numTotalTasks = 0;
  scanf("%d%d", &N, &M);
  for( int i = 0 ; i < N ; ++i )
    machReadyTime[i] = 0;
  for( int i = 0 ; i < M ; ++i ){
    scanf("%d%d", &lastTaskCompTime[i], &numJobTasks[i]);
    for(int j = 0 ; j < numJobTasks[i] ; ++j ){
      scanf("%d%d", &taskSeq[i][j][0], &taskSeq[i][j][1]);
      ++numTotalTasks;
    }
    nextTaskPos[i] = 0;
  }
  while( numTotalTasks != 0 ){
    int minCompTime = 1000000, minCompTimeJobIndex = 0, minCompTimeMachIndex = 0;
    for( int i = 0 ; i < M ; ++i ){
      int nextTaskPos_ = nextTaskPos[i];
      int taskMachId = taskSeq[i][nextTaskPos_][0];
      int earlStartTime, taskCompTime;
      if( nextTaskPos_ == numJobTasks[i] ) // the tasks in the ith job are all done
        continue;
        
      if( machReadyTime[taskMachId] < lastTaskCompTime[i] )
        earlStartTime = lastTaskCompTime[i];
      else
        earlStartTime = machReadyTime[taskMachId]; // can only do tasks when machine available
        
      taskCompTime = earlStartTime + taskSeq[i][nextTaskPos_][1];
      if( taskCompTime < minCompTime ){
        minCompTime = taskCompTime;      //schedule the task that has earliest completion time
        minCompTimeJobIndex = i;
        minCompTimeMachIndex = taskMachId;
      }
    }
    ++nextTaskPos[minCompTimeJobIndex];
    lastTaskCompTime[minCompTimeJobIndex] = minCompTime;
    machReadyTime[minCompTimeMachIndex] = minCompTime;
    --numTotalTasks;
  }
  for( int i = 0 ; i < M ; ++i )
    printf("%d\n", lastTaskCompTime[i]); // output the final completion time of each job
  return 0;
}

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


#define NUM_WAITING_CHAIRS 3


pthread_mutex_t mutex_thread;

sem_t sem_ta;
sem_t sem_students;


void * student_actions(void *);
void * ta_actions();

int isWaiting(int);


/* int num_students_waiting = 0 */
int num_students_waiting = 0;
int next_seating_position = 0;
int next_teaching_position = 0;
int ta_sleeping_flag = 0;


int waiting_room_chairs[3];


int main(int argc, char **argv) {
  srand((unsigned)time(NULL));
  pthread_t ta;
  pthread_t students[10];
  int student_id[10];
  int i;

  sem_init(&sem_students, 0, 0);
  sem_init(&sem_ta, 0, 1);
  

  
  pthread_mutex_init(&mutex_thread, NULL);

  
  pthread_create(&ta, NULL, ta_actions, NULL);

  
  for (i = 0; i < 10; i++) {
    student_id[i] = i + 1;
    pthread_create(&students[i], NULL, student_actions, (void *)&student_id[i]);
  }

  pthread_join(ta, NULL);
  
  for (i = 0; i < 10; i++)
    pthread_join(students[i], NULL);
  return 0;
}

void * student_actions(void * student_id) {
  int id_student = *(int *)student_id;
  while(1) {

    if (isWaiting(id_student) == 1) {continue;}
    int prog_time =rand() % 5;
    printf("\tStudent %d is programming for %d seconds.\n", id_student, prog_time);
      sleep(prog_time);
      pthread_mutex_lock(&mutex_thread);
      if (num_students_waiting < NUM_WAITING_CHAIRS) {
	waiting_room_chairs[next_seating_position] = id_student;
	num_students_waiting++;
	printf("\t\tStudent %d takes a seat. Student waiting = %d.\n", id_student, num_students_waiting);
	next_seating_position = (next_seating_position + 1) % NUM_WAITING_CHAIRS;
	pthread_mutex_unlock(&mutex_thread);
	sem_post(&sem_students);
	sem_wait(&sem_ta);
	
      }
      else {
	pthread_mutex_unlock(&mutex_thread);
	printf("\t\tStudent %d wil try later.\n", id_student);
      }
  }



  /* pthread_mutex_lock(&mutex_thread);
  sleep(1);
  printf("%d\n", id_student);
  pthread_mutex_unlock(&mutex_thread); */
  
};

void * ta_actions() {
  printf("Checking for students.\n");
  while(1) {
    if (num_students_waiting > 0) {
      ta_sleeping_flag = 0;
      sem_wait(&sem_students);
      pthread_mutex_lock(&mutex_thread);
      int help_time = rand() % 5;
      
      printf("Helping a student for %d seconds. Students waiting = %d.\n", help_time, (num_students_waiting - 1));
      printf("studnet %d receiveing help.\n", waiting_room_chairs[next_teaching_position]);
      waiting_room_chairs[next_teaching_position] = 0;
      num_students_waiting--;
      next_teaching_position = (next_teaching_position + 1) % NUM_WAITING_CHAIRS;
      sleep(help_time);
      pthread_mutex_unlock(&mutex_thread);
      sem_post(&sem_ta);
    }
    else {
      if (ta_sleeping_flag == 0) {
	printf("No students waiting. Sleeping.\n");
	ta_sleeping_flag = 1;
      }
    }
  }
}
  
int isWaiting(int student_id) {
  int i;
  for (i = 0; i < 3; i++)
    if (waiting_room_chairs[i] == student_id) {return i;}
  return 0;
}

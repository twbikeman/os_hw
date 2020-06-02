

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ReferenceLength 100

int pointer, hits, faults;


void print(int frame_size, int frame[]) {
  int i;
  for (i = 0; i < frame_size; i++) {
    if (frame[i] == -1)
      printf("- ");
    else
      printf("%d ", frame[i]);
  }

  printf("\n");
}



void add_reference(int frame_size, int frame[], int reference) {
  int i;
  bool alloted = false;
  for (i = 0; i < frame_size; i++) {
    if(frame[i] == reference) {
      alloted = true;
      printf("Hit for %d | ", reference);
      hits++;
      break;
    }
    else if (frame[i] == -1) {
      alloted = true;
      frame[i] = reference;
      printf("Fault for %d | ", reference);
      faults++;
      break;
    }
  }
  
  if (alloted == false) {
    faults++;
    printf("Fault for %d |", reference);
    frame[pointer] = reference;
    pointer = (pointer + 1) % frame_size;
   }
  print(frame_size, frame); 
}

void newReference(int reference[]) {
  int i;
  srand(time(NULL));
  for (i = 0; i < ReferenceLength; i++)
    reference[i] = rand() % 10;
}





int main() {
  int i, frame_size;
  printf("Enter frame size: ");
  scanf("%d", &frame_size);
  int frame[frame_size];
  for (i = 0; i < frame_size; i++)
    frame[i] = -1;

  print(frame_size, frame);

  int reference[ReferenceLength];
  newReference(reference);

  for (i = 0; i < ReferenceLength; i++) {
    add_reference(frame_size, frame,reference[i]);
  }

  printf("\nNumber of faults: %d \nNumber of hits: %d\n", faults, hits);

  
  return 0;
}

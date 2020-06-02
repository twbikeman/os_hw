/*
  Least Recently Used Page Replacement
*/

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

int predict(int reference_length, int reference[], int page_no, int frame_size, int frame[], int start);

void add_reference(int frame_size, int frame[], int reference, int current_position, int reference_length, int references[]) {
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
    int j = predict(reference_length, references, current_position, frame_size, frame, current_position + 1);
    frame[j] = reference;
   }
  print(frame_size, frame); 
}

void newReference(int reference[]) {
  int i;
  srand(time(NULL));
  for (i = 0; i < ReferenceLength; i++)
    reference[i] = rand() % 10;
}


int predict(int reference_length, int references[], int page_no, int frame_size, int frame[], int start) {

  int pos = -1, farthest = start, i;
  for (i = 0; i < frame_size; i++) {
    int j;
    for (j = start; j < reference_length; j++) {
      if (frame[i] == references[j]) {
	if (j > farthest) {
	  farthest = j;
	  pos = i;
	}
	break;
      }
    }
    if (j == page_no)
      return i;
    
  }
  if (pos == -1)
    return 0;
  else
    return pos;
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
    add_reference(frame_size, frame,reference[i], i, ReferenceLength, reference);
  }

  printf("\nNumber of faults: %d \nNumber of hits: %d\n", faults, hits);

  
  return 0;
}

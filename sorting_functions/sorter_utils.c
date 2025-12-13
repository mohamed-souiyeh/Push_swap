/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msouiyeh <msouiyeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:01:06 by msouiyeh          #+#    #+#             */
/*   Updated: 2022/03/12 23:02:41 by msouiyeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
#include "pqueue.h"
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

void just_print(char *holder) {
  write(1, holder, ft_strlen(holder));
  write(1, "\n", 1);
}

void ft_print(char *instruction) {
  static char *holder;
  int len;
  int comp;

  if (!holder) {
    holder = instruction;
    return;
  }
  comp = ft_strncmp(instruction, holder, 20);
  if ((instruction[comp] == 'a' && holder[comp] == 'b') ||
      (instruction[comp] == 'b' && holder[comp] == 'a')) {
    len = ft_strlen(instruction);
    while (len-- > 0 && *holder != 'p') {
      write(1, holder, 1);
      if (len == 0)
        write(1, "\n", 1);
    }
    instruction = NULL;
  } else
    just_print(holder);
  holder = instruction;
}

void sort3(int *stack) {
  if (stack[0] > 2) {
    if (stack[stack[0]] > stack[1] && stack[stack[0]] > stack[2])
      rotate(stack, 'a', true);
    else if (stack[2] > stack[1] && stack[2] > stack[stack[0]])
      reverse_rotate(stack, 'a', true);
  }
  if (stack[stack[0]] > stack[stack[0] - 1])
    swap(stack, NULL);
}

typedef struct s_Node {
  int instructionCount;
  char *instructions;
  int *stack_a;
  int *stack_b;
  int start;
  int s_start;
  int end;
  int s_end;
  int middle;
  int chunkSize;
} Node;

typedef struct s_HeapItem {
  pqueue_pri_t score;
  Node *data;
  size_t pos;
} HeapItem;

int *duplicate_stack(int *stack) {
  int *clone;
  int i;
  clone = ft_calloc(stack[0] + 1, sizeof(int));
  if (!clone)
    exit(1);

  i = 0;
  while (i <= stack[0]) {
    clone[i] = stack[i];
    i++;
  }

  return (clone);
}

char *duplicate_instructions(char *instructions, int instructions_size) {
  char *clone;
  int i;

  clone = ft_calloc(5000, sizeof(char));
  if (!clone)
    exit(1);

  i = 0;
  while (i < instructions_size) {
    clone[i] = instructions[i];
    i++;
  }

  return (clone);
}

#define RA 1
#define RB 2
#define RR 3
#define PB 4
#define TOP -1
#define BOTTOM 1
/*
static int cmp_pri(pqueue_pri_t next, pqueue_pri_t curr) {
  return (next < curr);
}

static pqueue_pri_t get_pri(void *a) { return ((HeapItem *)a)->score; }

static void set_pri(void *a, pqueue_pri_t pri) { ((HeapItem *)a)->score = pri; }

static size_t get_pos(void *a) { return ((HeapItem *)a)->pos; }

static void set_pos(void *a, size_t pos) { ((HeapItem *)a)->pos = pos; }
*/
/*
      push('b', data->stack_a, data->stack_b);
      if (data->stack_b[data->stack_b[0]] < data->sorted[data->midle]) {
        data->lower++;
        if (data->stack_b[0] > 1)
          rotate(data->stack_b, 'b');
      } else
        data->upper++;
 */

void change_values(t_struct *data) {
  static int lower = 0;
  static int upper = 0;

  ft_printf("lower: %d, upper: %d\n", data->lower, data->upper);
  ft_printf("start: %d, end: %d\n", data->start, data->end);
  if (data->lower == data->offset) {
    printf("we are updating the start, %d\n", lower++);
    if (data->start - data->offset < 0)
      data->start = 0;
    else
      data->start -= data->offset;
    data->lower = 0;
  }
  if (data->upper == data->offset) {
    printf("we are updating the end, %d\n", upper++);
    if (data->end + data->offset >= data->big_val_index)
      data->end = data->big_val_index + 1;
    else
      data->end += data->offset;
    data->upper = 0;
  }
}

// Node *initNode() {}

HeapItem *initHeapItem(Node *data, int score) {
  HeapItem *fresh;

  fresh = ft_calloc(1, sizeof(HeapItem));
  if (!fresh) {
    exit(1);
  }

  fresh->score = score;
  fresh->data = data;

  return (fresh);
}

typedef struct s_chunkBorders {
  int start;
  int end;

} ChunkBorders;

typedef struct s_alignedChunks {
  int *chunks;
  int chunkCount;
  ChunkBorders Borders[100];
} AChunks;

// i am not under any circumstances proud of this function, and yes i am writing
// this for myself more than for other putential reader.
AChunks *alignChunks(t_struct *data) {
  AChunks *final;
  int found[7000] = {0};

  final = ft_calloc(1, sizeof(AChunks));
  if (!final)
    exit(1);

  final->chunks = ft_calloc(data->totalToBeTransfered, sizeof(int));
  if (!final->chunks)
    exit(1);

  int i = 0;
  final->chunkCount = 0;
  for (int a = 0; a < data->totalToBeTransfered / (data->offset * 2); a++) {
    change_values(data);
    // printf("offset: %d, middle: %d\n", data->offset, data->midle);
    //    ft_printf("lower: %d, upper: %d\n", data->lower, data->upper);
    //   ft_printf("start: %d, end: %d\n", data->start, data->end);
    printf("extracting the chunk\n");
    int j = data->start;
    final->Borders[final->chunkCount].start = i;
    while (j < data->end) {
      // printf("hello %d\n", j);
      if (found[j] == 0) {
        if (data->sorted[j] < data->sorted[data->midle]) {
          data->lower++;
        } else
          data->upper++;
        final->chunks[i] = j;
        found[j] = 1;
        i++;
      }
      j++;
    }
    final->Borders[final->chunkCount].end = i;
    final->chunkCount++;
  }
  return (final);
}

void enumerateStacks(t_struct *data) {
  if (data->stack_a[0]) {
    for (int i = 1; i <= data->stack_a[0]; i++) {
      for (int j = 0; j < data->total; j++) {
        if (data->stack_a[i] == data->sorted[j]) {
          data->stack_a[i] = j;
          break;
        }
      }
    }
  }
  if (data->stack_b[0]) {
    for (int i = 1; i <= data->stack_b[0]; i++) {
      for (int j = 0; j < data->total; j++) {
        if (data->stack_b[i] == data->sorted[j]) {
          data->stack_b[i] = j;
          break;
        }
      }
    }
  }
}

void dump_a_to_b(t_struct *data) {
  // pqueue_t *pq;
  // HeapItem *genesis_node;
  // HeapItem *tmp;

  AChunks *alignedChunks = alignChunks(data);
  int i;

  // replace the values in the stack with there indexes from the sorted array (i
  // call it enumerateStack)
  enumerateStacks(data);

  printf("size of stack_a: %d\n", data->stack_a[0]);
  for (int a = 4; a <= data->stack_a[0]; a++) {
    printf("idx in stack_a: %d - idx in sorted: %d\n", a, data->stack_a[a]);
    printf("value in sorted: %d\n", data->sorted[data->stack_a[a]]);
  }

  i = 0;
  while (i < alignedChunks->chunkCount) {
    // prepare the current stack state for the beam search
    //
    // pass the heap node, and chunk info to the beam search engine
    //
    // run the beam search and get the best way to pass the current chunk
    //
    // apply the chunk moves to the actual stack

    i++;
  }

  // revese the enumeration so the next stage of sorting is not affected by this
  // stage changes to the stack.

  ft_printf("printing aligned chunks\n");
  for (int i = 0; i < alignedChunks->chunkCount; i++) {
    printf("chunk index: %d\n", i);
    for (int j = alignedChunks->Borders[i].start;
         j < alignedChunks->Borders[i].end; j++) {
      printf("=> idx: %d - %d\n", j, alignedChunks->chunks[j]);
    }
  }
}

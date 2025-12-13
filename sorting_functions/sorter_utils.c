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

typedef struct s_chunkBorders {
  int start;
  int end;
  int size;
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
    final->Borders[final->chunkCount].size =
        i - final->Borders[final->chunkCount].start;
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

#define RA 1
#define RB 2
#define RR 3
#define PB 4
#define TOP -1
#define BOTTOM 1

typedef struct s_Node {
  int instructionsCount;     // this is the real cost for the current state
  char instructions[100000]; // this prototype is getting very dirty
  int *stack_a; // stack containing the indexes of values from the sorted array
                // instead of the actual values
  int *stack_b; // same for this one

  int chunkSize;
  int chunkv[500]; // the chunk values which are indexes in the sorted array
  int foundChunkTargets[500]; // i know this could go very wrong if i am not
                              // carefull, but we are prototyping now so it's
                              // okay to play a bit dirty
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

  clone = ft_calloc(instructions_size, sizeof(char));
  if (!clone)
    exit(1);

  i = 0;
  while (i < instructions_size) {
    clone[i] = instructions[i];
    i++;
  }

  return (clone);
}

Node *initNode(int *stack_a, int *stack_b) {

  Node *fresh;

  fresh = ft_calloc(1, sizeof(Node));
  if (!fresh) {
    exit(1);
  }

  fresh->instructionsCount = 0;
  memset(fresh->instructions, 0, sizeof(fresh->instructions));
  fresh->stack_a = duplicate_stack(stack_a);
  fresh->stack_b = duplicate_stack(stack_b);
  fresh->chunkSize = 0;
  memset(fresh->chunkv, 0, sizeof(fresh->chunkv));
  memset(fresh->foundChunkTargets, 0, sizeof(fresh->foundChunkTargets));

  return (fresh);
}

Node *duplicateNode(Node *node) {
  Node *clone;

  clone = ft_calloc(1, sizeof(Node));
  if (!clone) {
    exit(1);
  }

  clone->instructionsCount = node->instructionsCount;
  memcpy(node->instructions, clone->instructions, node->instructionsCount);
  clone->stack_a = duplicate_stack(node->stack_a);
  clone->stack_b = duplicate_stack(node->stack_b);
  clone->chunkSize = node->chunkSize;
  memcpy(node->chunkv, clone->chunkv, sizeof(node->chunkv));
  memcpy(node->foundChunkTargets, clone->foundChunkTargets,
         sizeof(node->foundChunkTargets));

  return (clone);
}

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

static int cmp_pri(pqueue_pri_t next, pqueue_pri_t curr) {
  return (next < curr);
}

static pqueue_pri_t get_pri(void *a) { return ((HeapItem *)a)->score; }

static void set_pri(void *a, pqueue_pri_t pri) { ((HeapItem *)a)->score = pri; }

static size_t get_pos(void *a) { return ((HeapItem *)a)->pos; }

static void set_pos(void *a, size_t pos) { ((HeapItem *)a)->pos = pos; }

#define BEAMWIDTH 42

Node *beamSearch(Node *initialNode, int chunkSize) {

  pqueue_t *currentGenration;
  pqueue_t *candidates;
  HeapItem *genesis_node;
  HeapItem *parent;
  Node *parentData;
  Node *bestNode;
  int i;
  int j;

  currentGenration =
      pqueue_init(BEAMWIDTH, cmp_pri, get_pri, set_pri, get_pos, set_pos);
  genesis_node = initHeapItem(initialNode, 0);
  pqueue_insert(currentGenration, genesis_node);

  i = 0;
  while (i < chunkSize) {
    candidates = pqueue_init(chunkSize * chunkSize, cmp_pri, get_pri, set_pri,
                             get_pos, set_pos);
    while (pqueue_size(currentGenration)) {

      parent = pqueue_pop(currentGenration);
      parentData = parent->data;

      // creating a time line for grabing each remaining chunk target as the
      // first one from the current state (any order expantion of the timeline)
      j = 0;
      while (j < chunkSize) {
        if (parentData->foundChunkTargets[parentData->chunkv[j]] == 1)
          continue;
      }
    }

    // transfer the best BEAMWIDTH candidates to the current generation

    // dont forget to empty the candidates heap and free the items that didnt
    // transfer to the current generatio heap
    i++;
  }

  return (bestNode);
}

void dump_a_to_b(t_struct *data) {
  // pqueue_t *pq;
  // HeapItem *genesis_node;
  // HeapItem *tmp;

  AChunks *alignedChunks = alignChunks(data);
  Node *initialNode;
  Node *bestNode;
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
    initialNode = initNode(data->stack_a, data->stack_b);

    initialNode->chunkSize = alignedChunks->Borders[i].size;
    for (int s = alignedChunks->Borders[i].start, idx = 0;
         s < alignedChunks->Borders[i].end; s++, idx++) {
      initialNode->chunkv[idx] = alignedChunks->chunks[s];
    }
    /*
        printf("--------------------------------------------\n");
        printf("node nbr: %d\n", i);
        printf("node chunk size: %d\n", initialNode->chunkSize);
        printf("printing chunkv\n");
        for (int idx = 0; idx < initialNode->chunkSize; idx++) {
          printf("idx: %d, value: %d\n", idx, initialNode->chunkv[idx]);
        }
        printf("--------------------------------------------\n");
    */

    // pass the heap node, and chunk info to the beam search engine
    // run the beam search and get the best way to pass the current chunk
    bestNode = beamSearch(initialNode, alignedChunks->Borders[i].size);

    // apply the chunk moves to the actual stack

    free(initialNode->stack_a);
    free(initialNode->stack_b);
    free(initialNode);
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

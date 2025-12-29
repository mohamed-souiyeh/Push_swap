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
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
  // static int lower = 0;
  // static int upper = 0;

  // ft_printf("lower: %d, upper: %d\n", data->lower, data->upper);
  // ft_printf("start: %d, end: %d\n", data->start, data->end);
  if (data->lower == data->offset) {
    // printf("we are updating the start, %d\n", lower++);
    if (data->start - data->offset < 0)
      data->start = 0;
    else
      data->start -= data->offset;
    data->lower = 0;
  }
  if (data->upper == data->offset) {
    // printf("we are updating the end, %d\n", upper++);
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
  // printf("totalToBeTransfered: %d - offset: %d\n", data->totalToBeTransfered,
  //       data->offset);
  int totalChunkCount =
      ceil((double)(data->totalToBeTransfered) / (double)(data->offset * 2));
  // printf("totalChunkCount: %d\n", totalChunkCount);
  for (int a = 0; a < totalChunkCount; a++) {
    change_values(data);
    // printf("offset: %d, middle: %d\n", data->offset, data->midle);
    //    ft_printf("lower: %d, upper: %d\n", data->lower, data->upper);
    //   ft_printf("start: %d, end: %d\n", data->start, data->end);
    // printf("extracting the chunk\n");
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

void unEnumerateStacks(t_struct *data) {
  if (data->stack_a[0]) {
    for (int i = 1; i <= data->stack_a[0]; i++) {
      data->stack_a[i] = data->sorted[data->stack_a[i]];
    }
  }
  if (data->stack_b[0]) {
    for (int i = 1; i <= data->stack_b[0]; i++) {
      data->stack_b[i] = data->sorted[data->stack_b[i]];
    }
  }
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

#define RA 0
#define RB 1
#define RR 2
#define PB 3
#define RRA 4
#define TOP -1
#define BOTTOM 1

typedef struct s_Node {
  int instructionsCount;     // this is the real cost for the current state
  char instructions[100000]; // this prototype is getting very dirty
  int *stack_a; // stack containing the indexes of values from the sorted array
                // instead of the actual values
  int *stack_b; // same for this one
  int middle;
  int total;

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

int *duplicate_stack(int *stack, int total) {
  int *clone;
  int i;
  clone = ft_calloc(total + 1, sizeof(int));
  if (!clone)
    exit(1);

  i = 0;
  while (i < total + 1) {
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

Node *initNode(int *stack_a, int *stack_b, int middle, int total) {

  Node *fresh;

  fresh = ft_calloc(1, sizeof(Node));
  if (!fresh) {
    exit(1);
  }

  fresh->instructionsCount = 0;
  memset(fresh->instructions, 0, sizeof(fresh->instructions));
  fresh->stack_a = duplicate_stack(stack_a, total);
  fresh->stack_b = duplicate_stack(stack_b, total);
  fresh->middle = middle;
  fresh->total = total;
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
  memcpy(clone->instructions, node->instructions, node->instructionsCount);
  clone->stack_a = duplicate_stack(node->stack_a, node->total);
  clone->stack_b = duplicate_stack(node->stack_b, node->total);
  clone->middle = node->middle;
  clone->total = node->total;
  clone->chunkSize = node->chunkSize;
  memcpy(clone->chunkv, node->chunkv, sizeof(node->chunkv));
  memcpy(clone->foundChunkTargets, node->foundChunkTargets,
         sizeof(node->foundChunkTargets));

  return (clone);
}

void freeNode(Node *node) {
  free(node->stack_a);
  free(node->stack_b);
  free(node);
}

HeapItem *initHeapItem(Node *data, pqueue_pri_t score) {
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
  return (next >= curr);
}

static pqueue_pri_t get_pri(void *a) { return ((HeapItem *)a)->score; }

static void set_pri(void *a, pqueue_pri_t pri) { ((HeapItem *)a)->score = pri; }

static size_t get_pos(void *a) { return ((HeapItem *)a)->pos; }

static void set_pos(void *a, size_t pos) { ((HeapItem *)a)->pos = pos; }

#define BEAMWIDTH 35
#define FWD true
#define REV false
int getTargetIdx(Node *candidateData, int target) {

  for (int i = 1; i <= candidateData->stack_a[0]; i++) {
    if (candidateData->stack_a[i] == target)
      return (i);
  }

  return (-1);
}

void moveTargetAndSaveMoves(Node *candidateData, int target,
                            int targetStackIdx) {
  int fwd =
      candidateData->stack_a[0] - targetStackIdx; // forward rotation distance
  int rev = targetStackIdx;                       // reverse rotation distance
  bool direction = rev < fwd ? false : true;

  while (candidateData->stack_a[candidateData->stack_a[0]] != target) {
    if (direction == FWD) {
      rotate(candidateData->stack_a, 'a', false);
      if (candidateData->instructions[candidateData->instructionsCount - 1] ==
          RB) {
        candidateData->instructions[candidateData->instructionsCount - 1] = RR;
      } else {
        candidateData->instructions[candidateData->instructionsCount] = RA;
        candidateData->instructionsCount++;
      }
    } else if (direction == REV) {
      reverse_rotate(candidateData->stack_a, 'a', false);
      candidateData->instructions[candidateData->instructionsCount] = RRA;
      candidateData->instructionsCount++;
    }
  }

  push('b', candidateData->stack_a, candidateData->stack_b, false);
  candidateData->instructions[candidateData->instructionsCount] = PB;
  candidateData->instructionsCount++;

  if (target < candidateData->middle) {
    rotate(candidateData->stack_b, 'b', false);
    candidateData->instructions[candidateData->instructionsCount] = RB;
    candidateData->instructionsCount++;
  }
}

double runHeuristic(Node *candidateData, int *missing, int missingCount) {
  double hScore = 0;
  int cachedRawIdx[1000] = {0};

  for (int i = 1; i < candidateData->stack_a[0]; i++) {
    cachedRawIdx[candidateData->stack_a[i]] = i - 1;
  }

  int found[1000] = {0};

  int simHead = candidateData->stack_a[0];
  int stackSize = candidateData->stack_a[0];

  for (int i = 0; i < missingCount; i++) {
    int bestDist = INT_MAX;
    int bestIdx = -1;
    int bestVal = 0;

    for (int j = 0; j < missingCount; j++) {
      if (found[missing[j]])
        continue;

      int val = missing[j];
      int targetIdx = cachedRawIdx[val];

      int fwdDist = (simHead - targetIdx + stackSize) % stackSize;

      int revDist = (targetIdx - simHead + stackSize) % stackSize;

      int dist = fwdDist < revDist ? fwdDist : revDist;

      if (dist < bestDist) {
        bestDist = dist;
        bestIdx = targetIdx;
        bestVal = val;
      }
    }

    hScore += bestDist;

    simHead = bestIdx;
    found[bestVal] = 1;
  }

  return (hScore / missingCount);
}

Node *beamSearch(Node *initialNode, int chunkSize) {

  pqueue_t *currentGenration;
  pqueue_t *candidates;
  HeapItem *genesisNode;
  HeapItem *candidateNode;
  HeapItem *parent;
  HeapItem *bestNode = NULL; // check if this initializations is appropriate
                             // -----------------------------------------
  Node *bestData;
  Node *parentData;
  Node *candidateData;
  int target;
  int targetStackIdx;

  currentGenration =
      pqueue_init(BEAMWIDTH, cmp_pri, get_pri, set_pri, get_pos, set_pos);
  candidates = pqueue_init(chunkSize * chunkSize, cmp_pri, get_pri, set_pri,
                           get_pos, set_pos);
  genesisNode = initHeapItem(initialNode, 0);
  pqueue_insert(currentGenration, genesisNode);

  for (int i = 0; i < chunkSize; i++) {
    // exploring each timeline possible candidate timelines (feels like the
    // knock off version of Dr Strange simulating how to beat thanos)
    while (pqueue_size(currentGenration)) {

      // printf("current generation loop in beam search\n");
      parent = pqueue_pop(currentGenration);
      parentData = parent->data;

      // creating a time line for grabing each remaining chunk target as the
      // first one from the current state (any order expantion of the timeline)
      for (int j = 0; j < chunkSize; j++) {
        // printf("any order loop in beam search\n");
        if (parentData->foundChunkTargets[parentData->chunkv[j]] == 1) {
          // printf("we are skiping %d because it is found\n",
          //      parentData->chunkv[j]);
          continue;
        }
        target = parentData->chunkv[j];

        // create the candidate as a copy of the current parent
        candidateData = duplicateNode(parentData);

        // mark the target as found
        candidateData->foundChunkTargets[target] = 1;

        // find the current chunk target in stack_a
        targetStackIdx = getTargetIdx(candidateData, target);

        if (targetStackIdx == -1) {
          printf("buddy shit hit the fan with getTargetIdx in beamSearch "
                 "function");
          exit(1);
        }
        /*
                printf("current target is: %d\n", target);
                printf("current target idx: %d\n", targetStackIdx);
                printf("current cost: %d\n", candidateData->instructionsCount);
                printf("----------printing stack_a before--------------\n");
                for (int k = 1; k <= candidateData->stack_a[0]; k++) {
                  printf("idx: %d, value: %d\n", k, candidateData->stack_a[k]);
                }
                printf("done printing before moving target\n");
        */

        moveTargetAndSaveMoves(candidateData, target, targetStackIdx);

        /*
                printf("current cost: %d\n", candidateData->instructionsCount);
                printf("----------printing stack_a after--------------\n");
                for (int k = 1; k <= candidateData->stack_a[0]; k++) {
                  printf("idx: %d, value: %d\n", k, candidateData->stack_a);
                }
                printf("done printing after moving target\n");
        */

        // find the missing targets in the current chunk to run the heuristic on
        // them.
        int missing[1000] = {0};
        int missingCount = 0;
        for (int k = 0; k < chunkSize; k++) {
          if (!(candidateData->foundChunkTargets[candidateData->chunkv[k]] ==
                1)) {
            missing[missingCount] = candidateData->chunkv[k];
            missingCount++;
          }
        }

        double hScore;
        if (missingCount > 0) {
          hScore = runHeuristic(candidateData, missing, missingCount);
        }

        // the evaluation function score to rank timelines
        double fScore;

        fScore = (double)(candidateData->instructionsCount) + hScore;

        candidateNode = initHeapItem(candidateData, fScore);

        pqueue_insert(candidates, candidateNode);
        // printf("a new timeline is created\n");
      }
    }

    // printf("before transfer candidate size: %ld\n", pqueue_size(candidates));
    // printf("before transfer currentGeneration size: %ld\n",
    //        pqueue_size(currentGenration));

    // transfer the best BEAMWIDTH candidates to the current generation
    for (int w = 0; w < BEAMWIDTH; w++) {
      HeapItem *tmp = pqueue_pop(candidates);
      if (tmp) {
        pqueue_insert(currentGenration, tmp);
      }
    }

    // printf("currentGeneration size: %ld\n", pqueue_size(currentGenration));

    // dont forget to empty the candidates heap and free the items that didnt
    // transfer to the current generatio heap
    while (pqueue_size(candidates)) {
      HeapItem *tmp = pqueue_pop(candidates);

      freeNode(tmp->data);
      free(tmp);
    }
  }

  // printf("before extracting best node currentGeneration size: %ld\n",
  //        pqueue_size(currentGenration));
  //  extract the best chunk extraction route
  bestNode = pqueue_pop(currentGenration);

  // dont forget to empty the currentGeneration heap and free everything in it
  while (pqueue_size(currentGenration)) {
    HeapItem *tmp = pqueue_pop(currentGenration);
    freeNode(tmp->data);
    free(tmp);
  }

  bestData = bestNode->data;
  free(bestNode);
  // printf("best node stack_a address %p\n", bestData->stack_a);
  return (bestData);
}

void dump_a_to_b(t_struct *data) {
  // pqueue_t *pq;
  // HeapItem *genesis_node;
  // HeapItem *tmp;

  AChunks *alignedChunks = alignChunks(data);
  Node *initialNode;
  Node *bestNode;
  int i;

  /*
  ft_printf("printing aligned chunks\n");
  for (int i = 0; i < alignedChunks->chunkCount; i++) {
    printf("chunk index: %d\n", i);
    for (int j = alignedChunks->Borders[i].start;
         j < alignedChunks->Borders[i].end; j++) {
      printf("=> idx: %d - %d\n", j, alignedChunks->chunks[j]);
    }
  }
*/
  // replace the values in the stack with there indexes from the sorted array (i
  // call it enumerateStack)
  enumerateStacks(data);
  /*
    printf("size of stack_a: %d\n", data->stack_a[0]);
    for (int a = 4; a <= data->stack_a[0]; a++) {
      printf("idx in stack_a: %d - idx in sorted: %d\n", a, data->stack_a[a]);
      printf("value in sorted: %d\n", data->sorted[data->stack_a[a]]);
    }
  */

  i = 0;
  while (i < alignedChunks->chunkCount) {
    // prepare the current stack state for the beam search
    initialNode =
        initNode(data->stack_a, data->stack_b, data->midle, data->total);

    initialNode->chunkSize = alignedChunks->Borders[i].size;
    for (int s = alignedChunks->Borders[i].start, idx = 0;
         s < alignedChunks->Borders[i].end; s++, idx++) {
      initialNode->chunkv[idx] = alignedChunks->chunks[s];
    }
    // printf("simulating chunk nbr: %d\n", i);
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

    // printf("best node adress after beam search: %p\n", bestNode);

    // apply the chunk moves to the actual stack
    free(data->stack_a);
    data->stack_a = bestNode->stack_a;
    free(data->stack_b);
    data->stack_b = bestNode->stack_b;

    char instructions[][6] = {"ra", "rb", "rr", "pb", "rra"};

    for (int inst = 0; inst < bestNode->instructionsCount; inst++) {
      int move = bestNode->instructions[inst];
      ft_print(strdup(instructions[move]));
    }

    freeNode(initialNode);
    i++;
  }

  // revese the enumeration so the next stage of sorting is not affected by this
  // stage changes to the stack.
  unEnumerateStacks(data);
}

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
#include <stdbool.h>
#include <stddef.h>
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

typedef struct s_node {
  pqueue_pri_t instructions_size;
  char *instructions;
  size_t pos;
  int *stack_a;
  int *stack_b;
  int start;
  int end;
  int middle;
  int lower;
  int upper;
} t_node;

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

char *duplicate_instructions(char *instructions,
                             pqueue_pri_t instructions_size) {
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

t_node *init_node(int *stack_a, int *stack_b, int start, int end, int lower,
                  int upper, int middle, pqueue_pri_t instructions_size,
                  char *instructions) {
  t_node *node;

  node = ft_calloc(1, sizeof(t_node));
  if (!node)
    exit(1);
  node->instructions_size = instructions_size;
  node->instructions = duplicate_instructions(instructions, instructions_size);
  node->pos = 0;
  node->stack_a = duplicate_stack(stack_a);
  node->stack_b = duplicate_stack(stack_b);
  node->middle = middle;
  node->start = start;
  node->end = end;
  node->lower = lower;
  node->upper = upper;

  return (node);
}

static int cmp_pri(pqueue_pri_t next, pqueue_pri_t curr) {
  return (next <= curr);
}

static pqueue_pri_t get_pri(void *a) {
  return ((t_node *)a)->instructions_size;
}

static void set_pri(void *a, pqueue_pri_t pri) {
  ((t_node *)a)->instructions_size = pri;
}

static size_t get_pos(void *a) { return ((t_node *)a)->pos; }

static void set_pos(void *a, size_t pos) { ((t_node *)a)->pos = pos; }

int get_near_dist(t_node *curr_state, t_struct *data, int direction) {
  int index;
  int control;
  int dist;

  if (direction == TOP) {
    index = curr_state->stack_a[0];
    control = 0;
  }
  if (direction == BOTTOM) {
    index = 1;
    control = curr_state->stack_a[0];
  }

  dist = 0;
  while (index < control) {

    if (curr_state->stack_a[index] >= data->sorted[curr_state->start] &&
        curr_state->stack_a[index] <= data->sorted[curr_state->end - 1]) {
      return (dist);
    }
    index += direction;
    dist++;
  }

  return (-1000);
}
/*
      push('b', data->stack_a, data->stack_b);
      if (data->stack_b[data->stack_b[0]] < data->sorted[data->midle]) {
        data->lower++;
        if (data->stack_b[0] > 1)
          rotate(data->stack_b, 'b');
      } else
        data->upper++;
 */
void execute_instructions(t_node *node, int dest, int direction) {
  // execute and insert the instructions RA or RRA into the instructions array
  // push then maybe rotate insert them into the instructions array
  int i;

  i = 0;
  if (direction == TOP) {
    while (dest) {
      rotate(node->stack_a, 'a', false);
      node->instructions[i] = RA;
      i++;
      dest--;
    }
    push('b', node->stack_a, node->stack_b, false);
    node->instructions[i] = PB;
  } else if (direction == BOTTOM) {
  }
}

char *simulate(t_struct *data) {
  pqueue_t *pq;
  t_node *genesis_node;
  t_node *tmp;
  int near_dist;

  pq = pqueue_init(100, cmp_pri, get_pri, set_pri, get_pos, set_pos);

  genesis_node = init_node(data->stack_a, data->stack_b, data->start, data->end,
                           data->midle, data->lower, data->upper, 0, NULL);

  pqueue_insert(pq, genesis_node);

  while (/*something*/ 1) {
    // peek in the first node
    tmp = pqueue_peek(pq);

    // get the index of the element near the top of the stack a
    near_dist = get_near_dist(tmp, data, TOP);

    if (near_dist == -1000) {
      ft_printf(
          "FUUUUUUUUUUCK shit gone very south in the get near index funciton "
          "in the simulation, u may have some fun with this one ma guy\n");
      exit(1);
    }

    // create a node for the new top state
    genesis_node = init_node(tmp->stack_a, tmp->stack_b, tmp->start, tmp->end,
                             tmp->lower, tmp->middle, tmp->upper,
                             tmp->instructions_size, tmp->instructions);

    // get the element to the top and push it to stack b and maybe rotate it too
    execute_instructions(genesis_node, near_dist, TOP);

    // and save those instructuions insert in the queue
    // get the index of the element near the bottom of the stack a
    // create a node for the new bottom state
    // get the element to the top and push it to stack b and maybe rotate
    // save those instructions insert in the queue
  }
}

void change_values(t_struct *data) {

  /*
        if (data->lower == data->offset)
        {
                if (data->start - data->offset < 0)
                        data->start = 0;
                else
                        data->start -= data->offset;
                data->lower = 0;
        }
        else if (data->upper == data->offset)
        {
                if (data->end + data->offset >= data->big_val_index)
                        data->end = data->big_val_index + 1;
                else
                        data->end += data->offset;
                data->upper = 0;
        }
  */
}

void dump_a_to_b(t_struct *data) {
  char *instructions;

  instructions = simulate(data);
  while (data->stack_a[0] > 3) {
    /*
    change_values(data);
    if (data->stack_a[data->stack_a[0]] >= data->sorted[data->start] &&
        data->stack_a[data->stack_a[0]] <= data->sorted[data->end - 1]) {
      push('b', data->stack_a, data->stack_b);
      if (data->stack_b[data->stack_b[0]] < data->sorted[data->midle]) {
        data->lower++;
        if (data->stack_b[0] > 1)
          rotate(data->stack_b, 'b');
      } else
        data->upper++;
    } else
      rotate(data->stack_a, 'a');
    */
  }
}

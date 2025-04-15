#include "queue.h"
#include "tile_game.h"

#include <stdlib.h>

int check_prev(struct game_state current_state, struct queue * q)
{
    struct list_node * qu = q -> data.head;
    size_t cur = serialize(current_state);
    while(qu != NULL)
    {
        if(qu -> value == cur)
        {
            return 1;
        }
        qu = qu -> next;
    }
    return 0;
}

void enqueue(struct queue *q, struct game_state state) 
{
    // Serialize it then insert at head or tail
    uint64_t current_state = serialize(state);
    insert_at_head(&q -> data, current_state);
}

struct game_state dequeue(struct queue *q) 
{
    // Deserialize it then remove head or tail
    struct game_state state;
    size_t rem = remove_from_tail(&(q -> data));
    state = deserialize(rem);
    return (state);
}

int number_of_moves(struct game_state start) 
{
    struct queue q = {.data.head = NULL};
    struct game_state current_state = start;
    current_state.num_steps = 0;
    enqueue(&q, start);

    while(q.data.head != NULL)
    {
        current_state = dequeue(&q);
        if(current_state.empty_row < 3)
        {
            struct game_state cop = current_state;
            move_up(&cop);

            if(check_prev(cop, &q) == 0)
            {
                enqueue(&q, cop);
            }
        }
        if(current_state.empty_row > 0)
        {
            struct game_state cop = current_state;
            move_down(&cop);

            if(check_prev(cop, &q) == 0)
            {
                enqueue(&q, cop);
            }
        }
        if(current_state.empty_col < 3)
        {
            struct game_state cop = current_state;
            move_left(&cop);
            
            if(check_prev(cop, &q) == 0)
            {
                enqueue(&q, cop);
            }
        }
        if(current_state.empty_col > 0)
        {
            struct game_state cop = current_state;
            move_right(&cop);

            if(check_prev(cop, &q) == 0)
            {
                enqueue(&q, cop);
            }
        }

        if(current_state.empty_row == 3 && current_state.empty_col == 3)
        {
            int value = 1;
            int num_correct = 0;
            for(int rows = 0; rows < 4; rows++)
            {
                for(int cols = 0; cols < 4; cols++)
                {
                    if(current_state.tiles[rows][cols] == value)
                    {
                        num_correct++;
                    }
                    value++;
                }
            }
            if(num_correct == 15)
            {
                free_list(q.data);
                return current_state.num_steps;
            }
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 22
#define HASH_SIZE 10

typedef struct HASH_TABLE_s *HASH_TABLE;
typedef struct HASH_TABLE_s{
    int key;
    int flag;
    void *value;
} HASH_TABLE_t[1];

typedef struct LINKED_LIST_NODE_s *LINKED_LIST_NODE;
typedef struct LINKED_LIST_NODE_s {
    LINKED_LIST_NODE next;
    void *data;
} LINKED_LIST_NODE_t[1];

typedef struct LINKED_LIST_s {
    LINKED_LIST_NODE head;
} LINKED_LIST_t[1], *LINKED_LIST;

LINKED_LIST linked_list_init() {
    LINKED_LIST new;
    new = (LINKED_LIST) malloc(sizeof(LINKED_LIST_t));
    if (new != NULL) {
        new->head = NULL;
    } else {
        printf("Error @ linked_stack_init: Memory allocation.");
    }
    return new;
}

void linked_list_append(LINKED_LIST list, void *data) {
    LINKED_LIST_NODE node = (LINKED_LIST_NODE)list;
    while (node->next != NULL) {
        node = node->next;
    }
    node->next = malloc(sizeof(LINKED_LIST_NODE_t));
    node->next->data = data;
    node->next->next = NULL;
}

void linked_list_print(LINKED_LIST list) {
    LINKED_LIST_NODE node = list->head;
    while (node != NULL) {
        printf("%d ", *(int *)node->data);
        node = node->next;
    }
}

int hash(int key){ // The hash function
    return ((key*key*key) + (2*key*key)) % HASH_SIZE; // (n^3 + 2*n^2) mod 10
}

HASH_TABLE init_hashtable(){
    HASH_TABLE hashtable = malloc(HASH_SIZE*sizeof(HASH_TABLE_t));
    for (int i = 0; i < HASH_SIZE; ++i) {
        hashtable[i].key=0;
        hashtable[i].value=NULL;
        hashtable[i].flag=0;
    }
    return hashtable;
}

void put(HASH_TABLE h1,int key,void* value){

    int index=hash(key);
    if(h1[index].value==NULL){
        h1[index].value= value;
    }
    else
    {
        if(h1[index].flag==0){
            LINKED_LIST list = linked_list_init();
            linked_list_append(list,h1[index].value);
            linked_list_append(list,value);
            h1[index].value=list;
            h1[index].flag=1;
        }else{
            LINKED_LIST newlist=h1[index].value;
            linked_list_append(newlist,value);
            h1[index].value=newlist;

        }
    }
}

int main(void) {

    HASH_TABLE hashtable = init_hashtable();

    int keyArr[ARR_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 };
    int valArr[ARR_SIZE] = { 3, 12, 18, 22, 23, 33, 38, 45, 73, 82, 97, 98, 99, 100, 78, 11, 1, 77, 90, 25, 70, 66 };

    /* Put values to your hashtable and solve collisions with linked lists */

    for (int i = 0; i < ARR_SIZE; ++i) {
        put(hashtable, keyArr[i], &valArr[i]);
    }

    for (int i = 0; i < HASH_SIZE; ++i) {
        if(hashtable[i].value != NULL)
        {
            if (hashtable[i].flag == 1) {
                linked_list_print(hashtable[i].value);
                printf("\n");
            } else
            {
                printf("%d", *(int*)hashtable[i].value);
            }
        }
    }


}

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

struct node_s {
    char *key;
    char *value;
    struct node_s *next;
};

typedef struct node_s node;

struct hashtable_s {
    int size;
    node **table;
};

typedef struct hashtable_s hashtable_t;

/* create hashtable. returns a hashtable that has a null bin for
 * each integer in range 0-size */
hashtable_t *ht_create(int size) {
    hashtable_t *hashtable;

    /* Allocate pointers to the head nodes. */
    hashtable->table = malloc(sizeof(node*) * size);

    for (int i=0; i<size; i++) {
        hashtable->table[i] = NULL;
    }

    return hashtable;
}

/* hash function to return an integer that ranges from 0 to size of hashtable */
int hash(hashtable_t *hashtable, char *key) {
    unsigned long int hashval;
    int i = 0;

    /* Convert string to an integer */
    while(hashval < ULONG_MAX && i < strlen(key)) {
        hashval = hashval << 8;
        hashval += key[i];
        i++;
    }

    return hashval % hashtable->size;
}

/* insert key-value pair into your hashtable */
void ht_set(hashtable_t *hashtable, char *key, char *value) {
    int bin;
    node *next;
    node *last;
    node *newpair;

    bin = hash(hashtable, key);

    next = hashtable->table[bin];

    while (next != NULL && next->key != NULL && strcmp(key, next->key) != 0) {
         /* either it ends on last node, or ends on same key */
        last = next;
        next = next->next;
    }

    /* there's already key, replace value with passed value */
    if (next != NULL && next->key != NULL && key == next->key) {
        free(next->value);
        next->value = strdup(value); /* why duplicate? */
    /* key is new and unique. create new key/value pair to add to linked list */
    } else {
        newpair->key = key;
        newpair->value = value;
        newpair->next = NULL;
        
        /* starting linked list in this bin */
        if (next == hashtable->table[bin]) {
            newpair->next = next;
            hashtable->table[bin] = newpair;
        /* at end of linked list */
        } else if (next == NULL) {
            last->next = newpair;
        /* in middle of linked list.. when would this happen? */
        } else {
            newpair->next = next;
            last->next = newpair;
        }
    }
}

/* get value by key */
char *ht_get(hashtable_t *hashtable, char *key) {
    int bin;
    node *pair;

    bin = hash(hashtable, key);

    pair = hashtable->table[bin];

    while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) != 0) {
        pair = pair->next;
    }

    if (pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0) {
        return NULL;
    } else {
        /* found key! */
        return pair->value;
    }
}

int main() {
    hashtable_t *hashtable = ht_create(65536);

    ht_set(hashtable, "triple jump", "field");
    ht_set(hashtable, "long jump", "field");
    ht_set(hashtable, "4x100", "track");
    ht_set(hashtable, "200m", "track");

    printf( "%s\n", ht_get(hashtable, "triple jump"));
    printf( "%s\n", ht_get(hashtable, "200m"));
    printf( "%s\n", ht_get(hashtable, "javelin"));

    return 0;
}

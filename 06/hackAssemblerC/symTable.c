#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "symTable.h"

SymTable *new_symTable () { 
    SymTable *t = (SymTable *) malloc(sizeof(SymTable));

    for (int i = 0; i < 256; i++) { 
        t->entries[i] = NULL;
    }

    return t;
}

void add_entry (SymTable *t, char *k, int v) { 
    int index = hash(k);
    SymTableEntry *e = new_entry(k, v);
    
    if (t->entries[index] == NULL) { 
        t->entries[index] = e;
        return;
    }

    SymTableEntry *p = t->entries[index];
    while (p->next != NULL) { 
        p = p->next;
    }

    p->next = e;
}

int get_value (SymTable *t, char *k) { 
    int index = hash(k);

    if (t->entries[index] == NULL) { 
        perror("Symbol table entry does not exist");
        exit(1);
    }

    SymTableEntry *p = t->entries[index];
    while (strcmp(p->key, k) != 0) {
        if (p->next == NULL) { 
            break;
        }

        p = p->next;
    }

    if (strcmp(p->key, k) != 0) { 
        perror("Symbol table entry does not exist");
        exit(1);
    }

    return p->value;
}

static SymTableEntry *new_entry (char *k, int v) { 
    SymTableEntry *e = malloc(sizeof(SymTableEntry));
    e->key = k;
    e->value = v;
    e->next = NULL;

    return e;
}

static int hash (char *s) { 
    int sum = 0;
    for (int i = 0; s[i] != '\0'; i++) { 
        sum += s[i];
    }

    return sum % 256;
}

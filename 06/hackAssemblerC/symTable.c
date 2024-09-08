#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "symTable.h"

SymTable *new_symTable () { 
    SymTable *t = (SymTable *) malloc(sizeof(SymTable));

    for (int i = 0; i < 256; i++) { 
        t->entries[i] = NULL;
    }

    init_symTable(t);
    t->current_free = 16;

    return t;
}

static void init_symTable (SymTable *t) { 
    add_entry(t, "R0",  0);
    add_entry(t, "R1",  1);
    add_entry(t, "R2",  2);
    add_entry(t, "R3",  3);
    add_entry(t, "R4",  4);
    add_entry(t, "R5",  5);
    add_entry(t, "R6",  6);
    add_entry(t, "R7",  7);
    add_entry(t, "R8",  8);
    add_entry(t, "R9",  9);
    add_entry(t, "R10", 10);
    add_entry(t, "R11", 11);
    add_entry(t, "R12", 12);
    add_entry(t, "R13", 13);
    add_entry(t, "R14", 14);
    add_entry(t, "R15", 15);
    add_entry(t, "SCREEN", 16384);
    add_entry(t, "KBD", 24576);
    add_entry(t, "SP", 0);
    add_entry(t, "LCL", 1);
    add_entry(t, "ARG", 2);
    add_entry(t, "THIS", 3);
    add_entry(t, "THAT", 4);
}

void add_entry (SymTable *t, char *k, int v) { 
    int index = hash(k);
    SymTableEntry *e;
    if (v == -1) { 
        e = new_entry(k, t->current_free++);
    } else { 
        e = new_entry(k, v);
    }
    
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

int get (SymTable *t, char *k) { 
    int index = hash(k);

    if (t->entries[index] == NULL) { 
        return -1;
    }

    SymTableEntry *p = t->entries[index];
    while (strcmp(p->key, k) != 0) {
        if (p->next == NULL) { 
            break;
        }

        p = p->next;
    }

    if (strcmp(p->key, k) != 0) { 
        return -1;
    }

    return p->value;
}

static SymTableEntry *new_entry (char *k, int v) { 
    SymTableEntry *e = (SymTableEntry *) malloc(sizeof(SymTableEntry));
    if (e == NULL) { 
        printf("malloc failed to allocate an entry for the Symtable! \nentry-> k: %s, v: %d", k, v);
        exit(1);
    }

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

#ifndef __SYMTABLE__
#define __SYMTABLE__

typedef struct SymTableEntry { 
    char *key;
    int value;
    struct SymTableEntry *next;
} SymTableEntry;

typedef struct SymTable { 
    SymTableEntry *entries[256];
    int current_free;
} SymTable;

SymTable *new_symTable ();
static void init_symTable (SymTable *t);

void add_entry (SymTable *t, char *k, int v);
int get (SymTable *t, char *k);

static int hash (char *s);
static SymTableEntry *new_entry (char *k, int v);

#endif

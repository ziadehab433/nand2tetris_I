#ifndef __SYMTABLE__
#define __SYMTABLE__

typedef struct SymTableEntry { 
    char *key;
    int value;
    struct SymTableEntry *next;
} SymTableEntry;

typedef struct SymTable { 
    SymTableEntry *entries[256];
} SymTable;

SymTable *new_symTable ();
void add_entry (SymTable *t, char *k, int v);
int get_value (SymTable *t, char *k);

static int hash (char *s);
static SymTableEntry *new_entry (char *k, int v);

#endif

#include "model.h"

Book *createBook( char const *id, char const *name )
{
    Book *b = malloc(sizeof(Book));
    strcpy(b->name, name);
    strcpy(b->id, id);

    b->sold = 0;
    return b;
}

void freeBook( Book *book )
{

    free(book);

}

Salesperson *createSalesperson( char const *id, char const *name )
{
    Salesperson *s = malloc(sizeof(Salesperson));
    strcpy(s->name, name);
    strcpy(s->id, id);

    s->sold = 0;
    s->head = malloc(sizeof(BookNode));

    return s;


}

void freeSalesperson( Salesperson *salesperson )
{
    BookNode * tmp;

    while(salesperson->head != NULL) {
        tmp = salesperson->head;
        salesperson->head = salesperson->head->next;
        free(tmp);
    }

    free(salesperson);


}

Group *createGroup()
{
    Group *g = malloc(sizeof(Group));

    g->bCap = INITIAL_CAPACITY;
    g->sCap = INITIAL_CAPACITY;

    g->bCount = 0;
    g->sCount = 0;

    g->sList = malloc((g->sCap) *sizeof(Salesperson));
    g->bList = malloc((g->bCap) *sizeof(Book));

    return g;








}

void freeGroup(Group *group)
{
    for(int i = 0; i < group->sCount; i++) {
        freeSalesperson(group->sList[i]);
    }

    for(int j = 0; j < group->bCount; j++) {
        freeBook(group->bList[j]);
    }

    free(group);

}

Book *getBook( Group *group, char const *id )
{
    Book *b = NULL;
    int size = group->bCount;
    for(int i = 0; i < size; i++) {
        if(strcmp(id, group->bList[i]->id) == 0) {
            b = group->bList[i];
        }
    }

    return b;

}

Salesperson *getSalesperson( Group *group, char const *id )
{
    Salesperson *s = NULL;
    int size = group->sCount;
    for(int i = 0; i < size; i++) {
        if(strcmp(id, group->sList[i]->id) == 0) {
            s = group->sList[i];
        }
    }

    return s;

}
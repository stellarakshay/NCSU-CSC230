/**
 * main file
 * @author Akshay Banda
*/


#include "command.h"

/**
 * performs main actions of tracking sales
*/
int main()
{
    Group *g = createGroup();
    int count = 1;
    while(!feof(stdin)) {
        printf("%d> ", count);
        processCommand(g);
        count++;
    }




}

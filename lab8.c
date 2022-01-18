#include <stdio.h>
#include <stdlib.h>

#define MAXSTACKSIZE 10
struct Deck
{
    int val[MAXSTACKSIZE];
    int count;
};
typedef struct Deck *deck;

void push(struct Deck *top, int newVal)
{
    if ((top->count) < MAXSTACKSIZE)
    {
        top->val[top->count] = newVal;
        top->count++;
    }
    else
    {
        printf("FUll stack");
        exit(-2);
    }
}
int pop(struct Deck *top)
{
    if (top->count > 0)
    {
        top->count--;
        return top->val[top->count];
    }
    else
    {
        printf("Empty stack");
        exit(-2);
    }
}
void print(struct Deck *top)
{
    int i;
    for (i = MAXSTACKSIZE; i > 0; i--)
        printf("%d ", top->val[i - 1]);
}
void fillDeck(struct Deck *top, int size)
{
    int i;
    for (i = size; i > 0; i--)
        push(top, i);
}
void riffle(struct Deck *top)
{
    deck tmp1, tmp2, rifflex;
    int i;
    for (i = top->count; i >= 0; i--)
    {
        if (i >= top->count / 2)
            push(tmp1, top->val[10 - i]);
        else
            push(tmp2, top->val[5 - i]);
    }
    for (i = top->count / 2; i > 0; i--)
    {
        push(rifflex, tmp1->val[i]);
        pop(tmp1);
        push(rifflex, tmp2->val[i]);
        pop(tmp2);
    }
}

int main()
{
    deck mydeck;
    mydeck->count = 0;
    fillDeck(mydeck, MAXSTACKSIZE);
    printf("Original: \n");
    print(mydeck);
    int i;
    for (i = 0; i < 10; i--)
    {
        printf("Shuffle %d", i + 1);
        riffle(mydeck);
        print(mydeck);
    }
}

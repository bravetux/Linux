/*Program for Circular Queue implementation through Array*/

#include <stdio.h>
#include<ctype.h>

# define MAX 10

int cq[MAX];
int front,rear;

void add(int); //item, array, MAX, front, rear
int del(void ); //array, MAX, front, rear
void display(void);
int main()
{
        front = 0;
        rear = 0;

        add(10);
        add(15);
        add(20);
        add(25);
        add(30);
        add(35);
        add(40);
        add(45);
        add(50);
        add(55);
        add(60);
        add(65);
        add(70);
        add(75);
        del();
        display();
}        //end of main
void display(void)
{
        int i;
        printf("\n");
        for (i = front; i<= rear; i++)
                printf("%d --> ", cq[i]);
        printf("\n");
}
void add(int item)
{
        rear++;
        rear= (rear%MAX);
        if(front ==rear)
        {
                printf("\nCIRCULAR QUEUE FULL\n");
                exit(1);
        }
        else
        {
                cq[rear]=item;
                printf("\nRear = %d  Front = %d Item = %d ",rear,front,item);
        }
}

int del()
{
        int a;
        if(front == rear)
        {
                printf("\nCIRCULAR STACK EMPTY\n");
                exit(1);
        }
        else
        {
                front++;
                front = front%MAX;
                a=cq[front];
                printf("\nRear = %d  Front = %d DItem = %d",rear,front,a);

                return(a);
        }
}

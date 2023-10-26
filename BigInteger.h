#ifndef BigInteger_H_INCLUDED
#define BigInteger_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct node{
    int data;
    struct node* next;
}Node;

struct BigInteger {
    struct node *head;
    int length;
    int sign;
};

struct BigInteger initialize(char *);

struct BigInteger sub(struct BigInteger , struct BigInteger ) ;

struct BigInteger add(struct BigInteger , struct BigInteger ) ;

struct BigInteger mul(struct BigInteger ,struct BigInteger );

struct BigInteger div1(struct BigInteger ,struct BigInteger );

struct BigInteger mod(struct BigInteger,struct BigInteger);

void display(struct BigInteger);

void reverse(struct BigInteger* );

struct node* createnode(int );

void insert(Node** , int );

int rev(struct node** );

Node* newlist(int );

 Node* multiply( Node* , Node* ,int ,int ,int );

 int getLength(Node* );

 int compare(struct node ,struct node );

#endif
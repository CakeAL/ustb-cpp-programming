//
// Created by cakeal on 2023/4/20.
//
#include <cstdlib>
#include <iostream>

using namespace std;

struct LinkList{
    int data;
    struct LinkList* next;
};

int main(){
    struct LinkList Node{};
    int m, n, remained;
    int count = 0;
    struct LinkList* head, * tail, * cur, * next;
    head = (struct LinkList*) malloc(sizeof(struct LinkList));
    head->next = NULL;
    cin >> m >> n;
    remained = m;
    if (m == 0 || n == 0){
        free(head);
        exit(-1);
    }else {
        tail = head;
        for(int i = 0; i < m; i++){
            cur = (struct LinkList*) malloc(sizeof(struct LinkList));
            cur->data = i + 1;
            tail->next = cur;
            cur->next = head->next;
            tail = cur;
        }
        cur = head->next;
        next = tail;
        int i = 1;
        while (remained != 1){
            if (i == n){
                next->next = next->next->next;
                free(cur);
                cur = next->next;
                remained--;
                i = 1;
            }
            else{
                next = next->next;
                cur = cur->next;
                i++;
            }
        }
        cout << cur->data;
        free(cur);
    }

    return 0;
}
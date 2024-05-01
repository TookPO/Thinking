#include <stdio.h>
#include <stdlib.h>

//  Doubly linked list를 memory leak 없이 짜신 후에 제게 소스코드를 보내주세요.

// 이전 <- 현재 -> 이후
typedef struct node {
    struct node * pre;
    struct node * next;
    int number;
} Node;

void insert(Node * head);
void search(Node * head);
void delete(Node * head);
void deleteAll(Node * head);

int main(void){
    int select;
    Node * head = (Node*) malloc(sizeof(Node)); // 헤드는 number를 가지지x
    head -> pre = NULL; // NULL ptr로 만듬
    head -> next = NULL;
    //printf("head의 다음[%d]:", head->next->number);

    while(1){
        printf("1.Insert   2.Search All  3.Delete  4.exit \n"">");
        select = getchar();
        while(getchar() != '\n');
//        printf("[%d]", select);
        switch(select){

            case '1':
                insert(head);
                break;

            case '2':
                search(head);
                break;

            case '3':
                delete(head);
                break;

            case '4':
                deleteAll(head);
                return 0;

            default:
                printf("It's invalid value!");
                break;
        }
        printf("\n\n");
        printf("-------------------------------");
        printf("\n\n");
    }

    return 0;
}

void insert(Node * head){
    Node * cur, * newNode;

    newNode = malloc(sizeof(Node)); // 힙 영역에 Node의 크기만큼의 공간 할당
    newNode -> pre = NULL; // NULL ptr로 만듬
    newNode -> next = NULL;

    printf("Insert a number about new node>");
    scanf("%d", &(newNode->number));// 새로운 노드에 넣을 숫자 입력
    while(getchar() != '\n');

    // 첫 노드를 입력할 경우
    if(head->next == NULL){
        head->next = newNode;
        newNode -> pre = head;

        printf("head의 다음[%d]:", head->next->number);

        return;
    }

    // Node를 추가하려면 알맞은 공간을 찾아야하는데..
    // 모든 Node는 Number의 크기 순서로 배치되야함
    // 시작: 첫번째 node(전역변수)
    // 조건: Node가 처음부터 비어있음 or 현재 노드가 들어갈 알맞은 자리 찾음
    // 반복: 현재 = 다음
    for(cur=(head->next); (cur->next != NULL) && (cur->number) < (newNode->number); cur = (cur->next));

    // 사이에 넣어야 되는 경우
    // [이전] <-> [추가] <-> [현재]
    if((cur->number) > (newNode->number)){
        cur->pre->next= newNode;
        newNode->pre = cur->pre;
        newNode->next = cur;
        cur->pre = newNode;
        puts("Success!\n");
        return;
    }

    // 새로운 노드가 노드의 끝이 되는경우
    if(cur ->next == NULL){
        cur -> next = newNode;
        newNode -> pre = cur;
        puts("Success!\n");
        return;
    }

    // [새로운 노드의 숫자가 이미 존재하는 경우]
    if((cur->number) == (newNode->number)){
        puts("It already exist!\n");
        free(newNode); // 할당 해제, 노드 삭제시킴
        return;
    }

}

void search(Node * head){
    Node * cur;

    for(cur = (head->next); (cur != NULL); cur = (cur->next)){
        printf("[%d] <-> ", (cur->number));
    }
}

void delete(Node * head){
     int deleteNumber;
     Node * cur, *prePtr;

     puts("Insert the number that you want to delete>");
     scanf("%d", &deleteNumber);
     while(getchar()!='\n');

     for(cur=(head->next); (cur != NULL) && ((cur -> number) != deleteNumber); cur = (cur->next));

     // 찾아본결과 없으면..
     if(cur == NULL){
         puts("Number not found!\n");
         return;
     }

     // 찾았는데 있다면
     //             [현재]
     // [이전] <-            -> [다음]
     if((cur->number) == deleteNumber){
         prePtr = cur->pre;

         if(cur->next == NULL){ // 현재가 끝이였다면
             prePtr -> next = NULL;
         }else{
             prePtr -> next = cur->next;
             cur -> next -> pre = prePtr;
         }

         free(cur); // 할당했던 노드 삭제
         puts("The node is Deleted!\n");
     }
}

void deleteAll(Node * head){
     Node * cur;

     // 노드가 존재하지 x경우
     if(head->next == NULL){
         free(head);
         return;
     }

     // *삭제 과정*
     // 1. cur에 대상의 다음번쩨 노드를 넣음
     // 2. cur의 이전(대상노드) 삭제
     // 3. 반복
     for(cur=(head->next); (cur->next) != NULL; cur = (cur->next)){
         free(cur->pre);
     }

     // 마지막남은 노드 삭제
     free(cur);
}

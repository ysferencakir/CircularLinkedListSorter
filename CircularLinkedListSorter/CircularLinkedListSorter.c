#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

struct node {
    char ulke[MAX];
    struct node* next;
};
typedef struct node* NODEPTR;

NODEPTR head = NULL;
NODEPTR tail = NULL;
NODEPTR circularHead = NULL;


NODEPTR getnode(void) {
    NODEPTR p;
    p = (NODEPTR)malloc(sizeof(struct node));
    if (p == NULL) {
        printf("Bellek ayrilamadi. Program sonlandiriliyor.\n");
        exit(1);
    }
    return(p);
}
NODEPTR dugumOlustur() {
    NODEPTR yeniDugum = getnode();
    char yeniUlke[MAX];
    printf("Ulke Adi nedir: ");
    scanf(" %19[^\n]", yeniUlke);
    strcpy(yeniDugum->ulke, yeniUlke);
    yeniDugum->next = NULL;
    return yeniDugum;
}
void dugumEkle(NODEPTR yeniDugum) {
    if (head == NULL) {
        head = yeniDugum;
        tail = yeniDugum;
    }
    else {
        tail->next = yeniDugum;
        tail = yeniDugum;
    }
}
void ikinciyiSil() {
    NODEPTR current = head;
    NODEPTR temp, prev;

    while (current != NULL && current->next != NULL) {
        prev = current;
        temp = current->next;

        while (temp != NULL) {
            if (strcmp(current->ulke, temp->ulke) == 0) {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }
            else {
                prev = temp;
                temp = temp->next;
            }
        }
        current = current->next;
    }
}
void daireselEkle(NODEPTR yeniDugum) {
    if (circularHead == NULL) {
        circularHead = yeniDugum;
        circularHead->next = circularHead;
    }
    else {
        NODEPTR current = circularHead;
        NODEPTR prev = NULL;
        do {
            if (strcmp(yeniDugum->ulke, current->ulke) < 0) {
                break;
            }
            prev = current;
            current = current->next;
        } while (current != circularHead);

        if (prev == NULL) {
            yeniDugum->next = circularHead;
            NODEPTR tail = circularHead;
            while (tail->next != circularHead) {
                tail = tail->next;
            }
            tail->next = yeniDugum;

            circularHead = yeniDugum;
        }
        else {
            yeniDugum->next = current;
            prev->next = yeniDugum;
        }
    }
}
void freeCircularList() {
    if (circularHead == NULL) {
        return;
    }

    NODEPTR temp = circularHead;
    NODEPTR nextNode;

    do {
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    } while (temp != circularHead);

    circularHead = NULL;
}
void anaListeyiKopyala() {
    NODEPTR temp = head;
    while (temp != NULL) {

        NODEPTR yeniDugum = getnode();
        strcpy(yeniDugum->ulke, temp->ulke);
        yeniDugum->next = NULL;

        daireselEkle(yeniDugum);
        temp = temp->next;
    }
}
void listeyiYazdir() {
    if (circularHead == NULL) {
        printf("Dairesel liste bos.\n");
        return;
    }

    NODEPTR temp = circularHead;
    printf("Dairesel Liste (Alfabetik Sira):\n");
    do {
        printf("%s\n", temp->ulke);
        temp = temp->next;
    } while (temp != circularHead);
}


void freeList() {
    NODEPTR temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
}

void menu() {
    printf("\n");
    printf("***********************************************************\n");
    printf("*               Bay Chimaobi hosgeldiniz.                 *\n");
    printf("*       Lutfen yapmak istedigin islemi asagidan seciniz.  *\n");
    printf("***********************************************************\n");
    printf("*                  1. Turist Girisi                       *\n");
    printf("*                  2. Alfabetik Listeyi yazdir.           *\n");
    printf("*                  3. Cikis                               *\n");
    printf("***********************************************************\n");
    printf("Seciminiz nedir: ");

}

int main() {

    int secim;

    do {
        menu();
        scanf("%d", &secim);

        if (secim == 1) {
            NODEPTR yeniDugum = dugumOlustur();
            dugumEkle(yeniDugum);
        }
        else if (secim == 2) {
            ikinciyiSil();
            anaListeyiKopyala();
            listeyiYazdir();
        }
        else if (secim == 3) {
            printf("Cikiliyor...");
            freeList();
            freeCircularList();
            exit(1);
        }
        else {
            printf("Seciminiz yanlis. Yeniden deneyin\n");
        }

    } while (secim != 3);
    return 0;



}
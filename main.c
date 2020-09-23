#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
typedef struct cell {
    char name[10];
    int shomare_khoone;
    int energy;
    char prev ;
    struct cell *next;
} cell;

typedef struct node {
    int shomare_khoone;
    int energy;
    struct node *next;
} esource; //listi az khune haye manba energy

int check_odd_even(int num);

void print_menu1();

void update_map(int n, char *mode, int *sotoon); //1 o 2 o 3 o 4 ro be e , m ,n ,f tabdil mikone va sotoon ha ro ham zakhire mikone

void print_map(int n, int size, char mode[size],cell * head);

cell *add_cell(char name[50],int num_khane, cell *head,int energy);

void print_list(cell *head);

int random_place(int size, char *mode);

void print_menu2();

void print_menu3();

char move_north(int n , char *mode ,int index,cell * head);

char move_south(int n , char *mode ,int index,cell * head);

char jump_right(int n , char *mode ,int index,cell *head,int total , int col[total]);

char jump_left(int n , char *mode ,int index,cell *head,int total , int col[total]);

char move_northeast(int n , char *mode ,int index ,int size , int col[size],cell *head);

cell * sort_cells(cell * head);

int col[1000];

int find_index(cell * head , char esm[50]);

char move_northwest(int n , char *mode ,int index ,int size , int col[size],cell *head);

char move_southeast(int n , char *mode ,int index ,int size , int col[size],cell *head);

char move_southwest(int n , char *mode ,int index ,int size , int col[size],cell *head);

esource * add_esource(int numkhane ,int energy, esource *head);

cell * update_energy_cells(cell * head,int energy, int index);

esource * update_energy_sources(esource * ehead,cell * head,int index);

void print_list_energy(esource *head);

void print_list_energy_cells(cell * head);

int find_index_hamsaye(int index,int size, char mode[size],int n);

cell * change_energy(cell * head,int index);

int check_split(cell* head,int index);

int check_jump(cell* head,int index);

int main() {
    cell *HEAD = NULL;
    esource *eHEAD = NULL;
    FILE *fp, *fin;
    int n, total, x, n_cells1, n_cells2, i, index, y, z, shomare_khoone, g;
    char tmp[50], esm[20][20], func;

    fp = fopen("map6.bin", "rb");
    if (fp == NULL) {
        printf("Cannot find the file .");
        return -1;
    }
    fread(&n, sizeof(int), 1, fp);
    total = n * n;
    char khane[total];
    int col[total]; //sotoon haro tosh zakhire kardam
    while (feof(fp) != 1) {
        fread(khane, sizeof(char), total, fp);
    }
    char *pkhane;
    int *pcol;
    pkhane = &(khane[0]);
    pcol = &(col[0]);
    update_map(n, pkhane, pcol);//sotoon baraye har khanei ro ham zakhire mikone
    for (i = 0; i < total; i++) {
        if (khane[i] == 'e') {
            eHEAD = add_esource(i, 100, eHEAD);
        }
    }
    while (1) {
        print_menu1();
        scanf("%d", &x);
        if (x == 1) {//Load
            fin = fopen("cellsgame", "rb");
            fread(&n, sizeof(int), 1, fin);
            fread(khane, sizeof(char), total, fin);
            fread(&n_cells1, sizeof(int), 1, fin);
            fread(&n_cells2, sizeof(int), 1, fin);
            char temp[10];
            int num1, energy1;
            for (i = 0; i < (n_cells1+n_cells2); i++) {
                fread(temp, sizeof(char), 10, fin);
                fread(&num1, sizeof(int), 1, fin);
                fread(&energy1, sizeof(int), 1, fin);
                HEAD = add_cell(temp, num1, HEAD, energy1);

            }
            int num2, energy2;
            while (feof(fin) != 1) {
                fread(&num2, sizeof(int), 1, fin);
                fread(&energy2, sizeof(int), 1, fin);
                eHEAD = add_esource(num2, energy2, eHEAD);
            }
            fclose(fin);

        }
        if (x == 2) {//Single player mode :
            n_cells2=0;
            printf("Enter number of cells: ");
            scanf("%d", &n_cells1);
            getchar();
            for (i = 0; i < n_cells1; i++) {
                printf("Name of cell number %d: ", i + 1);
                gets(tmp);
                shomare_khoone = random_place(total, pkhane);//cell ra be jadval vared mikone
                HEAD = add_cell(tmp, shomare_khoone, HEAD, 0);
                strcpy(esm[i], tmp);
            }
            HEAD = sort_cells(HEAD);
            update_map(n, pkhane, pcol);
            print_map(n, total, khane, HEAD);
            printf("\n");
            while (1) {
                printf("Which cell ? : \n");
                scanf("%s", tmp);
                print_menu2();
                scanf("%d", &y);
                if (y == 1) {//move
                    print_menu3();
                    scanf("%d", &z);
                    if (z == 1) {
                        index = find_index(HEAD, tmp); //shomare khooneye seloole morede nazar
                        func = move_north(n, pkhane, index, HEAD);
                        HEAD = sort_cells(HEAD);
                        print_list(HEAD);
                        print_map(n, total, khane, HEAD);

                    }
                    if (z == 2) {
                        index = find_index(HEAD, tmp);
                        func = move_south(n, pkhane, index, HEAD);
                        HEAD = sort_cells(HEAD);
                        print_map(n, total, khane, HEAD);

                    }
                    if (z == 3) {
                        index = find_index(HEAD, tmp);
                        func = move_northeast(n, pkhane, index, total, col, HEAD);
                        HEAD = sort_cells(HEAD);
                        print_map(n, total, khane, HEAD);

                    }
                    if (z == 4) {
                        index = find_index(HEAD, tmp);
                        func = move_northwest(n, pkhane, index, total, col, HEAD);
                        HEAD = sort_cells(HEAD);
                        print_map(n, total, khane, HEAD);

                    }
                    if (z == 5) {
                        index = find_index(HEAD, tmp);
                        func = move_southeast(n, pkhane, index, total, col, HEAD);
                        HEAD = sort_cells(HEAD);
                        print_map(n, total, khane, HEAD);

                    }
                    if (z == 6) {
                        index = find_index(HEAD, tmp);
                        func = move_southwest(n, pkhane, index, total, col, HEAD);
                        HEAD = sort_cells(HEAD);
                        print_map(n, total, khane, HEAD);

                    }

                    if (z == 7) {
                        index = find_index(HEAD, tmp);
                        if (check_jump(HEAD,index)==1) {
                            func = jump_right(n, pkhane, index, HEAD, total, col);
                            HEAD = sort_cells(HEAD);
                            print_map(n, total, khane, HEAD);
                        }else{
                            printf("Your energy is below 30 , so you cannot jump. :(\n");
                        }

                    }
                    if (z == 8) {
                        index = find_index(HEAD, tmp);
                        if (check_jump(HEAD,index)==1) {
                            func = jump_left(n, pkhane, index, HEAD, total, col);
                            HEAD = sort_cells(HEAD);
                            print_map(n, total, khane, HEAD);
                        }else{
                            printf("Your energy is below 30 , so you cannot jump. :(\n");
                        }

                    }
                }
                if (y == 2) {//split
                    if (func == 'm') {
                        int index2;
                        index = find_index(HEAD, tmp);//shomare khooneye selooli ke sare jash mimone
                        if (check_split(HEAD,index)==1) {
                            index2 = find_index_hamsaye(index, total, khane, n);//shomare khooneye seloole jadid
                            printf("Name of the new cell : ");
                            scanf("%s", tmp);
                            HEAD = add_cell(tmp, index2, HEAD, 40);
                            HEAD = change_energy(HEAD, index);
                            khane[index2] = 'c';
                            HEAD = sort_cells(HEAD);
                            print_map(n, total, khane, HEAD);
                        }else{
                            printf("Your energy is below 80 , so you cannot split. :(\n");
                        }
                    }


                }
                if (y == 3) {//energy
                    if (func == 'e') {
                        printf("yes!");
                        index = find_index(HEAD, tmp);
                        update_energy_sources(eHEAD, HEAD, index);
                        print_map(n, total, khane, HEAD);
                    }
                }
                if (y == 4) {//save
                    fin = fopen("cellsgame", "wb");
                    fwrite(&n, sizeof(int), 1, fin);
                    fwrite(khane, sizeof(char), total, fin);
                    fwrite(&n_cells1, sizeof(int), 1, fin);
                    fwrite(&n_cells2, sizeof(int), 1, fin);
                    cell *curr1 = HEAD;
                    while (curr1 != NULL) {
                        char temp[10];
                        strcpy(temp, curr1->name);
                        int f = curr1->shomare_khoone;
                        int g = curr1->energy;
                        fwrite(temp, sizeof(char), 10, fin);
                        fwrite(&f, sizeof(int), 1, fin);
                        fwrite(&g, sizeof(int), 1, fin);
                        curr1 = curr1->next;
                    }
                    esource *curr2 = eHEAD;
                    while (curr2 != NULL) {
                        int f = curr2->shomare_khoone;
                        int g = curr2->energy;
                        fwrite(&f, sizeof(int), 1, fin);
                        fwrite(&g, sizeof(int), 1, fin);
                        curr2 = curr2->next;
                    }
                    fclose(fin);
                }
                if (y == 5) {//exit
                    return 0;
                }

            }


        }
        if (x == 3) {//Multi player mode
            printf("Enter number of cells for first player : ");
            scanf("%d", &n_cells1);
            getchar();
            for (i = 0; i < n_cells1; i++) {
                printf("Name of cell number %d: ", i + 1);
                gets(tmp);
                shomare_khoone = random_place(total, pkhane);//cell ra be jadval vared mikone
                HEAD = add_cell(tmp, shomare_khoone, HEAD, 0);
            }
            HEAD = sort_cells(HEAD);
            update_map(n, pkhane, pcol);
            printf("\n");
            printf("Enter number of cells for second player : ");
            scanf("%d", &n_cells2);
            getchar();
            for (i = 0; i < n_cells2; i++) {
                printf("Name of cell number %d: ", i + 1);
                gets(tmp);
                shomare_khoone = random_place(total, pkhane);//cell ra be jadval vared mikone
                HEAD = add_cell(tmp, shomare_khoone, HEAD, 0);
            }
            HEAD = sort_cells(HEAD);
            update_map(n, pkhane, pcol);
            print_map(n, total, khane, HEAD);
            printf("\n");
            while (1) {
                printf("Which cell ? : \n");
                scanf("%s", tmp);
                print_menu2();
                scanf("%d", &y);
                if (y == 1) {//move
                    print_menu3();
                    scanf("%d", &z);
                    if (z == 1) {
                        index = find_index(HEAD, tmp); //shomare khooneye seloole morede nazar
                        func = move_north(n, pkhane, index, HEAD);
                        HEAD = sort_cells(HEAD);
                        print_list(HEAD);
                        print_map(n, total, khane, HEAD);
                        if (func=='m')
                            printf("Check if you can split or not , choose 2.\n");
                        else if (func=='e')
                            printf("You can boost your energy , choose 3.\n");

                    }
                    if (z == 2) {
                        index = find_index(HEAD, tmp);
                        func = move_south(n, pkhane, index, HEAD);
                        HEAD = sort_cells(HEAD);
                        print_map(n, total, khane, HEAD);
                        if (func=='m')
                            printf("Check if you can split or not , choose 2.\n");
                        else if (func=='e')
                            printf("You can boost your energy , choose 3.\n");

                    }
                    if (z == 3) {
                        index = find_index(HEAD, tmp);
                        func = move_northeast(n, pkhane, index, total, col, HEAD);
                        HEAD = sort_cells(HEAD);
                        print_map(n, total, khane, HEAD);
                        if (func=='m')
                            printf("Check if you can split or not, choose 2.\n");
                        else if (func=='e')
                            printf("You can boost your energy , choose 3.\n");

                    }
                    if (z == 4) {
                        index = find_index(HEAD, tmp);
                        func = move_northwest(n, pkhane, index, total, col, HEAD);
                        HEAD = sort_cells(HEAD);
                        print_map(n, total, khane, HEAD);
                        if (func=='m')
                            printf("Check if you can split or not, choose 2.\n");
                        else if (func=='e')
                            printf("You can boost your energy , choose 3.\n");

                    }
                    if (z == 5) {
                        index = find_index(HEAD, tmp);
                        func = move_southeast(n, pkhane, index, total, col, HEAD);
                        HEAD = sort_cells(HEAD);
                        print_map(n, total, khane, HEAD);
                        if (func=='m')
                            printf("Check if you can split or not, choose 2.\n");
                        else if (func=='e')
                            printf("You can boost your energy , choose 3.\n");

                    }
                    if (z == 6) {
                        index = find_index(HEAD, tmp);
                        func = move_southwest(n, pkhane, index, total, col, HEAD);
                        HEAD = sort_cells(HEAD);
                        print_map(n, total, khane, HEAD);
                        if (func=='m')
                            printf("Check if you can split or not, choose 2.\n");
                        else if (func=='e')
                            printf("You can boost your energy , choose 3.\n");

                    }
                }
                if (y == 2) {//split
                    if (func == 'm') {
                        int index2;
                        index = find_index(HEAD, tmp);//shomare khooneye selooli ke sare jash mimone
                        if (check_split(HEAD, index) == 1) {
                            index2 = find_index_hamsaye(index, total, khane, n);//shomare khooneye seloole jadid
                            printf("Name of the new cell : ");
                            scanf("%s", tmp);
                            HEAD = add_cell(tmp, index2, HEAD, 40);
                            HEAD = change_energy(HEAD, index);
                            khane[index2] = 'c';
                            HEAD = sort_cells(HEAD);
                            print_map(n, total, khane, HEAD);
                        } else {
                            printf("Your energy is below 80 , so you cannot split. :(\n");
                        }
                    }

                }
                if (y == 3) {//energy
                    if (func == 'e') {
                        printf("yes!");
                        index = find_index(HEAD, tmp);
                        update_energy_sources(eHEAD, HEAD, index);
                        print_map(n, total, khane, HEAD);
                    }
                }
                if (y == 4) {//save
                    fin = fopen("cellsgame", "wb");
                    fwrite(&n, sizeof(int), 1, fin);
                    fwrite(khane, sizeof(char), total, fin);
                    fwrite(&n_cells1, sizeof(int), 1, fin);
                    fwrite(&n_cells2, sizeof(int), 1, fin);
                    cell *curr1 = HEAD;
                    while (curr1 != NULL) {
                        char temp[10];
                        strcpy(temp, curr1->name);
                        int f = curr1->shomare_khoone;
                        int g = curr1->energy;
                        fwrite(temp, sizeof(char), 10, fin);
                        fwrite(&f, sizeof(int), 1, fin);
                        fwrite(&g, sizeof(int), 1, fin);
                        curr1 = curr1->next;
                    }
                    esource *curr2 = eHEAD;
                    while (curr2 != NULL) {
                        int f = curr2->shomare_khoone;
                        int g = curr2->energy;
                        fwrite(&f, sizeof(int), 1, fin);
                        fwrite(&g, sizeof(int), 1, fin);
                        curr2 = curr2->next;
                    }
                    fclose(fin);
                }
                if (y == 5) {//exit
                    return 0;
                }

            }

        }
    }
}


cell *add_cell(char name[50],int num_khane, cell *head,int energy) {
    cell *curr = head;
    cell *nn;
    nn = (cell *) malloc(sizeof(cell));
    if (nn == NULL)
        return NULL;
    nn->next = NULL;
    nn->shomare_khoone=num_khane;
    nn->energy=energy;
    nn->prev='n';
    strcpy(nn->name, name);
    if (head == NULL)
        head = nn;
    else {
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = nn;
    }
    return head;
}

int check_odd_even(int num) {
    if (num % 2 == 0)
        return 1;//zoj
    else
        return 0;//fard
}

void print_menu1() {
    printf("1. Load\n2. New Single Player Game\n3. New Multi Player Game\n4. Exit\n");
}

void update_map(int n, char *mode,int *sotoon) {
    int i, j = 0, ctr = -1;
    for (i = 0; i < (n * 2); i++) {
        for (j = 0; j < n; j++) {
            if (check_odd_even(j + i) == 1) {
                ctr++;
                *(sotoon+ctr)=j;
                if (*(mode + ctr) == '4') {//normal
                    (*(mode + ctr)) = 'n';
                } else if (*(mode + ctr) == '3') {
                    (*(mode + ctr)) = 'f';
                } else if (*(mode + ctr) == '2') {
                    (*(mode + ctr)) = 'm';
                } else if (*(mode + ctr) == '1') {
                    (*(mode + ctr)) = 'e';
                }
            }
        }
    }
}

void print_map(int n, int size, char mode[size],cell* head) {
    int i, j = 0, ctr = -1;
    cell *curr=head;
    for (i = 0; i < (2 * n); i++) {
        for (j = 0; j < n; j++) {
            if (check_odd_even(j + i) == 1) {
                ctr++;
                if (mode[ctr] == 'n') //normal
                    printf("    ________    ");
                else if (mode[ctr] == 'f')
                    printf("   forbidden!   ");
                else if (mode[ctr] == 'm')
                    printf("    mitosis     ");
                else if (mode[ctr] == 'e')
                    printf("    energy      ");
                else if (mode[ctr] == 'c') {
                    printf("   ^o^ : %s ,%d ", curr->name,curr->energy);
                    curr=curr->next;
                }
            } else
                printf("            ");
        }
        printf("\n");
        printf("\n");

    }
}

void print_list(cell *head) {
    cell *curr = head;
    while (curr != NULL) {
        printf("%s : %d\n", curr->name,curr->shomare_khoone);
        curr = curr->next;
    }
}

int random_place(int size, char *mode) {
    int a, flag = 0;
    srand(time(NULL));
    a = rand() % size;
    flag = 0;
    if (*(mode+a) != 'c' ) //check mikone ke tosh selool nabashe
        *(mode+a) = 'c';
    else {
        while (flag == 0) {
            a = rand() % size;
            if (*(mode+a) != 'c' ) {
                *(mode+a) = 'c';
                flag = 1;
            }
        }
    }
    return a; //shomare khoone ro return mikone
}
void print_menu2(){
    printf("1. Move\n2. Split a cell\n3. Boost energy\n4. Save\n5. exit\n");
}
void print_menu3(){
    printf("1. North\n2. South\n3. Northeast\n4. Northwest\n5. Southeast\n6. Southwest\n7. Jump right\n8. Jump left ");
}
char jump_right(int n , char *mode ,int index,cell *head,int total , int col[total]){
    char x;
    cell * curr=head;
    while ( curr!=NULL){
        if(curr->shomare_khoone==index){
            break;}
        curr=curr->next;
    }
    x=*(mode+(index+1));
    if (*(mode+(index+1))!='f' && *(mode+(index+1))!='c') {
        if (col[index]!=n-2 && col[index]!=n-1) {
            *(mode+(index+1)) = 'c';
            *(mode+index) = curr->prev;
            curr->shomare_khoone=index+1;
        }
    }
    curr->prev=x;
    return x;//halati khunei ke mire tosh ro mifrestam bala to bebinam mitoone split ya energy kone.
}

char jump_left(int n , char *mode ,int index,cell *head,int total , int col[total]){
    char x;
    cell * curr=head;
    while ( curr!=NULL){
        if(curr->shomare_khoone==index){
            break;}
        curr=curr->next;
    }
    x=*(mode+(index-1));
    if (*(mode+(index-1))!='f' && *(mode+(index-1))!='c') {
        if (col[index]!=0 && col[index]!=1) {
            *(mode+(index-1)) = 'c';
            *(mode+index) = curr->prev;
            curr->shomare_khoone=index-1;
        }
    }
    curr->prev=x;
    return x;//halati khunei ke mire tosh ro mifrestam bala to bebinam mitoone split ya energy kone.
}
char move_north(int n , char *mode ,int index,cell *head){
    char x;
    cell * curr=head;
    while ( curr!=NULL){
        if(curr->shomare_khoone==index){
            break;}
        curr=curr->next;
    }
    x=*(mode+(index-n));
    if (*(mode+(index-n))!='f' && *(mode+(index-n))!='c') {
        if (index >= n) {
            *(mode+(index-n)) = 'c';
            *(mode+index) = curr->prev;
            curr->shomare_khoone=index-n;
        }
    }
    curr->prev=x;
    return x;//halati khunei ke mire tosh ro mifrestam bala to bebinam mitoone split ya energy kone.
}
char move_south(int n , char *mode ,int index,cell * head){
    char x;
    cell * curr=head;
    while ( curr!=NULL){
        if(curr->shomare_khoone==index){
            break;}
        curr=curr->next;
    }
    x=*(mode+(index+n));
    if (*(mode+(index+n))!='f' && *(mode+(index+n))!='c') {
        if (((n*n)-n)>index ) {
            *(mode+(index+n)) = 'c';
            *(mode+index) = curr->prev;
            curr->shomare_khoone=index+n;
        }
    }
    curr->prev=x;
    return x;//halati khunei ke mire tosh ro mifrestam bala to bebinam mitoone split ya energy kone.
}
char move_northeast(int n , char *mode ,int index,int total , int col[total],cell * head){
    char x;
    cell * curr=head;
    while ( curr!=NULL){
        if(curr->shomare_khoone==index){
            break;}
        curr=curr->next;
    }
    int a=(int)ceil(log2(n));

    if(col[index-a]>col[index]) {
        if (*(mode + (index - a)) != 'f' && *(mode + (index - a)) != 'c') {
            if (index >= (n-(n/2))) {
                if(col[index]!=n-1) {
                    x = *(mode + (index - a));
                    *(mode + (index - a)) = 'c';
                    *(mode + index) = curr->prev;
                    curr->shomare_khoone = index - a;
                }
            }
        }
    }else if (col[index-a]<col[index])
        if (*(mode + (index-a+1)) != 'f' && *(mode + (index-a+1)) != 'c') {
            if (index >= (n-(n/2))) {
                if(col[index]!=n-1) {
                    x = *(mode + (index - a + 1));
                    *(mode + (index - a + 1)) = 'c';
                    *(mode + index) = curr->prev;
                    curr->shomare_khoone = index - a + 1;
                }
            }
        }
    curr->prev=x;
    return x;//halati khunei ke mire tosh ro mifrestam bala to bebinam mitoone split ya energy kone.
}
cell * sort_cells(cell * head){
    cell * curr1=NULL;
    cell * curr2=NULL;
    for (curr1=head ; curr1->next !=NULL ; curr1=curr1->next){
        for(curr2=curr1->next ; curr2 !=NULL ; curr2=curr2->next){
            if (curr2->shomare_khoone < curr1->shomare_khoone){
                int tmp1;
                int tmp2;
                char tmp3;
                char tmpname[20];
                tmp1=curr1->shomare_khoone;
                curr1->shomare_khoone = curr2->shomare_khoone;
                curr2->shomare_khoone = tmp1;
                tmp2=curr1->energy;
                curr1->energy = curr2->energy;
                curr2->energy = tmp2;
                tmp3=curr1->prev;
                curr1->prev = curr2->prev;
                curr2->prev = tmp3;
                strcpy(tmpname,curr1->name);
                strcpy(curr1->name,curr2->name);
                strcpy(curr2->name,tmpname);
            }
        }
    }
    return head;

}
int find_index(cell * head , char esm[50]){
    cell * curr=head;
    int index;
    while ( curr!=NULL){
        if ( strcmp(curr->name,esm)==0){
            index=curr->shomare_khoone;
        }
        curr=curr->next;
    }
    return index;
}
char move_northwest(int n , char *mode ,int index ,int size , int col[size],cell *head){
    char x;
    cell * curr=head;
    while ( curr!=NULL){
        if(curr->shomare_khoone==index){
            break;}
        curr=curr->next;
    }
    int a=(int)ceil(log2(n));

    if(col[index-a]<col[index]) {
        if (*(mode + (index - a)) != 'f' && *(mode + (index - a)) != 'c') {
            if (index >= (n-(n/2)) ) {
                if(col[index]!=0) {
                    x = *(mode + (index - a));
                    *(mode + (index - a)) = 'c';
                    *(mode + index) = curr->prev;
                    curr->shomare_khoone = index - a;
                }
            }
        }
    }else if (col[index-a]>col[index])
        if (*(mode + (index-a-1)) != 'f' && *(mode + (index-a-1)) != 'c') {
            if (index >= (n-(n/2))) {
                if(col[index]!=0) {
                    x = *(mode + (index - a - 1));
                    *(mode + (index - a - 1)) = 'c';
                    *(mode + index) = curr->prev;
                    curr->shomare_khoone = index - a - 1;
                }
            }
        }
    curr->prev=x;
    return x;
}
char move_southeast(int n , char *mode ,int index ,int size , int col[size],cell *head){
    char x;
    cell * curr=head;
    while ( curr!=NULL){
        if(curr->shomare_khoone==index){
            break;}
        curr=curr->next;
    }
    int a=(int)ceil(log2(n));

    if(col[index+a]>col[index]) {
        if (*(mode + (index + a)) != 'f' && *(mode + (index + a)) != 'c') {
            if (index < ((n*n)-(n/2)) ) {
                if(col[index]!=(n-1)) {
                    x = *(mode + (index + a));
                    *(mode + (index + a)) = 'c';
                    *(mode + index) = curr->prev;
                    curr->shomare_khoone = index + a;
                }
            }
        }
    }else if (col[index+a]<col[index])
        if (*(mode + (index+a+1)) != 'f' && *(mode + (index+a+1)) != 'c') {
            if (index < ((n*n)-(n/2)) ) {
                if(col[index]!=(n-1)) {
                    x = *(mode + (index + a + 1));
                    *(mode + (index + a + 1)) = 'c';
                    *(mode + index) = curr->prev;
                    curr->shomare_khoone = index + a + 1;
                }
            }
        }
    curr->prev=x;
    return x;
}
char move_southwest(int n , char *mode ,int index ,int size , int col[size],cell *head){
    char x;
    cell * curr=head;
    while ( curr!=NULL){
        if(curr->shomare_khoone==index){
            break;}
        curr=curr->next;
    }
    int a=(int)ceil(log2(n));

    if(col[index+a]<col[index]) {
        if (*(mode + (index + a)) != 'f' && *(mode + (index + a)) != 'c') {
            if (index < ((n*n)-(n/2)) ) {
                if (col[index]!= 0) {
                    x = *(mode + (index + a));
                    *(mode + (index + a)) = 'c';
                    *(mode + index) = curr->prev;
                    curr->shomare_khoone = index + a;
                }
            }
        }
    }else if (col[index+a]>col[index])
        if (*(mode + (index+a-1)) != 'f' && *(mode + (index+a-1)) != 'c') {
            if (index < ((n*n)-(n/2)) ) {
                if (col[index]!= 0) {
                    x = *(mode + (index + a - 1));
                    *(mode + (index + a - 1)) = 'c';
                    *(mode + index) = curr->prev;
                    curr->shomare_khoone = index + a - 1;
                }
            }
        }
    curr->prev=x;
    return x;
}
esource  * add_esource(int numkhane,int energy ,esource *  head){
    esource *curr = head;
    esource *nn;
    nn = (esource *) malloc(sizeof(esource));
    if (nn == NULL)
        return NULL;
    nn->next = NULL;
    nn->shomare_khoone=numkhane;
    nn->energy=energy;
    if (head == NULL)
        head = nn;
    else {
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = nn;
    }
    return head;
}

esource * update_energy_sources(esource * ehead,cell * head,int index){
    esource * curr=ehead;
    while ( curr !=NULL){
        if(curr->shomare_khoone==index){
            break;
        }
        curr=curr->next;
    }
    if(curr->energy >= 15){
        curr->energy=(curr->energy)-15;
        head=update_energy_cells(head,15,index);
    }else{
        head=update_energy_cells(head,curr->energy,index);
        curr->energy=0;
    }
    return ehead;
}
cell * update_energy_cells(cell * head,int energy,int index){
    cell * curr=head;
    while ( curr !=NULL){
        if (curr->shomare_khoone==index){
            break;
        }
        curr=curr->next;
    }
    curr->energy=curr->energy + energy;
    return head;
}
void print_list_energy(esource *head) {
    esource *curr = head;
    while (curr != NULL) {
        printf("%d : %d\n", curr->shomare_khoone,curr->energy);
        curr = curr->next;
    }
}
void print_list_energy_cells(cell * head){
    cell *curr = head;
    while (curr != NULL) {
        printf("%s : %d\n", curr->name,curr->energy);
        curr = curr->next;
    }
}
int find_index_hamsaye(int index,int size, char mode[size],int n){
    int res;
    int a=(int)ceil(log2(n));
    if (mode[index-n] != 'f' && mode[index-n]!= 'c')
        res=index-n;
    else if (mode[index+n] != 'f' && mode[index+n]!= 'c')
        res=index+n;
    else if (mode[index-a] != 'f' && mode[index-a] != 'c')
        res=index-a;
    else if(mode[index+a] != 'f' && mode[index+a] != 'c')
        res=index-a;

    return res;
}
cell * change_energy(cell * head,int index){
    cell * curr=head ;
    while ( curr !=NULL){
        if ( curr->shomare_khoone==index)
            break;
        curr=curr->next;
    }
    curr->energy=40;
    return head;
}
int check_split(cell* head,int index){
    cell * curr=head;
    while(1){
        if(curr->shomare_khoone==index)
            break;
        curr=curr->next;
    }
    if(curr->energy>10)
        return 1;
    else
        return 0;
}
int check_jump(cell* head,int index){
    cell * curr=head;
    while(1){
        if(curr->shomare_khoone==index)
            break;
        curr=curr->next;
    }
    if(curr->energy>=30)
        return 1;
    else
        return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct user {
    char login[MAX_SIZE];
    char password[MAX_SIZE];
    int access_student;
    int access_book;
}users;

typedef struct students {
    char recordbook[MAX_SIZE];
    char surname[MAX_SIZE];
    char name[MAX_SIZE];
    char faculty[MAX_SIZE];
    char specialty[MAX_SIZE];
}students;

typedef struct books {
    char ISBN[20];
    char author[MAX_SIZE];
    char bookname[MAX_SIZE];
    int number;
    int access;
}books;

typedef struct student_book {
    char ISBN[20];
    char recordbook[MAX_SIZE];
    char data[20];
}student_book;

int check_login();
int compare(char a[], char b[]);
void check_user();
void view_student();
void view_book();
void view_data();

void student();
int search_student();
void add_newstudent();
void delete_student();
void edit_student();
void view_information();

void book();
int search_book();
void add_newbook();
void delete_book();
void edit_book();
void change_number();

int main() {
    int n;
    fflush(stdin);
    n = check_login();
    if(n == 1) {
        check_user();
    }
    else {
        printf("Login or password incorrect!");
    }
}

int compare(char a[], char b[]) {
    int n = 0;
    do {
        if(a[n] > b[n])
            return 1;
        else if(a[n] < b[n])
            return -1;
        n++;
    } while((a[n] != '\0') || (b[n] != '\0'));
    return 0;
}

int search() {
    char record[MAX_SIZE];
    FILE *f = fopen("student_book.csv","r+");
    student_book sb;
    int out = 0;
    fflush(stdin);
    gets(record);

    while( !feof(f) ) {
        fscanf(f, "%[^,], %[^,], %s \n", sb.ISBN, sb.recordbook, sb.data );
        if( compare(sb.ISBN,record) == 0 || compare(sb.recordbook,record) == 0 )
            out = 1;
    }
    return out;
}

int curpos;
int check_login(){
    FILE *f;
    f = fopen("users.csv", "r+");
    users user[MAX_SIZE];
    char log[MAX_SIZE], pass[MAX_SIZE];
    int i = 0;
    fflush(stdin);
    printf("\t\t\tLOGIN AND PASSWORD");
    printf("\n\n\t\t\tLogin: ");
    gets(log);
    printf("\n\t\t\tPassword: ");
    gets(pass);
    while( !feof(f) ) {
        fscanf(f, "%[^,], %[^,], %d, %d\n", user[i].login, user[i].password, &user[i].access_student, &user[i].access_book);
        if((compare(user[i].login,log) == 0) && (compare(user[i].password,pass) == 0)) {
            curpos = i;
            fclose(f);
            return 1;
        }
        i++;
    }
    fclose(f);
    curpos = i;
    return 0;
}

void check_user() {
    int select;
    int i = curpos;
    int j = 0;
    users user[MAX_SIZE];
    fflush(stdin);
    FILE *f = fopen("users.csv", "r");
    while( !feof(f) ) {
        fscanf(f, "%[^,], %[^,], %d, %d\n", user[j].login, user[j].password, &user[j].access_student, &user[j].access_book);
        j++;
    }
    if( (user[i].access_student == 0) && (user[i].access_book == 1)) {
        book();
    }
    else if((user[i].access_student == 1) && (user[i].access_book == 0)) {
        student();
    }
    else if ((user[i].access_student == 1) && (user[i].access_book == 1)) {
        printf("\t\t*____Menu____*\n\n");
        printf("\t1. Student\n");
        printf("\t2. Book");
        printf("\nChoose: ");
        scanf("%d", &select);
        switch (select) {
            case 1: {
                student();
                break;
            }
            case 2: {
                book();
                break;
            }
            default:
                printf("\nError!");
        }
    }
    fclose(f);
}

void student() {
    FILE *fl;
    Here:
    fl = fopen("students.csv","a+");
    int select;
    printf ("\nLIBRARY STUDENTS\n");
    printf ("\n1.Add");
    printf ("\n2.Delete");
    printf ("\n3.Edit");
    printf ("\n4.View");
    printf ("\n5.View student's book(s)");
    printf ("\n6.View data");
    printf ("\n7.Complete\n");
    printf ("\nChoose: ");
    scanf ("%d", &select);
    switch(select) {
        case 1: {
            int i;
            Here2:
            printf("\nEnter number of the record book: ");
            i = search_student();
            if(i == 0) {
                add_newstudent();
            }
            else {
                printf("Number of the record book existed!");
                goto Here2;
            }
            goto Here;
        }
        case 2: {
            printf("\nEnter the number of a record book: ");
            int i = search();
            if(i==0) {
                delete_student();
            }
            else if(i==1) {
                printf("Can't delete!\n\n");
                goto Here;
            }
            goto Here;
        }
        case 3: {
            edit_student();
            goto Here;
        }
        case 4: {
            view_information();
            goto Here;
        }
        case 5: {
            view_student();
            goto Here;
        }
        case 6: {
            view_data();
            goto Here;
        }
        default: {
            //check_login();
        }
    }
    fclose(fl);
}

int search_student() {
    FILE *f;
    char record[MAX_SIZE];
    f = fopen("students.csv","r+");
    students sb;
    int out = 0;
    fflush(stdin);
    gets(record);

    while( !feof(f) ) {
        fscanf(f, "%[^,], %[^,], %[^,], %[^,], %s \n", sb.recordbook, sb.surname, sb.name, sb.faculty, sb.specialty);
        if(compare(sb.recordbook,record) == 0)
            out = 1;
    }
    if(out == 1)
        return 1;
    else return out;
}

void add_newstudent() {
    students sb;
    fflush(stdin);

    printf("\nNumber of the record book: ");
    gets(sb.recordbook);
    printf("\nSurname: ");
    gets(sb.surname);
    printf("\nName: ");
    gets(sb.name);
    printf("\nFaculty: ");
    gets(sb.faculty);
    printf("\nSpecialty: ");
    gets(sb.specialty);

    FILE *f = fopen("students.csv","a+");
    fprintf(f,"%s, %s, %s, %s, %s\n", sb.recordbook, sb.surname, sb.name, sb.faculty, sb.specialty);
    printf("\n");
    fclose(f);
    printf("\nStudent have been added!\n");
}

void delete_student() {
    int total;
    int i = 0;
    students sb[MAX_SIZE];
    fflush(stdin);
    char record[MAX_SIZE];
    printf("\nEnter the number of the record book to be deleted: ");
    gets(record);

    FILE *f;
    f = fopen("students.csv", "a+");
    while(!feof(f)) {
        fscanf(f, "%[^,], %[^,], %[^,], %[^,], %s\n" , sb[i].recordbook, sb[i].surname, sb[i].name, sb[i].faculty, sb[i].specialty);
        i++;
    }
    total = i;
    fclose(f);

    f = fopen("students.csv", "w");
    for(i = 0; i < total; i++) {
        if(compare(record, sb[i].recordbook) != 0) {
            fprintf(f,"%s, %s, %s, %s, %s\n",sb[i].recordbook, sb[i].surname, sb[i].name, sb[i].faculty, sb[i].specialty);
        }
    }
    fclose(f);
    printf("\nDeleted from the library!\n");
}

void edit_student() {
    int total;
    int i = 0;
    students sb[MAX_SIZE];
    char record[MAX_SIZE];
    fflush(stdin);
    printf("\nEnter the number of the record book need editing: ");
    gets(record);

    FILE *f;
    f = fopen("students.csv", "a+");
    while(!feof(f)) {
        fscanf(f, "%[^,], %[^,], %[^,], %[^,], %s\n", sb[i].recordbook, sb[i].surname, sb[i].name, sb[i].faculty, sb[i].specialty);
        i++;
    }
    total = i;
    fclose(f);

    f = fopen("students.csv", "w");
    for(i = 0; i < total; i++) {
        if(compare(record, sb[i].recordbook) != 0) {
            fprintf(f,"%s, %s, %s, %s, %s\n", sb[i].recordbook, sb[i].surname, sb[i].name, sb[i].faculty, sb[i].specialty);
        }
        else if(compare(record, sb[i].recordbook) == 0) {
            printf("%15s %15s %15s %15s %20s \n", sb[i].recordbook, sb[i].surname, sb[i].name, sb[i].faculty, sb[i].specialty);
            char new_faculty[MAX_SIZE];
            char new_specialty[MAX_SIZE];
            fflush(stdin);
            printf("\nNew faculty: ");
            gets(new_faculty);
            printf("\nNew specialty: ");
            gets(new_specialty);
            fprintf(f,"%s, %s, %s, %s, %s\n", sb[i].recordbook, sb[i].surname, sb[i].name, new_faculty, new_specialty);
        }
    }
    fclose(f);
    printf("\nStudent have been edited!\n");
}

void view_information() {
    char record[MAX_SIZE];
    FILE *f = fopen("students.csv","r+");
    students sb;
    fflush(stdin);
    printf("\nEnter the number of the record book want to view: ");
    gets(record);
    while(!feof(f)) {
        fscanf(f, "%[^,], %[^,], %[^,], %[^,], %s\n", sb.recordbook, sb.surname, sb.name, sb.faculty, sb.specialty);
        if(compare(record, sb.recordbook) == 0) {
            printf("INFORMATION\n");
            printf("Record book: %s",sb.recordbook);
            printf("\nSurname: %s",sb.surname);
            printf("\nName: %s",sb.name);
            printf("\nFaculty: %s",sb.faculty);
            printf("\nSpecialty: %s\n",sb.specialty);
        }
    }
    fclose(f);
}

void book() {
    FILE *f;
    Here:
    f = fopen("books.csv","a+");
    int select;
    printf ("\nLIBRARY BOOKS\n");
    printf ("\n1.Add");
    printf ("\n2.Delete");
    printf ("\n3.Edit");
    printf ("\n4.Change");
    printf ("\n5.View which book(s) student have");
    printf ("\n6.View data");
    printf ("\n7.Complete\n");
    printf ("\nChoose: ");
    scanf ("%d", &select);

    switch(select) {
        case 1: {
            int i;
            Here2:
            printf("\nEnter number ISBN: ");
            i = search_book();
            if(i == 0) {
                add_newbook();
            }
            else {
                printf("Number ISBN existed!");
                goto Here2;
            }
            goto Here;
        }
        case 2: {
            int i;
            printf("\nEnter the number ISBN: ");
            i = search();
            if(i==0) {
                delete_book();
            }
            else if(i==1) {
                printf("Can't delete!\n\n");
                goto Here;
            }
            goto Here;
        }
        case 3: {
            edit_book();
            goto Here;
        }
        case 4: {
            change_number();
            goto Here;
        }
        case 5: {
            view_book();
            goto Here;
        }
        case 6: {
            view_data();
            goto Here;
        }
        default: {
            //check_login();
        }
    }
    fclose(f);
}

int search_book() {
    FILE *f;
    char record[MAX_SIZE];
    f = fopen("books.csv","rb");
    books bk;
    int out = 0;
    fflush(stdin);
    gets(record);
    while( !feof(f) ) {
        fscanf(f, "%[^,], %[^,], %[^,], %d, %d\n", bk.ISBN, bk.author, bk.bookname, &bk.number, &bk.access);
        if(compare(bk.ISBN,record) == 0)
            out = 1;
    }
    if(out == 1)
        return 1;
    else return out;
}

void add_newbook() {
    books bk;
    fflush(stdin);

    printf("\nISBN: ");
    gets(bk.ISBN);
    printf("\nAuthor: ");
    gets(bk.author);
    printf("\nBooks name: ");
    gets(bk.bookname);
    printf("\nNumber of book: ");
    scanf("%d",&bk.number);
    printf("\nNumber of access: ");
    scanf("%d",&bk.access);

    FILE *f = fopen("books.csv","a+");
    fprintf(f,"%s, %s, %s, %d, %d \n",bk.ISBN, bk.author, bk.bookname, bk.number, bk.access);
    fclose(f);
    printf("\nThe book have been added!\n");
}

void delete_book() {
    int total;
    int i = 0;
    books bk[MAX_SIZE];
    fflush(stdin);
    char record[MAX_SIZE];
    printf("\nEnter the ISBN numbers of the books to be deleted: ");
    gets(record);

    FILE *f;
    f = fopen("books.csv", "a+");
    while(!feof(f)) {
        fscanf(f, "%[^,], %[^,], %[^,], %d , %d \n" , bk[i].ISBN, bk[i].author, bk[i].bookname, &bk[i].number, &bk[i].access);
        i++;
    }
    total = i;
    fclose(f);

    f = fopen("books.csv", "w");
    for(i = 0; i < total; i++) {
        if(compare(record, bk[i].ISBN) != 0) {
            fprintf(f,"%s, %s, %s, %d, %d\n", bk[i].ISBN, bk[i].author, bk[i].bookname, bk[i].number, bk[i].access);
        }
    }
    fclose(f);
    printf("\nDeleted from the library!\n");
}

void edit_book() {
    fflush(stdin);
    int total;
    int i = 0;
    books bk[MAX_SIZE];
    char record[MAX_SIZE];
    printf("\nEnter the ISBN numbers of the books that need editing: ");
    gets(record);

    FILE *f;
    f = fopen("books.csv", "a+");
    while(!feof(f)) {
        fscanf(f, "%[^,], %[^,], %[^,], %d , %d \n" , bk[i].ISBN, bk[i].author, bk[i].bookname, &bk[i].number, &bk[i].access);
        i++;
    }
    total = i;
    fclose(f);

    f = fopen("books.csv", "w");
    for(i = 0; i < total; i++) {
        if(compare(record, bk[i].ISBN)!= 0) {
            fprintf(f,"%s, %s, %s, %d, %d\n", bk[i].ISBN, bk[i].author, bk[i].bookname, bk[i].number, bk[i].access);
        }
        else if(compare(record, bk[i].ISBN) == 0) {
            printf("%15s %20s %20s %5d %5d\n", bk[i].ISBN, bk[i].author, bk[i].bookname, bk[i].number, bk[i].access);
            char new_author[MAX_SIZE];
            char new_bookname[MAX_SIZE];
            fflush(stdin);
            printf("\nNew author: ");
            gets(new_author);
            printf("\nNew books name: ");
            gets(new_bookname);
            fprintf(f,"%s, %s, %s, %d, %d\n", bk[i].ISBN, new_author, new_bookname, bk[i].number, bk[i].access);
        }
    }
    fclose(f);
    printf("\nThe book have been edited!\n");
}

void change_number() {
    fflush(stdin);
    int total;
    int i = 0;
    books sb[MAX_SIZE];
    char record[MAX_SIZE];
    printf("\nEnter the ISBN numbers of the books that need editing: ");
    gets(record);
    FILE *f;

    f = fopen("books.csv", "a+");
    while(!feof(f)){
        fscanf(f, "%[^,], %[^,], %[^,], %d , %d \n" , sb[i].ISBN, sb[i].author, sb[i].bookname, &sb[i].number, &sb[i].access);
        i++;
    }
    total = i;
    fclose(f);

    f = fopen("books.csv", "w");
    for(i = 0; i < total; i++){
        if(compare(record, sb[i].ISBN)!=0) {
            fprintf(f,"%s, %s, %s, %d, %d\n", sb[i].ISBN, sb[i].author, sb[i].bookname, sb[i].number, sb[i].access);
        }
        else if(compare(record,sb[i].ISBN) == 0) {
            printf("%15s %20s %20s %5d %5d\n", sb[i].ISBN, sb[i].author, sb[i].bookname, sb[i].number, sb[i].access);
            int new_number;
            fflush(stdin);
            printf("\nNew number of the book: ");
            scanf("%d",&new_number);
            int new_access=sb[i].access+new_number-sb[i].number;
            fprintf(f,"%s, %s, %s, %d, %d\n", sb[i].ISBN, sb[i].author, sb[i].bookname, new_number, new_access);
        }
    }
    fclose(f);
    printf("\nNumber of the book have been changed!\n");
}

void view_student() {
    char record[MAX_SIZE];
    FILE *f = fopen("student_book.csv","r+");
    student_book sb;
    students stud;
    fflush(stdin);
    printf("\nEnter the number ISBN:  ");
    gets(record);
    while( !feof(f) ) {
        fscanf(f, "%[^,], %[^,], %s\n", sb.ISBN, sb.recordbook, sb.data);
        if(compare(record, sb.ISBN) == 0) {
            FILE *f1 = fopen("students.csv","r+");
            fflush(stdin);
            while( !feof(f1) ) {
                fscanf(f1, "%[^,], %[^,], %[^,], %[^,], %s \n", stud.recordbook, stud.surname, stud.name, stud.faculty, stud.specialty);
                fflush(stdin);
                if(compare(stud.recordbook, sb.recordbook) == 0) {
                    printf("\nINFORMATION");
                    printf("\nRecord book: %s",stud.recordbook);
                    printf("\nSurname: %s",stud.surname);
                    printf("\nName: %s",stud.name);
                    printf("\nFaculty: %s",stud.faculty);
                    printf("\nSpecialty: %s",stud.specialty);
                    printf("\nData: %s\n\n",sb.data);
                }
            }
            fclose(f1);
        }
    }
    fclose(f);
}

void view_book() {
    char record[MAX_SIZE];
    FILE *f = fopen("student_book.csv","r+");
    student_book sb;
    books book;
    fflush(stdin);

    printf("\nEnter the number of a record book:  ");
    gets(record);
    while( !feof(f) ) {
        fscanf(f, "%[^,], %[^,], %s\n", sb.ISBN, sb.recordbook, sb.data);
        if(compare(record, sb.recordbook) == 0) {
            FILE *f1 = fopen("books.csv","r+");
            while( !feof(f1) ) {
                fscanf(f1, "%[^,], %[^,], %[^,], %d, %d\n", book.ISBN, book.author, book.bookname, &book.number, &book.access);
                if(compare(sb.ISBN, book.ISBN) == 0) {
                    printf("\nINFORMATION\n");
                    printf("ISBN: %s",book.ISBN);
                    printf("\nAuthor: %s",book.author);
                    printf("\nBook name: %s",book.bookname);
                    printf("\nNumber: %d",book.number);
                    printf("\nAccess: %d",book.access);
                    printf("\nData: %s\n\n",sb.data);
                }
            }
            fclose(f1);
        }
    }
    fclose(f);
}

void view_data() {
    char record[MAX_SIZE];
    student_book sb;
    fflush(stdin);

    printf("\nData: ");
    gets(record);
    FILE *f = fopen("student_book.csv","r");
    while( !feof(f) ) {
        fscanf(f, "%[^,], %[^,], %s\n", sb.ISBN, sb.recordbook, sb.data);
        if(compare(record, sb.data) == 0) {
            printf("\nISBN: %s",sb.ISBN);
            printf("\nNumber of the record book: %s",sb.recordbook);
            printf("\n");
        }
    }
    fclose(f);
}

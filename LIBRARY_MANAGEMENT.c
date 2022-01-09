// LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>


COORD coord = {0, 0};
void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


//FUNCTION PROTOTYPE
void mainmenu();
int add_books(void);

void editbooks(void);

int viewbooks();

int password();
void get_password(char *);


// USER DEFINED DATA TYPE
struct BOOK
{
    int bookid;
    char bookname[30];
    char authorname[30];
    char issued_to[30];
    int rack;
    int price;
    int quantity;
};

struct BOOK book;



//FUNCTION FOR VIEWING ALL BOOK PRESENT IN LIBARARY
int viewbooks()
{
    FILE *ptr;
    ptr = fopen("book.dat", "r+");
    int j = 4;
    system("cls");
    struct BOOK input1;
    printf("\t\t\t************************** BOOKS PRESENT IN LIBRARY **************************\n");

    gotoxy(0, 2);
    printf("BOOK ID");
    gotoxy(10, 2);
    printf("BOOK NAME");
    gotoxy(40, 2);
    printf("BOOK AUTHOR");
    gotoxy(70, 2);
    printf("BOOK PRICE");
    gotoxy(90, 2);
    printf("BOOK QUANTITY");
    gotoxy(110, 2);
    printf("RACK NO");

    while (fread(&input1, sizeof(struct BOOK), 1, ptr))
    {

        gotoxy(0, j);
        printf("%d", input1.bookid);
        gotoxy(10, j);
        printf("%s", input1.bookname);
        gotoxy(40, j);
        printf("%s", input1.authorname);
        gotoxy(70, j);
        printf("%d Rs/-", input1.price);
        gotoxy(90, j);
        printf("%d N", input1.quantity);
        gotoxy(110, j);
        printf("%d", input1.rack);

        printf("\n\n");
        j++;
    }
    fclose(ptr);
     gotoxy(40, ++j);
    printf("Press any key to return to MENU");
    getch();
    mainmenu();
}


//FUNCTION FOR SEARCH BOOK BY ID
void searchByID()
{
    system("cls");
    int id;
    FILE *fp;
    gotoxy(25, 4);
    printf("****Search Books By Id****");
    gotoxy(20, 5);
    printf("Enter the book id:");
    scanf("%d", &id);
    int findBook = 0;
    fp = fopen("book.dat", "rb");
    while (fread(&book, sizeof(book), 1, fp) == 1)
    {
        if (book.bookid == id)
        {
            Sleep(2);
            gotoxy(20, 7);
            printf("The Book is available");
            gotoxy(20, 8);

            gotoxy(20, 9);
            printf(" ID:%d", book.bookid);
            gotoxy(20, 10);
            printf(" Name:%s", book.bookname);
            gotoxy(20, 11);
            printf(" Author:%s ", book.authorname);
            gotoxy(20, 12);
            printf(" Qantity:%d ", book.quantity);
            gotoxy(20, 13);
            printf(" Price:Rs.%d", book.price);
            gotoxy(20, 14);
            printf(" Rack No:%d ", book.rack);

            findBook = 1;
        }
    }
    if (findBook == 0)
    {

        gotoxy(22, 9);
        printf("\aNo Record Found");
    }
    fclose(fp);
    gotoxy(20, 17);
    printf("Try another search?(Y/N)");
    if (getch() == 'y')
        searchByID();
    else
        mainmenu();
}


//FUNCTION FOR SEARCH BOOK BY NAME
void searchByName()
{
    system("cls");
    char s[15];
    int d = 0;
    FILE *fp;
    gotoxy(25, 4);
    printf("****Search Books By Name****");

    gotoxy(20, 5);
    printf("Enter Book Name:");
    scanf("%s", s);
    fp = fopen("book.dat", "rb");
    while (fread(&book, sizeof(book), 1, fp) == 1)
    {
        if (strcmp(book.bookname, (s)) == 0)
        {
            gotoxy(20, 7);
            printf("The Book is available");

            gotoxy(20, 9);
            printf(" ID:%d", book.bookid);
            gotoxy(20, 10);
            printf(" Name:%s", book.bookname);
            gotoxy(20, 11);
            printf(" Author:%s", book.authorname);
            gotoxy(20, 12);
            printf(" Qantity:%d", book.quantity);
            gotoxy(20, 13);
            printf(" Price:Rs.%.2f", book.price);
            gotoxy(20, 14);
            printf(" Rack No:%d ", book.rack);

            d++;
        }
    }
    if (d == 0)
    {

        gotoxy(22, 9);
        printf("\aNo Record Found");
    }
    fclose(fp);
    gotoxy(20, 17);
    printf("Try another search?(Y/N)");
    if (getch() == 'y')
        searchByName();
    else
        mainmenu();
}


//FUNCTION FOR SEARCH BOOK DETAILS
void searchbooks()
{
    system("cls");
    printf("*****************************Search Books*********************************");
    gotoxy(20, 10);
    printf("\xDB\xDB\xDB\xB2 1. Search By ID");
    gotoxy(20, 14);
    printf("\xDB\xDB\xDB\xB2 2. Search By Name");
    gotoxy(15, 20);
    printf("Enter Your Choice");
    switch (getch())
    {
    case '1':
        searchByID();
        break;
        break;
    case '2':
        searchByName();
        break;
    default:
        getch();
        searchbooks();
    }
}


//FUNCTION FOR EDIT BOOK DETAILS
void editbooks(void) 
{
    system("cls");
    FILE *fp;
    int c = 0, d;
    gotoxy(20, 4);
    printf("****Edit Books Section****");
    char another = 'y';
    while (another == 'y')
    {
        system("cls");
        gotoxy(15, 6);
        printf("Enter Book Id to be edited:");
        scanf("%d", &d);
        fp = fopen("book.dat", "rb+");

        while (fread(&book, sizeof(book), 1, fp) == 1)
        {
            if (book.bookid == d)

            {
                gotoxy(15, 7);
                printf("The book is availble");
                gotoxy(15, 8);
                printf("The Book ID:%d", book.bookid);
                gotoxy(15, 9);
                printf("Enter new name:");
                scanf("\n");
                scanf("%[^'\n']s", book.bookname);
                // scanf("%s",book.bookname);
                gotoxy(15, 10);
                printf("Enter new Author:");
                scanf("\n");
                scanf("%[^'\n']s", book.authorname);
                // scanf("%s",book.authorname);
                gotoxy(15, 11);
                printf("Enter new quantity:");
                scanf("%d", &book.quantity);
                gotoxy(15, 12);
                printf("Enter new price:");
                scanf("%d", &book.price);
                gotoxy(15, 13);
                printf("Enter new rackno:");
                scanf("%d", &book.rack);
                gotoxy(15, 14);
                printf("The record is modified");
                fseek(fp, ftell(fp) - sizeof(book), 0);
                fwrite(&book, sizeof(book), 1, fp);
                fclose(fp);
                c = 1;
            }
            if (c == 0)
            {
                gotoxy(15, 9);
                printf("No record found");
            }
        }
        gotoxy(15, 16);
        printf("Modify another Record?(Y/N)");
        fflush(stdin);
        another = getch();
    }
    mainmenu();
}
void renameing()
{
    remove("book.dat");
    char old[] = "test.dat";
    char new[] = "book.dat";
    rename(old, new);
}


//FUNCTION FOR DELEATING DATA
void deletebooks()
{ 
    FILE *ft, *fp;
    system("cls");
    int d, findBook = 0;
    char another = 'y';
    while (another == 'y')
    {
        system("cls");
        gotoxy(10, 5);
        printf("Enter the Book ID to  delete:");
        scanf("%d", &d);
        fp = fopen("book.dat", "rb+");
        while (fread(&book, sizeof(book), 1, fp) == 1)
        {
            if (book.bookid == d)
            {
                gotoxy(10, 7);
                printf("The book record is available");
                gotoxy(10, 8);
                printf("Book name is %s", book.bookname);
                gotoxy(10, 9);
                printf("Rack No. is %d", book.rack);
                findBook = 1;
                gotoxy(10, 10);
                printf("Do you want to delete it?(Y/N):");
                if (getch() == 'y')
                {
                    ft = fopen("test.dat", "wb"); 
                    rewind(fp);
                    while (fread(&book, sizeof(book), 1, fp) == 1)
                    {
                        if (book.bookid != d)
                        {
                            fwrite(&book, sizeof(book), 1, ft); 
                        }                                      
                    }
                    fclose(fp);
                    fclose(ft);
                  
                    gotoxy(10, 11);
                    printf("The record is sucessfully deleted");
                }
            }
        }
        if (findBook == 0)
        {
            gotoxy(10, 10);
            printf("No record is found");
            getch();
        }
        gotoxy(10, 12);
        printf("Delete another record?(Y/N)");
        fflush(stdin);
        another = getch();
    }
}


//MAIN MENU FUNCTION
void mainmenu()
{
    while (1)
    {
        system("cls");
        gotoxy(20, 3);
        printf("**************************************** MAIN MENU ****************************************");
        gotoxy(20, 5);
        printf("\xDB\xDB\xDB\xDB\xB2 1. Add Books   ");
        gotoxy(20, 7);
        printf("\xDB\xDB\xDB\xDB\xB2 2. Delete Book");
        gotoxy(20, 9);
        printf("\xDB\xDB\xDB\xDB\xB2 3. Search Book");
        gotoxy(20, 11);
        printf("\xDB\xDB\xDB\xDB\xB2 4. View Book List");
        gotoxy(20, 13);
        printf("\xDB\xDB\xDB\xDB\xB2 5. Edit Book Record ");
        gotoxy(20, 15);
      printf("\xDB\xDB\xDB\xDB\xB2 6. Close Application");
      
       
        gotoxy(20, 17);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(20, 21);
        printf("Enter your choice:");
        switch (getch())
        {
        case '1':
            system("cls");
            add_books();
            break;
        case '2':
            deletebooks();
              remove("book.dat");
    char old[] = "test.dat";
    char new[] = "book.dat";
    rename(old, new);
            break;
        case '3':
            searchbooks();
            break;
        case '4':
            viewbooks();
            break;
        case '5':
            editbooks();
            break;
       
        case '6':

            system("cls");
            gotoxy(16, 3);
            printf("Programmer.... \n");
            gotoxy(16, 5);
            printf("DEEPAK SHARMA\n");
            gotoxy(16, 7);
            printf("Department of Computer science Enginnering \n");
            gotoxy(16, 8);
            printf("ADGITM, DELHI \n");
            exit(0);
        default:
            gotoxy(10, 23);
            printf("\aWrong Entry!!Please re-entered correct option");
            getch();
        }
    }
}


//FUNCTION FOR LOGIN USING PASSWORD
int password(char *array, FILE *ptr)
{

    char pass[20],c;

    int d = 0,j=0;
    printf("ENTER PASSWORD:\t");
   
      while( (c=getch())!= 13){//takes input till user press
        pass[j] = c;
        printf("*");
        j++;
    }
    for (int i = 0; i < strlen(array); i++)
    {
        if (array[i] != pass[i])
            d = 1;
    }

    if (d == 0)
    {
        printf("\nCORRECT PASSWORD.....\nYOU CAN PROCEED...\n");
        printf("Press any key");
        getch();
        return 1;
    }
    else
    {
        printf("\nWRONG PASSSWORD,... PLEASE RENTER YOU PASSWORD.\n");
        return 0;
    }
}
//FUNCTION TO ADD BOOKS
int add_books()
{

    FILE *ptr;
    ptr = fopen("book.dat", "a+");

    printf("ENTER BOOK ID       :     \t");
    scanf("%d", &book.bookid);
    printf("ENTER BOOK NAME     :    \t");

    scanf("\n");
    scanf("%[^'\n']s", book.bookname);

    printf("ENTER AUTHOR NAME   :  \t\t");

    scanf("\n");
    scanf("%[^'\n']s", book.authorname);
    printf("ENTER RACK NO.      :     \t");
    scanf("%d", &book.rack);
    printf("ENTER BOOK PRICE    :    \t");
    scanf("%d", &book.price);
    printf("ENTER BOOK QUANTITY :  \t\t");
    scanf("%d", &book.quantity);

    fseek(ptr, 0, SEEK_END);
    fwrite(&book, sizeof(book), 1, ptr);

    fclose(ptr);
    if (fwrite != 0)

    {
        printf("The record is sucessfully saved\n");
        printf("Save any more?(Y / N):");
        if (getch() == 'n')
            mainmenu();
        else
        {
            system("cls");
            add_books();
        }
        return 1;
    }
    else
    {
        printf("The record not saved");
        return 0;
    }
}

// DRIVER FUNCTION
int main()
{
    struct BOOK *book;
    int d;
    char arr[20];
    system("cls");
    FILE *fp = fopen("password.txt", "r");
    if (fp == NULL)
    { 
         fclose(fp);
        FILE *fp = fopen("password.txt", "w");
        printf("NEW USER PLEASE, CREATE A STRONG PASSWORD:\t");
        scanf("%s", arr);
        fprintf(fp, "%s", arr);
         fclose(fp);

    }
    else
    {
        fscanf(fp, "%s", &arr);
        do
        {
            d = password(arr, fp);

        } while (d != 1);
    }
   
    mainmenu();

    return 0;
}

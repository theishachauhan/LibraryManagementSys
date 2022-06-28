#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_YR  9999
#define MIN_YR  1900
#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20
#define MAX_Language 15
#define MAX_Category_Type	20
#define MAX_ISBNcode 15
#define MAX_TITLE 100
#define MAX_PUBLISHER_NAME 50 
#define FILE_NAME  "BookS.bin"
#define MAX_BOOK_NAME   50
#define MAX_AUTHOR_NAME 50
#define MAX_LIBRARIAN_NAME 10
#define MAX_ADMIN_NAME 10
#define FILE_HEADER_SIZE  sizeof(sFileHeader)
//structure to store date
//defined various

char description[2048];
char publisherID[30];
int found;
int option;
int choice;

typedef struct
	{
	    int yyyy;
	    int mm;
	    int dd;
	} Date;


typedef struct	//user and password
	{
	    char libuser[MAX_SIZE_USER_NAME];
	    char libpass[MAX_SIZE_PASSWORD];
	    char adminuser[MAX_SIZE_USER_NAME];
	    char adminpass[MAX_SIZE_PASSWORD];
	} sFileHeader;


typedef struct	// to store data about books 
	{ 
	    char language[MAX_Language];
	    char category[MAX_Category_Type];
	    char ISBNCode[MAX_ISBNcode];
	    char publisherName[MAX_PUBLISHER_NAME];
	    char bookName[MAX_BOOK_NAME];	
	    char authorName[MAX_AUTHOR_NAME];		
	    Date bookIssueDate;
	} s_BooksInfo;

//main program functions

void centermsg(const char* message)
{
	    int l =0;  // length
	    int p = 0; // position
	    //calculate how many space need to print
	    l = (78 - strlen(message))/2;
	    printf("\t\t\t");
	    for(p = 0; p < l ; p++)
	    	printf(" ");
	    printf("%s",message);
}



void mainmsg(const char *message)
{
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    centermsg(message);
    printf("\n\t\t\t----------------------------------------------------------------------------\n\n");
}



void printMessageCenter(const char* message)
{
	    int len =0;
	    int pos = 0;
	    //calculate how many space need to print
	    len = (78 - strlen(message))/2;
	    printf("\t\t\t");
	    for(pos =0 ; pos < len ; pos++)
	    	printf(" ");
	    printf("%s",message);
}



void headMessage(const char *message)
{
    //system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############      Library management System Project in C       ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}



void welcomeMessage()
{
    char message[100]="Welcome Screen";
	headMessage(message);
    printf("\n\n");
    printf("\n\t\t\t  *-------------------------------------------------------------------------*\n");
    printf("\n\t\t\t  *-------------------------------------------------------------------------*\n");
    printf("\n\t\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t\t\t        =                   TO                      =");
    printf("\n\t\t\t\t\t        =                 LIBRARY                   =");
    printf("\n\t\t\t\t\t        =               MANAGEMENT                  =");
    printf("\n\t\t\t\t\t        =                 SYSTEM                    =");
    printf("\n\t\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  *-------------------------------------------------------------------------*\n");
    printf("\n\t\t\t  *-------------------------------------------------------------------------*\n");
    printf("\n\t\t\t  Final Year Project : GROUP A5\n");
    printf("\n\t\t\t Isha Singh Chauhan, Khushi Babbar, Kismat, Lavanya Soni");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
}



int isNameValid(const char *name)
{
    int validName = 1;
    int l = 0;
    int index = 0;
    l = strlen(name);
    for(; index < l ; ++index)
    {		//changing the space caution
        if(!(isalnum(name[index])) && (name[index] != '\n') && (name[index] != ' ') && (name[index] != '-'))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}



int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}



int isValidDate(Date *validDate) // returns 1 if given date is valid.
{
    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}



void searchTitle() 
{  
    char bookName[MAX_BOOK_NAME] = {0};
    s_BooksInfo addBookInfoInDataBase = {0};
	FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
				 	   if(fp == NULL)
				    {
				        printf("\n\t\t\tFile is not opened\n");
				        exit(1);
				    }
				    headMessage("SEARCHING BOOK BY TITLE");
    //put the control on books detail
				    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
				    {
				        fclose(fp);
				        printf("\n\t\t\tFacing issue while reading file\n");
				        exit(1);
				    }
     printf("\n\n\t\t\tEnter Book Name to search :\t");
    fflush(stdin);
    fgets(bookName,MAX_BOOK_NAME,stdin);
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        if(!strcmp(addBookInfoInDataBase.bookName,bookName))
        {
            found = 1;
            break;
        }
    }
    if(found)// IF VALUE of found is 1, it is considered true value , hence the if statement would work
    {
        printf("\t\t\tBook Name =\t %s\n",addBookInfoInDataBase.bookName);
        printf("\t\t\tAuthor Name =\t %s\n",addBookInfoInDataBase.authorName);
        printf("\t\t\tLanguage =\t %s\n",addBookInfoInDataBase.language);
		printf("\t\t\tISBN Code =\t %s\n",addBookInfoInDataBase.ISBNCode);
   }
    else
    {
        printf("\n\t\t\tNo Record Found");
    }
    fclose(fp);
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}



void searchISBN() // not sure of the retuen type
{
	char ISBNCode[MAX_ISBNcode] = {0};
    s_BooksInfo addBookInfoInDataBase = {0};
	FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
				 	   if(fp == NULL)
				    {
				        printf("\n\t\t\tFile is not opened\n");
				        exit(1);
				    }
				    headMessage("SEARCHING BOOK BY ISBN CODE");
    //put the control on books detail
				    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
				    {
				        fclose(fp);
				        printf("\n\t\t\tFacing issue while reading file\n");
				        exit(1);
				    }
     printf("\n\n\t\t\tEnter The Code to search : \t");
    fflush(stdin);
    fgets(ISBNCode,MAX_ISBNcode,stdin);
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {  // might have to make changes in this function :addBookInfoInDataBase: or make anew one
        if(!strcmp(addBookInfoInDataBase.ISBNCode, ISBNCode))
        {
            found = 1;
            break;
        }
    }
    if(found)// IF VALUE of found is 1, it is considered true value , hence the if statement would work
    {
        printf("\t\t\tBook Name =\t %s\n",addBookInfoInDataBase.bookName);
        printf("\t\t\tAuthor Name =\t %s\n",addBookInfoInDataBase.authorName);
        printf("\t\t\tLanguage =\t %s\n",addBookInfoInDataBase.language);
		printf("\t\t\tISBN Code =\t %s\n",addBookInfoInDataBase.ISBNCode);
	}
    else
    {
        printf("\n\t\t\tNo Such Record Found");
    }
    fclose(fp);
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}



void searchAuthor()// not sure of the retuen type
{
    char authorName[MAX_AUTHOR_NAME] = {0};	  
        s_BooksInfo addBookInfoInDataBase = {0};
	FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
				 	   if(fp == NULL)
				    {
				        printf("\n\t\t\tFile is not opened\n");
				        exit(1);
				    }
				    headMessage("SEARCHING BOOK BY AUTHOR NAME");
    //put the control on books detail
				    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
				    {
				        fclose(fp);
				        printf("\n\t\t\tFacing issue while reading file\n");
				        exit(1);
				    }
     printf("\n\n\t\t\tEnter the name of Author : \t");
    fflush(stdin);
    fgets(authorName,MAX_AUTHOR_NAME,stdin);
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {  // might have to make changes in this function :addBookInfoInDataBase: or make anew one
        if(!strcmp(addBookInfoInDataBase.authorName, authorName))
        {
            found = 1;
            break;
        }
    }
    if(found)// IF VALUE of found is 1, it is considered true value , hence the if statement would work
    {
        printf("\t\t\tBook Name =\t %s\n",addBookInfoInDataBase.bookName);
        printf("\t\t\tAuthor Name =\t %s\n",addBookInfoInDataBase.authorName);
        printf("\t\t\tLanguage =\t %s\n",addBookInfoInDataBase.language);
		printf("\t\t\tISBN Code =\t %s\n",addBookInfoInDataBase.ISBNCode);
    }
    else
    {
        printf("\n\t\t\tNo Record Found");
    }
    fclose(fp);
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}



void searchPublisher()// not sure of the retuen type
{
	char publisherName[MAX_PUBLISHER_NAME] = {0};	
	    s_BooksInfo addBookInfoInDataBase = {0};   
	FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
				 	   if(fp == NULL)
				    {
				        printf("\n\t\t\tFile is not opened\n");
				        exit(1);
				    }
				    headMessage("SEARCHING BOOK BY PUBLISHER");
    //put the control on books detail
				    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
				    {
				        fclose(fp);
				        printf("\n\t\t\tFacing issue while reading file\n");
				        exit(1);
				    }
     printf("\n\n\t\t\tEnter the nmae of Publisher : \t");
    fflush(stdin);
    fgets(publisherName,MAX_PUBLISHER_NAME,stdin);
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {  // might have to make changes in this function :addBookInfoInDataBase: or make anew one
        if(!strcmp(addBookInfoInDataBase.publisherName, publisherName))
        {
            found = 1;
            break;
        }
    }
    if(found)// IF VALUE of found is 1, it is considered true value , hence the if statement would work
    {
        printf("\t\t\tBook Name =\t %s\n",addBookInfoInDataBase.bookName);
        printf("\t\t\tAuthor Name =\t %s\n",addBookInfoInDataBase.authorName);
        printf("\t\t\tLanguage =\t %s\n",addBookInfoInDataBase.language);
		printf("\t\t\tISBN Code =\t %s\n",addBookInfoInDataBase.ISBNCode);
    }
    else
    {
        printf("\n\t\t\tNo Record Found");
    }
    fclose(fp);
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}



void searchCategory()// not sure of the retuen type
{
	char category[MAX_Category_Type] = {0};	   
	    s_BooksInfo addBookInfoInDataBase = {0};
	FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
				 	   if(fp == NULL)
				    {
				        printf("\n\t\t\tFile is not opened\n");
				        exit(1);
				    }
				    headMessage("SEARCHING BOOK BY CATEGORY");
    //put the control on books detail
				    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
				    {
				        fclose(fp);
				        printf("\n\t\t\tFacing issue while reading file\n");
				        exit(1);
				    }
     printf("\n\n\t\t\tEnter the category of book : \t");
    fflush(stdin);
    fgets(category,MAX_Category_Type,stdin);
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {  // might have to make changes in this function :addBookInfoInDataBase: or make anew one
        if(!strcmp(addBookInfoInDataBase.category, category))
        {
            found = 1;
            break;
        }
    }
    if(found)// IF VALUE of found is 1, it is considered true value , hence the if statement would work
    {
        printf("\t\t\tBook Name =\t %s\n",addBookInfoInDataBase.bookName);
        printf("\t\t\tAuthor Name =\t %s\n",addBookInfoInDataBase.authorName);
        printf("\t\t\tLanguage =\t %s\n",addBookInfoInDataBase.language);
		printf("\t\t\tISBN Code =\t %s\n",addBookInfoInDataBase.ISBNCode);
	}
    else
    {
        printf("\n\t\t\tNo Record Found");
    }
    fclose(fp);
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}
  
  
   
void searchLanguage()// not sure of the retuen type
{
	char language[MAX_Language] = {0};	   
	s_BooksInfo addBookInfoInDataBase = {0};
	FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
				 	   if(fp == NULL)
				    {
				        printf("\n\t\t\tFile is not opened\n");
				        exit(1);
				    }
				    headMessage("SEARCHING BOOK BY LANGUAGE");
    //put the control on books detail
				    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
				    {
				        fclose(fp);
				        printf("\n\t\t\tFacing issue while reading file\n");
				        exit(1);
				    }
     printf("\n\n\t\t\tEnter The Language of the book : \t");
    fflush(stdin);
    fgets(language,MAX_Language,stdin);
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {  // might have to make changes in this function :addBookInfoInDataBase: or make anew one
        if(!strcmp(addBookInfoInDataBase.language, language))
        {
            found = 1;
            break;
        }
    }
    if(found)// IF VALUE of found is 1, it is considered true value , hence the if statement would work
    {
        printf("\t\t\tBook Name =\t %s\n",addBookInfoInDataBase.bookName);
        printf("\t\t\tAuthor Name =\t %s\n",addBookInfoInDataBase.authorName);
        printf("\t\t\tLanguage =\t %s\n",addBookInfoInDataBase.language);
		printf("\t\t\tISBN Code =\t %s\n",addBookInfoInDataBase.ISBNCode);
    }
    else
    {
        printf("\n\t\t\tNo Record Found");
    }
    fclose(fp);
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}
    


void addInDataBase() // Add books in list
{
    int days;  //days ko store karne ka struct
    int status = 0; // structure type ka variable toh esmein saare ceeze hongi structure wali
    s_BooksInfo addBookInfoInDataBase = {0}; // variable i value is zero for now, we are going to fill in sll the other declared variables in the struct
    FILE *fp = NULL; // fp is a pointer
    
    fp = fopen(FILE_NAME,"ab+");   // file_name is already defined
    if(fp == NULL)					
    {
        printf("File is not opened\n");
        exit(1);
    }
    headMessage("ADD NEW BOOKS");
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
	printf("\n\t\t\tBook ISBN Code = ");
	fflush(stdin);
	gets(addBookInfoInDataBase.ISBNCode);
    do // make this valid comment for all the things mentioned
    {
        printf("\n\t\t\tBook Name  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.bookName,MAX_BOOK_NAME,stdin);
        status = isNameValid(addBookInfoInDataBase.bookName);
        if (!status)
        {
            printf("\n\t\t\tBook Name contains invalid character. Please enter again.");
        }
    }
    while(!status);	
    do
    {
        printf("\n\t\t\tAuthor Name  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.authorName,MAX_AUTHOR_NAME,stdin);
        status = isNameValid(addBookInfoInDataBase.authorName);
        if (!status)
        {
            printf("\n\t\t\tAuthor name contains invalid character. Please enter again.");
        }
    }
    while(!status);	
	printf("\n\t\t\tPublisher ID = ");
    fflush(stdin);
    gets(addBookInfoInDataBase.publisherName);
    do
    {
        printf("\n\t\t\tCategory of book  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.category,MAX_Category_Type,stdin);
        status = isNameValid(addBookInfoInDataBase.category);
        if (!status)
        {
            printf("\n\t\t\tCategory contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tLanguage  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.language,MAX_Language,stdin);
        status = isNameValid(addBookInfoInDataBase.language);
        if (!status)
        {
            printf("\n\t\t\tLanguage name contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        //get date year,month and day from user
        printf("\n\t\t\tEnter date in format (day/month/year): ");
        scanf("%d/%d/%d",&addBookInfoInDataBase.bookIssueDate.dd,&addBookInfoInDataBase.bookIssueDate.mm,&addBookInfoInDataBase.bookIssueDate.yyyy);
        //check date validity
        status = isValidDate(&addBookInfoInDataBase.bookIssueDate);
        if (!status)
        {
            printf("\n\t\t\tPlease enter a valid date.\n");
        }
    }
    while(!status);
    printf("\n\t\t\tDescription = ");
    fflush(stdin);
    scanf("%s",&description);
    //taking a global variable for desription, and calling it here without structure
    fwrite(&addBookInfoInDataBase,sizeof(addBookInfoInDataBase), 1, fp);
    fclose(fp);
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}



void searchBooks()
{
	found = 0;
	printf("\n\n\t\t\tSearch book by... choose one.\n\n\n");
	printf("\t\t\t1. ISBN code\n");
	printf("\t\t\t2. Title\n");
	printf("\t\t\t3. Name of Author\n");
	printf("\t\t\t4. Name of Publisher\n");
	printf("\t\t\t5. Category\n");
	printf("\t\t\t6. Language\n");
	printf("\t\t\t0. To exit\n");
	scanf("%d",&option);
	switch(option)
        {
        case 1:
            searchISBN();
            break;
        case 2:
            searchTitle();
            break;
        case 3:
            searchAuthor();
            break;
        case 4:
            searchPublisher();
            break;
        case 5:
            searchCategory();
            break;
		case 6:
            searchLanguage();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you !\n\n\n\n\n");
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }
}



void viewBooks()
{
    found = 0;
    char bookName[MAX_BOOK_NAME] = {0};
    s_BooksInfo addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    unsigned int countBook = 1;
    headMessage("VIEW BOOKS DETAILS");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("Facing issue while reading file\n");
        exit(1);
    }
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
		printf("\n\t\t\tBook Name = %s",addBookInfoInDataBase.bookName);
        printf("\n\t\t\tBook ISBN Code = %s",addBookInfoInDataBase.ISBNCode);
        printf("\n\t\t\tBook Author Name = %s",addBookInfoInDataBase.authorName);
        printf("\n\t\t\tBook Publisher Name = %s",addBookInfoInDataBase.publisherName);
        printf("\n\t\t\tBook Language = %s",addBookInfoInDataBase.language);
        printf("\n\t\t\tBook Category = %s",addBookInfoInDataBase.category);
        printf("\n\t\t\tBook Count = %d\n\n",countBook);
        found = 1;
        ++countBook;
    }
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNo Record");
    }
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}

	

void updateCredential(void)
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    char userName[MAX_SIZE_USER_NAME] = {0};
    char password[MAX_SIZE_PASSWORD] = {0};
    headMessage("Update Credentials");
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\t\t\tPress 1 to Update Credentials for Librarian\n");
    printf("\n\t\t\tPress 2 to Update Credentials for Admin\n");
    printf("\n\t\t\tPress 2 to Exit");
    printf("\n\n\n\t\t\tEnter choice => \t");
    scanf("%d",&choice);
        switch(choice)
        {
        case 1:
        	    printf("\n\n\t\t\tNew Username:\t");
			    fflush(stdin);
			    fgets(userName,MAX_SIZE_USER_NAME,stdin);
			    printf("\n\n\t\t\tNew Password:\t");
			    fflush(stdin);
			    fgets(password,MAX_SIZE_PASSWORD,stdin);
			    strncpy(fileHeaderInfo.libuser,userName,sizeof(userName));
			    strncpy(fileHeaderInfo.libpass,password,sizeof(password));
            break;
        case 2:
        	    printf("\n\n\t\t\tNew Username:");
			    fflush(stdin);
			    fgets(userName,MAX_SIZE_USER_NAME,stdin);
			    printf("\n\n\t\t\tNew Password:");
			    fflush(stdin);
			    fgets(password,MAX_SIZE_PASSWORD,stdin);
			    strncpy(fileHeaderInfo.adminuser,userName,sizeof(userName));
			    strncpy(fileHeaderInfo.adminpass,password,sizeof(password));
            break;
        case 0:
	            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
	            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    while(choice!=0);     
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("\n\t\t\tPassword has been changed successfully");
    printf("\n\t\t\ttLogin Again:");
    fflush(stdin);
    getchar();
    exit(1);
}


	
void LostBooks()  //lost books - to keep record of all the lost books
{
    found = 0;
    char booklost[15];
    sFileHeader fileHeaderInfo = {0};
    char bookName[MAX_BOOK_NAME] = {0};
    s_BooksInfo addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    int status = 0;
	headMessage("Lost Book Details");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");  //check this tmpFp = fopen("tmp","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    
    printf("\n\t\t\tEnter Book ISBN Code ");
    scanf("%s",&booklost);
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        if(addBookInfoInDataBase.ISBNCode != booklost)
        {
            fwrite(&addBookInfoInDataBase,sizeof(addBookInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\t\t\tRecord deleted successfully....."):printf("\n\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
}



void menulibrarian()
{
//add more options depening upon "how data to add"
    choice = 0;
    do
    {
        printf("\n\n\t logged in as Libraian\n\n");
		headMessage("MAIN MENU");
        printf("\n\n\n\t\t\t1.Add Books");
        printf("\n\t\t\t2.Search Books");
        printf("\n\t\t\t3.View Books");
        printf("\n\t\t\t4.Lost Book Entry");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
			addInDataBase();
            break;
        case 2:
            searchBooks();
            break;
        case 3:
           	viewBooks();
            break;
        case 4:
            LostBooks();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended
}



void menuadmin()
{
    int choice = 0;
    do
    {
        printf("\n\n\t logged in as Admin\n\n");
		headMessage("MAIN MENU");
        printf("\n\n\n\t\t\t1.View Books");
        printf("\n\t\t\t2.Search Books");
        printf("\n\t\t\t3.Update Credential");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
        	viewBooks();
            break;
        case 2:
            searchBooks();
            break;
        case 3:
            updateCredential();
            break;      
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended
}



int isFileExists(const char *path)
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // File exists hence close file
        fclose(fp);
    }
    return status;
}



void login()//add exit n all statements
{
    char userName[MAX_SIZE_USER_NAME] = {0}; //821	48	C:\Users\cisha\OneDrive\Documents\full.cpp	[Error] invalid conversion from 'unsigned char*' to 'char*' [-fpermissive]
    char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    int n;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("Login");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(userName,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
 if((!strcmp(userName,fileHeaderInfo.adminuser)) ^ (!strcmp(userName,fileHeaderInfo.libuser)))
        {
            n=strcmp(userName,fileHeaderInfo.adminuser);
			if(n==0)
			{
				n=strcmp(password,fileHeaderInfo.adminpass);// compare password
				if(n==0)
					menuadmin();
				else
					printf("\n\t\t\t\tLogin Failed! Password Incorrect\n\n");
					//exit(0);
            }
            else
				n = strcmp(password,fileHeaderInfo.libpass);// saved space
				if(n==0)
					menulibrarian();
				else
					printf("\n\t\t\t\tLogin Failed! Password Incorrect\n\n");
            }
        else
        {
            printf("n\t\t\t\tLogin Failed! Invalid Username\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\t\t\t\tSorry,Unknown User.");
        getch();
        system("cls");
    }
}



void init()
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultadminUser[] ="admin\n";
    const char defaultadminPass[] ="pass123\n";
    const char defaultlibUser[] ="library\n";
    const char defaultlibPass[] ="pass123\n";
    sFileHeader fileHeaderInfo = {0};
    status = isFileExists(FILE_NAME);
    if(!status)
    {
        //create the binary file
        fp = fopen(FILE_NAME,"wb");
        if(fp != NULL)
        {
            //Copy default password
            strncpy(fileHeaderInfo.adminpass,defaultadminPass,sizeof(defaultadminPass));
            strncpy(fileHeaderInfo.adminuser,defaultadminUser,sizeof(defaultadminUser));
            strncpy(fileHeaderInfo.libpass,defaultlibPass,sizeof(defaultlibPass));
            strncpy(fileHeaderInfo.libuser,defaultlibUser,sizeof(defaultlibUser));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}



int main()
{
	int ch;
    init();
    welcomeMessage();//we are in main menu now
    do
	{
		printf("\n\n\n\t\t\tPress 1 to Login");
    	printf("\n\t\t\tPress 2 to Search Books");
    	printf("\n\t\t\tPress 0 to Exit.");
    	printf("\n\t\t\tEntre Your Choice\t\t\t- ");
        scanf("%d",&ch);
	    switch(ch)
        {
        case 1:
        	login();
            break;
        case 2:
            searchBooks();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(ch!=0);
}
/*						End of Prog  						*/														

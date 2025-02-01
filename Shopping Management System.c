#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include <windows.h>
char pass[20]={"Hira123"};
struct items
{
	char no[5];
	char name[50];
	int stocks;
	int price;
}item_x,item[200];

struct customers
{
	int id;
	char name[50];
	char address[40];
	char mobile[50];
	char email[50];
}cst,cstm[100];

struct employee
{
	int ID,age,stars,customers;
	float salary;
    char name[15];
    char address[50];
    char designation[15];
}e[20],e_x;


int id,sales[200];

int manager();
void bill();
void sales_report(void);
void details(void);
void member(void);
void products(void);
void sub_stocks1(void);
void sub_stocks2(void);
void stocks_check(void);
void customer_check(void);
void emp_status(void);
void emp_data(void);
void employee_report(void);

void main(void)
{
	int choice,x,quit=0,i;
	system("COLOR F4");
	
	FILE *fptr1;
	fptr1=fopen("Items.bin","rb");
	for(i=0;i<20;i++)
	{
		fread(&item_x,sizeof(struct items),1,fptr1);
		strcpy(item[i].name,item_x.name);
		strcpy(item[i].no,item_x.no);
		item[i].stocks=item_x.stocks;
		item[i].price=item_x.price;
		sales[i]=item[i].stocks;
	}
	fclose(fptr1);
	
	
	FILE *fptr2;
	fptr2=fopen("Employees.bin","rb");
	for(i=0;i<10;i++)
	{
		fread(&e_x,sizeof(struct employee),1,fptr2);
		e[i].ID=e_x.ID;
		e[i].age=e_x.age;
		e[i].customers=e_x.customers;
		e[i].stars=e_x.stars;
		e[i].salary=e_x.salary;
		strcpy(e[i].address,e_x.address);
		strcpy(e[i].designation,e_x.designation);
		strcpy(e[i].name,e_x.name);
	}
	fclose(fptr2);
	
	printf("\t\t\t\tWELCOME\n\n");
	for(;;)
	{
		system("cls");
		printf("\tWhat would you like to do?\n1)BILLING\t\t2)MEMBERSHIP\n3)SIGN IN AS MANAGER\t4)NEW PRODUCTS\n9)SHUT DOWN\n");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
				bill();
			case 2:
				member();
				continue;
			case 3:
				x=manager();
				if(x==2)
				continue;
				if(x==1)
				break;
			case 4:
				products();
				break;
			case 9:
				printf("Are you sure you want to quit? \n\tPress 1 if yes\n\tPress 2 if no\n");
				scanf("%d",&quit);
				if(quit==1)
				break;
				else
				continue;
			default:
				printf("WRONG INPUT\n");
				getch();
				continue;
		}
		if(choice==9)
		break;
		if(x==1)
		{
			do
			{
				system("cls");
				printf("\t\t\tWELCOME MANAGER\n\n");
				
				printf("What would you like to view?\n1)SALES REPORT\t2)EMPLOYEE REPORT\n3)STOCKS\t4)MEMBERS\n9)SIGN OUT\n");
				scanf("%d",&choice);
				switch(choice)
				{
					case 1:
						sales_report();
						continue;
					case 2:
						employee_report();
						continue;
					case 3:
						stocks_check();
						continue;
					case 4:
						customer_check();
						continue;
					case 9:
						break;
					default:
						printf("WRONG INPUT\n");
						getch();
						continue;
				}
				
			}
			while(choice!=9);
		}
	}
	
	fptr1=fopen("Items.bin","wb");
	for(i=0;i<20;i++)
	{
		fwrite(&item[i],sizeof(struct items),1,fptr1);
	}
	fclose(fptr1);
	
	fptr2=fopen("Employees.bin","wb");
	for(i=0;i<10;i++)
	{
		fwrite(&item[i],sizeof(struct employee),1,fptr2);
	}
	fclose(fptr2);
	
}

int manager(void)//for logging in as manager
{
	char pass2[20];
	int chances=0,var1=0;
	do
	{
		printf("\nEnter Password : ");
		scanf("%s",&pass2);
		if(strcmp(pass2,pass)==0)
		var1=1;
		else
		{
			printf("\nYOU HAVE ENTERED WRONG PASSWORD\n");
			chances++;
		}
	}
	while(var1!=1 && chances<5);
	if(var1==1)
	return 1;
	else
	{
		printf("\nYou entered wrong password 5 times. You cannot sign in as manager. ");
		getch();
		return 2;
	}
}

void bill()//for billing
{
	int i,qty1;
	static int g,star,qty[20],i_bill[20],count=0,total,cash;//these variables are for function only
	static char b[5]={'0'};
	char a[5];
	if(count==0)
	{
		system("cls");
		printf("\t\t\tBILLING\n");
		printf("\nEnter the id of Employee who greeted : ");
		scanf("%d",&g);
		printf("\nIf all items have been done, press '0' in item number to print bill. \n");
	}
	fflush(stdin);
	if(count!=20)
	{
		printf("\nEnter item number: ");
		gets(a);
	}
	else
	{
		printf("Only 20 items are allowed per bill.");
		a[0]='0';
	}
	if(strcmp(a,b)==0)
	{
		system("cls");
		for(i=0;i<count;i++)
		printf("\n\nItem no %s\t%s x %d\t\tRs.%d",item[i_bill[i]].no,item[i_bill[i]].name,qty[i],item[i_bill[i]].price*qty[i]);
		printf("\nTotal : Rs.%d\n_______________________________________________\nAmount Recieved : Rs",total);
		scanf("%d",&cash);
		printf("Change : %d",cash-total);
		for(i=0;i<g;i++)
		{
			if(e[i].ID==g)
			{
				printf("\n\nGreeted by Employee : %s\tID : %d",e[i].name,e[i].ID);
				printf("\n\nOut of 5, How much stars would you rate our employee : ");
				scanf("%d",&star);
				e[i].stars=e[i].stars+star;
				break;
			}
		}
		count=0;
	//	total=0;
		getch();
		return;
	}
	fflush(stdin);
	printf("Enter quantity: ");
	scanf("%d",&qty1);
	for(i=0;i<200;i++)
	{
		if(strcmp(a,item[i].no)==0 )//&& item[i].stocks!=0)
		{
			printf("Item no %s\t%s x %d\t\tRs.%d\n",item[i].no,item[i].name,qty1,item[i].price*qty1);
			total=total+(item[i].price*qty1);
			qty[count]=qty1;
			i_bill[count]=i;
			count++;
			item[i].stocks=item[i].stocks-1;
			break;
		}
		else if(item[i].stocks==0)
		{
			printf("This Item is out of stock. ");
			break;
		}
		else if(i==199)
		{
			printf("\t\tWrong Item Number\n");
			getch();	
		}
	
	}
	bill(item);
}

void sales_report(void)
{
	system("cls");
	int i,total=0,sub_total=0,daily_sales[200];
	for(i=0;i<200;i++)
	{
		daily_sales[i]=sales[i]-item[i].stocks;
	}
	printf("\n\t-------DAILY SALES REPORT-------\nFollowing are the number of items sold for each item.\n");
	for(i=0;i<200;i++)
	{
		if(daily_sales!=0)
		{
			sub_total=daily_sales[i]*item[i].price;
			printf("\nItem no %s %s : %d : Price : %d",item[i].no,item[i].name,daily_sales[i],sub_total);
			total=total+sub_total;
		}
	}
	printf("\nTOTAL EARNINGS OF THE DAY : %d\n\n",total);
	printf("\nFollowing are the items with no sales today.\n");
	for(i=0;i<200;i++)
	{
		if(daily_sales==0)
		printf("\nItem no %s %s : %d",item[i].no,item[i].name,daily_sales[i]);
	}
	getch();
}

void products(void)//for adding new products
{
	
	int i,n,amount;
	system("cls");
	printf("Enter the number of items : ");
	scanf("%d",&n);
	printf("Enter the amount(stock) of each item : ");
	scanf("%d",&amount);
	FILE *fptr;
	fptr=fopen("Items.bin","wb");
	
	printf("\n\tEnter the information of each item :\n\n");
	for(i=0;i<n;i++)
	{
	    fflush(stdin);
		printf("\n\nEnter item number: ");
		gets(item_x.no);
		printf("Enter item name: ");
		gets(item_x.name);
		printf("Enter the price of %s item no %s : ",item_x.name,item_x.no);
		scanf("%d",&item_x.price);
		item_x.stocks=amount;
		fwrite(&item_x,sizeof(struct items),1,fptr);		
	}
	fclose(fptr);
    printf("\n\n\t-----ALL ITEMS HAVE BEEN ADDED-----");
	getch();
}

void sub_stocks1(void)//for detailed view
{
	int i;
	static int a=0,b=0,c=0;
	printf("OUT OF STOCK :\n\n");
	for(i=0;i<200;i++)
	{
		if(item[i].stocks==0)
		{
			printf("Item no %s\t%s \n",item[i].no,item[i].name);
			a++;
		}
	}
	printf("ONLY FEW PIECES LEFT :\n\n");
	for(i=0;i<200;i++)
	{
		if(item[i].stocks<=10)
		{
			printf("Item no %s\t%s \n",item[i].no,item[i].name);
			b++;
		}
	}
	printf("ITEMS WITH LESS SALES :\n\n");
		
	for(i=0;i<200;i++)
	{
		if(item[i].stocks>=20)
		{
			printf("Item no %s\t%s \n",item[i].no,item[i].name);
			c++;
		}
	}
	printf("ITEMS WITH AVERAGE SALES :\n\n");
	for(i=0;i<200;i++)
	{
		if(item[i].stocks<20 || item[i].stocks>10)
		printf("Item no %s\t%s \n",item[i].no,item[i].name);
	}
	printf("\n\tItems Out of stock : %d\n\tItems with few pieces left : %d\n\tItems with less sales : %d\n\tItems with average sales : %d\n",a,b,c,200-(a+b+c));
	getch();
}

void sub_stocks2(void)//for summarized view
{
	int i,a=0,b=0,c=0;
	for(i=0;i<200;i++)
	{
		if(item[i].stocks==0)
		a++;
		else if(item[i].stocks<=10)
		b++;
		else if(item[i].stocks>=20)
		c++;
	}
	printf("\n\tItems Out of stock : %d\n\tItems with few pieces left : %d\n\tItems with less sales : %d\n\tItems with average sales : %d\n",a,b,c,200-(a+b+c));
	getch();
}

void stocks_check(void)//to check stocks
{
	char z;
	system("cls");
	printf("\t\t\tSTOCKS CHECK\n");
	fflush(stdin);
	printf("Would you like to have a detailed view? Press 'Y' for yes and 'N' for no.");
	scanf("%c",&z);
	switch(z)
	{
		case 'y':
			sub_stocks1();
			break;
		case 'Y':
			sub_stocks1();
			break;
		case 'n':
			sub_stocks2();
			break;
		case 'N':
			sub_stocks2();
			break;
		default:
			printf("\tWrong Input. ");
			stocks_check();
			break;
	}
}

void customer_check(void)//to check member customers
{
	system("cls");
	FILE *ptr;
	ptr=fopen("Customers Data.bin","rb");
	printf("\t\t\tCUSTOMER CHECK\n");
	int a,i;
	char name2[50];
	printf("Would you like to find customer by ID or by name?\n\tEnter '1' for ID and '2' for name : ");
	scanf("%d",&a);
	switch(a)
	{
		case 1:
			printf("Enter Customer ID : ");
			scanf("%d",&a);
			for(i=0;i<1000;i++)
			{
				if(a>=id && a<0)
				printf("\nCustomer ID does not exist.");
				else
				{
					fread(&cst,sizeof(struct employee),1,ptr);
					if(cst.id==a)
					{
						printf("\tCustomer ID : %d\n\tName      : %s\n\tMobile no : %s\n\te-mail ID : %s\n\tAddress   : %s",a,cst.name,cst.mobile,cst.email,cst.address);
						break;
					}
				}
			}
			if(i==1000)
			printf("Customer ID does not exist. ");
			break;
		case 2:
			fflush(stdin);
			printf("Enter Customer Name : ");
			gets(name2);
			for(a=1;a<=id;a++)
			{
				int x=strcmp(name2,cst.name);
				if(x==0)
				{
					printf("\tCustomer ID : %d\n\tName      : %s\n\tMobile no : %s\n\te-mail ID : %s\n\tAddress   : %s",a,cst.name,cst.mobile,cst.email,cst.address);
					break;
				}
				else if(a==id)
				printf("Customer ID does not exist. ");
			}
			break;
	}
	fclose(ptr);
	getch();
}

void details(void)//to take details from customers for membership
{
	FILE *fptrx;
	fptrx=fopen("constants.bin","wb+");
	//fread(&id,sizeof(int),1,fptrx);
	id=1;
	fwrite(&id,sizeof(int),1,fptrx);
	fclose(fptrx);
	cst.id=id;
	FILE *ptr;
	ptr=fopen("Customers.bin","ab");
	
	printf("Customer ID %d",id);
	fflush(stdin);
	printf("\nGive us a few details about yourself. \n\tYour Name : ");
	gets(cst.name);
	fflush(stdin);
	printf("\tMobile No : ");
	gets(cst.mobile);
	fflush(stdin);
	printf("\te-mail ID : ");
	gets(cst.email);
	fflush(stdin);
	printf("\tAddress(district/society/town) : ");
	gets(cst.address);
	fwrite(&cst,sizeof(struct customers),1,ptr);
	fclose(ptr);
}

void member(void)//to ask customer if they wish to be a member
{
	char ans;
	fflush(stdin);
	printf("\n\nWould you like to be a member of our community and gain the benifits. \nPress 'Y' for YES and 'N' for NO. ");
	scanf("%c",&ans);
	switch (ans)
	{
		case 'Y':
			details();
			break;
		case 'N':
			break;
		case 'y':
			details();
			break;
		case 'n':
			break;
		default:
			printf("\n\tWrong Input. \n");
			member();
	}
	printf("\nThank you for coming to our store . We hope to see you again. \n");
	getch();
	return;
}

void emp_status(void)//to check data of employees
{
	int i,ID;
	printf("Enter ID of employee you want to check info of : ");
	scanf("%d",&ID);
	FILE *fptr;
	fptr=fopen("Employees.bin","rb");
	for(i=0;i<20;i++)
	{
		fread(&e_x,sizeof(struct employee),1,fptr);
		if(e_x.ID==ID)
		{
			printf("\n-----------Employee details----------\n");
			printf("ID : %d\n",e_x.ID);
	        printf("Name : %s\n",e_x.name);
	        printf("Age : %d\n",e_x.age);
	        printf("Address : %s\n",e_x.address);
	        printf("Designation : %s\n",e_x.designation);
	        printf("Salary : Rs.%f\n",e_x.salary);
	        printf("Customers : %d\n",e_x.customers);
	        printf("Stars earned : %d\n",e_x.stars);
	        getch();
	        return;
	    }   
	}
	printf("\nWrong ID. There is no employee with this ID.");	
	getch();
}

void emp_data(void)//to add data of employees
{
	int n,i;
		FILE *fptr;
	    fptr=fopen("Employees.bin","wb");
	    printf("Enter number of employees you want to store info of(not more than 20) : ");
	    scanf("%d",&n);
	    if(n>20)
	    {
	    	printf("\n\nThe Store cannot handle that many employees.");
	    	getch();
	    	emp_data();
		}
	    for(i=0;i<n;i++)
        {
		    printf("\n\t-----INFO OF EMPLOYEE %d-------\n",i+1);
		    printf("Name : ");
		
		    fflush(stdin);
		    gets(e_x.name);
		    printf("ID : ");
		    scanf("%d",&e_x.ID);
		    printf("Age : ");
		    scanf("%d",&e_x.age);
		    printf("Address : ");
		    fflush(stdin);
		    gets(e_x.address);
		    printf("Designation : ");
		    gets(e_x.designation);
		    fflush(stdin);
		    printf("Salary : ");
		    scanf("%f",&e_x.salary);
		    e_x.stars=0;
			e_x.customers=0;
		    fwrite(&e_x,sizeof(struct employee),1,fptr);
		}
       	fclose(fptr);
	return;
}

void employee_report(void)//to open the menu for checking employees
{
	int i,n,j,q,ID;
	printf("\n1)ADD EMPLOYEE DATA\t2)CHECK EMPLOYEE STATUS\n");
	scanf("%d",&q);
	switch(q)
	{
		case 1:
			emp_data();
			break;
		case 2:
			emp_status();
			break;
		default:
			printf("Wrong Input");
			employee_report();
			break;
	}
}


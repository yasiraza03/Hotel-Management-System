// Hotel Managment system SEC-K
// 21k-4869 Yasir Raza (LEADER)
// 21k-4915 Farzeen Khan
// 21k-3440 Murtaza Ahmed
// 21k-4875 Rayyan Kirmani

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
int found=0;

//structs declared
struct admin
{
	char id[40],pass[30],name[30],phone[10];
};
struct customer
{
	char id[40],pass[30],name[30],phone[10];	
};
struct avail_date
{
	int day,month,year,n;
};
struct hotel
{
	char id[40],pass[30],name[20],services[50],city[15],area[20],code[10];
	int discount,review;
	float ratings,price,commission;
	struct avail_date book[30];
};

// function prototypes
int customer(char *e,char *p);
int admin(char *e,char *p);
int hotel_represent(char *e,char *p);
int new_customer();
int new_admin();
int new_hotel();

// main starts here
int main()
{
	system("Color 74");
	char id[40],pass[50];
	int choice;
	printf("-----------------------Welcome To HotelBuddy-------------------------------------\n");
	while (found==0)
	{
		printf("Enter your email ID:\t(Dont have an Account? Press 0 to create a new account)\n");
		gets(id);
		if (id[0]=='0')
		{
			printf("Press 1 for Customer profile\nPress 2 for Admin profile\nPress 3 for Hotel Representative profile\n");
			scanf("%d",&choice);
			if(choice==1)
				new_customer();
			else if(choice==2)
				new_admin();
			else if(choice==3)
				new_hotel();
		}
		else
		{	
			printf("Enter Password: \n");
			gets(pass);
			if (id[0]=='c')
				customer(id,pass);
			else if(id[0]=='a')
			{
				admin(id,pass);
			}
			else if (id[0]=='h')
			{
				hotel_represent(id,pass);
			}
			else
				printf("Invalid ID\n");	
		}
	}
}
// main ends 

int customer(char *e,char *p)
{
	struct customer temp;int match=0;
	struct hotel htemp;
	FILE *fp,*fp1;
	fp=fopen("Customer.Data","rb+");
	while (fread(&temp,sizeof(temp),1,fp)==1&&found==0)
	{
		if(strcmp(temp.id,e)==0&&strcmp(p,temp.pass)==0)
		{
			found=1;
			break;
		}	
	}
	if (found==0)
	{
		printf("Invalid Email ID or password\n");
		return;
	}
	else
	{
		printf("Access Granted\n");
		struct avail_date date,date1;
		printf("Enter today's date:\t(Format: Day Month Year)\n");
		scanf("%d %d %d",&date.day,&date.month,&date.year);
		char area[20],city[10],name[30],decision,code[6];int match=0,x,count=0,i,j,n;float discount,total;
		fflush(stdin);int choice=0;
		fp1=fopen("Hotel.Data","rb+");
		while (choice==0&&match==0)	
		{
			printf("Enter city in which you want to search hotel: \n");fflush(stdin);gets(city);fflush(stdin);
			printf("Enter Area in which you want to search hotel: \n");gets(area);fflush(stdin);
			printf("Nearest Hotels in %s------->",area);fflush(stdin);
			fflush(stdin);
			rewind(fp1);
			while (fread(&htemp,sizeof(htemp),1,fp1)==1)
			{
				if (strcmpi(area,htemp.area)==0&&strcmpi(city,htemp.city)==0)
				{
					puts(htemp.name);
					match=1;
				}
			}
			if (match==0)
			{
				printf("No hotels in this area\nPress 0 to try again\nIf uou want to see list of all hotels in the city, Press 1\nPress 2 to exit\n");
				scanf("%d",&choice);fflush(stdin);
			}
		}
		if (choice==1||match==1)
		{
			match=0;
			rewind(fp1);
			choice=0;
			printf("All hotels in the city:\n");
			while (fread(&htemp,sizeof(htemp),1,fp1)==1)
			{
				if (strcmpi(city,htemp.city)==0)
				{
					printf("---------------------\n");
					printf("Name: %s\nArea: %s\nServices: %s\nPrice of one night stay: %.2f Rupees\n",htemp.name,htemp.area,htemp.services,htemp.price);
					printf("Ratings:%f\n",htemp.ratings);
					printf("---------------------\n");
					choice=1;
					match=1;
				}
			}
			if(choice==0)
			{
				printf("No hotels in this city\n");
				match=1;
			}
			else	
			{
				choice=1;
				match=0;
			}	
			fflush(stdin);
			while (match==0||choice==1)
			{
				printf("Enter name of the hotel from above list of hotels: \n");fflush(stdin);gets(name);fflush(stdin);
				rewind(fp1);
				while (fread(&htemp,sizeof(htemp),1,fp1)==1&&match==0)
				{
  					if (choice==0)
						break;
					if (strcmpi(name,htemp.name)==0)
					{
						printf("Enter date on which you wish to book:  (Note:You can only schedule room booking only within 30 days from today )\n");fflush(stdin);
						scanf("%d %d %d",&date.day,&date.month,&date.year);
						for(i=0;i<30;i++)
						{
							if (htemp.book[i].day==date.day&&htemp.book[i].month==date.month&&htemp.book[i].year==date.year)
								break;
						}
						if (htemp.book[i].n>0&&i!=30)
						{
							match=1;
							choice=0;
							printf("Number of rooms available = %d\n",htemp.book[i].n);
							n=htemp.book[i].n;
							while(1)
							{
								printf("Enter how many rooms you want to book: \n");
								scanf("%d",&x);
								if(x>n)
									{printf("Not enough rooms available.Enter again\n");continue;}
								else
								{
									printf("How many days you want to stay:\n");scanf("%d",&count);
									printf("You have booked %d rooms for %d days on the date: %d %d %d\n",x,count,date.day,date.month,date.year);
									for(j=0;j<count;j++)
									{
										htemp.book[i].n-=x;
										i++;
									}
									printf("Do you have any promo coupons?.Press (Y/N)\n");scanf(" %c",&decision);
									if (decision=='Y')
									{
										printf("Enter coupon code: \n");fflush(stdin);gets(code);
										if(strcmp(code,htemp.code)==0)
											decision='Y';
										else 
										{
											printf("Invalid Code\n");
											decision='N';
										}	
									}
									if (decision=='N')
									{
										total=x*count*htemp.price;
										htemp.commission+=0.05*total;
										printf("No.of rooms:%d\nDuration of stay:%d days\nPrice for one night stay per room: %.2f Rupees\n",x,count,htemp.price);
										printf("Total bill=%.2f Rupees\n",total);
										printf("Registration Number: %d.Show this at reception at time of check in\n",rand());
										
									}
									else
									{
										printf("You get %d percent discount!\n",htemp.discount);
										printf("No.of rooms:%d\nDuration of stay:%d days\nPrice for one night stay per room: %.2f Rupees\n",x,count,htemp.price);
										printf("Original bill=%.2f Rupees\n",x*count*htemp.price);
										discount=100-htemp.discount;
										discount=discount/100;
										total=x*count*htemp.price*discount;
										htemp.commission+=0.05*total;
										printf("After discount-->Final Total Bill= %.2f Rupees\n",total);
										srand(time(0));
										printf("Registration Number: %d.\tShow this at reception at time of check in\n",rand());
									}
									printf("DO you want to rate this restaurant?(Y/N)\n");fflush(stdin);scanf(" %c",&decision);
									if (decision=='Y')
									{
										htemp.review++;
										printf("1 poor\n2 bad\n3 average\n4 good\n5 commendable\n");scanf("%d",&x);
										htemp.ratings=(htemp.ratings+x)/htemp.review;
									}
									fflush(stdin);
									fseek(fp1,-sizeof(htemp),SEEK_CUR);
									fwrite(&htemp,sizeof(htemp),1,fp1);
									fclose(fp1);
									break;
								}
							}
						}
						else
						{
							printf("No rooms available on the date: %d %d %d.If you wnat to try another date press 1\nOr press 0 to exit\n",date.day,date.month,date.year);
							scanf("%d",&choice);
							if (choice==0)
								match=1;
						}
					}
				}
			}
		}
		if (choice==2)
			printf("EXITED");
		else
		{
			printf("Do you want to update your account info?(Y/N)");
			scanf(" %c",&decision);
			if (decision=='Y')
			{
				while(decision=='Y')
				{
					printf("Press 1 to change name\nPress 2 to update password\nPress 3 to update contact number\n");
					fflush(stdin);
					scanf("%d",&choice);
					switch (choice)
					{
						case 1:
							printf("Enter new name: ");fflush(stdin);
							gets(temp.name);
							break;
						case 2:
							printf("Enter New password: ");fflush(stdin);
							gets(temp.pass);
							break;
						case 3:
							printf("Enter new contact number: ");fflush(stdin);
							gets(temp.phone);
							break;
						default:
							printf("Invalid input\n");
							break;	
					}
					printf("Do you want to make any more changes?(Y/N)\n");
					scanf(" %c",&decision);
					if (decision=='N')
					{
						fflush(stdin);
						fseek(fp,-sizeof(temp),SEEK_CUR);
						fwrite(&temp,sizeof(temp),1,fp);
						fclose(fp);
					}
				}
			}
		}
		printf("EXITED");	
	}
	fclose(fp);	
}
int new_customer()
{
	struct customer temp,ftemp;
	int match;
	FILE *fp;
	fflush(stdin);
	printf("Enter Name: \n");gets(temp.name);
	printf("Phone Number: \n");gets(temp.phone);
	printf("New Password: \n");gets(temp.pass);fflush(stdin);
	printf("Enter ID:\t(Example:c_xyz123.hotelbuddy)\n");
	fp=fopen("Customer.Data","ab+");
	match=1;
	while (match==1)
	{
		match=0;
		gets(temp.id);
		while (fread(&ftemp,sizeof(ftemp),1,fp)==1&&match==0);
		{
			if(strcmp(temp.id,ftemp.id)==0)
				match=1;		
		}
		if (match==0)
		{
			fseek(fp,0,SEEK_END);
			fwrite(&temp,sizeof(temp),1,fp);
		}
		else
			printf("This email id is already taken.Enter email id again\n");
	}
	fclose(fp);
}
int admin(char *e,char *p)
{
	struct admin temp,temp2;int match=0;
	struct hotel htemp;
	char decision,id[20];
	FILE *fp,*fp1,*fp2,*ft;
	fp=fopen("Admin.Data","rb+");
	while (fread(&temp,sizeof(temp),1,fp)==1&&found==0)
	{
		if(strcmp(temp.id,e)==0&&strcmp(p,temp.pass)==0)
		{
			found=1;
			break;
		}	
	}
	if (found==0)
	{
		printf("Invalid Email ID or password\n");
		return;
	}
	else
	{
		printf("Access Granted!\n");
		fp1=fopen("Hotel.Data","rb+");
		int choice;
		char name[20];
		while (match==0)
		{	
			printf("Press 1 to view Commission from all hotels and their respective ratings\nPress 2 to enter hotel and view its commission and its ratings\n");
			scanf("%d",&choice);	
			if (choice==1)
			{
				while(fread(&htemp,sizeof(htemp),1,fp1)==1)
				{
					printf("Commission from %s: %.2f rupees\n",htemp.name,htemp.commission);
					printf("Ratings: %.2f\n",htemp.ratings);
					printf("----------------\n");
				}
				match=1;	
			}
			else if (choice==2)
			{
				printf("Enter Hotel's name: ");fflush(stdin);gets(name);
				while(fread(&htemp,sizeof(htemp),1,fp1)==1&&match==0)
				{
					if(strcmp(name,htemp.name)==0)
					{
						printf("Commission from %s: %f rupees\n",htemp.name,htemp.commission);
						printf("Ratings: %f\n",htemp.ratings);
						match=1;
					}
				}
				if (match==0)
					printf("Invalid name.Enter again\n");
			}
			else 
				printf("Invalid input.Enter again\n");
		}
		printf("Press 1 to view all hotels with a rating less than or equal to 2\n");fflush(stdin);
		scanf("%d",&choice);
		if (choice==1)
		{
			match=0;
			rewind(fp1);
			while(fread(&htemp,sizeof(htemp),1,fp1)==1)
			{
				if(htemp.ratings<=2)
				{
					puts(htemp.name);
					match=1;
				}
			}
			if (match==0)
				printf("There are no hotels with that rating\n");
		}
		printf("Do you want to update your account info?(Y/N)\n");scanf(" %c",&decision);
		if (decision=='Y')
		{
			while(decision=='Y')
			{
				printf("Press 1 to change name\nPress 2 to update password\nPress 3 to update contact number\n");
				fflush(stdin);
				scanf("%d",&choice);
				switch (choice)
				{
					case 1:
						printf("Enter new name: ");fflush(stdin);
						gets(temp.name);
						break;
					case 2:
						printf("Enter New password: ");fflush(stdin);
						gets(temp.pass);
						break;
					case 3:
						printf("Enter new contact number: ");fflush(stdin);
						gets(temp.phone);
						break;
					default:
						printf("Invalid input\n");
						break;	
				}
				printf("Do you want to make any more changes?(Y/N)\n");
				scanf(" %c",&decision);
				if (decision=='N')
				{
					fflush(stdin);
					fseek(fp,-sizeof(temp),SEEK_CUR);
					fwrite(&temp,sizeof(temp),1,fp);
					fclose(fp);
				}
			}
		}
		printf("Do you want to delete any customer or hotel record?(Y/N)");fflush(stdin);scanf(" %c",&decision);
		if (decision=='Y')
		{
			while (decision=='Y')
			{
				printf("Press 1 for customer record\nPress 2 for hotel record\n");scanf("%d",&choice);
				if (choice==1)
				{
					printf("Enter customer id of record you want to delete: ");fflush(stdin);gets(id);
					struct customer ctemp;
					fp2=fopen("Customer.Data","rb");
					ft=fopen("Temp.Data","wb");
					while (fread(&ctemp,sizeof(ctemp),1,fp2)==1)
					{
						if(strcmp(id,ctemp.id)!=0)
							fwrite(&ctemp,sizeof(ctemp),1,ft);
					}
					fclose(fp2);
					fclose(ft);
					remove("Customer.Data");
					rename("Temp.Data","Customer.Data");
				}
				if (choice==2)
				{
					printf("Enter hotel id of record you want to delete: ");fflush(stdin);gets(id);
					ft=fopen("Temp.Data","wb");
					rewind(fp1);
					while (fread(&htemp,sizeof(htemp),1,fp1)==1)
					{
						if(strcmp(htemp.id,id)!=0)
							fwrite(&htemp,sizeof(htemp),1,ft);
					}
					fclose(fp1);
					fclose(ft);
					remove("Hotel.Data");
					rename("Temp.Data","Hotel.Data");
					fp1=fopen("Hotel.Data","rb+");
				}
				printf("Do you want to delete another record?(Y/N)");scanf(" %c",&decision);
			}
		}
		fclose(fp1);
	}
	fclose(fp);	
}
int hotel_represent(char *e,char *p)
{
	struct hotel temp;int match=0;int i,x;
	FILE *fp;
	char services[20];
	fp=fopen("Hotel.Data","rb+");
	while (fread(&temp,sizeof(temp),1,fp)==1&&found==0)
	{
		if(strcmp(temp.id,e)==0&&strcmp(p,temp.pass)==0)
		{
			found=1;
			break;
		}	
	}
	if (found==0)
	{
		printf("Invalid Email ID or password\n");
		return;
	}
	else
	{
		printf("Access Granted!\n");
		int choice;char decision;
		printf("Do you want to make any changes?(Y/N)\n");scanf(" %c",&decision);
		if(decision=='Y')
		{
			while(decision=='Y')
			{
				printf("Press 1 to change name\nPress 2 to update services\nPress 3 to update password\nPress 4 to update price\nPress 5 to update promo coupon\nPress 6 to update booking dates\n");
				fflush(stdin);
				scanf("%d",&choice);
				switch (choice)
				{
					case 1:
						printf("Enter new name: ");fflush(stdin);
						gets(temp.name);
						break;
					case 2:
						printf("Update services: ");
						fflush(stdin);gets(services);
						strcat(temp.services,services);
						break;
					case 3:
						printf("Enter new password: ");fflush(stdin);
						gets(temp.pass);
						break;
					case 4:
						printf("Enter new price: ");fflush(stdin);
						scanf("%f",&temp.price);
						break;
					case 5:
						printf("Enter new promo code: ");fflush(stdin);
						gets(temp.code);				
						printf("Enter new discount: \n");fflush(stdin);
						scanf("%d",&temp.discount);
						break;
					case 6:
						printf("Enter the date:\t(From this date onwards to next month all rooms will be available)\n");
						scanf("%d %d %d",&temp.book[0].day,&temp.book[0].month,&temp.book[0].year);
						for(i=0;i<30;i++)
						{
							temp.book[i+1].n=temp.book[i].n;
							x=temp.book[i].day;
							if (temp.book[i].month==12)
							{
								if(temp.book[i].day==31)
								{
									temp.book[i+1].month=1;
									temp.book[i+1].day=1;
									temp.book[i+1].year=temp.book[i].year+1;
								}
								else
								{
									x++;
									temp.book[i+1].day=x;
									temp.book[i+1].month=temp.book[i].month;
									temp.book[i+1].year=temp.book[i].year;
								}
							}
							else if (temp.book[i].month%2!=0||temp.book[i].month==8)
							{
								if (temp.book[i].day==31)
								{
									temp.book[i+1].month=temp.book[i].month+1;
									temp.book[i+1].day=1;
									temp.book[i+1].year=temp.book[i].year;
								}
								else
								{
									x++;
									temp.book[i+1].day=x;
									temp.book[i+1].month=temp.book[i].month;
									temp.book[i+1].year=temp.book[i].year;
								}
							}
							else if (temp.book[i].month==2)
							{
								if (temp.book[i].day==29)
								{
									temp.book[i+1].month=temp.book[i].month+1;
									temp.book[i+1].day=1;
									temp.book[i+1].year=temp.book[i].year;
								}
								else
								{
									x++;
									temp.book[i+1].day=x;
									temp.book[i+1].month=temp.book[i].month;
									temp.book[i+1].year=temp.book[i].year;
								}
							}
							else 
							{
								if (temp.book[i].day==30)
								{
									temp.book[i+1].month=temp.book[i].month+1;
									temp.book[i+1].day=1;
									temp.book[i+1].year=temp.book[i].year;
								}
								else
								{
									x++;
									temp.book[i+1].day=x;
									temp.book[i+1].month=temp.book[i].month;
									temp.book[i+1].year=temp.book[i].year;
								}
							}
						}
						printf("Success!\n");
						break;	
					default:
						printf("Invalid input\n");
						break;	
				}
				printf("Do you want to make any more changes?(Y/N)\n");
				scanf(" %c",&decision);
				if (decision=='N')
				{
					fflush(stdin);
					fseek(fp,-sizeof(temp),SEEK_CUR);
					fwrite(&temp,sizeof(temp),1,fp);
					fclose(fp);
				}
			}
		}
		
		printf("Press 1 to view Hotel's ratings\nPress any key other than 1 to exit\n");
		scanf("%d",&choice);
		if (choice==1)
			printf("Ratings: %.2f",temp.ratings);
		else
			printf("EXITED");	
	}
}
int new_admin()
{
	FILE *fp;
	struct admin temp,ftemp;
	printf("Enter name: ");fflush(stdin);gets(temp.name);
	printf("Enter contact number: ");gets(temp.phone);
	printf("New Password: \n");gets(temp.pass);fflush(stdin);
	printf("Enter ID:\t(Example:a_xyz123.hotelbuddy)\n");
	fp=fopen("Admin.Data","ab+");
	int match=1;
	while (match==1)
	{
		match=0;
		gets(temp.id);
		while (fread(&ftemp,sizeof(ftemp),1,fp)==1&&match==0);
		{
			if(strcmp(temp.id,ftemp.id)==0)
				match=1;		
		}
		if (match==0)
		{
			fseek(fp,0,SEEK_END);
			fwrite(&temp,sizeof(temp),1,fp);
		}
		else
			printf("This email id is already taken.Enter email id again\n");
	}
	fclose(fp);
}
int new_hotel()
{
	struct hotel temp,ftemp;
	int match,i,x;
	char decision;
	FILE *fp;
	printf("Enter today's date:\t(Format: Day Month Year)\n");
	scanf("%d %d %d",&temp.book[0].day,&temp.book[0].month,&temp.book[0].year);
	fflush(stdin);
	printf("Total number of rooms in hotel: \n");scanf("%d",&temp.book[0].n);
	printf("Price for one night stay: \n");fflush(stdin);scanf("%f",&temp.price);fflush(stdin);
	printf("Does your hotel provide Promo coupons for discount(Y/N)\n");scanf(" %c",&decision);
	if (decision=='Y')
	{
		printf("Enter code: \n");
		fflush(stdin);
		gets(temp.code);
		printf("Enter discount on this coupon: \n");
		scanf("%d",&temp.discount);
	}
	for(i=0;i<30;i++)
	{
		temp.book[i+1].n=temp.book[i].n;
		x=temp.book[i].day;
		if (temp.book[i].month==12)
		{
			if(temp.book[i].day==31)
			{
				temp.book[i+1].month=1;
				temp.book[i+1].day=1;
				temp.book[i+1].year=temp.book[i].year+1;
			}
			else
			{
				x++;
				temp.book[i+1].day=x;
				temp.book[i+1].month=temp.book[i].month;
				temp.book[i+1].year=temp.book[i].year;
			}
		}
		else if (temp.book[i].month%2!=0||temp.book[i].month==8)
		{
			if (temp.book[i].day==31)
			{
				temp.book[i+1].month=temp.book[i].month+1;
				temp.book[i+1].day=1;
				temp.book[i+1].year=temp.book[i].year;
			}
			else
			{
				x++;
				temp.book[i+1].day=x;
				temp.book[i+1].month=temp.book[i].month;
				temp.book[i+1].year=temp.book[i].year;
			}
		}
		else if (temp.book[i].month==2)
		{
			if (temp.book[i].day==29)
			{
				temp.book[i+1].month=temp.book[i].month+1;
				temp.book[i+1].day=1;
				temp.book[i+1].year=temp.book[i].year;
			}
			else
			{
				x++;
				temp.book[i+1].day=x;
				temp.book[i+1].month=temp.book[i].month;
				temp.book[i+1].year=temp.book[i].year;
			}
		}
		else 
		{
			if (temp.book[i].day==30)
			{
				temp.book[i+1].month=temp.book[i].month+1;
				temp.book[i+1].day=1;
				temp.book[i+1].year=temp.book[i].year;
			}
			else
			{
				x++;
				temp.book[i+1].day=x;
				temp.book[i+1].month=temp.book[i].month;
				temp.book[i+1].year=temp.book[i].year;
			}
		}
	}
	printf("Enter Name: \n");fflush(stdin);
	gets(temp.name);
	printf("Enter services: \n");
	gets(temp.services);
	printf("New Password: \n");
	gets(temp.pass);fflush(stdin);
	printf("Enter city: \n");
	gets(temp.city);
	printf("Enter Area: \n");
	gets(temp.area);	
	printf("Enter ID:\t(Example:h_xyz123.hotelbuddy)\n");
	fp=fopen("Hotel.Data","ab+");
	match=1;
	temp.commission=0.0;
	temp.ratings=0.0;
	temp.review=0;
	while (match==1)
	{
		match=0;
		gets(temp.id);
		fflush(stdin);
		while (fread(&ftemp,sizeof(ftemp),1,fp)==1&&match==0)
		{
			if(strcmp(temp.id,ftemp.id)==0)
				match=1;		
		}
		if (match==0)
		{
			fseek(fp,0,SEEK_END);
			fwrite(&temp,sizeof(temp),1,fp);
		}
		else
			printf("This email id is already taken.Enter email id again\n");
	}
	
	fclose(fp);
}




















#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<math.h>

struct question
{
	char qus[200];
	char op1[50];
	char op2[50];
	char op3[50];
	char op4[50];
	int ans;
}e,m,h;

struct player
{
	char name[50];
	long salary;
}p;

void main_menu();
void default_program(int);
void admin_part();
void exit_program(int);
void change_password();
void player_part();
void update(char[],int,int);
void del(char[],int,int);
void show_players();
void game(struct player);
long get_salary(int);
void game_over(struct player,int,int);
void remove_e(char[]);
void remove_m(char[]);
void remove_h(char[]);
char* string_converter(int);
char* convert_long(long);
void addLayout(int);
void showLayout(int);
void add_question();
void show_question();
void add_easy_question();
void add_medium_question();
void add_hard_question();
void gameLayout(struct player,int,int,int,int);
void authenticate();

void main()
{
	int gd = DETECT, gm;
	initgraph(&gd,&gm,"C:\\TC\\bgi");
	main_menu();
}

void main_menu()
{
	char ch;
	while(1)
	{
		cleardevice();
		setbkcolor(6);
		setfillstyle(SLASH_FILL,RED);
		bar(200,150,400,350);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(220,170,380,330);
		settextstyle(0,0,2);
		setcolor(9);
		outtextxy(270,190,"Menu");
		settextstyle(0,0,1);
		outtextxy(230,240,"1 - Admin");
		outtextxy(230,270,"2 - Player");
		ch = getch();
		switch(ch)
		{
			case '0':exit_program(0);
			break;
			case '1':authenticate();
			break;
			case '2':player_part();
			break;
			default:default_program(0);
		}
	}
}

void exit_program(int n)
{
	char ch;
	do
	{
		setfillstyle(SOLID_FILL,RED);
		bar(150,200,450,260);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(155,215,445,255);
		setcolor(9);
		settextstyle(0,0,1);
		outtextxy(170,225,"Do you really want to exit....??");
		outtextxy(270,235,"[y/n]");
		flushall();
		ch = getch();
	}while(!((ch == 'y') || (ch == 'Y') || (ch == 'n') || (ch == 'N')));
	if((ch == 'y') || (ch == 'Y'))
	{
		setfillstyle(SOLID_FILL,RED);
		bar(228,215,378,245);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(233,220,373,240);
		setcolor(9);
		settextstyle(0,0,1);
		outtextxy(238,225,"Thanks For Visit");
		getch();
		exit(0);
	}
	else
	{
		if(n == 0)
			main_menu();
		else if(n == 1)
			admin_part();
		else if(n == 11)
			add_question();
		else if(n == 12)
			show_question();
	}
}

void default_program(int n)
{
	setfillstyle(SOLID_FILL,RED);
	bar(150,200,450,260);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(155,215,445,255);
	setcolor(9);
	settextstyle(0,0,1);
	outtextxy(195,225,"Plz press the valid entry");
	getch();
	if(n == 0)
		main_menu();
	else if(n == 1)
		admin_part();
	else if(n == 11)
		add_question();
	else if(n == 12)
		show_question();
}

void admin_part()
{
	char ch;
	while(1)
	{
		cleardevice();
		setbkcolor(6);
		setfillstyle(SLASH_FILL,RED);
		bar(150,100,450,340);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(170,120,430,320);
		settextstyle(0,0,2);
		setcolor(9);
		outtextxy(210,130,"Admin Menu");
		settextstyle(0,0,1);
		outtextxy(190,170,"1 - Add Question");
		outtextxy(190,200,"2 - Show Question");
		outtextxy(190,230,"3 - Show Player");
		outtextxy(190,260,"4 - Change Password");
		outtextxy(190,290,"5 - Back");
		ch = getch();
		switch(ch)
		{
			case '0':exit_program(1);
			break;
			case '1':add_question();
			break;
			case '2':show_question();
			break;
			case '3':show_players();
			break;
			case '4':change_password();
			break;
			case '5':main_menu();
			break;
			default:default_program(1);
		}
	}
}

void authenticate() {
	char pass[32],filePass[32];
	FILE *password;
	cleardevice();
	setbkcolor(6);
	setcolor(9);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(200,250,400,350);
	setfillstyle(SOLID_FILL,RED);
	bar(210,290,390,340);
	settextstyle(0,0,1);
	outtextxy(250,270,"Enter Password");
	gotoxy(28,20);
	gets(pass);
	if((strlen(pass) > 0) && (strlen(pass) < 21)) {
		password = fopen("kpass.txt","r");
		fscanf(password,"%s",filePass);
		if(strcmp(pass,filePass) == 0) {
			admin_part();
		}
		else {
			setfillstyle(SOLID_FILL,RED);
			bar(150,200,450,260);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(155,215,445,255);
			setcolor(9);
			settextstyle(0,0,1);
			outtextxy(195,225,"Password Incorrect");
			getch();
			authenticate();
		}
	}
	else {
		setfillstyle(SOLID_FILL,RED);
		bar(150,200,450,260);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(155,215,445,255);
		setcolor(9);
		settextstyle(0,0,1);
		outtextxy(195,225,"Password Limit Exceed");
		getch();
		authenticate();
	}
	getch();
	main_menu();
}

void change_password()
{
	char oldPass[32],newPass1[32],newPass2[32];
	FILE *old,*_new;
	char filePass[32];
	char ch;
	cleardevice();
	setbkcolor(6);
	setfillstyle(SOLID_FILL,RED);
	bar(200,150,400,350);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(210,180,390,340);
	outtextxy(240,162,"Change Password");
	outtextxy(250,190,"Old Password");
	gotoxy(30,14);
	gets(oldPass);
	outtextxy(250,240,"New Password");
	gotoxy(30,17);
	gets(newPass1);
	outtextxy(250,290,"Repeat Password");
	gotoxy(30,20);
	gets(newPass2);
	old = fopen("kpass.txt","r");
	fscanf(old,"%s",&filePass);
	if(strcmp(filePass,oldPass) == 0) {
		if(strcmp(newPass1,newPass2) == 0) {
			_new = fopen("abc.txt","w");
			fprintf(_new,"%s",newPass1);
			setfillstyle(SOLID_FILL,RED);
			bar(150,200,450,260);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(155,215,445,255);
			setcolor(9);
			settextstyle(0,0,1);
			outtextxy(195,225,"Password Changed Successfully");
			getch();
			fcloseall();
			remove("kpass.txt");
			rename("abc.txt","kpass.txt");
		}
		else {
			setfillstyle(SOLID_FILL,RED);
			bar(150,200,450,260);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(155,215,445,255);
			setcolor(9);
			settextstyle(0,0,1);
			outtextxy(195,225,"New Password does not match");
			getch();
			fclose(old);
		}
	}
	else {
		setfillstyle(SOLID_FILL,RED);
		bar(150,200,450,260);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(155,215,445,255);
		setcolor(9);
		settextstyle(0,0,1);
		outtextxy(195,225,"Old Password is Incorrect");
		getch();
		fclose(old);
	}
	getch();
	admin_part();
}

void add_question()
{
	char ch;
	while(1)
	{
		cleardevice();
		setbkcolor(6);
		setfillstyle(SLASH_FILL,RED);
		bar(150,100,450,340);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(170,120,430,320);
		settextstyle(0,0,2);
		setcolor(9);
		outtextxy(210,130,"Add Question");
		settextstyle(0,0,1);
		outtextxy(190,170,"1 - Add Easy Question");
		outtextxy(190,200,"2 - Add Medium Question");
		outtextxy(190,230,"3 - Add Hard Question");
		outtextxy(190,260,"4 - Back");
		outtextxy(190,290,"5 - Main Menu");
		ch = getch();
		switch(ch)
		{
			case '0':exit_program(11);
			break;
			case '1':add_easy_question();
			break;
			case '2':add_medium_question();
			break;
			case '3':add_hard_question();
			break;
			case '4':admin_part();
			break;
			case '5':main_menu();
			break;
			default:default_program(11);
		}
	}
}

void addLayout(int n)
{
	FILE *qus_bank;
	char ques[200],option[4][50];
	int answer;
	cleardevice();
	if(n == 1)
		qus_bank = fopen("kquse.txt","a+");
	else if(n == 2)
		qus_bank = fopen("kqusm.txt","a+");
	else if(n == 3)
		qus_bank = fopen("kqush.txt","a+");
	settextstyle(0,0,1);
	outtextxy(100,100,"Question : ");
	flushall();
	gotoxy(25,7);
	gets(ques);
	if(strcmpi(ques,"back") == 0)
		add_question();
	else if(strcmpi(ques,"exit") == 0)
		exit_program(11);
	outtextxy(100,151,"Option 1 : ");
	flushall();
	gotoxy(25,10);
	gets(option[0]);
	if(strcmpi(option[0],"back") == 0)
		add_question();
	else if(strcmpi(option[0],"exit") == 0)
		exit_program(11);
	outtextxy(100,183,"Option 2 : ");
	flushall();
	gotoxy(25,12);
	gets(option[1]);
	if(strcmpi(option[1],"back") == 0)
		add_question();
	else if(strcmpi(option[1],"exit") == 0)
		exit_program(11);
	outtextxy(100,215,"Option 3 : ");
	flushall();
	gotoxy(25,14);
	gets(option[2]);
	if(strcmpi(option[2],"back") == 0)
		add_question();
	else if(strcmpi(option[2],"exit") == 0)
		exit_program(11);
	outtextxy(100,247,"Option 4 : ");
	flushall();
	gotoxy(25,16);
	gets(option[3]);
	if(strcmpi(option[3],"back") == 0)
		add_question();
	else if(strcmpi(option[3],"exit") == 0)
		exit_program(11);
	outtextxy(100,279,"Answer : ");
	gotoxy(24,18);
	scanf("%d",&answer);
	if(n == 1) {
		strcpy(e.qus,ques);
		strcpy(e.op1,option[0]);
		strcpy(e.op2,option[1]);
		strcpy(e.op3,option[2]);
		strcpy(e.op4,option[3]);
		e.ans = answer;
		fwrite(&e,sizeof(e),1,qus_bank);
	}
	else if(n == 2) {
		strcpy(m.qus,ques);
		strcpy(m.op1,option[0]);
		strcpy(m.op2,option[1]);
		strcpy(m.op3,option[2]);
		strcpy(m.op4,option[3]);
		m.ans = answer;
		fwrite(&m,sizeof(m),1,qus_bank);
	}
	else if(n == 3) {
		strcpy(h.qus,ques);
		strcpy(h.op1,option[0]);
		strcpy(h.op2,option[1]);
		strcpy(h.op3,option[2]);
		strcpy(h.op4,option[3]);
		h.ans = answer;
		fwrite(&h,sizeof(h),1,qus_bank);
	}
	setfillstyle(SOLID_FILL,RED);
	bar(150,200,450,260);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(155,215,445,255);
	setcolor(9);
	settextstyle(0,0,1);
	fcloseall();
	outtextxy(170,225,"Add Another Question....??");
	outtextxy(270,235,"[y/n]");
}
void add_easy_question()
{
	char ch;
	do
	{
		addLayout(1);
		flushall();
		ch = getch();
		if((ch == 'n') || (ch == 'N')) {
			add_question();
			break;
		}
	}while((ch == 'y') || (ch == 'Y'));
	admin_part();
}

void add_medium_question()
{
	char ch;
	do
	{
		addLayout(2);
		flushall();
		ch = getch();
		if((ch == 'n') || (ch == 'N')) {
			add_question();
			break;
		}
	}while((ch == 'y') || (ch == 'Y'));
	admin_part();
}

void add_hard_question()
{
	char ch;
	do
	{
		addLayout(3);
		flushall();
		ch = getch();
		if((ch == 'n') || (ch == 'N')) {
			add_question();
			break;
		}
	}while((ch == 'y') || (ch == 'Y'));
	admin_part();
}

void show_question()
{
	char ch;
	while(1)
	{
		cleardevice();
		setbkcolor(6);
		setfillstyle(SLASH_FILL,RED);
		bar(150,100,450,340);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(170,120,430,320);
		settextstyle(0,0,2);
		setcolor(9);
		outtextxy(210,130,"Show Question");
		settextstyle(0,0,1);
		outtextxy(190,170,"1 - Show Easy Question");
		outtextxy(190,200,"2 - Show Medium Question");
		outtextxy(190,230,"3 - Show Hard Question");
		outtextxy(190,260,"4 - Back");
		outtextxy(190,290,"5 - Main Menu");
		ch = getch();
		switch(ch)
		{
			case '0':exit_program(12);
			break;
			case '1':showLayout(1);
			break;
			case '2':showLayout(2);
			break;
			case '3':showLayout(3);
			break;
			case '4':admin_part();
			break;
			case '5':main_menu();
			break;
			default:default_program(11);
		}
	}
}

void showLayout(int n)
{
	FILE *qus_bank,*backup;
	char str[2],ch;
	if(n == 1) {
		qus_bank = fopen("kquse.txt","r");
		backup = fopen("kbacke.txt","r");
	}
	else if(n == 2) {
		qus_bank = fopen("kqusm.txt","r");
		backup = fopen("kbackm.txt","r");
	}
	else if(n == 3) {
		qus_bank = fopen("kqush.txt","r");
		backup = fopen("kbackh.txt","r");
	}
	while((n == 1)?(fread(&e,sizeof(e),1,qus_bank) == 1):((n == 2)?(fread(&m,sizeof(m),1,qus_bank) == 1):(fread(&h,sizeof(h),1,qus_bank) == 1)))
	{
		cleardevice();
		settextstyle(0,0,2);
		outtextxy(300,100,"Questions");
		flushall();
		settextstyle(0,0,1);
		outtextxy(100,150,"Question : ");
		outtextxy(100,180,"Option 1 : ");
		outtextxy(100,200,"Option 2 : ");
		outtextxy(100,220,"Option 3 : ");
		outtextxy(100,240,"Option 4 : ");
		outtextxy(100,260,"Answer : ");
		outtextxy(100,350,"press 1 to UPDATE the question");
		outtextxy(100,370,"press 2 to DELETE the question");
		outtextxy(100,390,"press 3 to Back");
		outtextxy(100,410,"press any other key to continue");
		if(n == 1) {
			outtextxy(180,150,e.qus);
			flushall();
			outtextxy(180,180,e.op1);
			flushall();
			outtextxy(180,200,e.op2);
			flushall();
			outtextxy(180,220,e.op3);
			flushall();
			outtextxy(180,240,e.op4);
			flushall();
			str[0] = '0' + e.ans;
			str[1] = NULL;
			outtextxy(180,260,str);
			ch = getch();
			switch(ch)
			{
				case '1':update(e.qus,1,1);
				break;
				case '2':del(e.qus,1,1);
				break;
				case '3':show_question();
				break;
				default:continue;
			}
		}
		else if(n == 2) {
			outtextxy(180,150,m.qus);
			flushall();
			outtextxy(180,180,m.op1);
			flushall();
			outtextxy(180,200,m.op2);
			flushall();
			outtextxy(180,220,m.op3);
			flushall();
			outtextxy(180,240,m.op4);
			flushall();
			str[0] = '0' + m.ans;
			str[1] = NULL;
			outtextxy(180,260,str);
			ch = getch();
			switch(ch)
			{
				case '1':update(m.qus,2,1);
				break;
				case '2':del(m.qus,2,1);
				break;
				case '3':show_question();
				break;
				default:continue;
			}
		}
		else if(n == 3) {
			outtextxy(180,150,h.qus);
			flushall();
			outtextxy(180,180,h.op1);
			flushall();
			outtextxy(180,200,h.op2);
			flushall();
			outtextxy(180,220,h.op3);
			flushall();
			outtextxy(180,240,h.op4);
			flushall();
			str[0] = '0' + h.ans;
			str[1] = NULL;
			outtextxy(180,260,str);
			ch = getch();
			switch(ch)
			{
				case '1':update(h.qus,3,1);
				break;
				case '2':del(h.qus,3,1);
				break;
				case '3':show_question();
				break;
				default:continue;
			}
		}
	}
	while((n == 1)?(fread(&e,sizeof(e),1,backup) == 1):((n == 2)?(fread(&m,sizeof(m),1,backup) == 1):(fread(&h,sizeof(h),1,backup) == 1)))
	{
		cleardevice();
		settextstyle(0,0,2);
		outtextxy(300,100,"Questions");
		flushall();
		settextstyle(0,0,1);
		outtextxy(100,150,"Question : ");
		outtextxy(100,180,"Option 1 : ");
		outtextxy(100,200,"Option 2 : ");
		outtextxy(100,220,"Option 3 : ");
		outtextxy(100,240,"Option 4 : ");
		outtextxy(100,260,"Answer : ");
		outtextxy(100,350,"press 1 to UPDATE the question");
		outtextxy(100,370,"press 2 to DELETE the question");
		outtextxy(100,390,"press 3 to Back");
		outtextxy(100,410,"press any other key to continue");
		if(n == 1) {
			outtextxy(180,150,e.qus);
			flushall();
			outtextxy(180,180,e.op1);
			flushall();
			outtextxy(180,200,e.op2);
			flushall();
			outtextxy(180,220,e.op3);
			flushall();
			outtextxy(180,240,e.op4);
			flushall();
			str[0] = '0' + e.ans;
			str[1] = NULL;
			outtextxy(180,260,str);
			ch = getch();
			switch(ch)
			{
				case '1':update(e.qus,1,2);
				break;
				case '2':del(e.qus,1,2);
				break;
				case '3':show_question();
				break;
				default:continue;
			}
		}
		else if(n == 2) {
			outtextxy(180,150,m.qus);
			flushall();
			outtextxy(180,180,m.op1);
			flushall();
			outtextxy(180,200,m.op2);
			flushall();
			outtextxy(180,220,m.op3);
			flushall();
			outtextxy(180,240,m.op4);
			flushall();
			str[0] = '0' + m.ans;
			str[1] = NULL;
			outtextxy(180,260,str);
			ch = getch();
			switch(ch)
			{
				case '1':update(m.qus,2,2);
				break;
				case '2':del(m.qus,2,2);
				break;
				case '3':show_question();
				break;
				default:continue;
			}
		}
		else if(n == 3) {
			outtextxy(180,150,h.qus);
			flushall();
			outtextxy(180,180,h.op1);
			flushall();
			outtextxy(180,200,h.op2);
			flushall();
			outtextxy(180,220,h.op3);
			flushall();
			outtextxy(180,240,h.op4);
			flushall();
			str[0] = '0' + h.ans;
			str[1] = NULL;
			outtextxy(180,260,str);
			ch = getch();
			switch(ch)
			{
				case '1':update(h.qus,3,2);
				break;
				case '2':del(h.qus,3,2);
				break;
				case '3':show_question();
				break;
				default:continue;
			}
		}
	}
	fcloseall();
	cleardevice();
	settextstyle(0,0,2);
	outtextxy(250,200,"The End");
	settextstyle(0,0,1);
	getch();
	admin_part();
}

void update(char str[],int n,int p)
{
	FILE *dummy,*qus_bank;
	dummy = fopen("abc.txt","a");
	if(n == 1)
	{
		if(p == 1)
			qus_bank = fopen("kquse.txt","r");
		else
			qus_bank = fopen("kbacke.txt","r");
		while(fread(&e,sizeof(e),1,qus_bank) == 1)
		{
			if(strcmp(e.qus,str) != 0)
				fwrite(&e,sizeof(e),1,dummy);
			else
			{
				cleardevice();
				settextstyle(0,0,1);
				outtextxy(100,100,"Question : ");
				flushall();
				gotoxy(25,7);
				gets(e.qus);
				if(strcmpi(e.qus,"back") == 0)
					add_question();
				else if(strcmpi(e.qus,"exit") == 0)
					exit_program(11);
				outtextxy(100,151,"Option 1 :");
				flushall();
				gotoxy(25,10);
				gets(e.op1);
				if(strcmpi(e.op1,"back") == 0)
					add_question();
				else if(strcmpi(e.op1,"exit") == 0)
					exit_program(11);
				outtextxy(100,183,"Option 2 : ");
				flushall();
				gotoxy(25,12);
				gets(e.op2);
				if(strcmpi(e.op2,"back") == 0)
					add_question();
				else if(strcmpi(e.op2,"exit") == 0)
					exit_program(11);
				outtextxy(100,215,"Option 3 : ");
				flushall();
				gotoxy(25,14);
				gets(e.op3);
				if(strcmpi(e.op3,"back") == 0)
					add_question();
				else if(strcmpi(e.op3,"exit") == 0)
					exit_program(11);
				outtextxy(100,247,"Option 4 : ");
				flushall();
				gotoxy(25,16);
				gets(e.op4);
				if(strcmpi(e.op4,"back") == 0)
					add_question();
				else if(strcmpi(e.op4,"exit") == 0)
					exit_program(11);
				outtextxy(100,279,"Answer : ");
				gotoxy(24,18);
				scanf("%d",&e.ans);
				fwrite(&e,sizeof(e),1,dummy);
			}
		}
		fcloseall();
		if(p == 1) {
			remove("kquse.txt");
			rename("abc.txt","kquse.txt");
		}
		else {
			remove("kbacke.txt");
			rename("abc.txt","kbacke.txt");
		}
	}
	else if(n == 2)
	{
		if(p == 1)
			qus_bank = fopen("kqusm.txt","r");
		else
			qus_bank = fopen("kbackm.txt","r");
		while(fread(&m,sizeof(m),1,qus_bank) == 1)
		{
			if(strcmp(str,m.qus) != 0)
				fwrite(&m,sizeof(m),1,dummy);
			else
			{
				settextstyle(0,0,1);
				outtextxy(100,100,"Question : ");
				flushall();
				gotoxy(25,7);
				gets(m.qus);
				if(strcmpi(m.qus,"back") == 0)
					add_question();
				else if(strcmpi(m.qus,"exit") == 0)
					exit_program(11);
				outtextxy(100,151,"Option 1 :");
				flushall();
				gotoxy(25,10);
				gets(m.op1);
				if(strcmpi(m.op1,"back") == 0)
					add_question();
				else if(strcmpi(m.op1,"exit") == 0)
					exit_program(11);
				outtextxy(100,183,"Option 2 : ");
				flushall();
				gotoxy(25,12);
				gets(m.op2);
				if(strcmpi(m.op2,"back") == 0)
					add_question();
				else if(strcmpi(m.op2,"exit") == 0)
				exit_program(11);
				outtextxy(100,215,"Option 3 : ");
				flushall();
				gotoxy(25,14);
				gets(m.op3);
				if(strcmpi(m.op3,"back") == 0)
					add_question();
				else if(strcmpi(m.op3,"exit") == 0)
					exit_program(11);
				outtextxy(100,247,"Option 4 : ");
				flushall();
				gotoxy(25,16);
				gets(m.op4);
				if(strcmpi(m.op4,"back") == 0)
					add_question();
				else if(strcmpi(m.op4,"exit") == 0)
					exit_program(11);
				outtextxy(100,279,"Answer : ");
				gotoxy(24,18);
				scanf("%d",&m.ans);
				fwrite(&m,sizeof(m),1,dummy);
			}
		}
		fcloseall();
		if(p == 1) {
			remove("kqusm.txt");
			rename("abc.txt","kqusm.txt");
		}
		else {
			remove("kbackm.txt");
			rename("abc.txt","kbackm.txt");
		}
	}
	else if(n == 3)
	{
		if(p == 1)
			qus_bank = fopen("kqush.txt","r");
		else
			qus_bank = fopen("kbackh.txt","r");
		while(fread(&h,sizeof(h),1,qus_bank) == 1)
		{
			if(strcmp(h.qus,str) == 0)
				fwrite(&h,sizeof(h),1,dummy);
			else
			{
				settextstyle(0,0,1);
				outtextxy(100,100,"Question : ");
				flushall();
				gotoxy(25,7);
				gets(h.qus);
				if(strcmpi(h.qus,"back") == 0)
					add_question();
				else if(strcmpi(h.qus,"exit") == 0)
					exit_program(11);
				outtextxy(100,151,"Option 1 :");
				flushall();
				gotoxy(25,10);
				gets(h.op1);
				if(strcmpi(h.op1,"back") == 0)
					add_question();
				else if(strcmpi(h.op1,"exit") == 0)
					exit_program(11);
				outtextxy(100,183,"Option 2 : ");
				flushall();
				gotoxy(25,12);
				gets(h.op2);
				if(strcmpi(h.op2,"back") == 0)
					add_question();
				else if(strcmpi(h.op2,"exit") == 0)
					exit_program(11);
				outtextxy(100,215,"Option 3 : ");
				flushall();
				gotoxy(25,14);
				gets(h.op3);
				if(strcmpi(h.op3,"back") == 0)
					add_question();
				else if(strcmpi(h.op3,"exit") == 0)
					exit_program(11);
				outtextxy(100,247,"Option 4 : ");
				flushall();
				gotoxy(25,16);
				gets(h.op4);
				if(strcmpi(h.op4,"back") == 0)
					add_question();
				else if(strcmpi(h.op4,"exit") == 0)
					exit_program(11);
				outtextxy(100,279,"Answer : ");
				gotoxy(24,18);
				scanf("%d",&h.ans);
				fwrite(&h,sizeof(h),1,dummy);
			}
		}
		fcloseall();
		if(p == 1) {
			remove("kqush.txt");
			rename("abc.txt","kqush.txt");
		}
		else {
			remove("kbackh.txt");
			rename("abc.txt","kbackh.txt");
		}
	}
}

void del(char str[],int n,int p)
{
	FILE *dummy,*qus_bank;
	clrscr();
	dummy = fopen("abc.txt","a");
	if(n == 1)
	{
		if(p == 1)
			qus_bank = fopen("kquse.txt","r");
		else
			qus_bank = fopen("kbacke.txt","r");
		while(fread(&e,sizeof(e),1,qus_bank) == 1)
		{
			if(strcmp(e.qus,str) == 0)
				fwrite(&e,sizeof(e),1,dummy);
		}
		fcloseall();
		if(p == 1) {
			remove("kquse.txt");
			rename("abc.txt","kquse.txt");
		}
		else {
			remove("kbacke.txt");
			rename("abc.txt","kbacke.txt");
		}
	}
	else if(n == 2)
	{
		if(p == 1)
			qus_bank = fopen("kqusm.txt","r");
		else
			qus_bank = fopen("kbackm.txt","r");
		while(fread(&m,sizeof(m),1,qus_bank) == 1)
		{
			if(strcmp(m.qus,str) == 0)
				fwrite(&m,sizeof(m),1,dummy);
		}
		fcloseall();
		if(p == 1) {
			remove("kqusm.txt");
			rename("abc.txt","kqusm.txt");
		}
		else {
			remove("kbackm.txt");
			rename("abc.txt","kbackm.txt");
		}
	}
	else if(n == 3)
	{
		if(p == 1)
			qus_bank = fopen("kqush.txt","r");
		else
			qus_bank = fopen("kbackh.txt","r");
		while(fread(&h,sizeof(h),1,qus_bank) == 1)
		{
			if(strcmp(h.qus,str) == 0)
				fwrite(&h,sizeof(h),1,dummy);
		}
		fcloseall();
		if(p == 1) {
			remove("kqush.txt");
			rename("abc.txt","kqush.txt");
		}
		else {
			remove("kbackh.txt");
			rename("abc.txt","kbackh.txt");
		}
	}
}

void player_part()
{
	cleardevice();
	setbkcolor(9);
	setfillstyle(SOLID_FILL,RED);
	bar(200,200,400,300);
	setfillstyle(SOLID_FILL,BLACK);
	bar(220,240,380,280);
	outtextxy(220,210,"Player Name");
	gotoxy(30,17);
	gets(p.name);
	if((strlen(p.name) <= 17) && (strlen(p.name) > 0)) {
		strcpy(p.name,"Paras Jain");
		if(strcmp(p.name,"back") == 0)
			main_menu();
		else if(strcmp(p.name,"exit") == 0)
			exit_program(0);
		p.salary = 0;
		game(p);
	}
	else
		player_part();
}

void show_players()
{
	FILE *players;
	int i = 30,flag = 0;
	char *str,ch;
	cleardevice();
	players = fopen("kplayer.txt","r");
	settextstyle(0,0,2);
	outtextxy(100,50,"Name");
	outtextxy(300,50,"Salary");
	while(fread(&p,sizeof(p),1,players) == 1)
	{
		if(((i/30)%9) == 0) {
			flag = 0;
			cleardevice();
			settextstyle(0,0,2);
			outtextxy(100,50,"Name");
			outtextxy(300,50,"Salary");
			i = 30;
		}
		settextstyle(0,0,1);
		outtextxy(100,70+i,p.name);
		strcpy(str,convert_long(p.salary));
		outtextxy(300,70+i,str);
		i = i+30;
		delay(200);
		if(((i/30)%9) == 0) {
			outtextxy(250,400,"press '0' for back");
			outtextxy(250,420,"press any other key for continue");
			ch = getch();
			flag = 1;
			if(ch == '0') {
				admin_part();
				break;
			}
		}
	}
	if(flag == 0) {
		settextstyle(0,0,1);
		outtextxy(200,70+i,"The End");
		outtextxy(250,400,"press '0' for back");
		outtextxy(250,420,"press any other key for continue");
	}
	getch();
	fcloseall();
	admin_part();
}

char* convert_long(long n)
{
	char *str;
	if(n == 0)
		strcpy(str,"0");
	else if(n == 1000)
		strcpy(str,"1000");
	else if(n == 2000)
		strcpy(str,"2000");
	else if(n == 3000)
		strcpy(str,"3000");
	else if(n == 5000)
		strcpy(str,"5000");
	else if(n == 10000)
		strcpy(str,"10000");
	else if(n == 20000)
		strcpy(str,"20000");
	else if(n == 40000)
		strcpy(str,"40000");
	else if(n == 80000)
		strcpy(str,"80000");
	else if(n == 160000)
		strcpy(str,"160000");
	else if(n == 320000)
		strcpy(str,"320000");
	else if(n == 640000)
		strcpy(str,"640000");
	else if(n == 1250000)
		strcpy(str,"1250000");
	else if(n == 2500000)
		strcpy(str,"2500000");
	else if(n == 5000000)
		strcpy(str,"5000000");
	else if(n == 10000000)
		strcpy(str,"10000000");
	return str;
}

void gameLayout(struct player p, int l1, int l2, int l3, int l4)
{
	int i;
	cleardevice();
	setbkcolor(6);
	outtextxy(200,50,"WELCOME TO KBC");
	settextstyle(0,0,1);
	outtextxy(450,90,"15 - 10000000");
	outtextxy(450,100,"14 - 5000000");
	outtextxy(450,110,"13 - 2500000");
	outtextxy(450,120,"12 - 1250000");
	outtextxy(450,130,"11 - 640000");
	outtextxy(450,140,"10 - 320000");
	outtextxy(450,150,"9 -  160000");
	outtextxy(450,160,"8 -  80000");
	outtextxy(450,170,"7 -  40000");
	outtextxy(450,180,"6 -  20000");
	outtextxy(450,190,"5 -  10000");
	outtextxy(450,200,"4 -  5000");
	outtextxy(450,210,"3 -  3000");
	outtextxy(450,220,"2 -  2000");
	outtextxy(450,230,"1 -  1000");
	outtextxy(50,120,"Name : ");
	outtextxy(100,120,p.name);
	outtextxy(220,120,"Current Ammount : ");
	outtextxy(360,120,convert_long(p.salary));
	circle(100,210,30);
	if(l1 == 1)
		outtextxy(80,250,"press a");
	else {
		line(70,180,130,240);
		line(130,180,70,240);
	}
	line(90,200,90,220);
	line(90,220,120,220);
	line(96,220,96,216);
	line(97,220,97,216);
	line(102,220,102,214);
	line(103,220,103,214);
	line(108,220,108,218);
	line(109,220,109,218);
	line(116,220,116,212);
	line(117,220,117,212);
	circle(180,210,30);
	if(l2 == 1)
		outtextxy(160,250,"press c");
	else {
		line(150,180,210,240);
		line(210,180,150,240);
	}
	settextstyle(1,0,1);
	outtextxy(180,200,"?");
	circle(260,210,30);
	settextstyle(0,0,1);
	if(l3 == 1)
		outtextxy(240,250,"press f");
	else {
		line(230,180,290,240);
		line(290,180,230,240);
	}
	outtextxy(240,210,"50:50");
	circle(340,205,30);
	if(l4 == 1)
		outtextxy(320,250,"press p");
	else {
		line(310,180,370,240);
		line(370,180,310,240);
	}
	for(i=1;i<=3;i++){
		circle(337,200,i);
		circle(343,215,i);
	}
	arc(365,200,180,210,30);
	arc(365,200,180,210,29);
	line(100,300,520,300);
	arc(100,315,90,150,15);
	line(86,308,75,330);
	line(75,330,0,330);
	line(75,334,0,334);
	line(75,334,86,346);
	arc(100,338,210,270,15);
	line(100,353,520,353);
	arc(520,315,30,90,15);
	line(534,308,545,330);
	line(545,330,700,330);
	line(545,334,700,334);
	line(545,334,534,346);
	arc(520,338,270,330,15);
	//        option 1
	line(100,358,275,358);
	arc(100,373,90,150,15);
	line(86,366,75,380);
	line(75,380,0,380);
	line(75,384,0,384);
	line(75,384,86,398);
	arc(100,390,210,270,15);
	line(100,405,275,405);
	arc(275,373,30,90,15);
	line(289,366,300,380);
	line(300,380,320,380);
	line(300,384,320,384);
	line(300,384,289,398);
	arc(276,390,270,330,15);
	//        option 2
	line(345,358,520,358);
	arc(345,373,90,150,15);
	line(331,366,320,380);
	line(320,384,331,398);
	arc(345,390,210,270,15);
	line(345,405,520,405);
	arc(520,373,30,90,15);
	line(534,366,545,380);
	line(545,380,700,380);
	line(545,384,700,384);
	line(545,384,534,398);
	arc(521,390,270,330,15);
	//        option 3
	line(100,410,275,410);
	arc(100,425,90,150,15);
	line(86,418,75,432);
	line(75,432,0,432);
	line(75,436,0,436);
	line(75,436,86,450);
	arc(100,442,210,270,15);
	line(100,457,275,457);
	arc(275,425,30,90,15);
	line(289,418,300,432);
	line(300,432,320,432);
	line(300,436,320,436);
	line(300,436,289,450);
	arc(276,442,270,330,15);
	//        option 4
	line(345,410,520,410);
	arc(345,425,90,150,15);
	line(331,418,320,432);
	line(320,436,331,450);
	arc(345,442,210,270,15);
	line(345,457,520,457);
	arc(520,425,30,90,15);
	line(534,418,545,432);
	line(545,432,700,432);
	line(545,436,700,436);
	line(545,436,534,450);
	arc(521,442,270,330,15);
}
void game(struct player p)
{
	int lifeline[4] = {1,1,1,1},qus = 1,i = 0,j,k,l;
	int fa,fb,aud[4] = {0};
	char op[4][2][20] = {{"",""},{"",""},{"",""},{"",""}};
	char ch,q[200] = "";
	char ques[3][50] = {"","",""};
	char ans[2];
	FILE *question;
	while(1) {
		gameLayout(p,lifeline[0],lifeline[1],lifeline[2],lifeline[3]);
		if(qus <= 5) {
			question = fopen("kquse.txt","r");
			fread(&e,sizeof(e),1,question);
			strcpy(q,e.qus);
			j = 0;
			k = 0;
			l = 0;
			for(j=0;q[j]!='\0';j++) {
				if(((l+1)%46) == 0) {
					l = 0;
					k++;
				}
				ques[k][l++] = q[j];
				ques[k][l] = '\0';
			}
			k++;
			for(;k<3;k++)
				strcpy(ques[k],"");
			outtextxy(110,310,ques[0]);
			outtextxy(110,320,ques[1]);
			outtextxy(110,330,ques[2]);
			j = 0;
			k = 0;
			l = 0;
			for(j=0;e.op1[j]!='\0';j++) {
				if(((l+1)%20) == 0) {
					l = 0;
					k++;
				}
				op[0][k][l++] = e.op1[j];
				op[0][k][l] = '\0';
			}
			k++;
			for(;k<2;k++)
				strcpy(op[0][k],"");
			outtextxy(110,368,op[0][0]);
			outtextxy(110,378,op[0][1]);
			j = 0;
			k = 0;
			l = 0;
			for(j=0;e.op2[j]!='\0';j++) {
				if(((l+1)%20) == 0) {
					l = 0;
					k++;
				}
				op[1][k][l++] = e.op2[j];
				op[1][k][l] = '\0';
			}
			k++;
			for(;k<2;k++)
				strcpy(op[1][k],"");
			outtextxy(355,368,op[1][0]);
			outtextxy(355,378,op[1][1]);
			j = 0;
			k = 0;
			l = 0;
			for(j=0;e.op3[j]!='\0';j++) {
				if(((l+1)%20) == 0) {
					l = 0;
					k++;
				}
				op[2][k][l++] = e.op3[j];
				op[2][k][l] = '\0';
			}
			k++;
			for(;k<2;k++)
				strcpy(op[2][k],"");
			outtextxy(110,420,op[2][0]);
			outtextxy(110,430,op[2][1]);
			j = 0;
			k = 0;
			l = 0;
			for(j=0;e.op4[j]!='\0';j++) {
				if(((l+1)%20) == 0) {
					l = 0;
					k++;
				}
				op[3][k][l++] = e.op4[j];
				op[3][k][l] = '\0';
			}
			k++;
			for(;k<2;k++)
				strcpy(op[3][k],"");
			outtextxy(355,420,op[3][0]);
			outtextxy(355,430,op[3][1]);
			EASY:
			ch = getch();
			if(ch == '0') {
				remove_e(q);
				game_over(p,1,qus);
			}
			else if(ch == '1') {
				if(e.ans == 1) {
					p.salary = get_salary(qus);
					qus++;
					fcloseall();
					remove_e(q);
				}
				else {
					fcloseall();
					remove_e(q);
					game_over(p,0,qus);
				}
			}
			else if(ch == '2') {
				if(e.ans == 2) {
					p.salary = get_salary(qus);
					qus++;
					fcloseall();
					remove_e(q);
				}
				else {
					fcloseall();
					remove_e(q);
					game_over(p,0,qus);
				}
			}
			else if(ch == '3') {
				if(e.ans == 3) {
					p.salary = get_salary(qus);
					qus++;
					fcloseall();
					remove_e(q);
				}
				else {
					fcloseall();
					remove_e(q);
					game_over(p,0,qus);
				}
			}
			else if(ch == '4') {
				if(e.ans == 4) {
					p.salary = get_salary(qus);
					qus++;
					fcloseall();
					remove_e(q);
				}
				else {
					fcloseall();
					remove_e(q);
					game_over(p,0,qus);
				}
			}
			else if(ch == 'p') {
				if(lifeline[3] == 1) {
					setfillstyle(SOLID_FILL,RED);
					bar(150,170,500,250);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(155,175,495,245);
					setcolor(9);
					settextstyle(0,0,1);
					for(i=1;i<=3;i++){
						circle(300,190,i);
						circle(306,205,i);
					}
					arc(328,190,180,210,30);
					arc(328,190,180,210,29);
					for(i=0;i<5;i++) {
						outtextxy(310+(10*i),200,".");
						delay(300);
					}
					outtextxy(280,220,"Answer is :");
					ans[0] = '0' + e.ans;
					ans[1] = NULL;
					outtextxy(370,220,ans);
					getch();
					lifeline[3] = 0;
				}
				else {
					setfillstyle(SOLID_FILL,RED);
					bar(150,200,450,260);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(155,215,445,255);
					setcolor(9);
					settextstyle(0,0,1);
					outtextxy(210,225,"You Already Used it");
					getch();
				}
				gameLayout(p,lifeline[0],lifeline[1],lifeline[2],lifeline[3]);
				outtextxy(110,310,ques[0]);
				outtextxy(110,320,ques[1]);
				outtextxy(110,330,ques[2]);
				outtextxy(110,368,op[0][0]);
				outtextxy(110,378,op[0][1]);
				outtextxy(355,368,op[1][0]);
				outtextxy(355,378,op[1][1]);
				outtextxy(110,430,op[2][0]);
				outtextxy(110,430,op[2][1]);
				outtextxy(355,430,op[3][0]);
				outtextxy(355,430,op[3][1]);
				goto EASY;
			}
			else if(ch == 'c') {
				clrscr();
				if(lifeline[1] == 1) {
					fcloseall();
					remove_e(q);
					fread(&e,sizeof(e),1,question);
					lifeline[1] = 0;
				}
				else {
					setfillstyle(SOLID_FILL,RED);
					bar(150,200,450,260);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(155,215,445,255);
					setcolor(9);
					settextstyle(0,0,1);
					outtextxy(210,225,"You Already Used it");
					getch();
				}
				gameLayout(p,lifeline[0],lifeline[1],lifeline[2],lifeline[3]);
				strcpy(q,e.qus);
				j = 0;
				k = 0;
				l = 0;
				for(j=0;q[j]!='\0';j++) {
					if(((l+1)%46) == 0) {
						l = 0;
						k++;
					}
					ques[k][l++] = q[j];
					ques[k][l] = '\0';
				}
				k++;
				for(;k<3;k++)
					strcpy(ques[k],"");
				outtextxy(110,310,ques[0]);
				outtextxy(110,320,ques[1]);
				outtextxy(110,330,ques[2]);
				j = 0;
				k = 0;
				l = 0;
				for(j=0;e.op1[j]!='\0';j++) {
					if(((l+1)%20) == 0) {
						l = 0;
						k++;
					}
					op[0][k][l++] = e.op1[j];
					op[0][k][l] = '\0';
				}
				k++;
				for(;k<2;k++)
					strcpy(op[0][k],"");
				outtextxy(110,368,op[0][0]);
				outtextxy(110,378,op[0][1]);
				j = 0;
				k = 0;
				l = 0;
				for(j=0;e.op2[j]!='\0';j++) {
					if(((l+1)%20) == 0) {
						l = 0;
						k++;
					}
					op[1][k][l++] = e.op2[j];
					op[1][k][l] = '\0';
				}
				k++;
				for(;k<2;k++)
					strcpy(op[1][k],"");
				outtextxy(355,368,op[1][0]);
				outtextxy(355,378,op[1][1]);
				j = 0;
				k = 0;
				l = 0;
				for(j=0;e.op3[j]!='\0';j++) {
					if(((l+1)%20) == 0) {
						l = 0;
						k++;
					}
					op[2][k][l++] = e.op3[j];
					op[2][k][l] = '\0';
				}
				k++;
				for(;k<2;k++)
					strcpy(op[2][k],"");
				outtextxy(110,430,op[2][0]);
				outtextxy(110,430,op[2][1]);
				j = 0;
				k = 0;
				l = 0;
				for(j=0;e.op4[j]!='\0';j++) {
					if(((l+1)%20) == 0) {
						l = 0;
						k++;
					}
					op[3][k][l++] = e.op4[j];
					op[3][k][l] = '\0';
				}
				k++;
				for(;k<2;k++)
					strcpy(op[3][k],"");
				outtextxy(355,430,op[3][0]);
				outtextxy(355,430,op[3][1]);
				goto EASY;
			}
			else if(ch == 'f') {
				if(lifeline[2] == 1) {
					randomize();
					do {
						do {
							fa = (rand()%4)+1;
						}while(fa == e.ans);
						do {
							fb = (rand()%4)+1;
						}while(fb == e.ans);
					}while(fa == fb);
					strcpy(op[fa-1][0],"");
					strcpy(op[fa-1][1],"");
					strcpy(op[fb-1][0],"");
					strcpy(op[fb-1][1],"");
					lifeline[2] = 0;
				}
				else {
					setfillstyle(SOLID_FILL,RED);
					bar(150,200,450,260);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(155,215,445,255);
					setcolor(9);
					settextstyle(0,0,1);
					outtextxy(210,225,"You Already Used it");
					getch();
				}
				gameLayout(p,lifeline[0],lifeline[1],lifeline[2],lifeline[3]);
				outtextxy(110,310,ques[0]);
				outtextxy(110,320,ques[1]);
				outtextxy(110,330,ques[2]);
				outtextxy(110,368,op[0][0]);
				outtextxy(110,378,op[0][1]);
				outtextxy(355,368,op[1][0]);
				outtextxy(355,378,op[1][1]);
				outtextxy(110,430,op[2][0]);
				outtextxy(110,430,op[2][1]);
				outtextxy(355,430,op[3][0]);
				outtextxy(355,430,op[3][1]);
				goto EASY;
			}
			else if(ch == 'a') {
				if(lifeline[0] == 1) {
					randomize();
					if(!((strcmp(op[0][0],"") == 0) || (strcmp(op[1][0],"") == 0) || (strcmp(op[2][0],"") == 0))) {
						aud[0] = (rand()%80)+1;
						aud[1] = 80 - aud[0];
						aud[2] = (rand()%20)+1;
						aud[3] = 20 - aud[2];
						if(e.ans == 1) {
							if(aud[0] < aud[1]) {
								aud[0] += aud[1];
								aud[1] = aud[0] - aud[1];
								aud[0] -= aud[1];
							}
						}
						else if(e.ans == 2) {
							if(aud[0] > aud[1]) {
								aud[0] += aud[1];
								aud[1] = aud[0] - aud[1];
								aud[0] -= aud[1];
							}
						}
						else if(e.ans == 3) {
							if(aud[0] > aud[1]) {
								aud[0] += aud[2];
								aud[2] = aud[0] - aud[2];
								aud[0] -= aud[2];
							}
							else {
								aud[1] += aud[2];
								aud[2] = aud[1] - aud[2];
								aud[1] -= aud[2];
							}
						}
						else if(e.ans == 4) {
							 if(aud[0] > aud[1]) {
								aud[0] += aud[3];
								aud[3] = aud[0] - aud[3];
								aud[0] -= aud[3];
							}
							else {
								aud[1] += aud[3];
								aud[3] = aud[1] - aud[3];
								aud[1] -= aud[3];
							}
						}
					}
					else {
						aud[0] = (rand()%100);
						aud[1] = 100 - aud[0];
						aud[2] = 0;
						aud[3] = 0;
						if(e.ans == 1) {
							if(aud[1] > aud[0]) {
								aud[0] += aud[1];
								aud[1] = aud[0] - aud[1];
								aud[0] -= aud[1];
							}
							if(strlen(op[1][0]) == 0) {
								if(strlen(op[2][0]) == 0) {
									aud[1] += aud[3];
									aud[3] = aud[1] - aud[3];
									aud[1] -= aud[3];
								}
								else {
									aud[1] += aud[2];
									aud[2] = aud[1] - aud[2];
									aud[1] -= aud[2];
								}
							}
						}
						else if(e.ans == 2) {
							if(aud[0] > aud[1]) {
								aud[0] += aud[1];
								aud[1] = aud[0] - aud[1];
								aud[0] -= aud[1];
							}
							if(strlen(op[0][0]) == 0) {
								if(strlen(op[2][0]) == 0) {
									aud[0] += aud[3];
									aud[3] = aud[0] - aud[3];
									aud[0] -= aud[3];
								}
								else {
									aud[0] += aud[2];
									aud[2] = aud[0] - aud[2];
									aud[0] -= aud[2];
								}
							}
						}
						else if(e.ans == 3) {
							if(aud[1] > aud[0]) {
								aud[2] += aud[1];
								aud[1] = aud[2] - aud[1];
								aud[2] -= aud[1];
							}
							else {
								aud[2] += aud[0];
								aud[0] = aud[2] - aud[0];
								aud[2] -= aud[0];
							}
							if(strlen(op[3][0]) != 0) {
								if(strlen(op[1][0]) == 0) {
									aud[0] += aud[3];
									aud[3] = aud[0] - aud[3];
									aud[0] -= aud[3];
								}
								else {
									aud[1] += aud[3];
									aud[3] = aud[1] - aud[3];
									aud[1] -= aud[3];
								}
							}
						}
						else if(e.ans == 4) {
							if(aud[1] > aud[0]) {
								aud[3] += aud[1];
								aud[1] = aud[3] - aud[1];
								aud[3] -= aud[1];
							}
							else {
								aud[3] += aud[0];
								aud[0] = aud[3] - aud[0];
								aud[3] -= aud[0];
							}
							if(strlen(op[2][0]) != 0) {
								if(strlen(op[1][0]) == 0) {
									aud[0] += aud[2];
									aud[2] = aud[0] - aud[2];
									aud[0] -= aud[2];
								}
								else {
									aud[1] += aud[2];
									aud[2] = aud[1] - aud[2];
									aud[1] -= aud[2];
								}
							}
						}
					}
					setfillstyle(SOLID_FILL,RED);
					bar(250,200,500,330);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(255,215,495,325);
					setcolor(9);
					settextstyle(0,0,1);
					outtextxy(325,220,"Audians Pole");
					line(310,240,310,290);
					line(320,290,420,290);
					setfillstyle(SOLID_FILL,9);
					bar(325,290,340,290-((int)(aud[0]/2)));
					bar(345,290,360,290-((int)(aud[1]/2)));
					bar(365,290,380,290-((int)(aud[2]/2)));
					bar(385,290,400,290-((int)(aud[3]/2)));
					outtextxy(325,300,"A");
					outtextxy(345,300,"B");
					outtextxy(365,300,"C");
					outtextxy(385,300,"D");
					getch();
					lifeline[0] = 0;
				}
				else {
					setfillstyle(SOLID_FILL,RED);
					bar(150,200,450,260);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(155,215,445,255);
					setcolor(9);
					settextstyle(0,0,1);
					outtextxy(210,225,"You Already Used it");
					getch();
				}
				gameLayout(p,lifeline[0],lifeline[1],lifeline[2],lifeline[3]);
				outtextxy(110,310,ques[0]);
				outtextxy(110,320,ques[1]);
				outtextxy(110,330,ques[2]);
				outtextxy(110,368,op[0][0]);
				outtextxy(110,378,op[0][1]);
				outtextxy(355,368,op[1][0]);
				outtextxy(355,378,op[1][1]);
				outtextxy(110,430,op[2][0]);
				outtextxy(110,430,op[2][1]);
				outtextxy(355,430,op[3][0]);
				outtextxy(355,430,op[3][1]);
				goto EASY;
			}
		}
		else if(qus <= 10) {
			question = fopen("kqusm.txt","r");
			fread(&m,sizeof(m),1,question);
			strcpy(q,m.qus);
			j = 0;
			k = 0;
			l = 0;
			for(j=0;q[j]!='\0';j++) {
				if(((l+1)%46) == 0) {
					l = 0;
					k++;
				}
				ques[k][l++] = q[j];
				ques[k][l] = '\0';
			}
			k++;
			for(;k<3;k++)
				strcpy(ques[k],"");
			outtextxy(110,310,ques[0]);
			outtextxy(110,320,ques[1]);
			outtextxy(110,330,ques[2]);
			j = 0;
			k = 0;
			l = 0;
			for(j=0;m.op1[j]!='\0';j++) {
				if(((l+1)%20) == 0) {
					l = 0;
					k++;
				}
				op[0][k][l++] = m.op1[j];
				op[0][k][l] = '\0';
			}
			k++;
			for(;k<2;k++)
				strcpy(op[0][k],"");
			outtextxy(110,368,op[0][0]);
			outtextxy(110,378,op[0][1]);
			j = 0;
			k = 0;
			l = 0;
			for(j=0;m.op2[j]!='\0';j++) {
				if(((l+1)%20) == 0) {
					l = 0;
					k++;
				}
				op[1][k][l++] = m.op2[j];
				op[1][k][l] = '\0';
			}
			k++;
			for(;k<2;k++)
				strcpy(op[1][k],"");
			outtextxy(355,368,op[1][0]);
			outtextxy(355,378,op[1][1]);
			j = 0;
			k = 0;
			l = 0;
			for(j=0;m.op3[j]!='\0';j++) {
				if(((l+1)%20) == 0) {
					l = 0;
					k++;
				}
				op[2][k][l++] = m.op3[j];
				op[2][k][l] = '\0';
			}
			k++;
			for(;k<2;k++)
				strcpy(op[2][k],"");
			outtextxy(110,420,op[2][0]);
			outtextxy(110,430,op[2][1]);
			j = 0;
			k = 0;
			l = 0;
			for(j=0;m.op4[j]!='\0';j++) {
				if(((l+1)%20) == 0) {
					l = 0;
					k++;
				}
				op[3][k][l++] = m.op4[j];
				op[3][k][l] = '\0';
			}
			k++;
			for(;k<2;k++)
				strcpy(op[3][k],"");
			outtextxy(355,420,op[3][0]);
			outtextxy(355,430,op[3][1]);
			MEDIUM:
			ch = getch();
			if(ch == '0') {
				remove_m(q);
				game_over(p,1,qus);
			}
			else if(ch == '1') {
				if(m.ans == 1) {
					p.salary = get_salary(qus);
					qus++;
					fcloseall();
					remove_m(q);
				}
				else {
					fcloseall();
					remove_m(q);
					game_over(p,0,qus);
				}
			}
			else if(ch == '2') {
				if(m.ans == 2) {
					p.salary = get_salary(qus);
					qus++;
					fcloseall();
					remove_m(q);
				}
				else {
					fcloseall();
					remove_m(q);
					game_over(p,0,qus);
				}
			}
			else if(ch == '3') {
				if(m.ans == 3) {
					p.salary = get_salary(qus);
					qus++;
					fcloseall();
					remove_m(q);
				}
				else {
					fcloseall();
					remove_m(q);
					game_over(p,0,qus);
				}
			}
			else if(ch == '4') {
				if(m.ans == 4) {
					p.salary = get_salary(qus);
					qus++;
					fcloseall();
					remove_m(q);
				}
				else {
					fcloseall();
					remove_m(q);
					game_over(p,0,qus);
				}
			}
			else if(ch == 'p') {
				if(lifeline[3] == 1) {
					setfillstyle(SOLID_FILL,RED);
					bar(150,170,500,250);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(155,175,495,245);
					setcolor(9);
					settextstyle(0,0,1);
					for(i=1;i<=3;i++){
						circle(300,190,i);
						circle(306,205,i);
					}
					arc(328,190,180,210,30);
					arc(328,190,180,210,29);
					for(i=0;i<5;i++) {
						outtextxy(310+(10*i),200,".");
						delay(300);
					}
					outtextxy(280,220,"Answer is :");
					ans[0] = '0' + m.ans;
					ans[1] = NULL;
					outtextxy(370,220,ans);
					getch();
					lifeline[3] = 0;
				}
				else {
					setfillstyle(SOLID_FILL,RED);
					bar(150,200,450,260);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(155,215,445,255);
					setcolor(9);
					settextstyle(0,0,1);
					outtextxy(210,225,"You Already Used it");
					getch();
				}
				gameLayout(p,lifeline[0],lifeline[1],lifeline[2],lifeline[3]);
				outtextxy(110,310,ques[0]);
				outtextxy(110,320,ques[1]);
				outtextxy(110,330,ques[2]);
				outtextxy(110,368,op[0][0]);
				outtextxy(110,378,op[0][1]);
				outtextxy(355,368,op[1][0]);
				outtextxy(355,378,op[1][1]);
				outtextxy(110,430,op[2][0]);
				outtextxy(110,430,op[2][1]);
				outtextxy(355,430,op[3][0]);
				outtextxy(355,430,op[3][1]);
				goto MEDIUM;
			}
			else if(ch == 'c') {
				clrscr();
				if(lifeline[1] == 1) {
					fcloseall();
					remove_m(q);
					fread(&m,sizeof(m),1,question);
					lifeline[1] = 0;
				}
				else {
					setfillstyle(SOLID_FILL,RED);
					bar(150,200,450,260);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(155,215,445,255);
					setcolor(9);
					settextstyle(0,0,1);
					outtextxy(210,225,"You Already Used it");
					getch();
				}
				gameLayout(p,lifeline[0],lifeline[1],lifeline[2],lifeline[3]);
				strcpy(q,m.qus);
				j = 0;
				k = 0;
				l = 0;
				for(j=0;q[j]!='\0';j++) {
					if(((l+1)%46) == 0) {
						l = 0;
						k++;
					}
					ques[k][l++] = q[j];
					ques[k][l] = '\0';
				}
				k++;
				for(;k<3;k++)
					strcpy(ques[k],"");
				outtextxy(110,310,ques[0]);
				outtextxy(110,320,ques[1]);
				outtextxy(110,330,ques[2]);
				j = 0;
				k = 0;
				l = 0;
				for(j=0;m.op1[j]!='\0';j++) {
					if(((l+1)%20) == 0) {
						l = 0;
						k++;
					}
					op[0][k][l++] = m.op1[j];
					op[0][k][l] = '\0';
				}
				k++;
				for(;k<2;k++)
					strcpy(op[0][k],"");
				outtextxy(110,368,op[0][0]);
				outtextxy(110,378,op[0][1]);
				j = 0;
				k = 0;
				l = 0;
				for(j=0;m.op2[j]!='\0';j++) {
					if(((l+1)%20) == 0) {
						l = 0;
						k++;
					}
					op[1][k][l++] = m.op2[j];
					op[1][k][l] = '\0';
				}
				k++;
				for(;k<2;k++)
					strcpy(op[1][k],"");
				outtextxy(355,368,op[1][0]);
				outtextxy(355,378,op[1][1]);
				j = 0;
				k = 0;
				l = 0;
				for(j=0;m.op3[j]!='\0';j++) {
					if(((l+1)%20) == 0) {
						l = 0;
						k++;
					}
					op[2][k][l++] = m.op3[j];
					op[2][k][l] = '\0';
				}
				k++;
				for(;k<2;k++)
					strcpy(op[2][k],"");
				outtextxy(110,430,op[2][0]);
				outtextxy(110,430,op[2][1]);
				j = 0;
				k = 0;
				l = 0;
				for(j=0;m.op4[j]!='\0';j++) {
					if(((l+1)%20) == 0) {
						l = 0;
						k++;
					}
					op[3][k][l++] = m.op4[j];
					op[3][k][l] = '\0';
				}
				k++;
				for(;k<2;k++)
					strcpy(op[3][k],"");
				outtextxy(355,430,op[3][0]);
				outtextxy(355,430,op[3][1]);
				goto MEDIUM;
			}
			else if(ch == 'f') {
				if(lifeline[2] == 1) {
					randomize();
					do {
						do {
							fa = (rand()%4)+1;
						}while(fa == m.ans);
						do {
							fb = (rand()%4)+1;
						}while(fb == m.ans);
					}while(fa == fb);
					strcpy(op[fa-1][0],"");
					strcpy(op[fa-1][1],"");
					strcpy(op[fb-1][0],"");
					strcpy(op[fb-1][1],"");
					lifeline[2] = 0;
				}
				else {
					setfillstyle(SOLID_FILL,RED);
					bar(150,200,450,260);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(155,215,445,255);
					setcolor(9);
					settextstyle(0,0,1);
					outtextxy(210,225,"You Already Used it");
					getch();
				}
				gameLayout(p,lifeline[0],lifeline[1],lifeline[2],lifeline[3]);
				outtextxy(110,310,ques[0]);
				outtextxy(110,320,ques[1]);
				outtextxy(110,330,ques[2]);
				outtextxy(110,368,op[0][0]);
				outtextxy(110,378,op[0][1]);
				outtextxy(355,368,op[1][0]);
				outtextxy(355,378,op[1][1]);
				outtextxy(110,430,op[2][0]);
				outtextxy(110,430,op[2][1]);
				outtextxy(355,430,op[3][0]);
				outtextxy(355,430,op[3][1]);
				goto MEDIUM;
			}
			else if(ch == 'a') {
				clrscr();
				if(lifeline[0] == 1) {
					randomize();
					if(!((strcmp(op[0][0],"") == 0) || (strcmp(op[1][0],"") == 0) || (strcmp(op[2][0],"") == 0))) {
						aud[0] = (rand()%80)+1;
						aud[1] = 80 - aud[0];
						aud[2] = (rand()%20)+1;
						aud[3] = 20 - aud[2];
						if(m.ans == 1) {
							if(aud[0] < aud[1]) {
								aud[0] += aud[1];
								aud[1] = aud[0] - aud[1];
								aud[0] -= aud[1];
							}
						}
						else if(m.ans == 2) {
							if(aud[0] > aud[1]) {
								aud[0] += aud[1];
								aud[1] = aud[0] - aud[1];
								aud[0] -= aud[1];
							}
						}
						else if(m.ans == 3) {
							if(aud[0] > aud[1]) {
								aud[0] += aud[2];
								aud[2] = aud[0] - aud[2];
								aud[0] -= aud[2];
							}
							else {
								aud[1] += aud[2];
								aud[2] = aud[1] - aud[2];
								aud[1] -= aud[2];
							}
						}
						else if(m.ans == 4) {
							 if(aud[0] > aud[1]) {
								aud[0] += aud[3];
								aud[3] = aud[0] - aud[3];
								aud[0] -= aud[3];
							}
							else {
								aud[1] += aud[3];
								aud[3] = aud[1] - aud[3];
								aud[1] -= aud[3];
							}
						}
					}
					else {
						aud[0] = (rand()%100);
						aud[1] = 100 - aud[0];
						aud[2] = 0;
						aud[3] = 0;
						if(m.ans == 1) {
							if(aud[1] > aud[0]) {
								aud[0] += aud[1];
								aud[1] = aud[0] - aud[1];
								aud[0] -= aud[1];
							}
							if(strlen(op[1][0]) == 0) {
								if(strlen(op[2][0]) == 0) {
									aud[1] += aud[3];
									aud[3] = aud[1] - aud[3];
									aud[1] -= aud[3];
								}
								else {
									aud[1] += aud[2];
									aud[2] = aud[1] - aud[2];
									aud[1] -= aud[2];
								}
							}
						}
						else if(m.ans == 2) {
							if(aud[0] > aud[1]) {
								aud[0] += aud[1];
								aud[1] = aud[0] - aud[1];
								aud[0] -= aud[1];
							}
							if(strlen(op[0][0]) == 0) {
								if(strlen(op[2][0]) == 0) {
									aud[0] += aud[3];
									aud[3] = aud[0] - aud[3];
									aud[0] -= aud[3];
								}
								else {
									aud[0] += aud[2];
									aud[2] = aud[0] - aud[2];
									aud[0] -= aud[2];
								}
							}
						}
						else if(m.ans == 3) {
							if(aud[1] > aud[0]) {
								aud[2] += aud[1];
								aud[1] = aud[2] - aud[1];
								aud[2] -= aud[1];
							}
							else {
								aud[2] += aud[0];
								aud[0] = aud[2] - aud[0];
								aud[2] -= aud[0];
							}
							if(strlen(op[3][0]) != 0) {
								if(strlen(op[1][0]) == 0) {
									aud[0] += aud[3];
									aud[3] = aud[0] - aud[3];
									aud[0] -= aud[3];
								}
								else {
									aud[1] += aud[3];
									aud[3] = aud[1] - aud[3];
									aud[1] -= aud[3];
								}
							}
						}
						else if(m.ans == 4) {
							if(aud[1] > aud[0]) {
								aud[3] += aud[1];
								aud[1] = aud[3] - aud[1];
								aud[3] -= aud[1];
							}
							else {
								aud[3] += aud[0];
								aud[0] = aud[3] - aud[0];
								aud[3] -= aud[0];
							}
							if(strlen(op[2][0]) != 0) {
								if(strlen(op[1][0]) == 0) {
									aud[0] += aud[2];
									aud[2] = aud[0] - aud[2];
									aud[0] -= aud[2];
								}
								else {
									aud[1] += aud[2];
									aud[2] = aud[1] - aud[2];
									aud[1] -= aud[2];
								}
							}
						}
					}
					setfillstyle(SOLID_FILL,RED);
					bar(250,200,500,330);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(255,215,495,325);
					setcolor(9);
					settextstyle(0,0,1);
					outtextxy(325,220,"Audians Pole");
					line(310,240,310,290);
					line(320,290,420,290);
					setfillstyle(SOLID_FILL,9);
					bar(325,290,340,290-((int)(aud[0]/2)));
					bar(345,290,360,290-((int)(aud[1]/2)));
					bar(365,290,380,290-((int)(aud[2]/2)));
					bar(385,290,400,290-((int)(aud[3]/2)));
					outtextxy(325,300,"A");
					outtextxy(345,300,"B");
					outtextxy(365,300,"C");
					outtextxy(385,300,"D");
					getch();
					lifeline[0] = 0;
				}
				else {
					setfillstyle(SOLID_FILL,RED);
					bar(150,200,450,260);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(155,215,445,255);
					setcolor(9);
					settextstyle(0,0,1);
					outtextxy(210,225,"You Already Used it");
					getch();
				}
				gameLayout(p,lifeline[0],lifeline[1],lifeline[2],lifeline[3]);
				outtextxy(110,310,ques[0]);
				outtextxy(110,320,ques[1]);
				outtextxy(110,330,ques[2]);
				outtextxy(110,368,op[0][0]);
				outtextxy(110,378,op[0][1]);
				outtextxy(355,368,op[1][0]);
				outtextxy(355,378,op[1][1]);
				outtextxy(110,430,op[2][0]);
				outtextxy(110,430,op[2][1]);
				outtextxy(355,430,op[3][0]);
				outtextxy(355,430,op[3][1]);
				goto MEDIUM;
			}
		}
		else if(qus <= 15)
		{
			question = fopen("kqush.txt","r");
			fread(&h,sizeof(h),1,question);
			strcpy(q,h.qus);
			j = 0;
			k = 0;
			l = 0;
			for(j=0;q[j]!='\0';j++) {
				if(((l+1)%46) == 0) {
					l = 0;
					k++;
				}
				ques[k][l++] = q[j];
				ques[k][l] = '\0';
			}
			k++;
			for(;k<3;k++)
				strcpy(ques[k],"");
			outtextxy(110,310,ques[0]);
			outtextxy(110,320,ques[1]);
			outtextxy(110,330,ques[2]);
			j = 0;
			k = 0;
			l = 0;
			for(j=0;h.op1[j]!='\0';j++) {
				if(((l+1)%20) == 0) {
					l = 0;
					k++;
				}
				op[0][k][l++] = h.op1[j];
				op[0][k][l] = '\0';
			}
			k++;
			for(;k<2;k++)
				strcpy(op[0][k],"");
			outtextxy(110,368,op[0][0]);
			outtextxy(110,378,op[0][1]);
			j = 0;
			k = 0;
			l = 0;
			for(j=0;h.op2[j]!='\0';j++) {
				if(((l+1)%20) == 0) {
					l = 0;
					k++;
				}
				op[1][k][l++] = h.op2[j];
				op[1][k][l] = '\0';
			}
			k++;
			for(;k<2;k++)
				strcpy(op[1][k],"");
			outtextxy(355,368,op[1][0]);
			outtextxy(355,378,op[1][1]);
			j = 0;
			k = 0;
			l = 0;
			for(j=0;h.op3[j]!='\0';j++) {
				if(((l+1)%20) == 0) {
					l = 0;
					k++;
				}
				op[2][k][l++] = h.op3[j];
				op[2][k][l] = '\0';
			}
			k++;
			for(;k<2;k++)
				strcpy(op[2][k],"");
			outtextxy(110,420,op[2][0]);
			outtextxy(110,430,op[2][1]);
			j = 0;
			k = 0;
			l = 0;
			for(j=0;h.op4[j]!='\0';j++) {
				if(((l+1)%20) == 0) {
					l = 0;
					k++;
				}
				op[3][k][l++] = h.op4[j];
				op[3][k][l] = '\0';
			}
			k++;
			for(;k<2;k++)
				strcpy(op[3][k],"");
			outtextxy(355,420,op[3][0]);
			outtextxy(355,430,op[3][1]);
			HARD:
			ch = getch();
			if(ch == '0') {
				remove_h(q);
				game_over(p,1,qus);
			}
			else if(ch == '1') {
				if(h.ans == 1) {
					p.salary = get_salary(qus);
					qus++;
					fcloseall();
					remove_h(q);
				}
				else {
					fcloseall();
					remove_h(q);
					game_over(p,0,qus);
				}
			}
			else if(ch == '2') {
				if(h.ans == 2) {
					p.salary = get_salary(qus);
					qus++;
					fcloseall();
					remove_h(q);
				}
				else {
					fcloseall();
					remove_h(q);
					game_over(p,0,qus);
				}
			}
			else if(ch == '3') {
				if(h.ans == 3) {
					p.salary = get_salary(qus);
					qus++;
					fcloseall();
					remove_h(q);
				}
				else {
					fcloseall();
					remove_h(q);
					game_over(p,0,qus);
				}
			}
			else if(ch == '4') {
				if(h.ans == 4) {
					p.salary = get_salary(qus);
					qus++;
					fcloseall();
					remove_h(q);
				}
				else {
					fcloseall();
					remove_h(q);
					game_over(p,0,qus);
				}
			}
			else if(ch == 'p') {
				if(lifeline[3] == 1) {
					setfillstyle(SOLID_FILL,RED);
					bar(150,170,500,250);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(155,175,495,245);
					setcolor(9);
					settextstyle(0,0,1);
					for(i=1;i<=3;i++){
						circle(300,190,i);
						circle(306,205,i);
					}
					arc(328,190,180,210,30);
					arc(328,190,180,210,29);
					for(i=0;i<5;i++) {
						outtextxy(310+(10*i),200,".");
						delay(300);
					}
					outtextxy(280,220,"Answer is :");
					ans[0] = '0' + h.ans;
					ans[1] = NULL;
					outtextxy(370,220,ans);
					getch();
					lifeline[3] = 0;
				}
				else {
					setfillstyle(SOLID_FILL,RED);
					bar(150,200,450,260);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(155,215,445,255);
					setcolor(9);
					settextstyle(0,0,1);
					outtextxy(210,225,"You Already Used it");
					getch();
				}
				gameLayout(p,lifeline[0],lifeline[1],lifeline[2],lifeline[3]);
				outtextxy(110,310,ques[0]);
				outtextxy(110,320,ques[1]);
				outtextxy(110,330,ques[2]);
				outtextxy(110,368,op[0][0]);
				outtextxy(110,378,op[0][1]);
				outtextxy(355,368,op[1][0]);
				outtextxy(355,378,op[1][1]);
				outtextxy(110,430,op[2][0]);
				outtextxy(110,430,op[2][1]);
				outtextxy(355,430,op[3][0]);
				outtextxy(355,430,op[3][1]);
				goto HARD;
			}
			else if(ch == 'c') {
				clrscr();
				if(lifeline[1] == 1) {
					fcloseall();
					remove_h(q);
					fread(&h,sizeof(h),1,question);
					lifeline[1] = 0;
				}
				else {
					setfillstyle(SOLID_FILL,RED);
					bar(150,200,450,260);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(155,215,445,255);
					setcolor(9);
					settextstyle(0,0,1);
					outtextxy(210,225,"You Already Used it");
					getch();
				}
				gameLayout(p,lifeline[0],lifeline[1],lifeline[2],lifeline[3]);
				strcpy(q,h.qus);
				j = 0;
				k = 0;
				l = 0;
				for(j=0;q[j]!='\0';j++) {
					if(((l+1)%46) == 0) {
						l = 0;
						k++;
					}
					ques[k][l++] = q[j];
					ques[k][l] = '\0';
				}
				k++;
				for(;k<3;k++)
					strcpy(ques[k],"");
				outtextxy(110,310,ques[0]);
				outtextxy(110,320,ques[1]);
				outtextxy(110,330,ques[2]);
				j = 0;
				k = 0;
				l = 0;
				for(j=0;h.op1[j]!='\0';j++) {
					if(((l+1)%20) == 0) {
						l = 0;
						k++;
					}
					op[0][k][l++] = h.op1[j];
					op[0][k][l] = '\0';
				}
				k++;
				for(;k<2;k++)
					strcpy(op[0][k],"");
				outtextxy(110,368,op[0][0]);
				outtextxy(110,378,op[0][1]);
				j = 0;
				k = 0;
				l = 0;
				for(j=0;h.op2[j]!='\0';j++) {
					if(((l+1)%20) == 0) {
						l = 0;
						k++;
					}
					op[1][k][l++] = h.op2[j];
					op[1][k][l] = '\0';
				}
				k++;
				for(;k<2;k++)
					strcpy(op[1][k],"");
				outtextxy(355,368,op[1][0]);
				outtextxy(355,378,op[1][1]);
				j = 0;
				k = 0;
				l = 0;
				for(j=0;h.op3[j]!='\0';j++) {
					if(((l+1)%20) == 0) {
						l = 0;
						k++;
					}
					op[2][k][l++] = h.op3[j];
					op[2][k][l] = '\0';
				}
				k++;
				for(;k<2;k++)
					strcpy(op[2][k],"");
				outtextxy(110,430,op[2][0]);
				outtextxy(110,430,op[2][1]);
				j = 0;
				k = 0;
				l = 0;
				for(j=0;h.op4[j]!='\0';j++) {
					if(((l+1)%20) == 0) {
						l = 0;
						k++;
					}
					op[3][k][l++] = h.op4[j];
					op[3][k][l] = '\0';
				}
				k++;
				for(;k<2;k++)
					strcpy(op[3][k],"");
				outtextxy(355,430,op[3][0]);
				outtextxy(355,430,op[3][1]);
				goto HARD;
			}
			else if(ch == 'f') {
				if(lifeline[2] == 1) {
					randomize();
					do {
						do {
							fa = (rand()%4)+1;
						}while(fa == h.ans);
						do {
							fb = (rand()%4)+1;
						}while(fb == h.ans);
					}while(fa == fb);
					strcpy(op[fa-1][0],"");
					strcpy(op[fa-1][1],"");
					strcpy(op[fb-1][0],"");
					strcpy(op[fb-1][1],"");
					lifeline[2] = 0;
				}
				else {
					setfillstyle(SOLID_FILL,RED);
					bar(150,200,450,260);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(155,215,445,255);
					setcolor(9);
					settextstyle(0,0,1);
					outtextxy(210,225,"You Already Used it");
					getch();
				}
				gameLayout(p,lifeline[0],lifeline[1],lifeline[2],lifeline[3]);
				outtextxy(110,310,ques[0]);
				outtextxy(110,320,ques[1]);
				outtextxy(110,330,ques[2]);
				outtextxy(110,368,op[0][0]);
				outtextxy(110,378,op[0][1]);
				outtextxy(355,368,op[1][0]);
				outtextxy(355,378,op[1][1]);
				outtextxy(110,430,op[2][0]);
				outtextxy(110,430,op[2][1]);
				outtextxy(355,430,op[3][0]);
				outtextxy(355,430,op[3][1]);
				goto HARD;
			}
			else if(ch == 'a') {
				clrscr();
				if(lifeline[0] == 1) {
					randomize();
					if(!((strcmp(op[0][0],"") == 0) || (strcmp(op[1][0],"") == 0) || (strcmp(op[2][0],"") == 0))) {
						aud[0] = (rand()%80)+1;
						aud[1] = 80 - aud[0];
						aud[2] = (rand()%20)+1;
						aud[3] = 20 - aud[2];
						if(h.ans == 1) {
							if(aud[0] < aud[1]) {
								aud[0] += aud[1];
								aud[1] = aud[0] - aud[1];
								aud[0] -= aud[1];
							}
						}
						else if(h.ans == 2) {
							if(aud[0] > aud[1]) {
								aud[0] += aud[1];
								aud[1] = aud[0] - aud[1];
								aud[0] -= aud[1];
							}
						}
						else if(h.ans == 3) {
							if(aud[0] > aud[1]) {
								aud[0] += aud[2];
								aud[2] = aud[0] - aud[2];
								aud[0] -= aud[2];
							}
							else {
								aud[1] += aud[2];
								aud[2] = aud[1] - aud[2];
								aud[1] -= aud[2];
							}
						}
						else if(h.ans == 4) {
							 if(aud[0] > aud[1]) {
								aud[0] += aud[3];
								aud[3] = aud[0] - aud[3];
								aud[0] -= aud[3];
							}
							else {
								aud[1] += aud[3];
								aud[3] = aud[1] - aud[3];
								aud[1] -= aud[3];
							}
						}
					}
					else {
						aud[0] = (rand()%100);
						aud[1] = 100 - aud[0];
						aud[2] = 0;
						aud[3] = 0;
						if(h.ans == 1) {
							if(aud[1] > aud[0]) {
								aud[0] += aud[1];
								aud[1] = aud[0] - aud[1];
								aud[0] -= aud[1];
							}
							if(strlen(op[1][0]) == 0) {
								if(strlen(op[2][0]) == 0) {
									aud[1] += aud[3];
									aud[3] = aud[1] - aud[3];
									aud[1] -= aud[3];
								}
								else {
									aud[1] += aud[2];
									aud[2] = aud[1] - aud[2];
									aud[1] -= aud[2];
								}
							}
						}
						else if(h.ans == 2) {
							if(aud[0] > aud[1]) {
								aud[0] += aud[1];
								aud[1] = aud[0] - aud[1];
								aud[0] -= aud[1];
							}
							if(strlen(op[0][0]) == 0) {
								if(strlen(op[2][0]) == 0) {
									aud[0] += aud[3];
									aud[3] = aud[0] - aud[3];
									aud[0] -= aud[3];
								}
								else {
									aud[0] += aud[2];
									aud[2] = aud[0] - aud[2];
									aud[0] -= aud[2];
								}
							}
						}
						else if(h.ans == 3) {
							if(aud[1] > aud[0]) {
								aud[2] += aud[1];
								aud[1] = aud[2] - aud[1];
								aud[2] -= aud[1];
							}
							else {
								aud[2] += aud[0];
								aud[0] = aud[2] - aud[0];
								aud[2] -= aud[0];
							}
							if(strlen(op[3][0]) != 0) {
								if(strlen(op[1][0]) == 0) {
									aud[0] += aud[3];
									aud[3] = aud[0] - aud[3];
									aud[0] -= aud[3];
								}
								else {
									aud[1] += aud[3];
									aud[3] = aud[1] - aud[3];
									aud[1] -= aud[3];
								}
							}
						}
						else if(h.ans == 4) {
							if(aud[1] > aud[0]) {
								aud[3] += aud[1];
								aud[1] = aud[3] - aud[1];
								aud[3] -= aud[1];
							}
							else {
								aud[3] += aud[0];
								aud[0] = aud[3] - aud[0];
								aud[3] -= aud[0];
							}
							if(strlen(op[2][0]) != 0) {
								if(strlen(op[1][0]) == 0) {
									aud[0] += aud[2];
									aud[2] = aud[0] - aud[2];
									aud[0] -= aud[2];
								}
								else {
									aud[1] += aud[2];
									aud[2] = aud[1] - aud[2];
									aud[1] -= aud[2];
								}
							}
						}
					}
					setfillstyle(SOLID_FILL,RED);
					bar(250,200,500,330);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(255,215,495,325);
					setcolor(9);
					settextstyle(0,0,1);
					outtextxy(325,220,"Audians Pole");
					line(310,240,310,290);
					line(320,290,420,290);
					setfillstyle(SOLID_FILL,9);
					bar(325,290,340,290-((int)(aud[0]/2)));
					bar(345,290,360,290-((int)(aud[1]/2)));
					bar(365,290,380,290-((int)(aud[2]/2)));
					bar(385,290,400,290-((int)(aud[3]/2)));
					outtextxy(325,300,"A");
					outtextxy(345,300,"B");
					outtextxy(365,300,"C");
					outtextxy(385,300,"D");
					getch();
					lifeline[0] = 0;
				}
				else {
					setfillstyle(SOLID_FILL,RED);
					bar(150,200,450,260);
					setfillstyle(SOLID_FILL,YELLOW);
					bar(155,215,445,255);
					setcolor(9);
					settextstyle(0,0,1);
					outtextxy(210,225,"You Already Used it");
					getch();
				}
				gameLayout(p,lifeline[0],lifeline[1],lifeline[2],lifeline[3]);
				outtextxy(110,310,ques[0]);
				outtextxy(110,320,ques[1]);
				outtextxy(110,330,ques[2]);
				outtextxy(110,368,op[0][0]);
				outtextxy(110,378,op[0][1]);
				outtextxy(355,368,op[1][0]);
				outtextxy(355,378,op[1][1]);
				outtextxy(110,430,op[2][0]);
				outtextxy(110,430,op[2][1]);
				outtextxy(355,430,op[3][0]);
				outtextxy(355,430,op[3][1]);
				goto HARD;
			}
		}
		if(qus > 15) {
			game_over(p,1,qus);
			break;
		}
	}
}

long get_salary(int qus)
{
	long salary;
	switch(qus)
	{
		case 1:salary = 1000;
		break;
		case 2:salary = 2000;
		break;
		case 3:salary = 3000;
		break;
		case 4:salary = 5000;
		break;
		case 5:salary = 10000;
		break;
		case 6:salary = 20000;
		break;
		case 7:salary = 40000;
		break;
		case 8:salary = 80000;
		break;
		case 9:salary = 160000;
		break;
		case 10:salary = 320000;
		break;
		case 11:salary = 640000;
		break;
		case 12:salary = 1250000;
		break;
		case 13:salary = 2500000;
		break;
		case 14:salary = 5000000;
		break;
		case 15:salary = 10000000;
		break;
	}
	return salary;
}

void game_over(struct player p, int n,int qus)
{
	char str[13];
	int i;
	FILE *play;
	cleardevice();
	play = fopen("kplayer.txt","a");
	if(n == 0) {
		if(p.salary < 10000)
			p.salary = 0;
		else if(p.salary < 320000)
			p.salary = 10000;
		else if(p.salary < 10000000)
			p.salary = 320000;
	}
	if(p.salary == 0) {
		settextstyle(1,0,1);
		outtextxy(200,200,"Sorry, You have won 0 Rupees");
		outtextxy(300,200,str);
	}
	else {
		settextstyle(0,0,2);
		outtextxy(200,50,"Congratulation");
		settextstyle(0,0,1);
		for(i=0;i<(qus*2);i++)
			line(200,300-(i*3),400,300-(i*3));
		line(220,(300-(i*3))-30,420,(300-(i*3))-30);
		line(200,300-(i*3),220,(300-(i*3))-30);
		for(i=0;i<(qus*2);i++)
			line(400,300-(i*3),420,(300-(i*3))-30);
		outtextxy(220,(300-(i*3))-28,"1000");
		outtextxy(370,(300-(i*3))-8,"1000");
		circle(300,(300-(i*3))-14,13);
		outtextxy(290,(300-(i*3))-18,"KBC");
		outtextxy(220,350,"You Have Won ");
		strcpy(str,convert_long(p.salary));
		strcat(str," Rupees");
		outtextxy(322,350,str);
	}
	fwrite(&p,sizeof(p),1,play);
	getch();
	main_menu();
}

void remove_e(char str[])
{
	FILE *main,*backup,*_new;
	main = fopen("kquse.txt","r");
	backup = fopen("kbacke.txt","a");
	_new = fopen("abc.txt","a");
	while(fread(&e,sizeof(e),1,main) == 1) {
		if(strcmp(e.qus,str) == 0)
			fwrite(&e,sizeof(e),1,backup);
		else
			fwrite(&e,sizeof(e),1,_new);
	}
	if(feof(_new)) {
		fcloseall();
		remove("kquse.txt");
		rename("abc.txt","kquse.txt");
	}
	else
	{
		fcloseall();
		remove("kquse.txt");
		rename("kbacke.txt","kquse.txt");
		rename("abc.txt","kbacke.txt");
	}
}

void remove_m(char str[])
{
	FILE *main,*backup,*_new;
	main = fopen("kqusm.txt","r");
	backup = fopen("kbackm.txt","a");
	_new = fopen("abc.txt","a");
	while(fread(&m,sizeof(m),1,main) == 1) {
		if(strcmp(m.qus,str) == 0)
			fwrite(&m,sizeof(m),1,backup);
		else
			fwrite(&m,sizeof(m),1,_new);
	}
	if(feof(_new)) {
		fcloseall();
		remove("kqusm.txt");
		rename("abc.txt","kqusm.txt");
	}
	else
	{
		fcloseall();
		remove("kqusm.txt");
		rename("kbackm.txt","kqusm.txt");
		rename("abc.txt","kbackm.txt");
	}
}

void remove_h(char str[])
{
	FILE *main,*backup,*_new;
	main = fopen("kqush.txt","r");
	backup = fopen("kbackh.txt","a");
	_new = fopen("abc.txt","a");
	while(fread(&h,sizeof(h),1,main) == 1) {
		if(strcmp(h.qus,str) == 0)
			fwrite(&h,sizeof(h),1,backup);
		else
			fwrite(&h,sizeof(h),1,_new);
	}
	if(feof(_new)) {
		fcloseall();
		remove("kqush.txt");
		rename("abc.txt","kqush.txt");
	}
	else
	{
		fcloseall();
		remove("kqush.txt");
		rename("kbackh.txt","kqush.txt");
		rename("abc.txt","kbackh.txt");
	}
}
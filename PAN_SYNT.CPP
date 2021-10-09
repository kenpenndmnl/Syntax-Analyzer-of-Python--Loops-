/*Programmer: Kenyleen D. Pan
BSIT I-1
E-mail	: kenypan@yahoo.com
Final Project for Second Semester 2018-2019
*/
#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<process.h>
#include<graphics.h>
#include<dos.h>
#include<string.h>

void menu();
void file_B(char fname[]);
void while_loop(char str[100]);
void for_loop(char str[100]);


void box(int x, int y, int x2, int y2)
{
	int temp;
	temp=x;
	for(;x<=y;x++)
	{
		gotoxy(x,x2);
		cout<<"\xB0";
		gotoxy(x,y2);
		cout<<"\xB0";
	}
	x=temp;
	for(;x2<=y2; x2++)
	{
		gotoxy(x,x2);
		cout<<"\xB0";
		gotoxy(y,x2);
		cout<<"\xB0";
	}
}

void grid1(int x, int y, int x1)
{
	for(; x <= x1 ; x++)
	{
		gotoxy(x,y); cout << "\xB0";
	}
}

void grid2(int x, int y, int y1)
{
	for(;y <= y1; y++)
	{
		gotoxy(x,y); cout << "\xB0";
	}
}

void opening()
{
	clrscr();
	box(1,79,1,24);
	gotoxy(30,13); cout << "Opening the file ...";
	delay(500);
}

void closing()
{
	clrscr();
	box(1,79,1,24);
	gotoxy(28,13); cout << "Saving and closing the file ...";
	delay(500);
}

void file_A(char fname[])
{
	ofstream fout;
	char string[100], c;
	int ch = 0, i = 0;
	char ans = 'y';

	fout.open(fname, ios::out);

	if(!fout)
	{
		gotoxy(31,4); cout << "Error in creating the file." <<endl;
		gotoxy(24,6); cout << "Press any key to return to Home" <<endl;
		getch();
		menu();
	}

	cin.get(c);
	gotoxy(2,3); cout << "Enter Statement/s:";
	while(ans == 'y' || ans == 'Y')
	{
		gotoxy(2,5+i); cin.getline(string, 100);
		fout << string <<endl;
		gotoxy(42,5+i);cout << "Do you want to enter more?";
		gotoxy(42,5+i+1);cout << "Y- Yes";
		gotoxy(50,5+i+1);cout << "N- No";
		gotoxy(42,6+i+1);cin >> ans;
		ch++;
		i++;
		cin.get(c);
	}
	fout.close();
	file_B(fname);
	getch();
}

void file_B(char fname[])
{
	int k = 0;
	ifstream fin(fname, ios::in);
	char string[100], ch;
	char WHILE_SY[] = "while";
	int i, j, cnt1 = 0, cnt2 = 0, line = 1;
	if(!fin)
	{
		gotoxy(31,4); cout << "Error in opening the file.";
		gotoxy(24,6); cout << "Press any key to return to Home";
		getch();
		menu();
	}
	fin.seekg(0);

	while(fin)
	{
		gotoxy(2,5+k); fin.getline(string,100);
		fin.get(ch);
		if(line == 1)
		{
			for(i = 0; i < 5; i++)
			{
				for(j = 0; j < 5; j++)
				{
					if(string[i] == WHILE_SY[j])
						cnt1++;
				}
			}
			if(cnt1 >= 5)
				while_loop(string);
			if(cnt1 == 0)
				for_loop(string);
		}
		// for indention, 4 spaces are required to declare as no error
		else
		{
			for(int j = 0; j < 4; j++)
				if(string[j] == ' ')
					cnt2++;
			if(cnt2 != 3)
			{
				gotoxy(3,24);cout << "Error: Indention required.";
			}
		}
	k++;
	line++;
	}
	fin.close();
}

void readFile_B(char fname[])
{
	int k = 0;
	ifstream fin(fname, ios::in);
	char string[100], ch;
	if(!fin)
	{
		gotoxy(31,4); cout << "Error in opening the file.";
		gotoxy(24,6); cout << "Press any key to return to Home";
		getch();
		menu();
	}
	grid1(1,4,80);
	grid1(1,20,80);
	grid2(41,4,20);
	gotoxy(2,2); cout << "Outputting " <<fname;
	fin.seekg(0);
	while(fin)
	{
		fin.get(string,100);
		fin.get(ch);
		gotoxy(2,5+k); cout << string;
		k++;
	}
	fin.close();
	file_B(fname);
}

void while_loop(char str[100])
{
	int cnt1 = 0, cnt2 = 0, i,j, num[100];
	char WHILE_SY[]  = "while", ope[]="<>=";
	int len = strlen(str);

	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
		{
			if(str[i] == WHILE_SY[j])
			{
				cnt1++;
			}
		}
	}

	if(cnt1 == 5)
		num[0] = 1;
	else
		num[0] = 0;

	if(str[len-1] == ':')
		num[1] = 1;
	else
		num[1] = 0;

	for(i = 0; i < len; i++)
	{
		for(j = 0; j < 3; j++)
		{
			if(str[i]==ope[j])
			{
				cnt2++;
			}
		}
	}

	if(cnt2 == 2)
		num[2] = 1;
	else
		num[2] = 0;

	int check = 0;

	for(int k=0; k<3; k++)
		if(num[k] == 1)
			check++;

	int n=0;
	if(check == 3)
	{
		gotoxy(3,21+n);
		cout << "No Error.";
		n++;
	}

	for(int s = 0; s < 3; s++)
	{
		if(num[s] == 0)
		{
			switch(s)
			{
				case 0	:	gotoxy(3,21+n);cout << "Error: 'while' is missing.";
						n++;
						break;
				case 1	:	gotoxy(3,21+n);cout << "Error: ':' is missing.";
						n++;
						break;
				case 2	:	gotoxy(3,21+n);cout << "Error: Conditional operator.";
						n++;
						break;
			}
		}
	}

}

void for_loop(char str[100])
{
	int i, j, s, cnt1 = 0, cnt2 = 0;
	char FOR_SY[] = "for";
	char IN_SY[] = "in";
	int len = strlen(str), num[100];

	for(i = 0; i < 3; i++)
	{
		if(str[i] == FOR_SY[i])
		{
			cnt1++;
		}
	}

	if(cnt1 == 3)
		num[0] = 1;
	else
		num[0] = 0;

	if(str[len-1] == ':')
		num[1] = 1;
	else
		num[1] = 0;

	for(i = 0; i < len; i++)
	{
		for(j = 0; j < 2; j++)
		{
			if(str[i] == IN_SY[j])
				cnt2++;
		}
	}

	if(cnt2 == 2)
		num[2] = 1;
	else
		num[2] = 0;

	int check = 0;

	for(int k = 0; k < 3; k++)
		if(num[k] == 1)
			check++;
	int n = 0;
	if(check == 3)
	{
		gotoxy(3,21+n);
		cout << "No Error";
		n++;
	}

	for(s = 0; s < 3; s++)
	{
		if(num[s] == 0)
		{
			switch(s)
			{
				case 0	:	gotoxy(3,21+n); cout << "Error: 'for' is missing.";
							n++;
							break;
				case 1	:	gotoxy(3,21+n); cout << "Error: ':' is missing.";
							n++;
							break;
				case 2	:	gotoxy(3,21+n);cout << "Error: 'in' is missing.";
							n++;
							break;
			}
		}
	}
}

void menu()
{
	char WHILE_SY[] = "while";
	char fname[50];
	int i, j, cnt1 = 0, cnt2 = 0;
	char choice, stmts[150], ans='y';
	do{
		clrscr();
		int gdriver = DETECT, gmode, i, c = 0;
		initgraph(&gdriver, &gmode, "C:\\Turboc3\\BGI");
		settextstyle(7,0,5);
		outtextxy(90,110,"Python Syntax Analyzer");
		gotoxy(33,12); cout << "Loop Statements";
		gotoxy(24,13); cout << "It is best to study with Python!";
		gotoxy(35,15); cout << "Main Menu";
		gotoxy(30,16); cout << "A- Create a File";
		gotoxy(30,17); cout << "B- Open a File";
		gotoxy(30,18); cout << "C- Enter Statement/s";
		gotoxy(30,19); cout << "D- Exit";
		gotoxy(30,21); cout << "Enter your choice: ";
		cin >> choice;
		closegraph();

		switch(choice)
		{
			case 'A'	:	case 'a'	:		clrscr();
									box(1,79,1,24);
									gotoxy(32,12); cout << "Creating a File";
									gotoxy(28,14); cout << "Enter file name: ";
									cin >>fname;
									opening();
									clrscr();
									grid1(1,4,80);
									grid1(1,20,80);
									grid2(41,4,20);
									gotoxy(2,2); cout << "Inputting to " << fname;
									file_A(fname);
									closing();
									break;
			case 'B'	:	case 'b'	:		clrscr();
									box(1,79,1,24);
									gotoxy(33,12); cout << "Opening a File";
									gotoxy(28,14); cout << "Enter file name: ";
									cin >>fname;
									opening();
									clrscr();
									readFile_B(fname);
									getch();
									closing();
									break;
			case 'C'	:	case 'c'	:	clrscr();
									grid1(1,4,80);
									grid1(1,20,80);
									grid2(41,4,20);
									gotoxy(2,3); cout << "Enter statement/s:";
									while(ans == 'Y' || ans == 'y')
									{
										cin.ignore();
										gotoxy(2,5+c); cin.getline(stmts,150);
										gotoxy(42,5+c); cout << "Do you want to enter more?";
										gotoxy(42,5+c+1); cout << "Y- Yes";
										gotoxy(50,5+c+1); cout << "N- No";
										gotoxy(42,6+c+1); cin >> ans;
										c++;
									}
									if(stmts != "    ")
									{
										for(i = 0; i < 5; i++)
										{
											for(j = 0; j < 5; j++)
											{
												if(stmts[i] == WHILE_SY[j])
													cnt1++;
											}
										}
										if(cnt1 >= 5)
											while_loop(stmts);
										if(cnt1 == 0)
											for_loop(stmts);
									}
									else
									{
										for(int j = 0; j < 4; j++)
											if(stmts[j] == ' ')
												cnt2++;
										if(cnt2 == 4)
										{
											gotoxy(3,24);cout << "No Error.";
										}
										else
										{
											gotoxy(3,24);cout << "Error: Indention required.";
										}
									}
									getch();
									break;
			case 'D'	:	case 'd'	:	exit(0);
			default					:		cout << "Invalid Choice";
									cin >> choice;
									break;
		}
	}while(choice != 'D' || choice != 'd');
}

void main()
{
	menu();
}


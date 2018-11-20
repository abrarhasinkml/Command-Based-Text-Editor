#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include<fstream>


#define MAX_X 79
#define MAX_Y 24
#define MODE_COMMAND 0
#define MODE_INSERT 1

using namespace std;


class ViEditor
{
public:
    string text;// text message of this editor
    string text2;
    int cursor_x; // X location of cursor
    int cursor_y; // X location of cursor
    int mode;   // 0 means command, 1 means insert
    ViEditor ()
    {
        mode=0;
        cursor_x=0;
        cursor_y = 1;
    }
public:
    int getMode ()
    {
        return mode;
    }
    void setMode (int m)
    {
        mode = m;
    }
    void getCursor(int &x, int &y)
    {
        x=cursor_x;
        y=cursor_y;
    }
    void setCursor( int x, int y )
    {
        cursor_x=x;
        cursor_y=y;
    }
    void printStatus (string msg)
    {
        COORD coord;
        coord.X = 0;
        coord.Y = MAX_Y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << msg;
    }
    void printAtCursor (int x, int y, char msg)
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << msg;
    }
    char inputCommand ()
    {
        COORD coord;
        coord.X = 0;
        coord.Y = MAX_Y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        return getche();
    }
    char inputText ()
    {
        COORD coord;
        coord.X = cursor_x;
        coord.Y = cursor_y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        return getche();
    }
    void countchar()
    {
        cout<<"Number of characters input: "<<text.length()<<endl;
    }
    void newline()
    {
        COORD newc;
        newc.X=cursor_x--;
        newc.Y=cursor_y++;

    }
    void cursormoveright()
    {
        COORD rightmove;
        rightmove.X=cursor_x++;
    }
    void cursormoveleft()
    {
        COORD leftmove;
        leftmove.X=cursor_x--;
    }
    void cursormoveup()
    {
        COORD upmove;
        upmove.Y=cursor_y--;
    }
    void cursormovedown()
    {
        COORD downmove;
        downmove.Y=cursor_y++;
    }
    void append()
    {

        cout<< "Enter string you want to append: "<<endl;
        getline(cin, text2);
        text2=text+text2;
        cout<<"Appended text: "<<text2<<endl;
    }
    void save()
    {
        ofstream savefile;
        savefile.open("data.txt", ios::app);
        savefile<<text;
        savefile<<text2;
        savefile.close();

    }
    void open()
    {
        ifstream openf;
        openf.open("data.txt", ios::in);

        char my_character ;
        int number_of_lines=0;

        while (!openf.eof() )
        {

            openf.get(my_character);
            cout <<my_character;
            if (my_character == '\n')
            {
                ++number_of_lines;
            }



        }


    }
    void lineend()
    {
        COORD linend;
        linend.X= cursor_x= 79;
    }
    void bottom()
    {
        COORD btm;
        btm.X=cursor_x=0;
        btm.Y=cursor_y=12;
    }
    void movelinebottom()
    {
        COORD mlb;
        mlb.X=cursor_x=0;
        mlb.Y=cursor_y=12;
        cout<<" "<<text<<endl;
    }
    void gobacktop()
    {
        COORD goback;
        goback.X=cursor_x=0;
        goback.Y=cursor_y=0;
    }

    void rep()
    {
        int x,y;
        getCursor(x,y);
        setCursor(x-2,y);

        text.erase(x,y);


    }

    void movetolinex()
    {
        int c;

        cout<<"\nEnter number of line(between 2 to 23) you want to go to: "<<endl;
        cin>>c;
        COORD e;
        e.Y=cursor_y=c;

    }
    void dlt()
    {
        getCursor(cursor_x,cursor_y);
        setCursor(cursor_x-2,cursor_y);
        getche();
        text.erase(cursor_x,cursor_y);
    }
    void movetoliney()
    {
        int c;

        cout<<"\nEnter number of line(between 2 to 78) you want to go to: "<<endl;
        cin>>c;
        COORD e;
        e.X=cursor_x=c;

    }
    void clearscreen()
    {
        system("cls");
    }
};


int main ()
{
    ViEditor a;

    char ch;
    int x, y;

    do
    {

        if ( a.getMode() == MODE_COMMAND )
        {
            ch = a.inputCommand();
            if ( ch == 27 )//switches to insert mode
            {
                a.setMode( MODE_INSERT );
            }
            else if ( ch == 's' )//saves your input text to file
            {

                a.save();

                a.setMode(MODE_INSERT);

                string msg;
                msg = " bytes stored in data.txt file";
                a.printStatus( msg );
            }
            else if(ch=='c')//counts the numbers of characters you've entered
            {
                a.countchar();
            }
            else if(ch=='n')// jumps to a new line in insert mode
            {

                a.newline();
                a.setMode( MODE_INSERT );
            }

            else if(ch=='u')//cursor moves up
            {
                a.cursormoveup();
                a.setMode(MODE_INSERT);
            }

            else if(ch=='d')//cursor moves down
            {
                a.cursormovedown();
                a.setMode(MODE_INSERT);
            }

            else if(ch=='r')//cursor moves right
            {
                a.cursormoveright();
                a.setMode(MODE_INSERT);
            }
            else if(ch== 'l')//cursor moves left
            {
                a.cursormoveleft();
                a.setMode(MODE_INSERT);

            }
            else if(ch=='o')//opens the saved text from file
            {
                a.open();
                a.setMode(MODE_INSERT);
            }
            else if(ch=='e')//cursor goes to the end of the line
            {
                a.lineend();
                a.setMode(MODE_INSERT);
            }
            else if(ch=='b')//cursor moves to the bottom of insert mode
            {
                a.bottom();
                a.setMode(MODE_INSERT);
            }
            else if(ch=='m')//text moves to the bottom of insert mode
            {
                a.movelinebottom();
                a.setMode(MODE_INSERT);
            }
            else if(ch=='g')//cursor goes back to the top of insert mode
            {
                a.gobacktop();
                a.setMode(MODE_INSERT);
            }
            else if(ch=='x')//asks the user to input a line number and jumps to that line
            {
                a.movetolinex();

                a.setMode(MODE_INSERT);
            }
            else if(ch=='y')//asks the user to input a column number and cursor goes to that point
            {
                a.movetoliney();
                a.setMode(MODE_INSERT);
            }
            else if(ch=='w')//press w to clear screen
            {
                a.clearscreen();
            }


        }
        else
        {
            ch = a.inputText();
            if ( ch == 27 )//escape switches to command mode
            {
                a.setMode( MODE_COMMAND );
                continue;


            }
            else if(ch=='/')//option to append new text with previously entered text
            {
                a.append();

            }
            else if(ch==8)//backspace to replace characters which have the cursor underneath them
            {
                a.rep();

            }
            else if(ch==9)//tab(press twice) to delete a character from the string
            {
                a.dlt();

            }



            a.text += ch;
            a.getCursor( x, y );
            a.setCursor(x+1, y);
        }


        if ( a.getMode() == MODE_COMMAND && ch == 'q' ) break;// q in command mode to exit program

    }
    while ( true );

    return 0;
}

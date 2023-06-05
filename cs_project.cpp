#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

class Tile
{

public:
    string color;

    string win_scheme;

    Tile()
    {

        color = "Blank";

        win_scheme = "";
    }
    Tile(int c) // assigns the color and win scheme
    {

        switch (c)
        {

        case 0:

            color = "orange";

            win_scheme = "V";

            break;

        case 1:

            color = "green";

            win_scheme = "h";

            break;

        case 2:

            color = "yellow";

            win_scheme = "dlr";

            break;

        case 3:
            color = "purple";

            win_scheme = "drl";

            break;
        }
    }

    bool operator==(Tile t) // checks if two tiles have the same color
    {

        if (color == t.color)
        {

            return true;
        }
        else
        {
            return false;
        }
    }
    bool isEmpty() // checks if the tile is empty
    {

        if (color == "Blank")
        {

            return true;
        }
        else
        {

            return false;
        }
    }
    void operator=(Tile t) // assigns a tile to another tile
    {

        color = t.color;

        win_scheme = t.win_scheme;
    }
    Tile operator=(Tile *t) // returns the tile
    {

        *this = *t;

        return *this;
    }
    void display() { cout << color << "'s win scheme is " << win_scheme << endl; } // displays waht the win scheme for the color is

    void print() { cout << color; } // displays the color
};
class Player
{
public:
    string name;
    int number;
    Tile tile;
    Player(string n, int x, Tile t)
    {
        name = n;
        number = x;
        tile = t;
    }
    void info() // displays the player's info
    {
        cout << "The player " << number << " with name " << name << " got the tile color " << tile.color << endl;
        tile.display();
    }
};
class Board
{
public:
    int no_of_rows = 6;
    int no_of_cols = 7;
    Tile board[6][7];
    int blankCount;
    Board() { blankCount = 42; }
    void displayBoard() // displays the board
    {

        cout << "    col1       col2       col3       col4       col5       col6       col7 ";

        cout << endl;
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                cout << " | ";
                board[i][j].print();
                cout << " | ";
            }
            cout << endl;
        }
    }

    bool insert(int c, Tile *t) // inserts a tile in the board based on the chosin column
    {
        for (int i = no_of_rows - 1; i >= 0; i--)
        {
            if (board[i][c].isEmpty())
            {
                board[i][c] = t;
                blankCount--;
                return true;
            }
        }
        cout << "No insert possible" << endl;
        return false;
    }
    bool checkRTLConnected(Tile *winner) // checks purple's win scheme
    {
        for (int i = 0; i < no_of_rows; i++)
        {
            for (int j = 0; j < no_of_cols; j++)
            {
                int x = i;
                int y = j;
                int counter = 0;
                int k = 0;
                while (k < 4 && x < no_of_rows && y >= 0)
                {
                    if (board[x][y].color == "purple")
                    {
                        counter++;
                    }
                    k++;
                    x++;
                    y--;
                }
                if (counter == 4)
                {
                    winner->win_scheme = "drl";
                    winner->color = "purple";
                    return true;
                }
            }
        }
        return false;
    }
    bool checkLTRConnected(Tile *winner) // checks yellow's win scheme
    {
        for (int i = 0; i < no_of_rows; i++)
        {
            for (int j = 0; j < no_of_cols; j++)
            {
                int x = i;
                int y = j;
                int counter = 0;
                int k = 0;
                while (k < 4 && x < no_of_rows && y < no_of_cols)
                {
                    if (board[x][y].color == "yellow")
                    {
                        counter++;
                    }
                    k++;
                    x++;
                    y++;
                }
                if (counter == 4)
                {
                    winner->win_scheme = "dlr";
                    winner->color = "yellow";
                    return true;
                }
            }
        }
        return false;
    }
    bool checkHorizontallyConnected(Tile *winner) // checks green's win scheme
    {
        for (int i = 0; i < no_of_rows; i++)
        {
            for (int j = 0; j < no_of_cols; j++)
            {
                int x = i;
                int y = j;
                int counter = 0;
                int k = 0;
                while (k < 4 && y < no_of_cols)
                {
                    if (board[x][y].color == "green")
                    {
                        counter++;
                    }
                    k++;
                    y++;
                }
                if (counter == 4)
                {
                    winner->win_scheme = "h";
                    winner->color = "green";
                    return true;
                }
            }
        }
        return false;
    }
    bool checkVerticallyConnected(Tile *winner) // checks orange's win scheme
    {
        for (int i = 0; i < no_of_rows; i++)
        {
            for (int j = 0; j < no_of_cols; j++)
            {
                int x = i;
                int y = j;
                int counter = 0;
                int k = 0;
                while (k < 4 && x < no_of_rows)
                {
                    if (board[x][y].color == "orange")
                    {
                        counter++;
                    }
                    k++;
                    x++;
                }
                if (counter == 4)
                {
                    winner->win_scheme = "v";
                    winner->color = "orange";
                    return true;
                }
            }
        }
        return false;
    }
};

class Game
{
public:
    int *score;
    int *tilenumber;
    int *playernumber;
    int numberofplayers;
    Player **player;
    Board board;
    Board blank_board;
    Tile winner;
    bool win;
    char Continue;
    int turn = 0;

    Game() // assigns the values for the variables
    {
        win = false;
        cout << "How many Players will play from 2-4?";
        cin >> numberofplayers;
        score = new int[numberofplayers];
        tilenumber = new int[numberofplayers];
        playernumber = new int[numberofplayers];
        player = new Player *[numberofplayers];
        Continue = 'y';
    }

    void GameStart() // starts the game as it contains most of the methods
    {
        this->IntializeTeams();
        board.displayBoard();
        for (int i = 0; i < numberofplayers; i++) // sets all the scores to 0
        {
            score[i] = 0;
        }
        while (Continue == 'y' || Continue == 'Y') // loops the game until the players don't want to play
        {
            this->PlayStart();
            score[turn]++;
            win = false;
            cout << "-------------" << endl;
            for (int i = 0; i < numberofplayers; i++)
            {
                cout << "Player" << i + 1 << " | " << score[i] << endl;
                cout << "-------------" << endl;
            }
            cout << "Do you want to continue \"answer with y/n\"? ";
            cin >> Continue;
            if ((Continue == 'y' || Continue == 'Y'))
            {
                board = blank_board;
                board.displayBoard();
            }
            else
            {
                cout << "Thanks for playing";
            }
        }
    }
    void PlayStart() // takes the value of the column the player wants to insert in
    {
        int c;
        while (!win)
        {
            turn = turn % numberofplayers;
            cout << endl
                 << "Player " << turn + 1 << " enter the column number from 1-7:";
            cin >> c;
            c = c - 1;
            bool flag = board.insert(c, &player[turn]->tile);
            if (flag == true)
            {
                board.displayBoard();
                if (checkState() == true)
                {
                    cout << endl
                         << "Winner is " << player[turn]->name << endl;
                    win = true;
                }
                else if (board.blankCount == 0)
                {
                    cout << "draw game, no one wins" << endl;
                    win = true;
                }
                else
                    turn++;
            }
        }
    }

    void IntializeTeams()
    {
        choosetile(numberofplayers);
        for (int i = 0; i < numberofplayers; i++)
        {
            player[i]->info();
        }
    }

    void choosetile(int numberofplayers) // takes how many players will play and gives them a random color
    {
        for (int i = 0; i < 4; i++)
        {
            tilenumber[i] = i;
        }
        srand(time(0));
        for (int i = 0; i <= rand() % 10; i++)
        {
            int r = rand();
            if (r % 4 == 0)
            {
                swap(tilenumber[0], tilenumber[1]);
            }
            else if (r % 3 == 0)
            {
                swap(tilenumber[1], tilenumber[2]);
            }
            else if (r % 2 == 0)
            {
                swap(tilenumber[2], tilenumber[3]);
            }
            else
            {
                swap(tilenumber[3], tilenumber[0]);
            }
        }
        for (int i = 0; i < numberofplayers; i++)
        {
            Tile t(tilenumber[i]);
            string name;
            cout << "Enter the player number " << (i + 1) << " name:";
            cin >> name;
            player[i] = new Player(name, i + 1, t);
        }
    }
    bool checkState() // checks if their is a winner
    {
        if (board.checkHorizontallyConnected(&winner))
        {
            return true;
        }
        if (board.checkVerticallyConnected(&winner))
        {
            return true;
        }
        if (board.checkLTRConnected(&winner))
        {
            return true;
        }
        if (board.checkRTLConnected(&winner))
        {
            return true;
        }
        return false;
    }
};
int main()
{
    Game game;
    game.GameStart();
    return 0;
}
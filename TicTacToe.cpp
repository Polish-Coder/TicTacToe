
#include <iostream>
#include <random>
#include <string>
#include <thread>

using namespace std;

string update_cross(int fields[]);
int is_won(int fields[]);

int main(int argc, char* argv[])
{
    random_device rd;
    mt19937 generator(rd());
    const uniform_int_distribution<> distribution(1, 9);
    
    int fields[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    
    string cross = "1|2|3\n-----\n4|5|6\n-----\n7|8|9\n";
    string input;

    while (true)
    {        
        cout << "\033[2J\n";

        cross = update_cross(fields);
        
        cout << cross;

        if (is_won(fields) != 0)
        {
            break;
        }
        
        if (all_of(fields, fields + size(fields), [](const int value) { return value != 0; }))
        {
            cout << "Brak mozliwych ruchow, nikt nie wygral";
            return 0;
        }
        
        cout << "Wpisz numer pola\n";
        
        cin >> input;
        
        if (!isdigit(input[0]) || (input[0] - '0') < 0 || (input[0] - '0') > 9 || fields[(input[0] - '0') - 1] != 0)
        {
            cout << "Wpisano niepoprawny numer pola\n";
            this_thread::sleep_for(chrono::seconds(1));
            
            continue;
        }

        fields[(input[0] - '0') - 1] = 1;

        cout << "\033[2J\n";
        
        cross = update_cross(fields);

        cout << cross;

        if (is_won(fields) != 0)
        {
            break;
        }

        if (all_of(fields, fields + size(fields), [](const int value) { return value != 0; }))
        {
            cout << "Brak mozliwych ruchow, nikt nie wygral";
            return 0;
        }
        
        cout << "Przeciwnik wybiera... ";

        this_thread::sleep_for(chrono::seconds(1));
        
        int bot_field = distribution(generator);
        while (fields[bot_field - 1] != 0)
        {
            bot_field = distribution(generator);
        }

        fields[bot_field - 1] = 2;

        cout << bot_field;

        this_thread::sleep_for(chrono::seconds(1));
    }

    const string winner = is_won(fields) == 1 ? "gracz" : "bot";
    cout << "Wygrywa " + winner;

    return 0;
}

string update_cross(int fields[])
{
    string cross = "1|2|3\n-----\n4|5|6\n-----\n7|8|9\n";

    for (int i = 0; i < 9; ++i)
    {
        if (fields[i] == 0) continue;

        const char sign = fields[i] == 1 ? 'X' : 'O';

        switch (i)
        {
        case 0:
            cross[0] = sign;
            break;
        case 1:
            cross[2] = sign;
            break;
        case 2:
            cross[4] = sign;
            break;
        case 3:
            cross[12] = sign;
            break;
        case 4:
            cross[14] = sign;
            break;
        case 5:
            cross[16] = sign;
            break;
        case 6:
            cross[24] = sign;
            break;
        case 7:
            cross[26] = sign;
            break;
        case 8:
            cross[28] = sign;
            break;
        default:
            break;
        }
    }
    
    return cross;
}

int is_won(int fields[])
{
    // Horizontal
    
    if (fields[0] != 0 && fields[0] == fields[1] && fields[1] == fields[2])
    {
        return fields[0];
    }

    if (fields[3] != 0 && fields[3] == fields[4] && fields[4] == fields[5])
    {
        return fields[3];
    }

    if (fields[6] != 0 && fields[6] == fields[7] && fields[7] == fields[8])
    {
        return fields[6];
    }

    // Vertical

    if (fields[0] != 0 && fields[0] == fields[3] && fields[3] == fields[6])
    {
        return fields[0];
    }

    if (fields[1] != 0 && fields[1] == fields[4] && fields[4] == fields[7])
    {
        return fields[1];
    }

    if (fields[2] != 0 && fields[2] == fields[5] && fields[5] == fields[8])
    {
        return fields[2];
    }

    // Diagonal

    if (fields[0] != 0 && fields[0] == fields[4] && fields[4] == fields[8])
    {
        return fields[0];
    }

    if (fields[2] != 0 && fields[2] == fields[4] && fields[4] == fields[6])
    {
        return fields[2];
    }

    return 0;
}
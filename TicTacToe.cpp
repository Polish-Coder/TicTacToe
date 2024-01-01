
#include <iostream>
#include <random>
#include <string>
#include <thread>

using namespace std;

string update_cross(int fields[]);

int main(int argc, char* argv[])
{
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(1, 9);
    
    int fields[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    
    string cross = "1|2|3\n-----\n4|5|6\n-----\n7|8|9\n";
    string input;

    while (true)
    {
        cout << "\033[2J\n";

        cross = update_cross(fields);
        
        cout << cross;
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

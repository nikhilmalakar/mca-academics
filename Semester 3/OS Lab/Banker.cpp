#include <iostream>

using namespace std;

int p, r;    

int allocation[5][3] = {
    {0, 2, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}};

int maximum[5][3] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}};

int available[3] = {3, 2, 2};

int need[5][3];

void calcNeed()
{
    for (p = 0; p < 5; p++)
        for (r = 0; r < 3; r++)
            need[p][r] = maximum[p][r] - allocation[p][r];
}

bool isSystemSafe()
{
    calcNeed();

    int tempAvail[3];
    for (r = 0; r < 3; r++)
        tempAvail[r] = available[r];

    int finished[5] = {0};

    bool hasChanged = false;
    do
    {
        hasChanged = false;
        for (p = 0; p < 5; p++)
            if (finished[p] == 0)
            {
                for (r = 0; r < 3; r++)
                    if (need[p][r] > tempAvail[r])
                        break;
                if (r == 3)
                {
                    finished[p] = 1;
                    cout << "P" << p << "  ";
                    for (r = 0; r < 3; r++)
                    {
                        tempAvail[r] += allocation[p][r];
                    }
                    hasChanged = true;
                }
            }
    } while (hasChanged);

    for (p = 0; p < 5; p++)
        if (finished[p] == 0)
        {
            cout << "\nSystem Is UnSafe\n";
            return false;
        }

    cout << "\nSystem Is Safe\n";
    return true;
}


int main(int argc, char const *argv[])
{
	isSystemSafe();
    return 0;
}
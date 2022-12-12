// 使用克莱姆规则

#include <iostream>
using namespace std;

void CramerSRule(float x1, float y1, float r1,
                float x2, float y2, float r2, float& Rx, float& Ry)
{
    float Delte, DelteX, DelteY;
    
    Delte = (x1 * y2) - (x2 * y1);
    DelteX = (r1 * y2) - (y1 * r2);
    DelteY = (x1 * r2) - (r1 * x2);

    Rx = DelteX / Delte;
    Ry = DelteY / Delte;
}

void PrintResult(float x, float y)
{
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
}

int main()
{
    float x, y;

    CramerSRule(6, 4, 76, 4, 2, 46, x, y);
    PrintResult(x, y);

    return 0;
}

// // 使用暴力算法
// #include <iostream>
// using namespace std;

// int main()
// {
//     for(int x = 0; x < 10; x++)
//     {
//         for(int y = 0; y < 10; y++)
//         {
//             if((6 * x + 4 * y) == 76 && (4 * x + 2 * y) == 46)
//             {
//                 cout << "x: " << x << endl;
//                 cout << "y: " << y << endl;
//             }
//         }
//     }

//     return 0;
// }
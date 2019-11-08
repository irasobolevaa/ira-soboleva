#include "TXLib.h"

const float dt=0.1;



void drawBall(float x, float y, int r, int R, int G, int B)
{
    for(int i=r; r>0; r=r-1)
    {

        int R1=R-(R*r/i);
        int G1=G-(G*r/i);
        int B1=B-(B*r/i);

        txSetFillColor(RGB(R1,G1,B1));
        txSetColor(RGB(R1,G1,B1));
        txCircle(x,y,r);
        txSetFillColor(RGB(255,255,255));
    }
}


void crashBall(float *x, float *y, float *x1, float *y1, float *vx, float *vy, float *vx1, float *vy1)
    {
        if (sqrt((*x - *x1)*(*x - *x1)+(*y - *y1)*(*y - *y1)) < 40)
            {
                *vx= -(*vx);
                *vy= -(*vy);
                *vx1= -(*vx1);
                *vy1= -(*vy1);

            }

    }

void moveBall(float *x, float *y, float *vx, float *vy, float dt)

    {
        *x += *vx * dt;
        *y += *vy * dt;
        if(*y>500 || *y< 100)
        *vy = -*vy;
        if(*x>700 ||*x<100)
        *vx=-*vx;
    }


void winBall(float *x, float *y, float *x1, float *y1)
    {
        if (*x<150 & *y<150)
        std::cout<<"Blue win ";
        else
            if (*x1<150 & *y1<150)
            std::cout<<"Red win ";
            else
                if (*x<150 & *y<150 & *x1<150 & *y1<150)
                std::cout<<"Both ";
                else
                    std::cout<<" ";
    }



void controllBall(float *vx, float *vx1)

    {
        if (GetAsyncKeyState(VK_LEFT))
        *vx = *vx - 0.5;
        if (GetAsyncKeyState(VK_RIGHT))
        *vx = *vx + 0.5;
        if (GetAsyncKeyState(VK_UP))
        *vx1 = *vx1 + 0.5;
        if (GetAsyncKeyState(VK_DOWN))
        *vx1 = *vx1 - 0.5;



    }


int main()

{
    txCreateWindow(800, 600);
    float x = 300;
    float y = 400;
    float x1 = 600;
    float y1 = 400;
    float vx = 5;
    float vy = 5;
    float vy1 = 5;
    float vx1 = 5;

    for(;;)

    {
        txClear();
        drawBall(x1, y1, 20, 250, 43, 112);
        drawBall(x, y, 20, 48, 213, 200);
        moveBall(&x1, &y1, &vx1, &vy1, dt);
        moveBall(&x, &y, &vx, &vy, dt);
        controllBall(&vx, &vx1);
        crashBall(&x, &y, &x1, &y1, &vx, &vy, &vx1, &vy1);

        txRectangle(0,0,150,150);
        txSetFillColor(RGB(0,0,0));
        winBall(&x, &y, &x1, &y1);
        txSleep(dt);

    }

return 0;

}

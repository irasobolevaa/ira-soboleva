#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace sf;



class classBall
{
    public:
        float x;
        float y;
        float r;
        float vx;
        float vy;
        float R;
        float G;
        float B;
        const float dt=0.1;
};

void drawBall(classBall Ball, RenderWindow* window)
{
    
    for(float i=Ball.r; i>0; i--)
    {

        float R1=Ball.R-(Ball.R*i/Ball.r); 
        float G1=Ball.G-(Ball.G*i/Ball.r);
        float B1=Ball.B-(Ball.B*i/Ball.r);


        CircleShape okruzhnost(100);
        okruzhnost.setRadius(i);
        okruzhnost.setFillColor(Color(R1,G1,B1));
        okruzhnost.setPosition(Ball.x - i, Ball.y - i);
        window->draw(okruzhnost); //Рисует шар//
        
    }
}


void crashBall(classBall *BallFirst, classBall *BallSecond)
    {
        if (sqrt(((*BallFirst).x - (*BallSecond).x)*((*BallFirst).x - (*BallSecond).x)+((*BallFirst).y - (*BallSecond).y)*((*BallFirst).y - (*BallSecond).y)) < 25)
            {
                (*BallFirst).vx= -((*BallFirst).vx);
                (*BallFirst).vy= -((*BallFirst).vy);
                (*BallSecond).vx= -((*BallSecond).vx);
                (*BallSecond).vy= -((*BallSecond).vy);

            }

    }

void moveBall(classBall *Ball)

    {
        (*Ball).x += (*Ball).vx * (*Ball).dt;
        (*Ball).y += (*Ball).vy * (*Ball).dt;
        if((*Ball).y > 575 || (*Ball).y < 25)
            (*Ball).vy = -(*Ball).vy;
        if((*Ball).x > 725 ||(*Ball).x < 25)
            (*Ball).vx=-(*Ball).vx;
    }


int main()
{   

    classBall *Balls = new classBall[350];
    
    
        for (int i = 0; i < 15; i++)
        {
            for (int j = 1; j < 15; j++)
            {
                Balls[i*15 + j -1].x = (i+1)*40;
                Balls[i*15 + j -1].y = (1+j)*30;
                Balls[i*15 + j -1].r = 12;
                Balls[i*15 + j -1].vx = i+3;
                Balls[i*15 + j -1].vy = 2*j;
                Balls[i*15 + j -1].R = 245;
                Balls[i*15 + j -1].G = 192;
                Balls[i*15 + j -1].B = 203;
            }
        }
        



    RenderWindow window(VideoMode(800, 600), "SFML Works!");
    
    CircleShape okruzhnost(100);
    
        
    while (window.isOpen())
    {  
        Event event;
        while (window.pollEvent(event))
        {   
            if (event.type == Event::Closed)
                window.close();
        } 
        window.clear();
    
        for (int m = 0; m < 350; m++)
                {
                    drawBall(Balls[m], &window);
                    moveBall(&Balls[m]);
                    
                    for (int n = 0; n < 350 && n!=m; n++)
                    {   
                        crashBall(&Balls[n], &Balls[m]);
                    }
                }
              
        window.display();
  
    }


    return 0;
}   

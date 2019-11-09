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

void drawBall(classBall Ball, RenderWindow* window) //Функция зарисовки шара//
{
    
    for(float i=Ball.r; Ball.r>0; Ball.r--)
    {

        float R1=Ball.R-(Ball.R*Ball.r/i); 
        float G1=Ball.G-(Ball.G*Ball.r/i);
        float B1=Ball.B-(Ball.B*Ball.r/i);


        CircleShape okruzhnost();
        okruzhnost.setRadius(i);
        okruzhnost.setFillColor(Color(R1,G1,B1));
        okruzhnost.setPosition(Ball.x, Ball.y);
        window->draw(okruzhnost); //Рисует шар//
        window->display(); ///Выводит его на экран/
        window->clear(); ///Чистит экран от изображения предыдущего положения шара/


    }
}


void crashBall(classBall *BallFirst, classBall *BallSecond) //Столкновение//
    {
        if (sqrt(((*BallFirst).x - (*BallSecond).x)*((*BallFirst).x - (*BallSecond).x)+((*BallFirst).y - (*BallSecond).y)*((*BallFirst).y - (*BallSecond).y)) < 2*(*BallFirst).r)
            {
                (*BallFirst).vx= -((*BallFirst).vx);
                (*BallFirst).vy= -((*BallFirst).vy);
                (*BallSecond).vx= -((*BallSecond).vx);
                (*BallSecond).vy= -((*BallSecond).vy);

            }

    }

void moveBall(classBall *Ball) //Движение внутри рамки//

    {
        (*Ball).x += (*Ball).vx * (*Ball).dt;
        (*Ball).y += (*Ball).vy * (*Ball).dt;
        if((*Ball).y>500 || (*Ball).y< 100)
            (*Ball).vy = -(*Ball).vy;
        if((*Ball).x>700 ||(*Ball).x<100)
            (*Ball).vx=-(*Ball).vx;
    }


int main()
{   
    srand(time(NULL))
        
    classBall *Balls = new classBall[350];
    
    
        for (int i = 0; i < 15; i++) //Цикл проходит по всем молекулам класса//
        {
            for (int j = 1; j < 15; j++)
            {
                Balls[i*15 + j -1].x = 50*i+35*j; //Проходит по всем молекулам, начиная с первой(нулевой компоненты массива), задавая положение этой молекулы//
                Balls[i*15 + j -1].y = 20*i+75*j;
                Balls[i*15 + j -1].r = 12;
                Balls[i*15 + j -1].vx = 2+i;
                Balls[i*15 + j -1].vy = 2+j;
                Balls[i*15 + j -1].R = 245;
                Balls[i*15 + j -1].G = 192;
                Balls[i*15 + j -1].B = 203;
            }
        }
        



        RenderWindow window(VideoMode(800, 600), "SFML Works!");
    for(;;) //Запуск функций//
            {
                for (int m = 0; m < 350; m++)
                {
                    drawBall(Balls[m], &window);
                    moveBall(&Balls[m]);
                    
                    for (int n = 0; n < 350; n++)
                    {
                        crashBall(&Balls[n], &Balls[m]);
                    }
                }
                
            }    
    CircleShape okruzhnost();
    window.clear(Color::White);
    window.display();
        
    while (window.isOpen())
    {   
        
        
        Event event;
        while (window.pollEvent(event))
        {   
            if (event.type == Event::Closed)
                window.close();
        } 

        window.clear(Color::White);
        window.display();
  
    }


    return 0;
}



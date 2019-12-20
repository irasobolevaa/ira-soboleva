#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "DescriptionVector.h"
using namespace sf;



class classBall
{
    public:
        Vector2f position;
    	Vector2f velocity;
        float x;
        float y;
        float r;
        float vx;
        float vy;
        float R;
        float G;
        float B;
        const float dt=0.1;
        

    void drawBall(RenderWindow* window)
    {
        for(float i=r; i>0; i--)
        {
            float R1=R-(R*i/r); 
            float G1=G-(G*i/r);
            float B1=B-(B*i/r);

            CircleShape okruzhnost(100);
            okruzhnost.setRadius(i);
            okruzhnost.setFillColor(Color(R1,G1,B1));
            okruzhnost.setPosition(x - i, y - i);
            window->draw(okruzhnost); //Рисует шар//    
        }
    }

    void moveBall()

    {
        x += vx * dt;
        y += vy * dt;
        if(y > 575 || y < 25)
            vy = -vy;
        if(x > 725 ||x < 25)
            vx=-vx;
    }
};




void collide(classBall* Ball1, classBall* Ball2)
{
    if (sqrt(((*Ball1).x - (*Ball2).x)*((*Ball1).x - (*Ball2).x)+((*Ball1).y - (*Ball2).y)*((*Ball1).y - (*Ball2).y)) > 60)
     {
        Vector2f centre_mass = Ball2->position - Ball1->position;
        Vector2f V1projection = normolize(centre_mass) * ((scular(Ball1->velocity, centre_mass)) / centre_mass.len() );
        Vector2f V2projection = normolize(centre_mass) * ((scular(Ball2->velocity, centre_mass)) / centre_mass.len() );

        Ball1->velocity = Ball1->velocity - V1projection;
        Ball1->velocity = Ball1->velocity + V2projection;

        Ball2->velocity = Ball2->velocity - V2projection;
        Ball2->velocity = Ball2->velocity + V1projection;

        if (centre_mass.len() < (Ball1->r + Ball2->r)) 
            {
                Ball2->position = Ball2->position + normolize(centre_mass) * ((Ball1->r + Ball2->r - centre_mass.len()) / 2);
                Ball1->position = Ball1->position - normolize(centre_mass) * ((Ball1->r + Ball2->r - centre_mass.len()) / 2);
            }
    }
 
	

}

void colide_all_particles(classBall* Balls)
{
    for (int i = 0; i < 350; i++)
    {
        for (int j = 0; j < 100; j++)
         {
             if (i < j)
             {
                 collide(&Balls[i], &Balls[j]);
             }
           
         }
    }

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
                    Balls[m].drawBall(&window);
                    Balls[m].moveBall();
                    
                    colide_all_particles(Balls);
                
                }
              
        window.display();
  
    }


    return 0;
}   

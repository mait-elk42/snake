#include<NSX/nsx_game.hpp>

#define up(key) key == 22 || key == 73
#define right(key) key == 3 || key == 72
#define down(key) key == 18 || key == 74
#define left(key) key == 0 || key == 71

#define u {0,(float)-10}
#define d {0,(float)10}
#define r {(float)10,0}
#define l {(float)-10,0}

enum controll{
    up,
    right,
    down,
    left   
};
typedef struct s_snake{
    RectangleShape shape;
    struct s_snake *next;
} t_snake;
int main()
{
    int len_of_snake = 1;
    Clock clock;
    float time = 0;
    float speed = 10;
    controll ctrl = up;
    controll state = ctrl;
    Vector2f direction;
    t_snake *snakecurr;


    t_snake *snakehead = new t_snake();
    snakehead->shape = RectangleShape(Vector2f(10.0,10.0));
    snakehead->shape.setFillColor(Color::Green);
    // Texture *foodtxtr = new Texture();
    // foodtxtr->loadFromFile("resources/food.png");

    t_snake food;
    food.shape = RectangleShape(Vector2f(10.0,10.0));
    food.shape.setPosition(50,100);
    
    
    snakecurr = snakehead;

    RenderWindow window = RenderWindow(VideoMode(500,500),"SNAKE", Style::Close);
    //player.setOrigin(player.getSize().x/2,player.getSize().y/2);
    snakehead->shape.setPosition(window.getSize().x/2,window.getSize().y/2);
    while(window.isOpen())
    {
        prt(snakehead->shape.getPosition().x);
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                return 0;
            if(event.type == Event::KeyPressed)
                    if(up(event.key.code))
                        ctrl = up;
                    else
                    if(right(event.key.code))
                        ctrl = right;
                    else 
                    if(down(event.key.code))
                        ctrl = down;
                    else 
                    if(left(event.key.code))
                        ctrl = left;
        }
        switch(ctrl)
        {
            case up:
            if(state != down)
            {
                direction = u;
                state = up;
            }
                break;
            case right:
            if(state != left)
            {
                direction = r;
                state = right;
            }
                break;
            case down:
            if(state != up)
            {
                direction = d;
                state = down;
            }
                break;
            case left:
            if(state != right)
            {
                direction = l;
                state = left;
            }
                break;
        }
        window.clear();
        t_snake *snaketmp = snakehead;
        window.draw(food.shape);
        while(snaketmp)
        {
            window.draw(snaketmp->shape);
            snaketmp = snaketmp->next;
        }
        window.display();
        if(time >= 1)
        {   
            t_snake *snaket = snakehead;
            Vector2f sheadpos = snaket->shape.getPosition();
            Vector2f pos2;
            Vector2f foodpos = food.shape.getPosition();

            t_snake *tmp = snakehead->next;
            while(tmp)
            {
                Vector2f pos = tmp->shape.getPosition();
                if(sheadpos.x == pos.x && sheadpos.y == pos.y)
                    prt("YOU LOOSE , DON'T EAT YOURSELF");
                tmp = tmp->next;
            }
            if((sheadpos.x == foodpos.x) && (sheadpos.y == foodpos.y))
            {
                len_of_snake++;
                speed += 1;
                prt("NEW LENGTH OF SNAKE IS : " << len_of_snake);
                prt("EATING FOOD FROM POSITION :" << foodpos.x << ":" << foodpos.y );
                int randmx = rand() %  window.getSize().x;
                int randmy = rand() %  window.getSize().y;

                randmx -=  (randmx % 10);
                randmy -=  (randmy % 10);
                // prt(randmx  << ":" << randmy);
                food.shape.setPosition ( randmx , randmy );

                snakecurr->next = new t_snake();
                snakecurr->next->shape = RectangleShape(Vector2f(10.0,10.0));
                snakecurr->next->shape.setSize(Vector2f(snakecurr->shape.getSize().x-0.5,snakecurr->shape.getSize().y-0.5));
                snakecurr = snakecurr->next;
            }
            if(sheadpos.x+direction.x >= window.getSize().x)
                snaket->shape.setPosition(-10,sheadpos.y);
            else
            if(sheadpos.x+direction.x < 0)
                snaket->shape.setPosition(window.getSize().x,sheadpos.y);
            
            if(sheadpos.y+direction.y >= window.getSize().y)
                snaket->shape.setPosition(sheadpos.x,-10);
            else
            if(sheadpos.y+direction.y < 0)
                snaket->shape.setPosition(sheadpos.x,window.getSize().y);

            
            snaket->shape.move(direction);
            snaket = snaket->next;
            while(snaket)
            {
                // prt(snaket<< " : " << sheadpos.y);
                pos2 = snaket->shape.getPosition();
                snaket->shape.setPosition(sheadpos);
                sheadpos = pos2;
                snaket = snaket->next;
            }
            time = 0;
        }
        if(time <= 1)
        {
            // prt(time);
            time += clock.restart().asSeconds() * speed;
        }
    }
}
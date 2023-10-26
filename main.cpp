#include<NSX/nsx_game.hpp>

#define STEP_SIZE 10

#define up(key) key == 22 || key == 73
#define right(key) key == 3 || key == 72
#define down(key) key == 18 || key == 74
#define left(key) key == 0 || key == 71


#define u {0,(float)-STEP_SIZE}
#define d {0,(float)STEP_SIZE}
#define r {(float)STEP_SIZE,0}
#define l {(float)-STEP_SIZE,0}



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


Vector2f randompos(Vector2u windowsize, int stepsize)
{
    int randx = rand() % windowsize.x;
    int randy = rand() % windowsize.y;

    randx -= (randx % stepsize);
    randy -= (randy % stepsize);

    return Vector2f(randx,randy);

}

int snake_out(t_snake *snakehead ,Vector2f windowpos)
{
    Vector2f sheadpos = snakehead->shape.getPosition();
    Vector2f sheadsize = snakehead->shape.getSize();
    if(sheadpos.x+sheadsize.x > windowpos.x)
        return 1;
    else
    if(sheadpos.x < 0)
        return 1;
    else
    if(sheadpos.y+sheadsize.y > windowpos.y)
        return 1;
    else
    if(sheadpos.y+sheadsize.y < 0)
        return 1;
    return 0;
}

int eating_myself(t_snake *head)
{
    t_snake *tmp = head->next;
    Vector2f headpos = head->shape.getPosition();
    while(tmp)
    {
        Vector2f pos = tmp->shape.getPosition();
        if((headpos.x == pos.x) && (headpos.y == pos.y))
            return 1;
        tmp = tmp->next;
    }
    return 0;
}
void draw_snake(RenderWindow &window, t_snake *snakehead)
{
    while(snakehead)
    {
        t_snake snake = *snakehead;
        window.draw(snake.shape);
        snakehead = snakehead->next;
    }
}
void add_snake(t_snake **currsnake)
{
    Vector2f currssize = (*currsnake)->shape.getSize();
    (*currsnake)->next = new t_snake();
    (*currsnake)->next->shape = RectangleShape(currssize);
    (*currsnake) = (*currsnake)->next;
}



void StartGame(RenderWindow &window)
{
    int len_of_snake = 1;
    Clock clock;
    float time = 0;
    float speed = 10;
    controll ctrl = up;
    controll state = ctrl;
    Vector2f direction;
    t_snake *snakecurr;
    t_snake *snakehead;
    t_snake item;
    Text score;
    Font font;
    String s = " SCORE : ";
    font.loadFromFile( "resources/font" );
    score.setFont( font );
    

    snakehead = new t_snake();
    snakehead->shape = RectangleShape(Vector2f(STEP_SIZE,STEP_SIZE));
    snakehead->shape.setFillColor(Color::Green);


    item.shape = RectangleShape(Vector2f(STEP_SIZE,STEP_SIZE));
    item.shape.setPosition(randompos(window.getSize(),STEP_SIZE));
    

    snakecurr = snakehead;

    snakehead->shape.setPosition(200,200);
    while(1)
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                return;
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
        window.draw(item.shape);
        score.setString(s+std::to_string(len_of_snake));
        window.draw(score);
        draw_snake(window,snakehead);
        window.display();
        if(time >= 1)
        {   
            t_snake *snaket = snakehead;
            Vector2f sheadpos = snaket->shape.getPosition();
            Vector2f foodpos = item.shape.getPosition();

            if( eating_myself( snakehead ) )
                    return;
                // prt("YOU LOOSE , DON'T EAT YOURSELF");
            if((sheadpos.x == foodpos.x) && (sheadpos.y == foodpos.y))
            {
                len_of_snake ++;
                speed ++;

                prt("NEW LENGTH OF SNAKE IS : " << len_of_snake);
                prt("EATING FOOD FROM POSITION :" << foodpos.x << ":" << foodpos.y );

                item.shape.setPosition (randompos(window.getSize(),STEP_SIZE));

                add_snake(&snakecurr);
            }

            if(snake_out(snakehead,(Vector2f)window.getSize()))
                return;

            Vector2f targpos = {sheadpos.x+direction.x,sheadpos.y+direction.y};
            while ( snaket )
            {
                // prt(snaket<< " : " << sheadpos.y);
                Vector2f currpos = snaket->shape.getPosition();
                snaket->shape.setPosition(targpos);
                targpos = currpos;
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

int main()
{
    RenderWindow window = RenderWindow(VideoMode(500,500),"SNAKE", Style::Close);
    Image icon;
    icon.loadFromFile("resources/icon");
    window.setIcon(icon.getSize().y,icon.getSize().x,icon.getPixelsPtr());
    StartGame(window);
    
}
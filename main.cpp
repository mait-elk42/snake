#include<NSX/nsx_game.hpp>

#define STEP_SIZE 10

#define up(key) key == 22
#define right(key) key == 3
#define down(key) key == 18
#define left(key) key == 0

#define up2(key) key == 73
#define right2(key)  key == 72
#define down2(key)  key == 74
#define left2(key)  key == 71



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
    struct s_snake *prev;

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
    t_snake *tmp = head->prev;
    Vector2f headpos = head->shape.getPosition();
    while(tmp)
    {
        Vector2f pos = tmp->shape.getPosition();
        if((headpos.x == pos.x) && (headpos.y == pos.y))
            return 1;
        tmp = tmp->prev;
    }
    return 0;
}
void draw_snake(RenderWindow &window, t_snake *snakehead)
{
    while(snakehead)
    {
        t_snake snake = *snakehead;
        // if(!snake.prev) // LAST
        //     snake.shape.setFillColor(Color::Red);
        // if(!snake.next) //FIRST
        //     snake.shape.setFillColor(Color::Blue);
        window.draw(snake.shape);
        snakehead = snakehead->prev;
    }
}


void add_snake(t_snake *&currsnake)
{
    Vector2f currssize = currsnake->shape.getSize();
    currsnake->prev = new t_snake();
    currsnake->prev->next = currsnake;
    currsnake->prev->shape = RectangleShape(currssize);
    currsnake = currsnake->prev;
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
    score.setFillColor(Color::Blue);
    score.setOutlineThickness(2);
    score.setOutlineColor(Color::White);
    

    snakehead = new t_snake();
    snakehead->shape = RectangleShape(Vector2f(STEP_SIZE,STEP_SIZE));
    snakehead->shape.setFillColor(Color::Green);


    item.shape = RectangleShape(Vector2f(STEP_SIZE,STEP_SIZE));
    item.shape.setPosition(randompos(window.getSize(),STEP_SIZE));
    

    snakecurr = snakehead;
    add_snake(snakecurr);
    add_snake(snakecurr);
    add_snake(snakecurr);

    snakehead->shape.setPosition(200,200);
    while(1)
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                exit(0);
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
        draw_snake(window,snakehead);
        window.draw(score);
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

                add_snake(snakecurr);
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
                snaket = snaket->prev;
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

void StartGame2p(RenderWindow &window)
{
    int len_of_snake = 1;
    Clock clock;
    float time = 0;
    float speed = 10;
    controll ctrl = up;
    controll ctrl2 = up;
    controll state = ctrl;
    controll state2 = ctrl2;
    Vector2f direction;
    Vector2f direction2;
    t_snake *snakecurr;
    t_snake *snakecurr2;
    t_snake *snakehead;
    t_snake *snakehead2;
    t_snake item;
    Text score;
    Font font;
    String s = " SCORE : ";
    font.loadFromFile( "resources/font" );
    score.setFont( font );
    score.setFillColor(Color::Blue);
    score.setOutlineThickness(2);
    score.setOutlineColor(Color::White);
    

    snakehead = new t_snake();
    snakehead->shape = RectangleShape(Vector2f(STEP_SIZE,STEP_SIZE));
    snakehead->shape.setFillColor(Color::Green);

    snakehead2 = new t_snake();
    snakehead2->shape = RectangleShape(Vector2f(STEP_SIZE,STEP_SIZE));
    snakehead2->shape.setFillColor(Color::Blue);


    item.shape = RectangleShape(Vector2f(STEP_SIZE,STEP_SIZE));
    item.shape.setPosition(randompos(window.getSize(),STEP_SIZE));
    

    snakecurr = snakehead;
    add_snake(snakecurr);
    add_snake(snakecurr);
    add_snake(snakecurr);

    snakecurr2 = snakehead2;
    add_snake(snakecurr2);
    add_snake(snakecurr2);
    add_snake(snakecurr2);

    snakehead->shape.setPosition(200,200);
    snakehead->shape.setPosition(400,200);
    while(1)
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                exit(0);
            if(event.type == Event::KeyPressed)
            {
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

                    if(up2(event.key.code))
                        ctrl2 = up;
                    else
                    if(right2(event.key.code))
                        ctrl2 = right;
                    else 
                    if(down2(event.key.code))
                        ctrl2 = down;
                    else 
                    if(left2(event.key.code))
                        ctrl2 = left;
            }
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
        switch(ctrl2)
        {
            case up:
            if(state2 != down)
            {
                direction2 = u;
                state2 = up;
            }
                break;
            case right:
            if(state2 != left)
            {
                direction2 = r;
                state2 = right;
            }
                break;
            case down:
            if(state2 != up)
            {
                direction2 = d;
                state2 = down;
            }
                break;
            case left:
            if(state2 != right)
            {
                direction2 = l;
                state2 = left;
            }
                break;
        }
        window.clear();
        window.draw(item.shape);
        score.setString(s+std::to_string(len_of_snake));
        draw_snake(window,snakehead);
        draw_snake(window,snakehead2);
        window.draw(score);
        window.display();
        if(time >= 1)
        {   
            t_snake *snaket = snakehead;
            t_snake *snaket2 = snakehead;
            Vector2f sheadpos = snaket->shape.getPosition();
            Vector2f sheadpos2 = snaket2->shape.getPosition();
            Vector2f foodpos = item.shape.getPosition();

            if( eating_myself( snakehead ) )
                    // return;
                prt("YOU LOOSE , DON'T EAT YOURSELF");

            if( eating_myself( snakehead2 ) )
                    // return;
                prt("YOU LOOSE , DON'T EAT YOURSELF");
            
            if((sheadpos.x == foodpos.x) && (sheadpos.y == foodpos.y))
            {
                len_of_snake ++;
                speed ++;

                prt("NEW LENGTH OF SNAKE IS : " << len_of_snake);
                prt("EATING FOOD FROM POSITION :" << foodpos.x << ":" << foodpos.y );

                item.shape.setPosition (randompos(window.getSize(),STEP_SIZE));

                add_snake(snakecurr);
            }

            if((sheadpos2.x == foodpos.x) && (sheadpos2.y == foodpos.y))
            {
                len_of_snake ++;
                speed ++;

                prt("NEW LENGTH OF SNAKE IS : " << len_of_snake);
                prt("EATING FOOD FROM POSITION :" << foodpos.x << ":" << foodpos.y );

                item.shape.setPosition (randompos(window.getSize(),STEP_SIZE));

                add_snake(snakecurr2);
            }

            if(snake_out(snakehead,(Vector2f)window.getSize()))
                return;
            if(snake_out(snakehead2,(Vector2f)window.getSize()))
                return;

            Vector2f targpos = {sheadpos.x+direction.x,sheadpos.y+direction.y};
            while ( snaket )
            {
                // prt(snaket<< " : " << sheadpos.y);
                Vector2f currpos = snaket->shape.getPosition();
                snaket->shape.setPosition(targpos);
                targpos = currpos;
                snaket = snaket->prev;
            }

            Vector2f targpos2 = {sheadpos2.x+direction2.x,sheadpos2.y+direction2.y};
            while ( snaket2 )
            {
                // prt(snaket<< " : " << sheadpos.y);
                Vector2f currpos = snaket2->shape.getPosition();
                snaket2->shape.setPosition(targpos);
                targpos2 = currpos;
                snaket2 = snaket2->prev;
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
    Font font;
    font.loadFromFile("resources/font");
    Text hint;
    hint.setFont(font);
    hint.setString("PRESS 'r' TO RESTART...");
    RenderWindow window = RenderWindow(VideoMode(500,500),"SNAKE", Style::Close);
    Image icon;
    icon.loadFromFile("resources/icon");
    window.setIcon(icon.getSize().y,icon.getSize().x,icon.getPixelsPtr());
    StartGame2p(window);
    while(1)
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                return 0;
            if(event.type == Event::KeyPressed)
                if(event.key.code == Keyboard::Key::R)
                    StartGame(window);
        }
        window.clear();
        window.draw(hint);
        window.display();
    }
    return 0;
}

//
// void StartSplash(RenderWindow &window, String text, String iconpath = "resources/me", String fontpath = "resources/font")
// {
//     float time = 0;
//     int c1c = 0;
//     Texture icon__;
//     CircleShape icon(50.0);
//     Text logoname;
//     Font f;
//     f.loadFromFile(fontpath);
//     logoname.setFont(f);
//     logoname.setString(text);
//     logoname.setOrigin(logoname.getLocalBounds().width/2,logoname.getLocalBounds().height/2);
//     logoname.setPosition(window.getSize().x/2,window.getSize().y/2+70);
//     icon__.loadFromFile(iconpath);
//     icon.setTexture(&icon__);
//     icon.setOrigin(icon.getLocalBounds().height/2,icon.getLocalBounds().width/2);
//     icon.setPosition(window.getSize().x/2,window.getSize().y/2);
//     icon.setOutlineThickness(2);
//     while(1)
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if(event.type == Event::TouchBegan)
//                 prt(event.touch.x);
//             if(event.type == sf::Event::Resized)
//             {
//                 sf::FloatRect view(0, 0, event.size.width, event.size.height);
//                 icon.setPosition(window.getSize().x/2,window.getSize().y/2);
//                 logoname.setPosition(window.getSize().x/2,window.getSize().y/2+70);
//                 window.setView(sf::View(view));
//             }
//             if (event.type == Event::Closed)
//                 exit(0);
//         }
//         window.draw(logoname);
//         window.draw(icon);
//         window.display();
//         window.clear();
//         if(c1c && (time <= 0))
//             break;
//         if(!c1c && (time >= 255))
//         {
//             c1c = 1;
//         }
//         if(!c1c)
//         {
//             time += 0.1;
//         }else
//         if(c1c)
//         {
//             time -= 0.1;
//         }
//         icon.setOutlineColor(Color(255,0,0,time));
//         icon.setFillColor(Color(255,255,255,time));
//         logoname.setFillColor(Color(255,0,0,time));
//     }
// }
// int StartGame()
// {
//     RenderWindow window = RenderWindow(VideoMode(700, 400), "GAME ENGINE");
//     Image icon;
//     icon.loadFromFile("resources/icon");
//     window.display();
//     window.setIcon( icon.getSize().y , icon.getSize().x , icon.getPixelsPtr() );
//     //  StartSplash(window,"NS STUDIO");   
//     //  prt("SPLASH ENDED");
//     while (1)
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Resized)
//             {
//                 prt(event.size.height << ":" << event.size.width);
//             }
//             if (event.type == Event::Closed)
//                 return 0;
//         }
//         window.display();
//         window.clear();
//     }
// }
// int StartGame2()
// {
//     RenderWindow window = RenderWindow(VideoMode(500,500),"NAME OSF - NAME");
//      while (1)
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Resized)
//             {
//                 prt(event.size.height << ":" << event.size.width);
//             }
//             if (event.type == Event::Closed)
//                 return 0;
//         }
//         window.display();
//         window.clear();
//     }
// }
// float fps = 0;
// float GetFps()
// {
//     return fps;
// }
// int OnStart()
// {
//     float m_secondCounter;
//     float m_tempFps;
//     Clock deltac;
//     float deltatime = 0;
//     RenderWindow *__window =new RenderWindow(VideoMode(700, 400), "GAME ENGINE");
//     Game::OnAwake(__window);
//     Game::OnStart();
//     while(1)
//     {
//         sf::Event event;
//         while (__window->pollEvent(event))
//         {
//             Game::OnEvent(event);
//             if (event.type == sf::Event::Closed)
//                 return 0;
//         }
//         __window->clear();
//         Game::OnUpdate(deltatime);
//         int hh = 9999999;
//         while(hh--);
//         if (m_secondCounter <= 1) {
//             m_secondCounter += deltatime;
//             m_tempFps++;
//         }
//         else 
//         {
//             fps = m_tempFps;
//             m_secondCounter = 0;
//             m_tempFps = 0;
//         }
//         __window->display();
//         deltatime = deltac.restart().asSeconds();
//     }
//     return 0;
// }



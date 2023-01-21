#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main()
{
    RenderWindow app(VideoMode(1052,1315), "huao rong dao -Puzzle!");
	app.setFramerateLimit(60);

	Texture t;
    t.loadFromFile("images/huarongdao.png");
 
	int w = 263;
	Sprite zhang_fei;
    zhang_fei.setTexture(t);
    zhang_fei.setTextureRect(IntRect(0, 0, w, w*2));
    Sprite cao_cao;
    cao_cao.setTexture(t);
    cao_cao.setTextureRect(IntRect(w, 0, w*2, w * 2));
    Sprite zhao_yun;
    zhao_yun.setTexture(t);
    zhao_yun.setTextureRect(IntRect(w*3, 0, w, w * 2));

    Sprite ma_chao;
    ma_chao.setTexture(t);
    ma_chao.setTextureRect(IntRect(0, w*2, w, w * 2));
    Sprite guan_yu;
    guan_yu.setTexture(t);
    guan_yu.setTextureRect(IntRect(w, w * 2, w*2, w));

    Sprite huang_zhong;
    huang_zhong.setTexture(t);
    huang_zhong.setTextureRect(IntRect(w*3, w * 2, w, w*2));

    Sprite soldier1;
    soldier1.setTexture(t);
    soldier1.setTextureRect(IntRect(0, w * 4, w, w ));
    Sprite soldier2;
    soldier2.setTexture(t);
    soldier2.setTextureRect(IntRect(w, w * 3, w, w));
    Sprite soldier3;
    soldier3.setTexture(t);
    soldier3.setTextureRect(IntRect(w*2, w * 3, w, w));
    Sprite soldier4;
    soldier4.setTexture(t);
    soldier4.setTextureRect(IntRect(w * 3, w * 4, w, w));

    Sprite blank1;
    blank1.setTexture(t);
    blank1.setTextureRect(IntRect(w, w * 4, w, w));
    Sprite blank2;
    blank2.setTexture(t);
    blank2.setTextureRect(IntRect(w*2, w * 4, w, w));

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
/*
   			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
                  {
                     Vector2i pos = Mouse::getPosition(app);
                     int x = pos.x/w + 1;
                     int y = pos.y/w + 1;

                     int dx=0;
                     int dy=0;

                     if (grid[x+1][y]==16) {dx=1; dy=0;};
                     if (grid[x][y+1]==16) {dx=0; dy=1;};
                     if (grid[x][y-1]==16) {dx=0; dy=-1;};
                     if (grid[x-1][y]==16) {dx=-1;dy=0;};

                     int n = grid[x][y];
                     grid[x][y] = 16;
                     grid[x+dx][y+dy] = n;

					 //animation
                     sprite[16].move(-dx*w,-dy*w);
                     float speed=3;

                     for (int i=0;i<w;i+=speed)
                     {sprite[n].move(speed*dx,speed*dy);
                      app.draw(sprite[16]);
                      app.draw(sprite[n]);
                      app.display(); }
                  }
*/
        }

       app.clear(Color::White);
       zhang_fei.setPosition(0, 0);
       cao_cao.setPosition(w, 0);
       zhao_yun.setPosition(w*3, 0);
       ma_chao.setPosition(0, w * 2);
       guan_yu.setPosition(w, w * 2);
       huang_zhong.setPosition(w*3, w * 2);
       soldier1.setPosition(0, w * 4);
       soldier2.setPosition(w, w * 3);
       soldier3.setPosition(w*2, w * 3);
       soldier4.setPosition(w * 3, w * 4);
       blank1.setPosition(w , w * 4);
       blank2.setPosition(w*2, w * 4);
       app.draw(zhang_fei);
       app.draw(cao_cao);
       app.draw(zhao_yun);
       app.draw(ma_chao);
       app.draw(guan_yu);
       app.draw(huang_zhong);
       app.draw(soldier1);
       app.draw(soldier2);
       app.draw(soldier3);
       app.draw(soldier4);
       app.draw(blank1);
       app.draw(blank2);

       app.display();
    }

    return 0;
}

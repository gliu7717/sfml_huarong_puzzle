#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
const int w = 263;
void  initSpriteBlockers(Sprite blockers[])
{
    blockers[1].setTextureRect(IntRect(0, 0, w, w * 2)); // Zhang Fei
    blockers[2].setTextureRect(IntRect(w, 0, w * 2, w * 2)); //Cao Cao
    blockers[3].setTextureRect(IntRect(w * 3, 0, w, w * 2)); // Zhao Yun
    blockers[4].setTextureRect(IntRect(0, w * 2, w, w * 2)); // Mao Chao
    blockers[5].setTextureRect(IntRect(w, w * 2, w * 2, w)); // Guan Yu
    blockers[6].setTextureRect(IntRect(w * 3, w * 2, w, w * 2)); // Huang Zhong
    blockers[7].setTextureRect(IntRect(0, w * 4, w, w));  //soldier1 
    blockers[8].setTextureRect(IntRect(0, w * 4, w, w));  // soldier2
    blockers[9].setTextureRect(IntRect(0, w * 4, w, w));  // soldier3
    blockers[10].setTextureRect(IntRect(0, w * 4, w, w)); // soldier4
    blockers[11].setTextureRect(IntRect(w, w * 4, w, w)); // blank1
    blockers[12].setTextureRect(IntRect(w, w * 4, w, w)); // blank2
}

void initBoard(int board[4][5], Sprite blockers[])
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 5; ++j)
            board[i][j] = 0;
    board[0][0] = 1;
    board[1][0] = 2;
    board[3][0] = 3;
    board[0][2] = 4;
    board[1][2] = 5;
    board[3][2] = 6;
    board[1][3] = 7;
    board[2][3] = 8;
    board[0][4] = 9;
    board[1][4] = 11;
    board[2][4] = 12;
    board[3][4] = 10;
}

// which corner
// 0 : top left
// 1: top right
// 2: bottom left
// 3: bottom right
int getBlockerCorner(Sprite& blocker, int x, int y)
{
    Vector2f pos = blocker.getPosition();
    int toLeft = x - pos.x ;
    int toRight = blocker.getTextureRect().width + pos.x - x;
    int toTop = y - pos.y;
    int toBottom = blocker.getTextureRect().height + pos.y - y;
    std::cout << "toLeft:" << toLeft << std::endl;
    std::cout << "toRight:" << toRight << std::endl;
    std::cout << "toTop:" << toTop << std::endl;
    std::cout << "toBottom:" << toBottom << std::endl;
    if (toLeft < toRight)
    {
        if (toTop < toBottom)
            return 0;
        else
            return 2;
    }
    else
    {
        if (toTop < toBottom)
            return 1;
        else
            return 3;
    }
    return 0;
}

int getBlockerIndex(int board[4][5], Sprite blockers[], int x, int y)
{
    if (board[x][y] > 0)
        return board[x][y];
    if (x > 0)
    {
        int i = board[x - 1][y];
        if (i > 0)
        {
            int i1 = blockers[i].getTextureRect().width /w;
            std::cout << "i=" << i << "  width=" << i1 << std::endl;
            if (i1 > 1 && board[x - 1][y] > 0)
            {
                std::cout << "x return block index=" << board[x - 1][y] << std::endl;
                return board[x - 1][y];
            }
        }
    }
    if (y > 0)
    {
        int i = board[x ][y - 1];
        if (i > 0)
        {
            int i1 = blockers[i].getTextureRect().height / w;
            std::cout << "i=" << i << "  height=" << i1 << std::endl;
            if (i1 > 1 && board[x ][y -1] > 0)
            {
                std::cout << " y return block index=" << board[x ][y -1] << std::endl;
                return board[x ][y - 1];
            }
        }
    }
    if (x> 0 && y > 0)
    {
        int i = board[x-1][y - 1];
        if (i > 0)
        {
            int i1 = blockers[i].getTextureRect().width / w;
            int j1 = blockers[i].getTextureRect().height / w;
            if (i1 > 1 && j1> 0 && board[x - 1][y - 1] > 0)
            {
                std::cout << " xy return block index=" << board[x -1][y - 1] << std::endl;
                return board[x-1][y - 1];
            }
        }
    }

    return 0;
}

// return
// 1: move down
// 2: move up
// 3: move righ
// 4: move left
int moveBlock(int board[4][5], Sprite blockers[], int blockIndex, int corner)
{
    Vector2f pos = blockers[blockIndex].getPosition();
    int x = pos.x / w;
    int y = pos.y / w;
    std::cout << "x=" << x << "  y = " << y << std::endl;
    int w1 = blockers[blockIndex].getTextureRect().width / w;
    int h = blockers[blockIndex].getTextureRect().height / w;
    std::cout << "w1=" << w1 << "  h = " << h << std::endl;

    // moving down
    if (y + h - 1 < 4)
    {
        if (w1 == 1)
        {
            bool force_move_other_dir = false;
            if (y > 0 && (board[x][y - 1] == 11 || board[x][y - 1] == 12))
            {
                // can also move up
                force_move_other_dir = (corner == 0 || corner == 1);
            }
            if (!force_move_other_dir && h == 1 && x > 0 && (board[x - 1][y] == 11 || board[x - 1][y] == 12))
                // can also move left
                force_move_other_dir = (corner == 0 || corner == 2);
            if (!force_move_other_dir && h == 1 && x < 3 && (board[x + 1][y] == 11 || board[x + 1][y] == 12))
                force_move_other_dir = (corner == 1 || corner == 3);

            if (!force_move_other_dir && (board[x][y + h] == 11 || board[x][y + h] == 12))
            {
                // can move down 
                std::cout << "Can move down." << std::endl;
                int tmp = board[x][y + h];
                board[x][y + 1] = board[x][y];
                board[x][y] = tmp;
                if (h == 2)
                    board[x][y + h] = 0;
                return 1;
            }
        }
        if (w1 == 2)
        {
            if ((board[x][y + h] == 11 || board[x][y + h] == 12) &&
                (board[x+ 1][y + h] == 11 || board[x+1][y + h] == 12) )
            {
                // can move down 
                std::cout << "Can move 2 down." << std::endl;
                int tmp = board[x][y + h];
                int tmp1 = board[x + 1][y + h];
                board[x][y + 1] = board[x][y];
                board[x+1][y + h] = 0;
                board[x][y] = tmp;
                board[x + 1][y] = tmp1;

                if(h == 2)
                    board[x ][y + h] = 0;
                return 1;
            }
        }
    }

    // moving up
    if (y > 0)
    {
        if (w1 == 1)
        {
            bool force_move_left_right = false;
            if (h == 1 && x > 0 && (board[x - 1][y] == 11 || board[x - 1][y] == 12))
                // can also move left
                force_move_left_right = (corner == 0 || corner == 2);
            if(!force_move_left_right && h == 1 && x < 3 && (board[x + 1][y] == 11 || board[x + 1][y] == 12))
                force_move_left_right = (corner == 1 || corner == 3);

            if (!force_move_left_right && (board[x][y - 1] == 11 || board[x][y - 1] == 12))
            {
                // can move up 
                std::cout << "Can move up." << std::endl;
                int tmp = board[x][y - 1];
                board[x][y - 1] = board[x][y];
                board[x][y + h -1] = tmp;
                if (h == 2)
                    board[x][y] = 0;
                return 2;
            }
        }

        if (w1 == 2)
        {
            if ((board[x][y - 1] == 11 || board[x][y - 1] == 12) &&
                (board[x + 1][y - 1] == 11 || board[x + 1][y -1 ] == 12))
            {
                // can move up 
                std::cout << "Can move 2 up." << std::endl;
                int tmp = board[x][y - 1];
                int tmp1 = board[x + 1][y - 1];
                board[x][y - 1] = board[x][y];
                board[x + 1][y  - 1] = 0;
                board[x][y + h -1] = tmp;
                board[x + 1][y + h -1] = tmp1;
                if (h == 2)
                {
                    board[x][y + h - 2] = 0;
                    board[x + 1][y - 1] = 0;
                }
                return 2;
            }
        }
    }

    // moving right
    if (x + w1 - 1 < 3)
    {
        if (h == 1)
        {
            bool force_move_left = false;
            if (x > 0 && (board[x - 1][y] == 11 || board[x - 1][y] == 12))
            {
                // can also move left
                force_move_left = (corner == 0 || corner == 2);
            }

            if (!force_move_left && (board[x + w1 ][y] == 11 || board[x + w1][y ] == 12))
            {
                std::cout << "Can move right." << std::endl;
                int tmp = board[x + w1][y ];
                board[x + 1][y] = board[x][y];
                board[x][y] = tmp;
                if (w1 == 2)
                    board[x + 2][y] = 0;
                return 3;
            }
        }
        if (h == 2)
        {
            if ((board[x + w1][y ] == 11 || board[x + w1][y] == 12) &&
                (board[x + w1][y + 1] == 11 || board[x + w1][y + 1] == 12))
            {
                std::cout << "Can move 2 right." << std::endl;
                int tmp = board[x + w1][y];
                int tmp1 = board[x + w1][y + 1];
                board[x + 1][y] = board[x][y];
                board[x + 1][y + 1] = 0;
                board[x][y] = tmp;
                board[x][y + 1] = tmp1;
                if (w1 == 2)
                {
                    board[x + 2][y] = 0;
                    board[x + 2][y+ 1] = 0;
                }
                return 3;
            }
        }
    }

    // moving left
    if (x > 0)
    {
        if (h == 1)
        {
            if (board[x - 1][y] == 11 || board[x - 1][y] == 12)
            {
                std::cout << "Can move left." << std::endl;
                int tmp = board[x - 1][y];
                board[x - 1][y] = board[x][y];
                board[x + w1 -1][y] = tmp;
                if (w1 == 2)
                    board[x][y] = 0;
                return 4;
            }
        }
        if (h == 2)
        {
            if ((board[x - 1][y] == 11 || board[x - 1][y] == 12) &&
                (board[x - 1][y + 1] == 11 || board[x - 1][y + 1] == 12))
            {
                std::cout << "Can move 2 left." << std::endl;
                int tmp = board[x -1][y ];
                int tmp1 = board[x - 1][y + 1];
                board[x-1][y] = board[x][y];
                board[x - 1][y + 1] = 0;
                board[x + w1 -1 ][y] = tmp;
                board[x + w1 -1 ][y + 1] = tmp1;

                if (w1 == 2)
                {
                    board[x][y] = 0;
                    board[x][y + 1] = 0;
                }
                return 4;
            }
        }
    }

    return 0;
}

void animation(RenderWindow& app, Sprite& blocker, int  move_direction)
{

    float speed = 10;
    int dx = 0;
    int dy = 1;

    switch (move_direction)
    {
    case 1:
        dx = 0;
        dy = 1;
        break;
    case 2:
        dx = 0;
        dy = -1;
        break;
    case 3:
        dx = 1;
        dy = 0;
        break;
    case 4:
        dx = -1;
        dy = 0;
        break;
    default:
        return;
    }

    for (int i = 0; i < w; i += speed)
    {
        blocker.move(speed * dx, speed * dy);
        app.draw(blocker);
        app.display();
    }
}

int main()
{
    RenderWindow app(VideoMode(1052,1315), "huao rong dao - Puzzle!");
	app.setFramerateLimit(60);
    Texture t;
    Sprite  blockers[13];
    t.loadFromFile("images/huarongdao.png");
    for (int i = 0; i < 13; ++i)
        blockers[i].setTexture(t);

    initSpriteBlockers(blockers);

    int board[4][5];
    initBoard(board, blockers);

    //setting sound
    sf::SoundBuffer buffer;
    sf::Sound sound;
    buffer.loadFromFile("sound.wav");
    sound.setBuffer(buffer);
    sound.setVolume(50);
    sound.setPitch(1);

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
            if (e.type == Event::MouseButtonPressed)
            {
                if (e.key.code == Mouse::Left)
                {
                    Vector2i pos = Mouse::getPosition(app);
                    int x = pos.x / w;
                    int y = pos.y / w;
                    std::cout << "x=" << x << " y=" << y << std::endl;
                    int blockIndex = getBlockerIndex(board, blockers, x, y);
                    int corner = getBlockerCorner(blockers[blockIndex], pos.x, pos.y);
                    int move_direction = moveBlock(board, blockers, blockIndex, corner);
                    if (move_direction > 0)
                    {
                        sound.play();
                        animation(app, blockers[blockIndex], move_direction);
                    }
                }
            }
        }

        app.clear(Color::White);
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (board[i][j] > 0)
                {
                    int blockIndex = board[i][j];
                    blockers[blockIndex].setPosition(w * i, w * j);
                    app.draw(blockers[blockIndex]);
                }
            }
        }
       app.display();
    }

    return 0;
}

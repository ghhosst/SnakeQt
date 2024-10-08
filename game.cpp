#include "game.h"
#include <QDebug>
#include <QPainter>
#include <QMessageBox>
#include <ctime>

Game::Game()
{
    // устанавливаем размеры
    resize(DOT_WIDTH * FIELD_WIDTH, DOT_HEIGHT * FIELD_HEIGHT);
    
    // пишем заголовок окна (заголовок игры)
    setWindowTitle("Snake game");
    
    
    
    // инициализируем игру
    initGame();
    
    
}






void Game::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
     
    
    if (m_inGame)
    {
        check_apple();
        move();
        check_collision();
    }
    
    repaint();
}





void Game::keyPressEvent(QKeyEvent *e)
{
    // здесь обрабатываем нажатия любой клавиши
    
    int key = e->key();
    
    if (key == Qt::Key_Left && m_dir != Directions::right)
        m_dir = Directions::left;
    
    if (key == Qt::Key_Right && m_dir != Directions::left)
        m_dir = Directions::right;
    
    if (key == Qt::Key_Up && m_dir != Directions::down)
        m_dir = Directions::up;
    
    if (key == Qt::Key_Down && m_dir != Directions::up)
        m_dir = Directions::down;
}






void Game::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    doDrawing();    
}








void Game::doDrawing()
{
    QPainter qp(this);
    
    // Если мы в игре - выполняем отрисовку
    if (m_inGame)
    {
        // рисуем яблоко
        qp.setBrush(Qt::red);
        qp.drawEllipse(m_apple.x() * DOT_WIDTH, m_apple.y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
        
        
        // рисуем змейку
        for (int i = 0; i < m_dots.size(); i++)
        {
            if (i == 0) // голова
            {
                qp.setBrush(QBrush(QColor(8, 163, 145)));
                qp.drawEllipse(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
            }
            else // тело змейки
            {
                qp.setBrush(Qt::green);
                qp.drawEllipse(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
            }
        }
    }
    else
    {
        gameOver();
    }    
}



// располагаем яблоко в рандомном месте игрового поля
void Game::localApple()
{
    srand(time(NULL));  
    m_apple.setX(rand() % (DOT_WIDTH - 1));
    m_apple.setY(rand() % (DOT_HEIGHT - 1));   
}



void Game::move()
{
    for (int i = m_dots.size() - 1; i > 0; i--)
    {
        m_dots[i] = m_dots[i - 1];
    }
    
    switch (m_dir)
    { 
    case left:
        m_dots[0].rx() -= 1;
        break;
    case right:
        m_dots[0].rx() += 1;
        break;
    case up:
        m_dots[0].ry() -= 1;
        break;
    case down:
        m_dots[0].ry() += 1;
        break;
    default:
        break;
    }
}





void Game::check_collision()
{
    // проверяем на столкновение головы с телом змейки
    if (m_dots.size() > 4)
    {
        for (int i = 1; i < m_dots.size(); i++)
        {
            if (m_dots[0] == m_dots[i])
                m_inGame = false;
        }
    }
    
    // проверяем столкновение с границами игрового поля
    if ((m_dots[0].x() >= FIELD_WIDTH) || (m_dots[0].x() < 0) ||
        (m_dots[0].y() >= FIELD_HEIGHT) || (m_dots[0].y() < 0))
            m_inGame = false;
    
    if (!m_inGame)
        killTimer(m_timerId);
}




void Game::gameOver()
{
    QMessageBox msgb;
    msgb.setText("Игра окончена!");
    msgb.exec();
    initGame();
}

void Game::check_apple()
{
    if (m_apple == m_dots[0])
    {
        m_dots.push_back(QPoint(0, 0));
        localApple();
    }
}






void Game::initGame()
{
    /* Инициалтизация игры вызывается в 2х случаях:
       когда 1-й раз зашли в программу,
       и после завершения, когда проиграли.
    */
    
    m_inGame = true; // мы в игре
    m_dir = right; // начальное направление
    
    // пусть изначально у змейки будет 3 части
    m_dots.resize(3);
    
    
    
    
    // заполним изначальное положение змейки
    // назначаем координаты змейки
    for (int i = 0; i < m_dots.size(); i++)
    {
        m_dots[i].setX(m_dots.size() - i - 1);
        m_dots[i].setY(0);
    }
    
    
    
    // располагаем яблоко в рандомном месте игрового поля
    // назначаем координаты
    localApple();
    
    
    // объявляем таймер
    m_timerId = startTimer(DELAY);
    
    
}




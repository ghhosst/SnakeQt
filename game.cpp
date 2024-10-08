#include "game.h"
#include <QDebug>
#include <QPainter>
#include <QMessageBox>

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
    
    bool eatenApple = false;
    
    if (m_inGame)
    {
        m_inGame = snake.check_collision(m_inGame, FIELD_WIDTH, FIELD_HEIGHT);
        if (!m_inGame)
            killTimer(m_timerId);
        
        eatenApple = snake.check_apple(m_apple);
        if (eatenApple)
            localApple();
            
        snake.move();
    }
    repaint();
}


void Game::keyPressEvent(QKeyEvent *e)
{
    // здесь обрабатываем нажатия любой клавиши   
    snake.change_direction(e->key());
}


void Game::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    doDrawing();    
}


void Game::doDrawing()
{
    // яблоко
    // QPixmap appleImage;
    // appleImage.load("C:\forStudy\\QtProjects\\Snake\apple.png");
    
    QPainter qp(this);
    QVector<QPoint> dots = snake.get_dots();
    
    // Если мы в игре - выполняем отрисовку
    if (m_inGame)
    {
        // рисуем яблоко
        qp.setBrush(Qt::red);
        qp.drawEllipse(m_apple.x() * DOT_WIDTH, m_apple.y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
        
        
        // рисуем змейку
        for (int i = 0; i < dots.size(); i++)
        {
            if (i == 0) // голова
            {
                qp.setBrush(QBrush(QColor(8, 163, 145)));
                qp.drawEllipse(dots[i].x() * DOT_WIDTH, dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
            }
            else // тело змейки
            {
                qp.setBrush(Qt::green);
                qp.drawEllipse(dots[i].x() * DOT_WIDTH, dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
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


void Game::gameOver()
{
    QMessageBox msgb;
    msgb.setText("Игра окончена!");
    msgb.exec();
    initGame();
}


void Game::initGame()
{
    /* Инициалтизация игры вызывается в 2х случаях:
       когда 1-й раз зашли в программу,
       и после завершения, когда проиграли.
    */
    m_inGame = true; // мы в игре
    
    // рождение змейки
    snake = CSnake();
    
    // располагаем яблоко в рандомном месте игрового поля
    // (назначаем координаты яблока)
    localApple();
    
    // объявляем таймер
    m_timerId = startTimer(DELAY);
}

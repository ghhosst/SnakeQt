#include "CSnake.h"



CSnake::CSnake()
{
    m_dir = right; // начальное направление движения змейки
    
    // пусть изначально у змейки будет 3 части
    m_dots.resize(3);
    
    
    // заполним изначальное положение змейки
    // (назначаем координаты змейки)
    for (int i = 0; i < m_dots.size(); i++)
    {
        m_dots[i].setX(m_dots.size() - i - 1);
        m_dots[i].setY(0);
    }
    
    m_headSnake.load("C:\\forStudy\\QtProjects\\Snake\\headSnake.png");
}


QPixmap CSnake::get_headSnake()
{
    return m_headSnake;
}

void CSnake::set_headSnake(QPixmap headSnake)
{
    m_headSnake = headSnake;
}


QVector<QPoint> CSnake::get_dots()
{
    return m_dots;
}

CSnake::Directions CSnake::get_direction()
{
    return m_dir;
}

void CSnake::set_direction(Directions dir)
{
    m_dir = dir;
}



void CSnake::move()
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


bool CSnake::check_collision(bool inGame, int fieldWidth, int fieldHeight)
{
    // проверяем на столкновение головы с телом змейки
    if (m_dots.size() > 4)
    {
        for (int i = 1; i < m_dots.size(); i++)
        {
            if (m_dots[0] == m_dots[i])
                inGame = false;
        }
    }
    
    // проверяем столкновение с границами игрового поля
    if ((m_dots[0].x() >= fieldWidth) || (m_dots[0].x() < 0) ||
        (m_dots[0].y() >= fieldHeight) || (m_dots[0].y() < 0))
            inGame = false;
    
    return inGame;
}


bool CSnake::check_apple(QPoint apple)
{
    bool eatenApple = false;
    if (apple == m_dots[0])
    {
        m_dots.push_back(QPoint(0, 0));
        eatenApple = true;
    }
    return eatenApple;
}

void CSnake::change_direction(int key)
{
    // для поворота головы
    QTransform tr;    
    
    
    if (key == Qt::Key_Left && m_dir != right)
    {
        switch (m_dir) { 
        case up:
            tr.rotate(-90);
            m_headSnake = m_headSnake.transformed(tr);
            break;
        case down:
            tr.rotate(90);
            m_headSnake = m_headSnake.transformed(tr);
        default:
            break;
        }
        m_dir = left;
    }
    
    if (key == Qt::Key_Right && m_dir != left)
    {
        switch (m_dir) { 
        case up:
            tr.rotate(90);
            m_headSnake = m_headSnake.transformed(tr);
            break;
        case down:
            tr.rotate(-90);
            m_headSnake = m_headSnake.transformed(tr);
        default:
            break;
        }   
        m_dir = right;
    }
    
    if (key == Qt::Key_Up && m_dir != down)
    {
        switch (m_dir) { 
        case right:
            tr.rotate(-90);
            m_headSnake = m_headSnake.transformed(tr);
            break;
        case left:
            tr.rotate(90);
            m_headSnake = m_headSnake.transformed(tr);
        default:
            break;
        }
        m_dir = up;
    }
    
    if (key == Qt::Key_Down && m_dir != up)
    {
        switch (m_dir) { 
        case right:
            tr.rotate(90);
            m_headSnake = m_headSnake.transformed(tr);
            break;
        case left:
            tr.rotate(-90);
            m_headSnake = m_headSnake.transformed(tr);
            break;
        default:
            break;
        }
        m_dir = down;
    }
}

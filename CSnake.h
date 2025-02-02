#ifndef CSNAKE_H
#define CSNAKE_H

#include <QVector>
#include <QPoint>
#include <QPainter>

class CSnake
{
private:
    // перечисление всех возможных вариантов
    // движения змейки (направления)
    enum Directions { left, right, up, down };
    Directions m_dir;
    
    // переменная, которая хранит инф-цию о всех точках змейки
    QVector<QPoint> m_dots;
    QPixmap m_headSnake;
public:
    CSnake();
    
    QPixmap get_headSnake();
    void set_headSnake(QPixmap headSnake);
    QVector<QPoint> get_dots();
    Directions get_direction();
    void set_direction(Directions dir);
    
    void move();
    bool check_collision(bool inGame, int fieldWidth, int fieldHeight);
    bool check_apple(QPoint apple);
    void change_direction(int key);
};

#endif // CSNAKE_H

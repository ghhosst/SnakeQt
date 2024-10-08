#ifndef GAME_H
#define GAME_H


/*
    -> Готовый интерфейс не используем,
    генерируем его на ходу. Для этого
    будем отображать класс game. Для того,
    чтобы его отобразить, унаследуем его от класса Widget.
*/

#include <QWidget>
#include <QKeyEvent>
#include "CSnake.h"


// В этом классе описываем логику игры
class Game : public QWidget
{
private:
    // размеры игровой клетки
    static const int DOT_WIDTH = 20;    // ширина клеточки
    static const int DOT_HEIGHT = 20;   // высота клеточки
    
    // размеры игрового поля
    // (колличество клеток (или точек))
    static const int FIELD_WIDTH = 20;  // ширина игрового поля
    static const int FIELD_HEIGHT = 20; // высота игрового поля
    
    // все действия нужно выполнять по таймеру
    // для этого заведем переменную
    static const int DELAY = 250;       // 250 мс
    
    
    void doDrawing();   // отрисовка объектов
    void localApple();  // расположение яблока на игровом поле
    void gameOver();    // конец игры
    void initGame();    // функция инициализации игры
    
    int m_timerId;      // таймер
    bool m_inGame;      // состояние игры
    
    CSnake snake;       // змейка
    QPoint m_apple;     // информация о яблоке
public:
    Game();
protected:
    void timerEvent(QTimerEvent*) override;
    
    // обработка нажатий 
    void keyPressEvent(QKeyEvent* event) override; // слот в Qt
    
    // как только нужно отрисовать виджет, вызывается этот слот
    void paintEvent(QPaintEvent* event) override; // слот
};

#endif // GAME_H

#ifndef GAME_H
#define GAME_H


/*
    -> Готовый интерфейс не используем,
    генерируем его на ходу. Для этого
    будем отображать класс game. Для того,
    чтобы его отобразить, унаследуем его от класса Widget.
*/

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>




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
    static const int DELAY = 160;       // 150 мс
    
    
    
    void doDrawing();
    void localApple();
    void move();
    void check_collision();
    void gameOver();
    void check_apple();
    
    
    int m_timerId;
    
    
    QPoint m_apple; // информация о яблоке
    
    
    
    // перечисление всех возможных вариантов
    // движения змейки
    enum Directions
    {
        left, right, up, down
    };
    
    Directions m_dir;
    
    
    
    bool m_inGame;
    
    // переменная, которая хранит инф-цию о всех точках змейки
    QVector<QPoint> m_dots;
    
    
    // функция инициализации игры
    void initGame();
    
public:
    // зачем мы внутрь конструктора
    // передаем указатель на QWidget ?
    Game(QWidget* parent);
    Game();
protected:
    void timerEvent(QTimerEvent*) override;
    
    // обработка нажатий 
    void keyPressEvent(QKeyEvent* event) override; // слот в Qt
    
    // как только нужно отрисовать виджет, вызывается этот слот
    void paintEvent(QPaintEvent* event) override; // слот
};












#endif // GAME_H

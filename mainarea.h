/*
  Copyright (c) 2007 Paolo Capriotti <p.capriotti@gmail.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
*/

#ifndef MAINAREA_H
#define MAINAREA_H

#include <QTimer>
#include <QTime>
#include <QList>
#include <QGraphicsScene>
#include "animator.h"

class Renderer;
class Ball;
class Message;
class Animation;
class QGraphicsSceneMouseEvent;
class QGraphicsTextItem;

namespace Phonon { class AudioPlayer; }
struct Collision;

class MainArea : public QGraphicsScene
{
Q_OBJECT
    QTimer m_timer;
    QTime m_global_time;
    int m_last_time;
    int m_last_game_time;
    QTime m_time;
    QTime m_event_time;

    /// time interval between two balls being added
    int m_ball_timeout;

    int m_size;
    Renderer* m_renderer;
    QPixmap m_background;
    Animator m_animator;

    QList<Ball*> m_balls;
    QList<Ball*> m_fading;
    Ball* m_man;

    /// the blue ball is dead
    bool m_death;

    /// the falling animation is over, we're waiting for a new game to start
    bool m_game_over;

    QGraphicsTextItem* m_welcome_msg;

    Phonon::AudioPlayer* m_player;

    double radius() const;
    QPointF randomPoint() const;
    QPointF randomDirection(double val) const;

    Ball* addBall(const QString& id);
    bool collide(const QPointF& a, const QPointF& b,
                double diam, Collision& collision);

    /* TODO msg
    Animation* writeMessage(const QString& text);
    Animation* writeText(const QStringList& lines);
    void displayMessages(const QList<KSharedPtr<Message> >& msgs);
    */
    void onCollision();
    void setManPosition(const QPointF& p);
    void drawBackground(QPainter*, const QRectF&);
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
public:
    MainArea();

    void start();

public slots:
    void tick();
    void enableSounds();
    void abort();
signals:
    void starting();
    void gameOver(int);
    void changeBallNumber(int);
    void changeGameTime(int);
};

#endif // MAINAREA_H


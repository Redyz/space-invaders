#pragma once

#include <iostream>
class Logic;
class Entity;

class Message {
  public:
    Message();
    virtual ~Message();
    virtual void execute();
    virtual bool canExecute();
    virtual std::string toString();
  private:
    friend class Logic;
    void setId(unsigned int id);
    unsigned int messageId = 0;
};
class DeathMessage final : public Message {
  public:
    DeathMessage(Entity* killed);
    DeathMessage(Entity* killed, Entity* killer);
    virtual void execute(Logic *logic);
  protected:
    Entity* killed;
    Entity* killer;
};
class FireMessage final : public Message{
  public:
    FireMessage(Entity* firer, int startX, int startY, int direction);
    virtual void execute(Logic *logic);
  protected:
    int startX;
    int startY;
    int direction;
    Entity* firer;
};

class ArmageddonMessage final : public Message{
  public:
    ArmageddonMessage();
    virtual void execute(Logic *logic);
};

class HitMessage final : public Message{
  public:
    HitMessage(Entity* firer, Entity* fired);
    void execute(Logic* logic);
  protected:
    Entity* firer;
    Entity* fired;
};

class InvertDirectionMessage final : public Message{
  public:
    InvertDirectionMessage();
    void execute(Logic* logic);
};

enum GAME_OVER_REASON{
    REACHED_BOTTOM,
    LOST_ALL_LIVES,
    NO_MORE_ENEMIES,
    QUIT_GAME
};
class GameOverMessage final : public Message{
  public:
    GameOverMessage(int reason);
    void execute(Logic* logic);
  protected:
    int reason;
};

class KillAllEnemiesMessage final : public Message{
  public:
    KillAllEnemiesMessage();
    void execute(Logic* logic);
};

class ConsoleMessage final : public Message{
  public:
    ConsoleMessage(std::string message);
    virtual void execute(Logic *logic);
    virtual bool canExecute(Logic *logic);
    virtual std::string toString();
  protected:
    std::string message;
};

class DisplayCenterMessage final : public Message{
  public:
    DisplayCenterMessage(std::string message, unsigned int duration);
    virtual void execute(Logic *logic);
  private:
    std::string message;
    unsigned int duration;
};

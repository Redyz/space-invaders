#ifndef MESSAGE_H
#define MESSAGE_H
class Logic;
class Entity;
class Message{
  public:
    Message();
    ~Message();
    void init();
    virtual void execute(Logic *logic);
};


class DeathMessage : public Message{
  public:
    DeathMessage(Entity *killed);
    DeathMessage(Entity *killed, Entity *killer);
    virtual void execute(Logic *logic);
  private:
    Entity *killed;
    Entity *killer;
};


class FireMessage : public Message{
  public:
    FireMessage(Entity *firer, int startX, int startY, int direction);
    virtual void execute(Logic *logic);
  private:
    int startX;
    int startY;
    int direction;
    Entity *firer;
};
#endif

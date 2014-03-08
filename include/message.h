#ifndef MESSAGE_H
#define MESSAGE_H
class Logic;
class Entity;
class Message{
  public:
    Message();
    ~Message();
    void init();
    void execute(Logic *logic);
};


class DeathMessage : public Message{
  public:
    DeathMessage(Entity *killed);
    DeathMessage(Entity *killed, Entity *killer);
    void execute(Logic *logic);
  private:
    Entity *killed;
    Entity *killer;
};
#endif

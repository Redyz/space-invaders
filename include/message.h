#ifndef MESSAGE_H
#define MESSAGE_H
class Logic;
template <class Object>
class Message{
  public:
    Message(int messageType, Object* concernedObject);
    ~Message();
  private:
    Logic *logic;


};
#endif

#include "logic.h"
#include "message.h"

Message::Message(int messageType, Object* concernedObject){
  this->logic = concernedObject->logic;
}

Message::~Message(){

}






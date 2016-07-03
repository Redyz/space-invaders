#pragma once

class Logic;
class Input final{
  public:
    Input(Logic* logic);
    ~Input();
    void step();
  private:
    Logic* logic;
};

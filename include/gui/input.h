#ifndef INPUT_H
#define INPUT_H

class Logic;

class Input final{
  public:
    Input(Logic *logic);
    ~Input();

    void step();

  private:
    Logic *logic;
};

#endif

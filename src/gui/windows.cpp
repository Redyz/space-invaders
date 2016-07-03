#include "config.h"
#include "logic.h"
#include "entity.h"
#include "utility.h"
#include "menumanager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

//TODO: Think this bit through
static sf::Sprite ghostSprite;
static sf::Texture ghostTexture;

static sf::Sprite missileSprite;
static sf::Texture missileTexture;

static sf::Sprite sprite;
static sf::Texture texture;

//TODO: Array-ize everything here
Window::Window(){
  sfWindow = new sf::RenderWindow();
  font = new sf::Font();
  debugText = new sf::Text("Hello", *font);
  configText(*debugText);
  //TODO: Portable paths
  font->loadFromFile("fonts/Comprehension-Dark.ttf");
  texture.loadFromFile("assets/img/Spaceship.png");
  ghostTexture.loadFromFile("assets/img/Ghost.png");
  ghostSprite.setTexture(ghostTexture);
  missileTexture.loadFromFile("assets/img/Missile.png");
  missileSprite.setTexture(missileTexture);
  sprite.setTexture(texture);
}

Window::~Window(){
  delete input;
  delete sfWindow;
  delete font;
  delete debugText;
  delete visualMenu;
  delete menuManager;
}

#define GAME_WIDTH 1280
#define GAME_HEIGHT 720

static unsigned int scale;
void Window::setup(Logic *logic){
  this->logic = logic;
  sfWindow->create(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "Window");
  sfWindow->setFramerateLimit(SFML_FRAME_LIMIT);
  width = GAME_WIDTH;
  height = GAME_HEIGHT;
  logic->setGameWidth(GAME_WIDTH);
  logic->setGameHeight(GAME_HEIGHT);

  this->menuManager = new MenuManager(logic);
  logic->menu = this->menuManager->MAINMENU;
  this->input = new Input(logic);
  visualMenu = new VisualMenu(logic, logic->menu);

}

void Window::configText(sf::Text &text){
  text.setCharacterSize(30);
  text.setStyle(sf::Text::Bold);
  text.setColor(sf::Color::White);
}

void Window::clearWindow(){

}

void Window::inputStep(){
  sf::Event event;
  while (sfWindow->pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      destroy();
  }
  input->step();
}

void Window::draw(){
  auto size = sfWindow->getSize();
  scale = size.x / 512;
  sfWindow->clear(sf::Color::Black);
  std::vector<Entity*> entityVector = logic->getEntityVector();
  for(std::vector<Entity*>::iterator it = entityVector.begin(); it != entityVector.end(); ++it){
    Entity* entity = *it;
    switch(entity->getType()){
      case GHOST:
        ghostSprite.setPosition(entity->getX()*scale, entity->getY());
        sfWindow->draw(ghostSprite);
        break;
      case BULLET:
        missileSprite.setPosition(entity->getX()*scale, entity->getY());
        sfWindow->draw(missileSprite);
      default:
        break;  
    }  
  }
  sprite.setPosition(logic->getPlayer()->getX()*scale, logic->getPlayer()->getY());
  sfWindow->draw(sprite);
  sfWindow->draw(*debugText);
  sfWindow->draw(sprite);
  drawMenu();
  sfWindow->display();
}

void Window::drawMenu(){
  if(!logic->menu->isVisible())
    return;
  visualMenu->draw();
}

void Window::changeMenu(Menu *newMenu){
  logic->menu = newMenu;
  this->visualMenu->changeMenu(logic->menu);
}

void Window::debug(std::string text){
  debugText->setString(text);
}

void Window::display(std::string text){
  debug(text);
}

void Window::display_center(std::string text){
  
}

void Window::console(std::string text){
  std::cout << text << std::endl;
}

void Window::destroy(){
  sfWindow->close();
  logic->setGameState(QUITTING);
}



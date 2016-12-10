//// BouncingSFMLSpriteExample.cpp
//// Use the SFML library to bounce a sprite around a game window.
////
//// Requires SFML-graphics library.

#include "stdafx.h"
#include <exception>
#include <vector>
#include <functional>

#include <SFML/Graphics.hpp>

using MessageContainer = std::vector<std::string>;

class TextBox {
public:
	TextBox() { Setup(5, 9, 200, sf::Vector2f(0, 0)); }
	TextBox(int visible, int charSize, int width, sf::Vector2f screenPos) {
		Setup(visible, charSize, width, screenPos);
	}
	~TextBox() { Clear(); }

	void Setup(int visible, int charSize, int width, sf::Vector2f screenPos);
	void Add(std::string message);
	void Clear() { _messages.clear(); }

	void Render(sf::RenderWindow& window);
private:
	MessageContainer _messages;
	int _numVisible;

	sf::RectangleShape _backdrop;
	sf::Font _font;
	sf::Text _content;
};

void TextBox::Setup(int visible, int charSize, int width, sf::Vector2f screenPos)
{
	_numVisible = visible;

	sf::Vector2f offset(2.0f, 2.0f);

	_font.loadFromFile("arial.ttf");
	_content.setFont(_font);
	_content.setString("");
	_content.setCharacterSize(charSize);
	_content.setColor(sf::Color::White);
	_content.setPosition(screenPos + offset);

	auto backdropHeight = visible * (charSize * 1.2f);
	_backdrop.setSize(sf::Vector2f(width, backdropHeight));
	_backdrop.setFillColor(sf::Color(90, 90, 90, 90));
	_backdrop.setPosition(screenPos);
}

void TextBox::Add(std::string message)
{
	_messages.push_back(message);
	if (_messages.size() >= 5) {
		_messages.erase(_messages.begin());
	}
}

void TextBox::Render(sf::RenderWindow & window)
{
	std::string content;
	for (auto &itr : _messages) {
		content.append(itr + "\n");
	}

	if (content == "") {
		return;
	}

	_content.setString(content);
	window.draw(_backdrop);
	window.draw(_content);
}

struct SnakeSegment {
	SnakeSegment(int x, int y) : position(x, y) {}
	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction { None, Up, Down, Left, Right };

class Snake {
public:
	Snake(int blockSize);
	~Snake();

	void SetDirection(Direction dir) { _direction = dir; }

	// Get direction snake is moving
	Direction GetDirection() { return _direction; }

	int GetSpeed() { return _speed; }
	sf::Vector2i GetPosition() { return !_body.empty() ? _body.front().position : sf::Vector2i(1, 1); }
	int GetLives() { return _lives; }
	int GetScore() { return _score; }
	int GetLength() { return _body.size(); }

	// Get direction snake is facing
	Direction GetPhysicalDirection();

	void IncreaseScore() { _score += 10; }
	bool HasLost() { return _lost; }

	void Lose() { _lost = true; }
	void ToggleLost() { _lost = !_lost; }

	void Extend();
	void ResetToStart();

	void Move();
	void Tick();
	void Cut(int segments);
	void Render(sf::RenderWindow& window);
private:
	void CheckCollision();

	SnakeContainer _body;
	int _size;
	int _speed;
	Direction _direction;
	int _lives;
	int _score;
	bool _lost;
	sf::RectangleShape _bodyRect;
};

Snake::Snake(int blockSize) {
	_size = blockSize;
	_bodyRect.setSize(sf::Vector2f(_size - 1, _size - 1));
	ResetToStart();
}

Snake::~Snake() {}

Direction Snake::GetPhysicalDirection()
{
	if (_body.size() <= 1) {
		return Direction::None;
	}

	auto head = _body[0];
	auto neck = _body[1];
	if (head.position.x == neck.position.x) {
		return (head.position.y > neck.position.y) ? Direction::Down : Direction::Up;
	}
	else if (head.position.y == neck.position.y) {
		return (head.position.x > neck.position.x) ? Direction::Right : Direction::Left;
	}
	else {
		return Direction::None;
	}
}

void Snake::Extend() {
	if (_body.empty()) { return; }

	auto tail_head = _body[_body.size() - 1];
	if (_body.size() > 1) {
		// Snake has more than one segment
		auto tail_bone = _body[_body.size() - 2];

		if (tail_head.position.x == tail_bone.position.x) {
			if (tail_head.position.y > tail_bone.position.y) {
				// [H]
				// [ ]
				_body.push_back({ tail_head.position.x, tail_head.position.y + 1 });
			}
			else {
				// [ ]
				// [H]
				_body.push_back({ tail_head.position.x, tail_head.position.y - 1 });
			}
		}
		else if (tail_head.position.y == tail_bone.position.y) {
			if (tail_head.position.x > tail_bone.position.x) {
				// [ ] [H]
				_body.push_back({ tail_head.position.x + 1, tail_head.position.y });
			}
			else {
				// [H] [ ]
				_body.push_back({ tail_head.position.x - 1, tail_head.position.y });
			}
		}
	}
	else {
		switch (_direction) {
		case Direction::Up:
			_body.push_back({ tail_head.position.x, tail_head.position.y + 1 });
			break;
		case Direction::Down:
			_body.push_back({ tail_head.position.x, tail_head.position.y - 1 });
			break;
		case Direction::Left:
			_body.push_back({ tail_head.position.x + 1, tail_head.position.y });
			break;
		case Direction::Right:
			_body.push_back({ tail_head.position.x - 1, tail_head.position.y });
			break;
		}
	}
}

void Snake::Tick() {
	if (_body.empty()) { return; }
	if (_direction == Direction::None) { return; }
	Move();
	CheckCollision();
}

void Snake::Move() {
	// Move body
	for (int i = _body.size() - 1; i > 0; --i) {
		_body[i].position = _body[i - 1].position;
	}
	// Move head
	switch (_direction) {
	case Direction::Left:
		--_body[0].position.x;
		break;
	case Direction::Right:
		++_body[0].position.x;
		break;
	case Direction::Up:
		--_body[0].position.y;
		break;
	case Direction::Down:
		++_body[0].position.y;
		break;
	}
}

void Snake::CheckCollision() {
	if (_body.size() < 5) { return; }
	auto head = _body.front();
	for (auto itr = _body.begin() + 1; itr != _body.end(); ++itr) {
		if (itr->position == head.position) {
			// current position intersected with head
			int segments = _body.end() - itr;
			Cut(segments);
			break;
		}
	}
}

void Snake::Cut(int segments) {
	for (int i = 0; i < segments; ++i) {
		_body.pop_back();
	}

	_lives -= 1;
	if (!_lives) {
		Lose();
	}
}

void Snake::Render(sf::RenderWindow& window) {
	if (_body.empty()) { return; }

	// Draw head
	auto head = _body.begin();
	_bodyRect.setFillColor(sf::Color::Yellow);
	_bodyRect.setPosition(head->position.x * _size, head->position.y * _size);
	window.draw(_bodyRect);

	// Draw body
	_bodyRect.setFillColor(sf::Color::Green);
	for (auto itr = _body.begin() + 1; itr != _body.end(); ++itr) {
		_bodyRect.setPosition(itr->position.x * _size, itr->position.y * _size);
		window.draw(_bodyRect);
	}
}

void Snake::ResetToStart() {
	_body.clear();
	_body.push_back(SnakeSegment(5, 7));
	_body.push_back(SnakeSegment(5, 6));
	_body.push_back(SnakeSegment(5, 5));

	SetDirection(Direction::None);
	_speed = 0;
	_lives = 3;
	_score = 0;
	_lost = false;
}

class World {
public:
	World(sf::Vector2u windowSize);
	~World();

	int GetBlockSize() { return _blockSize; }
	void RespawnApple();

	void Update(Snake& player);
	void Render(sf::RenderWindow& window);
	void SetMessageCallback(std::function<void(std::string)> msgCallback) { _msgCallback = msgCallback; }
private:
	sf::Vector2u _windowSize;
	sf::Vector2i _item;
	int _blockSize;
	std::function<void(std::string)> _msgCallback;

	sf::CircleShape _appleShape;
	sf::RectangleShape _bounds[4];
};

World::World(sf::Vector2u windowSize) :
	_windowSize(windowSize),
	_blockSize(16),
	_msgCallback([](std::string str) {})
{
	RespawnApple();
	_appleShape.setFillColor(sf::Color::Red);
	_appleShape.setRadius(_blockSize / 2);

	_bounds[0].setFillColor(sf::Color(150, 0, 0));
	_bounds[0].setSize(sf::Vector2f(_windowSize.x, _blockSize));
	_bounds[0].setOrigin(_bounds[0].getSize());
	_bounds[0].setPosition(sf::Vector2f(windowSize));

	_bounds[1].setFillColor(sf::Color(150, 0, 0));
	_bounds[1].setSize(sf::Vector2f(_blockSize, _windowSize.y));
	_bounds[1].setOrigin(_bounds[1].getSize());
	_bounds[1].setPosition(sf::Vector2f(windowSize));

	_bounds[2].setFillColor(sf::Color(150, 0, 0));
	_bounds[2].setSize(sf::Vector2f(_windowSize.x, _blockSize));
	_bounds[2].setPosition(0, 0);

	_bounds[3].setFillColor(sf::Color(150, 0, 0));
	_bounds[3].setSize(sf::Vector2f(_blockSize, _windowSize.y));
	_bounds[3].setPosition(0, 0);
}

World::~World() {}

void World::RespawnApple() {
	_msgCallback("Respawning Apple");
	int maxX = _windowSize.x / _blockSize - 2;
	int maxY = _windowSize.y / _blockSize - 2;
	_item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
	_appleShape.setPosition(_item.x * _blockSize, _item.y * _blockSize);
}

void World::Update(Snake& player) {
	auto currentPos = player.GetPosition();

	if (currentPos == _item) {
		// Eat apple
		player.Extend();
		player.IncreaseScore();
		_msgCallback(std::string("Length +1 [") + std::to_string(player.GetLength()) + "]");
		RespawnApple();
	}

	int gridSizeX = _windowSize.x / _blockSize;
	int gridSizeY = _windowSize.y / _blockSize;
	if (currentPos.x <= 0
		|| currentPos.y <= 0
		|| currentPos.x >= gridSizeX - 1
		|| currentPos.y >= gridSizeY - 1) {
		// Out of bounds
		player.Lose();
	}
}

void World::Render(sf::RenderWindow& window) {
	for (int i = 0; i < 4; ++i) {
		window.draw(_bounds[i]);
	}
	window.draw(_appleShape);

}

class Window {
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	// Clear the window
	void BeginDraw();

	// Display the changes
	void EndDraw();

	void Update();

	bool isDone() { return _isDone; }
	bool isFullscreen() { return _isFullscreen; }
	sf::Vector2u GetWindowSize() { return _windowSize; }
	sf::RenderWindow* GetRenderWindow() { return &_window; }

	void ToggleFullscreen();

	void Draw(sf::Drawable& drawable);
private:
	void Setup(const std::string title, const sf::Vector2u size);
	void Destroy();
	void Create();

	sf::RenderWindow _window;
	std::string _windowTitle;
	sf::Vector2u _windowSize;
	bool _isDone;
	bool _isFullscreen;
};

Window::Window() { Setup("Window", sf::Vector2u(640, 480)); }

Window::Window(const std::string& title, const sf::Vector2u& size) { Setup(title, size); }

Window::~Window() { Destroy(); }

void Window::Setup(const std::string title, const sf::Vector2u size) {
	_windowTitle = title;
	_windowSize = size;
	_isFullscreen = false;
	_isDone = false;
	Create();
}

void Window::Create() {
	auto style = _isFullscreen ? sf::Style::Fullscreen : sf::Style::Default;
	_window.create({ _windowSize.x, _windowSize.y, 32 }, _windowTitle, style);
}

void Window::Update() {
	sf::Event evt;
	while (_window.pollEvent(evt)) {
		if (evt.type == sf::Event::Closed) {
			_isDone = true;
		} else if (evt.type == sf::Event::KeyPressed && evt.key.code == sf::Keyboard::F5) {
			ToggleFullscreen();
		}
	}
}

void Window::ToggleFullscreen() {
	_isFullscreen = _isFullscreen;
	Destroy();
	Create();
}

void Window::Draw(sf::Drawable& drawable) {
	_window.draw(drawable);
}

void Window::Destroy() {
	_window.close();
}

void Window::BeginDraw() {
	_window.clear(sf::Color::Black);
}

void Window::EndDraw() {
	_window.display();
}


class Game {
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();
	Window* GetWindow() { return &_window; }
	sf::Time GetElapsed();
	void RestartClock();
private:
	Window _window;
	World _world;
	Snake _snake;
	TextBox _textBox;
	sf::Clock _clock;
	sf::Time _elapsed;
};

Game::Game() :
	_window("Retro Snake", sf::Vector2u(800, 600)),
	_snake(_world.GetBlockSize()),
	_textBox(5, 14, 350, sf::Vector2f(255, 0)),
	_world(sf::Vector2u(800, 600))
{
	_textBox.Add("Seeded random number generator with: " + std::to_string(time(NULL)));
	_world.SetMessageCallback(std::bind(&TextBox::Add, &_textBox, std::placeholders::_1));
}

Game::~Game() {}

void Game::Update() {
	float frametime = 1.0f / 10.f;
	if (_elapsed.asSeconds() >= frametime) {
		_snake.Tick();
		_world.Update(_snake);
		_elapsed -= sf::seconds(frametime);

		if (_snake.HasLost()) {
			_textBox.Add("Game Over! Final Score: " + std::to_string(_snake.GetScore()));
			_snake.ResetToStart();
		}
	}
}

void Game::Render() {
	_window.BeginDraw();
	_world.Render(*_window.GetRenderWindow());
	_snake.Render(*_window.GetRenderWindow());
	_textBox.Render(*_window.GetRenderWindow());
	_window.EndDraw();
}

void Game::HandleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& _snake.GetPhysicalDirection() != Direction::Down) {
		_snake.SetDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& _snake.GetPhysicalDirection() != Direction::Up) {
		_snake.SetDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& _snake.GetPhysicalDirection() != Direction::Right) {
		_snake.SetDirection(Direction::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& _snake.GetPhysicalDirection() != Direction::Left) {
		_snake.SetDirection(Direction::Right);
	}
}

sf::Time Game::GetElapsed() { return _clock.getElapsedTime(); }

void Game::RestartClock() { _elapsed += _clock.restart(); }

int main()
{
	Game game;
	while (!game.GetWindow()->isDone()) {
		game.HandleInput();
		game.Update();
		game.Render();

		//sf::sleep(sf::seconds(0.2));
		game.RestartClock();
	}
}

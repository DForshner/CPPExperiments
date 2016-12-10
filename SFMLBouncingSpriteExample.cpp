// SFMLBouncingSpriteExample.cpp
// Use the SFML library to bounce a sprite around a game window.

#include "stdafx.h"
#include <exception>>

#include <SFML/Graphics.hpp>

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
	sf::Time GetElapsed() { return _elapsed; }
	void RestartClock() { _elapsed += _clock.restart(); }
private:
	void MoveCat();
	Window _window;
	sf::Texture _catTexture;
	sf::Sprite _catSprite;
	sf::Vector2f _increment;
	sf::Clock _clock;
	sf::Time _elapsed;
};

Game::Game() :
	_window("Cat Bounce!", sf::Vector2u(800, 600)),
	_increment({400.0f, 400.0f})
{
	if (!_catTexture.loadFromFile("Cat.png")) {
		throw std::exception("Could not fine file");
	}
	auto size = _catTexture.getSize();
	_catSprite.setTexture(_catTexture);
	_catSprite.setOrigin(size.x / 2, size.y / 2);
}

Game::~Game() {}

void Game::HandleInput() {

}

void Game::Update() {
	float frametime = 1.0f / 60.f;
	if (_elapsed.asSeconds() >= frametime) {
		_window.Update();
		MoveCat();
		_elapsed -= sf::seconds(frametime);
	}
}

void Game::MoveCat() {
	sf::Vector2u windowSize = _window.GetWindowSize();
	sf::Vector2u textSize = _catTexture.getSize();

	if (
		(_catSprite.getPosition().x > windowSize.x - textSize.x && _increment.x > 0)
		|| (_catSprite.getPosition().x < 0 && _increment.x < 0)
		) {
		_increment.x = -_increment.x;
	}

	if (
		(_catSprite.getPosition().y > windowSize.y - textSize.y && _increment.y > 0)
		|| (_catSprite.getPosition().y < 0 && _increment.y < 0)
		) {
		_increment.y = -_increment.y;
	}

	float elapsed = _elapsed.asSeconds();

	_catSprite.setPosition(
		_catSprite.getPosition().x + (_increment.x * elapsed),
		_catSprite.getPosition().y + (_increment.y * elapsed));
}

void Game::Render() {
	_window.BeginDraw();
	_window.Draw(_catSprite);
	_window.EndDraw();
}

int main()
{
	Game game;
	while(!game.GetWindow()->isDone()) {
		game.HandleInput();
		game.Update();
		game.Render();

		//sf::sleep(sf::seconds(0.2));
		game.RestartClock();
	}
}


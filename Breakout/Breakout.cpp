#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "windows.h"
#include "bouncingBall.h"
#include "constants.h"
#include <fstream>


const std::string highscores = "highscore.txt";///< the txt file where the score is saved

 /**
 * Starts the game
 * @param window which displays the game
 */
void runGame(sf::RenderWindow &window);
	
/**
 * The struct saves the score in the txt file
 */
struct Highscore {

	int score = 0;
	int highestScore;
	
	/**
	* Loads score from the file
	* @return true if the load was successful
	*/
	bool load() {
		std::ifstream inFile(highscores);

		if (!inFile.is_open()) {
			return false;
		}
		inFile >> score;
		return true;
	}
	
	/**
	* Saves the score to the file
	*/
	void save() {
		std::ofstream outFile(highscores);
		outFile << score << "\n";
	}

};

/**
 * The struct defines the bricks that will be smashed by the ball
 */
struct Brick {
	Rectang rect;
	
	sf::RectangleShape shape;
	bool isHit = false;

	/**
	* Draws a brick into the window
	* @param window to drawing into
	*/
	void draw(sf::RenderWindow &window) {
		
		if (!isHit) {
			window.draw(shape);
		}
	}
	
};

/**
 *The struct defines a game menu, 
 */
struct GameMenu {

	////////////////
	sf::Text newGameText;
	sf::Text loadGameText;
	sf::Text helpText;
	sf::Text quitText;
	sf::Text arrowText;
	/**
	* Initilizes a game menu
	* @param font defines the type of the font.
	*/
	GameMenu(sf::Font &font) {
		
		newGameText.setString("New Game");
		loadGameText.setString("High Score");
		helpText.setString("Help");
		quitText.setString("Exit");
		arrowText.setString("=>");

		newGameText.setFont(font);
		loadGameText.setFont(font);
		helpText.setFont(font);
		quitText.setFont(font);
		arrowText.setFont(font);

		newGameText.setPosition(300, 100);
		loadGameText.setPosition(300, 200);
		helpText.setPosition(300, 300);
		quitText.setPosition(300, 400);
		arrowText.setPosition(200, 100);
	}

	/**
	* moves the arrow downward throught the game menu
	*/
	void arrowDown() {
		
		arrowText.move(0, 100);
		if (arrowText.getPosition().y > quitText.getPosition().y) {
			arrowText.setPosition(200, 100);
		}
	}
	/**
	* moves the arrow upward throught the game menu
	*/
	void arrowUp() {

		arrowText.move(0, -100);
		if (arrowText.getPosition().y < newGameText.getPosition().y) {
			arrowText.setPosition(200, 400);
		}
	}

	/**
	* Checks which option has been chosen
	* @param window which displays the choices
	* @param font defines the type of the font
	* @return true if the player wants to quit
	*/
	bool arrowSelect(sf::RenderWindow &window, sf::Font& font){
		if (arrowText.getPosition().y == newGameText.getPosition().y) {
			runGame(window);
		}
		else if (arrowText.getPosition().y == loadGameText.getPosition().y) {
			showHighScore(window, font);
		}
		else if (arrowText.getPosition().y == helpText.getPosition().y) {
			help(window, font);

		}
		else if (arrowText.getPosition().y == quitText.getPosition().y) {
			return true;
		}
		
		return false;
	}


		/**
	   * Displays high score menu
	   * @param window which displays the high score texts
	   * @param font defines the type of the font
	   */
	void showHighScore(sf::RenderWindow &window, sf::Font &font) {		
		Highscore scoreList;
		scoreList.load();
		sf::Text TheHighScore;
		sf::Text TheScoreList;

		TheHighScore.setString("The latest Score: ");
		TheHighScore.setFont(font);
		TheHighScore.setPosition(200, 100);

		//score is an int and it needs to be converted to a string
		TheScoreList.setString(std::to_string(scoreList.score));
		TheScoreList.setFont(font);
		TheScoreList.setPosition(200, 200);

		
		sf::Event event;
		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				if (event.type == event.Closed) {
					window.close();
				}
				else if (event.type == event.KeyPressed) {

					if (event.key.code == sf::Keyboard::Key::Space) {
						return;
					}
				}
			}
			window.clear();
			window.draw(TheHighScore);
			window.draw(TheScoreList);
			window.display();
			Sleep(50);

		}
		
	}
	
		/**
	   * Displays help
	   * @param window which displays the help info texts
	   * @param font defines the type of the font
	   */
	void help(sf::RenderWindow& window, sf::Font& font) {

		sf::Text displayHelp;
		sf::Text displayHelpText;

		displayHelp.setString("You have given 4 failures");
		displayHelp.setFont(font);
		displayHelp.setPosition(200, 100);

		displayHelpText.setString("Use arrow key to move the racket");
		displayHelpText.setFont(font);
		displayHelpText.setPosition(200, 200);


		sf::Event event;
		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				if (event.type == event.Closed) {
					window.close();
				}
				else if (event.type == event.KeyPressed) {

					if (event.key.code == sf::Keyboard::Key::Space) {
						return;
					}
				}
			}
			window.clear();
			window.draw(displayHelp);
			window.draw(displayHelpText);
			window.display();
			Sleep(50);
		}

	}

	void gameOver(sf::RenderWindow &window,sf::Font& font) {
	
		sf::Text gameOver;

		gameOver.setString("GAME OVER");
		gameOver.setFont(font);
		gameOver.setPosition(300, 100);
		window.clear();
		window.draw(gameOver);
		window.display();
		Sleep(50);
	
	
	}

	
		/**
	   * Displays the menu
	   * @param window to display the menu in
	   */
	void draw(sf::RenderWindow &window) {
		window.draw(newGameText);
		window.draw(loadGameText);
		window.draw(helpText);
		window.draw(quitText);
		window.draw(arrowText);

	}

};

/**
*The struct defines the player/racket 
*/

struct Player {
	sf::RectangleShape shape;
	int x = 400;
	int y = 550;
	int health = 5;

	/**
	*Initilizes the racket color, size and the position
	*/
	Player() {
		shape.setFillColor(sf::Color::White);
		shape.setSize(sf::Vector2f(playerWidth, playerHeight));//vector2f is a point in coodinate system where it holds the x and y values
		shape.setPosition(x, y);
	}
	
	/**
   * Draws the rack into window 
   * @param window which displays the racket
   */
	void draw(sf::RenderWindow &window) {
		
		window.draw(shape);

	}
	/**
	* moves the racket to the left
	*/
	void goLeft() {
		x -= 20;
		if (x < 0) {
			x = 0;
		}
		shape.setPosition(x, y);
	}
	/**
	* moves the racket to the right
	*/
	void goRight() {
		x += 20;
		if (x + playerWidth > screenWidth - 2) {
			x = screenWidth - playerWidth - 1;
		}
		shape.setPosition(x, y);
	}


	/**
	* Checks if the ball has collided with the racket
	* @param ball to check collision with
	* @return true if the ball has collided with the racket
	*/
	bool intersects(BouncingBall &ball) {
		Rectang rect;
		rect.x = x;
		rect.y = y;
		rect.height = playerHeight;
		rect.width = playerWidth;
		return ball.intersects(rect);
	}
	
};


/**
* Loads the level from a file
* @param path of the file
* @return all the bricks of the level
*/

std::vector<Brick> loadLevel(std::string path) {
	std::vector<Brick> result;
	std::ifstream inFile(path);
	
	if (!inFile.is_open()) {
		return result;
	}
	//https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
	std::random_device rd;            // generating integers from a random_device is expensive
	std::mt19937 generator(rd());    // generating integers from a mersenne twister (mt19937) is a lot cheaper
	std::uniform_int_distribution<> colorDistribution(0, 255);
	char current = 0;
	char previous = 0;
	int x = 0, y = 0;
	while (inFile.get(current)) {
		if (current == '#') {
			if (previous == '#') {
				Brick brick;
				
				brick.rect.x = x * 20;
				brick.rect.y = y * 20;
				brick.rect.width = 20;
				brick.rect.height = 20;
				//random color 0 till 255
				sf::Color color;
				color.a = 255;
				color.r = colorDistribution(generator);
				color.g = colorDistribution(generator);
				color.b = colorDistribution(generator);
				brick.shape.setFillColor(color);
				
				brick.shape.setPosition(brick.rect.x, brick.rect.y);
				//vector2f is a point in coodinate system where it holds the x and y values
				brick.shape.setSize(sf::Vector2f(brick.rect.width, brick.rect.height));

				
				result.push_back(brick);
			}
		}
		x += 1;
		//it basically translate the brick into pixels
		if (current == '\n') {
			y += 1;
			x = 0;
		}
		previous = current;
	}

	return result;
}

/**
* Starts the game
* @param window to display the game
*/
void runGame(sf::RenderWindow &window) {
	Highscore scoreList;
	Player player;
	BouncingBall ball;
	std::random_device rd;            // generating integers from a random_device is expensive
	std::mt19937 generator(rd());    // generating integers from a mersenne twister (mt19937) is a lot cheaper
	
	
	
	std::vector<std::string> levels = {
		//"pyramid.level", "heart.level", 
		"star.level", "sigma.level"
	};
	std::uniform_int_distribution<> levelsDistribution(0, levels.size() - 1);
	std::string level = levels[levelsDistribution(generator)];
	std::vector<Brick> bricks = loadLevel(level);
	


	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == event.Closed) {
				window.close();
			}
	
		}
		//player
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			player.goLeft();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			player.goRight();
		}
		


		
		/**
		* updating the ball direction after colliding with the racket
		*/
		ball.updateBall();
		
		if (player.intersects(ball)) {
			while (player.intersects(ball)) {
				int oldx = ball.x - ball.vx;
				int oldy = ball.y - ball.vy;
				ball.x = oldx;
				ball.y = oldy;

			}
			//ball.y -> velocity
			ball.vy = -ball.vy;
		}



		/**
		* if the ball hits the floor then the number of lives will be reduced
		*/
		if (ball.y + ball.shape.getRadius() * 2 > screenHeight) {
			player.health--;
		}
		if (player.health == 0) {
			break;

		}
	


		for (auto &brick : bricks) {
			if (!brick.isHit && ball.intersects(brick.rect)) {
				brick.isHit = true;

				int oldx = ball.x - ball.vx;
				int oldy = ball.y - ball.vy;
				
				
				bool CollideBottomTop = oldx >= brick.rect.x && oldx <= brick.rect.width + brick.rect.x;//checks for collision between ball and bricks
				bool CollideLeftRight = oldy >= brick.rect.y && oldy <= brick.rect.height + brick.rect.y;

				if (CollideBottomTop) {
					ball.vy = -ball.vy;
				}
				if (CollideLeftRight) {
					ball.vx = -ball.vx;
				}
				if (!CollideBottomTop && !CollideLeftRight) {
					ball.vx = -ball.vx;
					ball.vy = -ball.vy;
				}
				ball.x = oldx;
				ball.y = oldy;
				scoreList.score += 10;
			}
		}

		window.clear();// wipes everything
		/**
		* usin &/reference in order to avoid copting sf::Rectangle shape because of the time and the cost 
		*/
		for (auto &brick : bricks) {
		brick.draw(window);
		}
		player.draw(window);
		ball.draw(window);
		window.display();
		Sleep(50);
	}
		
	scoreList.save();
}

/**
* Displays the menu and provides navigation between options and exit
*/
void runMenu() {
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "breakout");
	sf::Font font;

	font.loadFromFile("C:/Windows/Fonts/ariblk.ttf");
	GameMenu menu(font);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == event.Closed) {
				window.close();
			}
			else if (event.type == event.KeyPressed) {
				if (event.key.code == sf::Keyboard::Key::Down) {
					menu.arrowDown();
				}
				else if (event.key.code == sf::Keyboard::Key::Up) {
					menu.arrowUp();
				}
				else if (event.key.code == sf::Keyboard::Key::Space) {
					if (menu.arrowSelect(window, font)) {
						window.close();
					}
				}
			}
		}
		window.clear();
		menu.draw(window);
		window.display();
		Sleep(50);
	}
	
}

int main() {
	runMenu();
}
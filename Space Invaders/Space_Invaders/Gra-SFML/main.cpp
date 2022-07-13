#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <ctime>

//klasy


class Spaceship
{
public:
	sf::Sprite shape1;
	float speed;
	int points;
	int hp;
	sf::Vector2u size;

	Spaceship(float speed_)
	{
		speed = speed_;
		points = 0;
		hp = 5;
	}
};

class Bullet
{
public:
	Bullet(int typ, float dmg_, float speed_, const sf::Texture Pociski[])
	{
		missile.setTexture(Pociski[typ]);
		size = Pociski[typ].getSize();
		dmg = dmg_;
		speed = speed_;
	}
	sf::Sprite missile;
	float dmg;
	float speed;
	sf::Vector2u size;
};

class Enemy
{
public:
	Enemy(int typ_, float dmg_, float speed_, const sf::Texture Przeciwnicy[], int hp_, float bulletspeed_, int attackdelay)
	{
		shape.setTexture(Przeciwnicy[typ_]);
		shape.rotate(180);
		size = Przeciwnicy[typ_].getSize();
		dmg = dmg_;
		speed = speed_;
		bulletspeed = bulletspeed_;
		int ystart = (rand() % 100) - 100 - size.y;
		int a = size.x;
		int xstart = (rand() % (1280 - a)) + a;
		shape.setPosition(xstart, ystart);
		attackpoint = (rand() % 300) + 100;
		delay = delay_.getElapsedTime();
		points = hp_;
		hp = hp_;
		typ = typ_;
		attackdelay__ = attackdelay;
	}
	int attackdelay__;
	int typ;
	float bulletspeed;
	sf::Sprite shape;
	float dmg;
	float speed;
	sf::Vector2u size;
	float attackpoint;
	sf::Clock delay_;
	sf::Time delay;
	sf::Clock attackdelay_;
	sf::Time attackdelay;
	int kierunek;
	int hp;
	int points;
};

class Asteroid
{
public:

	sf::Sprite shape;
	int hp;
	float speed;
	float xstart;
	float ystart;
	float px;
	float py;
	int dmg;

	Asteroid(int x, const sf::Texture Asteroidy[])
	{
		sf::Vector2u asize;

		if (x < 15)
		{
			if (x < 5)
				shape.setTexture(Asteroidy[0]);
			else if (x < 10)

				shape.setTexture(Asteroidy[1]);
			else
				shape.setTexture(Asteroidy[2]);
			asize = Asteroidy[0].getSize();
			hp = 5;
			speed = 0.1;
			dmg = 5;
		}
		else if (x < 60)
		{
			if (x < 30)
				shape.setTexture(Asteroidy[3]);
			else if (x < 45)
				shape.setTexture(Asteroidy[4]);
			else
				shape.setTexture(Asteroidy[5]);
			asize = Asteroidy[3].getSize();
			hp = 3;
			speed = 0.3;
			dmg = 2;
		}
		else
		{
			if (x < 90)
				shape.setTexture(Asteroidy[6]);
			else if (x < 120)
				shape.setTexture(Asteroidy[7]);
			else
				shape.setTexture(Asteroidy[8]);
			asize = Asteroidy[6].getSize();
			hp = 1;
			speed = 0.6;
			dmg = 1;
		}

		xstart = rand() % 1680 - 200;
		int tmp = asize.y;
		ystart = -tmp;
		px = (float(rand() % 100) / 100) * 5;
		py = (float(rand() % 100) / 100) * 5;
		shape.setPosition(xstart, ystart);
	}
};

class Heal
{
public:

	sf::Sprite shape;
	float speed;
	float xstart;
	float ystart;
	
	Heal(float speed_, const sf::Texture healtexture[])
	{
		shape.setTexture(healtexture[0]);
		xstart = rand() % 1220 + 30;
		ystart = -30;
		speed = speed_;
		shape.setPosition(xstart, ystart);
	}
};


void Clear(sf::Clock & clock, int & p, std::vector<Bullet> & Bullets, std::vector<Asteroid> & Asteroids, std::vector<Enemy> & Enemies, int & fala, bool & next, int & points, bool & end, int & hp, std::vector<Bullet> & EnemyBullets, std::vector<Heal> & Heals)
{
	clock.restart();
	p = 0;
	Bullets.clear();
	Asteroids.clear();
	Enemies.clear();
	EnemyBullets.clear();
	Heals.clear();
	fala = 1;
	next = true;
	points = 0;
	end = false;
	hp = 5;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Space Invaders by Krzysztof Msciszewski!");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	srand(time(NULL));

	//tekstury
	sf::Font font;
	font.loadFromFile("graphics/SPACEMAN.ttf");

	sf::Text GameOver;
	GameOver.setFont(font);
	GameOver.setString("GAME OVER");
	GameOver.setColor(sf::Color::Red);
	GameOver.setCharacterSize(80);
	sf::FloatRect GameOverRec = GameOver.getLocalBounds();
	GameOver.setPosition(1280 / 2 - GameOverRec.width / 2.0, 720 / 3 - GameOverRec.height / 2);

	sf::Text Again;
	Again.setFont(font);
	Again.setString("ZAGRAJ JESZCE RAZ");
	Again.setColor(sf::Color::Blue);
	Again.setCharacterSize(30);
	sf::FloatRect AgainRec = Again.getLocalBounds();
	Again.setPosition(1280 - AgainRec.width - 50, 650);

	sf::Text Back;
	Back.setFont(font);
	Back.setString("POWROT");
	Back.setColor(sf::Color::Blue);
	Back.setCharacterSize(30);
	Back.setPosition(50, 650);

	sf::Text Pause;
	Pause.setFont(font);
	Pause.setString("Pause");
	Pause.setColor(sf::Color::Red);
	Pause.setCharacterSize(80);
	sf::FloatRect PauseRec = Pause.getLocalBounds();
	Pause.setPosition(1280 / 2 - PauseRec.width / 2.0, 720 / 2 - PauseRec.height / 2);

	sf::Text New;
	New.setFont(font);
	New.setString("Nowa Gra");
	New.setColor(sf::Color::Blue);
	New.setCharacterSize(50);
	sf::FloatRect NewRec = New.getLocalBounds();
	New.setPosition(1280 / 2 - NewRec.width / 2.0, 720 / 2 - NewRec.height / 2);

	sf::Text Exit;
	Exit.setFont(font);
	Exit.setString("Wyjdz");
	Exit.setColor(sf::Color::Blue);
	Exit.setCharacterSize(50);
	sf::FloatRect ExitRec = Exit.getLocalBounds();
	Exit.setPosition(1280 / 2 - ExitRec.width / 2.0, 720 / 1.5 - ExitRec.height / 2);

	sf::Text Czas;
	Czas.setFont(font);
	sf::Text Punkty;
	Punkty.setFont(font);
	sf::Text Fala;
	Fala.setFont(font);

	sf::Texture texture;
	texture.loadFromFile("graphics/bg5.jpg");
	sf::Sprite background(texture);

	sf::Texture title_;
	title_.loadFromFile("graphics/title.png");
	sf::Sprite title(title_);
	sf::Vector2u titlesize = title_.getSize();
	title.setPosition(sf::Vector2f(640 - titlesize.x / 2, titlesize.y));

	sf::Texture zycie_;
	zycie_.loadFromFile("graphics/heart.png");
	sf::Sprite zycie1(zycie_);
	sf::FloatRect ZycieRec1 = zycie1.getLocalBounds();
	zycie1.setPosition(1280 - ZycieRec1.width - 50, 650);
	sf::Sprite zycie2(zycie_);
	sf::FloatRect ZycieRec2 = zycie2.getLocalBounds();
	zycie2.setPosition(1280 - ZycieRec2.width - 100, 650);
	sf::Sprite zycie3(zycie_);
	sf::FloatRect ZycieRec3 = zycie3.getLocalBounds();
	zycie3.setPosition(1280 - ZycieRec3.width - 150, 650);
	sf::Sprite zycie4(zycie_);
	sf::FloatRect ZycieRec4 = zycie4.getLocalBounds();
	zycie4.setPosition(1280 - ZycieRec4.width - 200, 650);
	sf::Sprite zycie5(zycie_);
	sf::FloatRect ZycieRec5 = zycie5.getLocalBounds();
	zycie5.setPosition(1280 - ZycieRec5.width - 250, 650);

	sf::Texture healtexture[1];
	healtexture[0].loadFromFile("graphics/heal.png");

	sf::Texture bstexture;
	bstexture.loadFromFile("graphics/bgbattleship.png");
	Spaceship bs(1);
	bs.shape1.setTexture(bstexture);
	bs.size = bstexture.getSize();


	sf::Texture Pociski[2];
	Pociski[0].loadFromFile("graphics/bullets/11.png");
	Pociski[1].loadFromFile("graphics/bullets/5.png");

	sf::Texture EnemyPociski[3];
	EnemyPociski[0].loadFromFile("graphics/bullets/15.png");
	EnemyPociski[1].loadFromFile("graphics/bullets/1.png");
	EnemyPociski[2].loadFromFile("graphics/bullets/6.png");

	sf::Texture Przeciwnicy[3];
	Przeciwnicy[0].loadFromFile("graphics/smallship.png");
	Przeciwnicy[1].loadFromFile("graphics/normalship.png");
	Przeciwnicy[2].loadFromFile("graphics/bigship.png");

	sf::Texture Asteroidy[9];
	Asteroidy[0].loadFromFile("graphics/large/1.png");
	Asteroidy[1].loadFromFile("graphics/large/2.png");
	Asteroidy[2].loadFromFile("graphics/large/3.png");
	Asteroidy[3].loadFromFile("graphics/medium/1.png");
	Asteroidy[4].loadFromFile("graphics/medium/2.png");
	Asteroidy[5].loadFromFile("graphics/medium/3.png");
	Asteroidy[6].loadFromFile("graphics/small/1.png");
	Asteroidy[7].loadFromFile("graphics/small/2.png");
	Asteroidy[8].loadFromFile("graphics/small/3.png");


	//zmienne
	std::vector<Bullet> Bullets;
	std::vector<Bullet> EnemyBullets;
	std::vector<Asteroid> Asteroids;
	std::vector<Enemy> Enemies;
	std::vector<Heal> Heals;
	sf::Clock clock;
	sf::Clock clock2;
	sf::Clock clock3;
	sf::Clock gtime;
	sf::Clock endtime_;
	sf::Clock pausedelay_;
	sf::Clock pausetime_;


	bool end = false;
	bool pause = false;
	bool menu = true;
	bool next = true;
	int x = 0;
	int p = 0;
	sf::FloatRect pos;
	int fala = 1;

	//petla
	while (window.isOpen())
	{
		sf::Vector2f bspos = bs.shape1.getPosition();
		sf::Vector2i pozycjaMyszy = sf::Mouse::getPosition(window);
		sf::Time pausetime;
		pausetime = pausetime_.getElapsedTime();
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}

		//menu
		if (menu)
		{
			window.clear();
			window.draw(background);
			window.draw(New);
			window.draw(Exit);
			window.draw(title);
			window.display();
			pos = New.getGlobalBounds();
			if (pozycjaMyszy.x > pos.left && pozycjaMyszy.x<pos.left + pos.width && pozycjaMyszy.y>pos.top && pozycjaMyszy.y < pos.top + pos.height)
			{
				New.setFillColor(sf::Color::Green);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					bs.shape1.setPosition(sf::Vector2f(640 - bs.size.x / 2, 600 - bs.size.y / 2));
					Clear(endtime_, p, Bullets, Asteroids, Enemies, fala, next, bs.points, end, bs.hp, EnemyBullets, Heals);
					menu = false;
				}

			}
			else
			{
				New.setFillColor(sf::Color::Blue);
			}
			pos = Exit.getGlobalBounds();
			if (pozycjaMyszy.x > pos.left && pozycjaMyszy.x<pos.left + pos.width && pozycjaMyszy.y>pos.top && pozycjaMyszy.y < pos.top + pos.height)
			{
				Exit.setFillColor(sf::Color::Green);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					window.close();
				}

			}
			else
			{
				Exit.setFillColor(sf::Color::Blue);
			}
		}

		//koniec
		else if (end)
		{
			window.clear();
			window.draw(background);
			window.draw(bs.shape1);
			for (int i = 0; i < Bullets.size(); i++)
			{
				window.draw(Bullets[i].missile);
			}
			for (int i = 0; i < EnemyBullets.size(); i++)
			{
				window.draw(EnemyBullets[i].missile);
			}
			for (int i = 0; i < Asteroids.size(); i++)
			{
				window.draw(Asteroids[i].shape);
			}
			for (int i = 0; i < Enemies.size(); i++)
			{
				window.draw(Enemies[i].shape);
			}
			window.draw(GameOver);
			window.draw(Czas);
			window.draw(Again);
			window.draw(Back);
			window.draw(Punkty);
			window.display();
			pos = Again.getGlobalBounds();
			if (pozycjaMyszy.x > pos.left && pozycjaMyszy.x<pos.left + pos.width && pozycjaMyszy.y>pos.top && pozycjaMyszy.y < pos.top + pos.height)
			{
				Again.setFillColor(sf::Color::Green);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					bs.shape1.setPosition(sf::Vector2f(640 - bs.size.x / 2, 600 - bs.size.y / 2));
					Clear(endtime_, p, Bullets, Asteroids, Enemies, fala, next, bs.points, end, bs.hp, EnemyBullets, Heals);
				}

			}
			else
			{
				Again.setFillColor(sf::Color::Blue);
			}
			pos = Back.getGlobalBounds();
			if (pozycjaMyszy.x > pos.left && pozycjaMyszy.x<pos.left + pos.width && pozycjaMyszy.y>pos.top && pozycjaMyszy.y < pos.top + pos.height)
			{
				Back.setFillColor(sf::Color::Green);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					menu = true;
				}

			}
			else
			{
				Back.setFillColor(sf::Color::Blue);
			}
		}
		else
		{
			//pauza
			sf::Time pausedelay = pausedelay_.getElapsedTime();

			if (pausedelay.asSeconds() > 0.2)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					if (!pause)
					{
						pausetime_.restart();
						pause = true;
					}

					else
					{
						p += pausetime.asSeconds();
						pause = false;
					}
					pausedelay_.restart();
				}
			}

			std::string Fala_ = "Fala: " + std::to_string(fala);
			Fala.setString(Fala_);
			Fala.setColor(sf::Color::Red);
			Fala.setCharacterSize(30);
			Fala.setPosition(50, 650);

			//gra
			if (!pause)
			{
				//Timery
				sf::Time missiledelay = clock.getElapsedTime();
				sf::Time asteroidsdelay = clock2.getElapsedTime();
				sf::Time rocketdelay = clock3.getElapsedTime();
				sf::Time endtime = endtime_.getElapsedTime();

				//poruszanie statkiem
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					if (bspos.x > 0)
						bs.shape1.move(-5 * bs.speed, 0);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					if (bspos.x + bs.size.x < 1280)
						bs.shape1.move(5 * bs.speed, 0);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					if (bspos.y > 0)
						bs.shape1.move(0, -5 * bs.speed);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					if (bspos.y + bs.size.y < 720)
						bs.shape1.move(0, 5 * bs.speed);
				}

				//strzelanie

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (missiledelay.asMilliseconds() > 500)
					{
						Bullet tmp(0, 1, 1, Pociski);
						tmp.missile.setPosition(bspos.x + bs.size.x / 2 - tmp.size.x / 2, bspos.y - tmp.size.y);
						Bullets.push_back(tmp);
						clock.restart();
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					if (rocketdelay.asMilliseconds() > 1000)
					{
						Bullet tmp(1, 2, 0.5, Pociski);
						tmp.missile.setPosition(bspos.x + bs.size.x / 2 - tmp.size.x / 2, bspos.y - tmp.size.y);
						Bullets.push_back(tmp);
						clock3.restart();
					}
				}

				sf::Vector2f mpos;
				if (Bullets.size() != 0)
				{
					for (int i = 0; i < Bullets.size();)
					{
						Bullets[i].missile.move(0, -7.5*Bullets[i].speed);
						mpos = Bullets[i].missile.getPosition();
						if (mpos.y < -100)
						{
							Bullets.erase(Bullets.begin() + i);
						}
						else
							i++;
					}
				}

				if (EnemyBullets.size() != 0)
				{
					for (int i = 0; i < EnemyBullets.size();)
					{
						EnemyBullets[i].missile.move(0, -7.5*EnemyBullets[i].speed);
						mpos = EnemyBullets[i].missile.getPosition();
						if (mpos.y > 820)
						{
							EnemyBullets.erase(EnemyBullets.begin() + i);
						}
						else
							i++;
					}
				}

				//tworzenie przeciwników
				if (next)
				{
					if (fala > 1)
					{
					Heal tmp(3, healtexture);
					Heals.push_back(tmp);
					}
					for (int i = 0; i < fala + 1; i++)
					{
						Enemy tmp(0, 1, 3, Przeciwnicy, 1, 1, 2);
						Enemies.push_back(tmp);
					}
					for (int i = 0; i < fala; i++)
					{
						Enemy tmp(1, 2, 2, Przeciwnicy, 2, 0.5, 3);
						Enemies.push_back(tmp);
					}
					for (int i = 0; i < fala / 2; i++)
					{
						Enemy tmp(2, 3, 1, Przeciwnicy, 5, 0.2, 5);
						Enemies.push_back(tmp);
					}
					next = false;
				}

				//poruszanie przeciwników
				sf::Vector2f position;
				if (Enemies.size() != 0)
				{
					for (int i = 0; i < Enemies.size(); i++)
					{
						position = Enemies[i].shape.getPosition();
						if (Enemies[i].attackpoint < position.y)
						{
							Enemies[i].delay = Enemies[i].delay_.getElapsedTime();
							Enemies[i].attackdelay = Enemies[i].attackdelay_.getElapsedTime();
							if (position.x <= 0 + Enemies[i].size.x || position.x >= 1280)
								Enemies[i].kierunek *= -1;
							if (Enemies[i].attackdelay.asSeconds() > Enemies[i].attackdelay__)
							{
								Bullet tmp(Enemies[i].typ, Enemies[i].dmg, Enemies[i].bulletspeed*-1, EnemyPociski);
								tmp.missile.setPosition(position.x - Enemies[i].size.x / 2 - tmp.size.x / 2, position.y);
								EnemyBullets.push_back(tmp);
								Enemies[i].attackdelay_.restart();
							}
							if (Enemies[i].delay.asSeconds() > 1)
							{
								Enemies[i].kierunek = rand() % 3 - 1;
								Enemies[i].delay_.restart();
							}
							Enemies[i].shape.move(Enemies[i].speed*Enemies[i].kierunek, 0);
						}
						else
							Enemies[i].shape.move(0, Enemies[i].speed);
					}
				}
				else
				{
					next = true;
					fala++;
				}

				//asteroidy
				if (asteroidsdelay.asMilliseconds() > 2000)
				{
					int x = rand() % 150 + 1;
					Asteroid tmp(x, Asteroidy);
					Asteroids.push_back(Asteroid(tmp));
					clock2.restart();
				}

				if (Asteroids.size() != 0)
				{
					for (int i = 0; i < Asteroids.size();)
					{
						sf::Vector2f apos = Asteroids[i].shape.getPosition();
						if (Asteroids[i].xstart < 640)
							Asteroids[i].shape.move(Asteroids[i].px*Asteroids[i].speed, Asteroids[i].py*Asteroids[i].speed);
						else
							Asteroids[i].shape.move(-Asteroids[i].px*Asteroids[i].speed, Asteroids[i].py*Asteroids[i].speed);
						if (apos.y < -200 || apos.y>820 || apos.x < -500 || apos.x>1580)
						{
							Asteroids.erase(Asteroids.begin() + i);
						}
						else
							i++;
					}
				}

				//Heale
				if (Heals.size() != 0)
				{
					for (int i = 0; i < Heals.size();)
					{
						sf::Vector2f hpos = Heals[i].shape.getPosition();
						Heals[i].shape.move(0, Heals[i].speed);
						if (hpos.y < -200 || hpos.y>820)
						{
							Heals.erase(Heals.begin() + i);
						}
						else
							i++;
					}
				}

				//kolizje

				//asteroida z pociskami
				for (int i = 0; i < Bullets.size();)
				{
					bool flag = true;
					for (int j = 0; j < Asteroids.size();)
					{
						if (Bullets[i].missile.getGlobalBounds().intersects(Asteroids[j].shape.getGlobalBounds()))
						{
							Asteroids[j].hp -= Bullets[i].dmg;
							if (Asteroids[j].hp <= 0)
							{
								Asteroids.erase(Asteroids.begin() + j);
							}
							Bullets.erase(Bullets.begin() + i);
							flag = false;
							break;
						}
						else
							j++;
					}
					if (flag)
						i++;
				}


				//przeciwnicy z pociskami
				for (int i = 0; i < Bullets.size();)
				{
					bool flag2 = true;
					for (int j = 0; j < Enemies.size();)
					{
						if (Bullets[i].missile.getGlobalBounds().intersects(Enemies[j].shape.getGlobalBounds()))
						{
							Enemies[j].hp -= Bullets[i].dmg;
							if (Enemies[j].hp <= 0)
							{
								bs.points += Enemies[j].points;
								Enemies.erase(Enemies.begin() + j);
							}
							Bullets.erase(Bullets.begin() + i);
							flag2 = false;
							break;
						}
						else
							j++;
					}
					if (flag2)
						i++;
				}

				//asteroida ze statkiem
				for (int j = 0; j < Asteroids.size();)
				{
					if (bs.shape1.getGlobalBounds().intersects(Asteroids[j].shape.getGlobalBounds()))
					{
						bs.hp -= Asteroids[j].dmg;
						Asteroids.erase(Asteroids.begin() + j);
					}
					else
						j++;
				}

				//heal ze statkiem
				for (int j = 0; j < Heals.size();)
				{
					if (bs.shape1.getGlobalBounds().intersects(Heals[j].shape.getGlobalBounds()))
					{
						if(bs.hp<5)
						bs.hp += 1;
						Heals.erase(Heals.begin() + j);
					}
					else
						j++;
				}


				//pociski ze statkiem
				for (int j = 0; j < EnemyBullets.size();)
				{
					if (bs.shape1.getGlobalBounds().intersects(EnemyBullets[j].missile.getGlobalBounds()))
					{
						bs.hp -= EnemyBullets[j].dmg;
						EnemyBullets.erase(EnemyBullets.begin() + j);
					}
					else
						j++;
				}

				//koniec gry
				if (bs.hp <= 0)
				{
					x = endtime.asSeconds();
					x -= p;
					std::string czas = "Czas: " + std::to_string(x);
					Czas.setString(czas);
					Czas.setColor(sf::Color::Red);
					Czas.setCharacterSize(30);
					sf::FloatRect CzasRec = Czas.getLocalBounds();
					Czas.setPosition(1280 / 2 - CzasRec.width / 2.0, 400);
					std::string punkty = "Punkty: " + std::to_string(bs.points);
					Punkty.setString(punkty);
					Punkty.setColor(sf::Color::Red);
					Punkty.setCharacterSize(30);
					sf::FloatRect PunktyRec = Punkty.getLocalBounds();
					Punkty.setPosition(1280 / 2 - PunktyRec.width / 2.0, 500);
					end = true;
				}

			}
			//Rysowanie
			window.clear();
			window.draw(background);
			window.draw(Fala);
			if (bs.hp == 1)
				window.draw(zycie1);
			else if (bs.hp == 2)
			{
				window.draw(zycie1);
				window.draw(zycie2);
			}	
			else if (bs.hp == 3)
			{
				window.draw(zycie1);
				window.draw(zycie2);
				window.draw(zycie3);
			}
			else if (bs.hp == 4)
			{
				window.draw(zycie1);
				window.draw(zycie2);
				window.draw(zycie3);
				window.draw(zycie4);
			}
			else
			{
				window.draw(zycie1);
				window.draw(zycie2);
				window.draw(zycie3);
				window.draw(zycie4);
				window.draw(zycie5);
			}
			window.draw(bs.shape1);
			for (int i = 0; i < Bullets.size(); i++)
			{
				window.draw(Bullets[i].missile);
			}
			for (int i = 0; i < Heals.size(); i++)
			{
				window.draw(Heals[i].shape);
			}
			for (int i = 0; i < EnemyBullets.size(); i++)
			{
				window.draw(EnemyBullets[i].missile);
			}
			for (int i = 0; i < Asteroids.size(); i++)
			{
				window.draw(Asteroids[i].shape);
			}
			for (int i = 0; i < Enemies.size(); i++)
			{
				window.draw(Enemies[i].shape);
			}
			if (pause)
				window.draw(Pause);
			window.display();
		}
	}
	return 0;
}
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>

using namespace sf;

#include "Map.h"

int Kolvo_In_Osndia_FOXs(int radok, int stovbec, int * Masiv, int N);
int Kolvo_In_Pobdia_FOXs(int radok, int stovbec, int * Masiv, int N);
int Kolvo_In_Radok_FOXs(int radok, int stovbec, int * Masiv, int N);
int Kolvo_In_Stovbets_FOXs(int radok, int stovbec, int * Masiv, int N);
void Welcome();
void You_Win();
int Menu(RenderWindow &window);

int main()
{
	int k;
	RenderWindow window(VideoMode(1250, 680), "Hunting for foxes");
	k = Menu(window);
	if (k == 0)
	{
		int radok, stovbec;
		srand(time(NULL));
		int N = 8;
		int Fox = N;
		int Hod = 0;
		int Kolvo_pobdia, Kolvo_osndia, Kolvo_Radok, Kolvo_stovbets;

		int *Masiv;
		Masiv = (int *)malloc(N * N * sizeof(int));


		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				Masiv[i * N + j] = 0;
			}
		}

		for (int i = 0; i < N; i++)
		{
			radok = 0 + rand() % 8;
			stovbec = 0 + rand() % 8;
			if (Masiv[radok * N + stovbec] == 1)
			{
				i--;
			}
			else
			{
				Masiv[radok * N + stovbec] = 1;
			}
			
			
		}



		Image HunterImage;
		HunterImage.loadFromFile("pictures/Hunter.png");
		HunterImage.createMaskFromColor(Color::White);

		Texture HunterTexture;
		HunterTexture.loadFromImage(HunterImage);

		Sprite HunterSprite;
		HunterSprite.setTexture(HunterTexture);
		HunterSprite.setPosition(0, 0);


		Image map_image;
		map_image.loadFromFile("pictures/Bush.png");
		Texture map;
		map.loadFromImage(map_image);
		Sprite s_map;
		s_map.setTexture(map);


		Clock clock;
		float CurrentFrame = 0;
		float speed = 1;
		int H = 0, V = 0;
		int BeforeH = 0, BeforeV = 0;
		int flag = 0;
		float RealH = 0, RealV = 0;

		Text text;

		Font font;


		text.setFillColor(Color::Red);

		text.setFont(font);
		font.loadFromFile("Fonts/arial.ttf");

		text.setCharacterSize(20);

		text.setStyle(sf::Text::Bold | sf::Text::Underlined);

		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			time = time / 800;
			Event event;
			while (window.pollEvent(event))
			{
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					k = Menu(window);
				}
			}
			window.clear();

			if ((H >= BeforeH) && (V > BeforeV))
			{
				if (RealV < V)
				{
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 2) CurrentFrame -= 2;
					HunterSprite.setTextureRect(IntRect(0, 75 * int(CurrentFrame), 40, 75));
					HunterSprite.move(0, speed);
					RealV = RealV + speed;
				} 

				if ((RealH < H) && (RealV >= V))
				{
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 2) CurrentFrame -= 2;
					HunterSprite.setTextureRect(IntRect(80, 75 * int(CurrentFrame), -40, 75));
					HunterSprite.move(speed, 0);
					RealH = RealH + speed;
				}
			}

			if ((H < BeforeH) && (V < BeforeV))
			{
				if ((RealH > H) && (RealV <= V))
				{
					CurrentFrame += 0.005 * time;
					if (CurrentFrame > 2) CurrentFrame -= 2;
					HunterSprite.move(-speed, 0);
					HunterSprite.setTextureRect(IntRect(40, 75 * int(CurrentFrame), 40, 75));
					RealH = RealH - speed;
				}

				if (RealV > V)
				{
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 2) CurrentFrame -= 2;
					HunterSprite.move(0, -speed);
					HunterSprite.setTextureRect(IntRect(80, 75 * int(CurrentFrame), 40, 75));
					RealV = RealV - speed;
				}
			}

			if ((H >= BeforeH) && (V <= BeforeV))
			{
				if (RealV > V)
				{
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 2) CurrentFrame -= 2;
					HunterSprite.move(0, -speed);
					HunterSprite.setTextureRect(IntRect(80, 75 * int(CurrentFrame), 40, 75));
					RealV = RealV - speed;
				}
				if ((RealH < H) && (RealV <= V))
				{
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 2) CurrentFrame -= 2;
					HunterSprite.setTextureRect(IntRect(80, 75 * int(CurrentFrame), -40, 75));
					HunterSprite.move(speed, 0);
					RealH = RealH + speed;
				}
			}
			if ((H < BeforeH) && (V >= BeforeV))
			{
				if (RealV < V)
				{
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 2) CurrentFrame -= 2;
					HunterSprite.setTextureRect(IntRect(0, 75 * int(CurrentFrame), 40, 75));
					HunterSprite.move(0, speed);
					RealV = RealV + speed;
				}
				if ((RealH > H) && (RealV >= V))
				{
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 2) CurrentFrame -= 2;
					HunterSprite.setTextureRect(IntRect(40, 75 * int(CurrentFrame), 40, 75));
					HunterSprite.move(-speed, 0);
					RealH = RealH - speed;
				} 
			}

			
			if (((int(H - RealH) <= 1) && (int(H - RealH) >= -1)) && ((int(V - RealV) <= 1) && (int(V - RealV) >= -1)))
			{
				BeforeH = RealH;
				BeforeV = RealV;

				stovbec = (H - 125) / 100;
				radok = (V - 25) / 50;
				if (Masiv[radok * N + stovbec] == 1)
				{
					Masiv[radok * N + stovbec] = 0;
					Welcome();
					Fox--;
				}
				HunterSprite.setPosition(H, V);
				HunterSprite.setTextureRect(IntRect(80, 0, 40, 75));
			}




			for (int i = 0; i < HEIGHT_MAP; i++)
				for (int j = 0; j < WIDTH_MAP; j++)
				{
					if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 100, 50)); 
					if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 50, 100, 50));

					if ((TileMap[i][j] == ' ') && (IntRect(j * 100, i * 50, 100, 50).contains(Mouse::getPosition(window))))
					{ 
						s_map.setColor(Color::Blue);
						if(Mouse::isButtonPressed(Mouse::Left))
						{
							V = 25 + (i - 1) * 50;
							H = 125 + (j - 1) * 100;
							Hod++;
							Fox--;
						}
					}


					s_map.setPosition(j * 100, i * 50);

					window.draw(s_map);
					s_map.setColor(Color::White);
				}

			window.draw(HunterSprite);
			Kolvo_osndia = Kolvo_In_Osndia_FOXs(radok, stovbec, Masiv, N);
			Kolvo_pobdia = Kolvo_In_Pobdia_FOXs(radok, stovbec, Masiv, N);
			Kolvo_Radok = Kolvo_In_Radok_FOXs(radok, stovbec, Masiv, N);
			Kolvo_stovbets = Kolvo_In_Stovbets_FOXs(radok, stovbec, Masiv, N);

			text.setPosition(1000, 25);

			std::ostringstream playerScoreString1;
			playerScoreString1 << Kolvo_osndia;
			text.setString("Fox in Osndia: " + playerScoreString1.str());

			window.draw(text);

			text.setPosition(1000, 50);

			std::ostringstream playerScoreString2;
			playerScoreString2 << Kolvo_pobdia;
			text.setString("Fox in Pobdia: " + playerScoreString2.str());

			window.draw(text);

			text.setPosition(1000, 75);

			std::ostringstream playerScoreString3;
			playerScoreString3 << Kolvo_Radok;
			text.setString("Fox in Radok: " + playerScoreString3.str());

			window.draw(text);

			text.setPosition(1000, 100);

			std::ostringstream playerScoreString4;
			playerScoreString4 << Kolvo_stovbets;
			text.setString("Fox in Stovbets: " + playerScoreString4.str());

			window.draw(text);

			text.setPosition(1000, 200);

			std::ostringstream playerScoreString5;
			playerScoreString5 << Fox;
			text.setString("Fox: " + playerScoreString5.str());

			window.draw(text);

			text.setPosition(1000, 250);

			std::ostringstream playerScoreString6;
			playerScoreString6 << Hod;
			text.setString("Number of moves: " + playerScoreString6.str());

			window.draw(text);

			playerScoreString6.clear();
			playerScoreString6.str("");
			text.setPosition(1000, 300);
			playerScoreString6 << RealH;
			text.setString("RealH: " + playerScoreString6.str());
			window.draw(text);
			
			playerScoreString6.clear();
			playerScoreString6.str("");
			text.setPosition(1000, 350);
			playerScoreString6 << RealV;
			text.setString("RealV: " + playerScoreString6.str());
			window.draw(text);


			playerScoreString6.clear();
			playerScoreString6.str("");
			text.setPosition(1000, 400);
			playerScoreString6 << H;
			text.setString("H: " + playerScoreString6.str());

			window.draw(text);
			
			playerScoreString6.clear();
			playerScoreString6.str("");
			text.setPosition(1000, 450);
			playerScoreString6 << V;
			text.setString("V: " + playerScoreString6.str());
			window.draw(text);

			window.display();

			if (Fox == 0)
			{
				You_Win();
				Menu(window);
			}
		}
	}
	return 0;
}

int Kolvo_In_Osndia_FOXs(int radok, int stovbec, int * Masiv, int N)
{
	int Kolvo_osndia = 0;
	int i;
	i = 1;
	while ((radok + i < N) && (stovbec + i < N))
	{
		if (Masiv[(radok + i) * N + stovbec + i] == 1)
		{
			Kolvo_osndia++;
		}
		i++;
	}

	i = 1;
	while ((radok - i >= 0) && (stovbec - i >= 0))
	{
		if (Masiv[(radok - i) * N + stovbec - i] == 1)
		{
			Kolvo_osndia++;
		}
		i++;
	}

	return Kolvo_osndia;

}

int Kolvo_In_Pobdia_FOXs(int radok, int stovbec, int * Masiv, int N)
{
	int Kolvo_pobdia = 0;
	int i = 1;
	while ((radok - i >= 0) && (stovbec + i < N))
	{
		if (Masiv[(radok - i) * N + stovbec + i] == 1)
		{
			Kolvo_pobdia++;
		}
		i++;
	}

	i = 1;
	while ((radok + i < N) && (stovbec - i >= 0))
	{
		if (Masiv[(radok + i) * N + stovbec - i] == 1)
		{
			Kolvo_pobdia++;
		}
		i++;
	}
	return Kolvo_pobdia;
}

int Kolvo_In_Radok_FOXs(int radok, int stovbec, int * Masiv, int N)
{
	int Kolvo_radok = 0;
	for (int i = 0; i < N; i++)
	{
		if (Masiv[radok * N + i] == 1)
		{
			Kolvo_radok++;
		}
	}

	return Kolvo_radok;
}

int Kolvo_In_Stovbets_FOXs(int radok, int stovbec, int * Masiv, int N)
{
	int Kolvo_stolbets = 0;
	for (int i = 0; i < N; i++)
	{
		if (Masiv[i * N + stovbec] == 1)
		{
			Kolvo_stolbets++;
		}
	}

	return Kolvo_stolbets;
}

void Welcome()
{

	Image WelcomeImagine;
	WelcomeImagine.loadFromFile("pictures/Welcome");

	Texture WelcomeTexture;
	WelcomeTexture.loadFromImage(WelcomeImagine);

	Sprite WelcomeSprite;
	WelcomeSprite.setTexture(WelcomeTexture);
	WelcomeSprite.setPosition(0, 0);

	sf::Text text;

	sf::Font font;


	text.setFillColor(Color::Red);

	text.setFont(font);
	font.loadFromFile("Fonts/arial.ttf");

	text.setCharacterSize(20);

	// �������� ����� ������
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	RenderWindow window(VideoMode(1000, 680), "Welcome");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Tab)))
			{
				window.close();
			}
		}
		window.clear();

		window.draw(WelcomeSprite);

		text.setPosition(20, 20);
		text.setString("Hi, you found a fox !!! WELL DONE!!!!!");

		window.draw(text);

		text.setPosition(600, 650);
		text.setString("Pleas, press Escape to Continium");

		window.draw(text);
		window.display();
	}
}

void You_Win()
{
	sf::Text text;

	sf::Font font;


	text.setFillColor(Color::Red);

	text.setFont(font);
	font.loadFromFile("Fonts/arial.ttf");

	text.setCharacterSize(20);


	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	Image WinImagine;
	WinImagine.loadFromFile("pictures/Win.png");

	Texture WinTexture;
	WinTexture.loadFromImage(WinImagine);

	Sprite WinSprite;
	WinSprite.setTexture(WinTexture);
	WinSprite.setPosition(0, 0);

	RenderWindow window(VideoMode(450, 470), "Win");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == Event::Closed) || (Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				window.close();
			}
		}
		window.clear();
		window.draw(WinSprite);
		text.setPosition(50, 300);
		text.setString("Please, press Escape to back Menu");

		window.draw(text);
		window.display();
	}
}

int Menu(RenderWindow &window)
{
	std::ostringstream playerScoreString4;
	sf::Vector2i pixelPos;
	short index = 1;
	Image ex;
	ex.loadFromFile("pictures/Exit.png");
	//exit.createMaskFromColor(Color::White);


	Music mus;
	mus.openFromFile("music/track2.wav");
	mus.play();


	Text text;
	Font font;
	text.setFillColor(Color::Red);
	text.setFont(font);
	font.loadFromFile("Fonts/arial.ttf");
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	Texture play_texture, exit_texture, background_texture, music_on_texture, music_off_texture;
	play_texture.loadFromFile("pictures/Play.png");
	exit_texture.loadFromImage(ex);
	background_texture.loadFromFile("pictures/Zastavka.png");
	music_on_texture.loadFromFile("pictures/music_on.png");
	music_off_texture.loadFromFile("pictures/music_off.png");

	Sprite play_sprite(play_texture), exit_sprite(exit_texture), background_sprite(background_texture), music_sprite(music_on_texture);
	bool isMenu = 1;
	int menuNum = 0;
	int k = 0;

	play_sprite.setPosition(0, 0);

	exit_sprite.setPosition(40, 110);
	exit_sprite.scale(0.4f, 0.4f);

	music_sprite.setPosition(75, 230);
	music_sprite.scale(0.5f, 0.5f);

	background_sprite.setPosition(0, 0);

	Event event;
	while (isMenu)
	{

		play_sprite.setColor(Color::White);
		exit_sprite.setColor(Color::White);
		music_sprite.setColor(Color::White);
		window.clear(Color(129, 181, 221));

		if (IntRect(25, 0, 215, 100).contains(Mouse::getPosition(window))) 
		{ 
			play_sprite.setColor(Color::Blue);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				isMenu = false;
			}
		}

		if (IntRect(40, 110, 170, 100).contains(Mouse::getPosition(window))) 
		{ 
			exit_sprite.setColor(Color::Blue);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				window.close();
				mus.stop();
				mus.~Music();
				exit(0);
			}
		}

		if (IntRect(75, 230, 100, 100).contains(Mouse::getPosition(window))) 
		{ 
			music_sprite.setColor(Color::Blue);
			while(window.pollEvent(event))
			{
				if (event.type == Event::MouseButtonReleased)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (index == 1)
						{
							music_sprite.setTexture(music_off_texture);
							mus.stop();
							index = 0;
						}
						else
						{
							music_sprite.setTexture(music_on_texture);
							mus.play();
							index = 1;
						}
					}
				}	
			}
		}

		window.draw(background_sprite);

		playerScoreString4.clear();
		playerScoreString4.str("");
		text.setPosition(1000, 100);
		pixelPos = Mouse::getPosition(window);
		playerScoreString4 << pixelPos.x;
		text.setString("H: " + playerScoreString4.str());
		window.draw(text);

		playerScoreString4.clear();
		playerScoreString4.str("");
		text.setPosition(1000, 150);
		playerScoreString4 << pixelPos.y;
		text.setString("V: " + playerScoreString4.str());
		window.draw(text);

		window.draw(play_sprite);
		window.draw(exit_sprite);
		window.draw(music_sprite);

		window.display();
	}
	
	return k;
}

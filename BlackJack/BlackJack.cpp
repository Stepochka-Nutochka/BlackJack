#include "enum.h"
#include "libraries.h"
#include "Prototipes.h"
#include "Structs.h" // хэдеры

Card Deck[4][12]{}; // наша колода
Player AllPlayers[2]; //массив игроков
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //дескриптор на вывод
const int card_size = 10;

int main()
{

	system("title Black Jack"); // для названия консоли
	srand(time(0)); // рандом
	MoveWindow(GetConsoleWindow(), 50, 50, 1200, 700, true);//размер консоли
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = false;// спрятать курсор
	cursor.dwSize = 100;
	SetConsoleCursorInfo(h, &cursor);
	system("mode con cols=80 lines=50");
	MainMenu(); //вывод главного меню
	Sleep(INFINITE);

}
void MainMenu() { //менюшка
	system("cls");
	system("mode con cols=80 lines=50");


	const int items_count = 4; //всего кнопок
	string menu_items[items_count] = { "PLAY","HOW TO PLAY","ABOUT AUTHOR", "EXIT" }; //массив кнопок

	int startX = 35; //координата по иксу
	int startY = 15; //координата по игрику
	int margin = 2; // для расстояния

	COORD position = { startX, startY }; //делаем координаты

	for (auto item : menu_items) // ф-ия перебора элементов нашего массива с названиями кнопок
	{
		SetConsoleTextAttribute(h, Yellow);
		SetConsoleCursorPosition(h, position);
		cout << item; //вывод наших всееех кнопок
		position.Y += margin; //позиция по игрику(строки на нужное кол-во вниз)
	}

	int current_item = 0; //для new game, чтоб окрасить в фиол
	SetConsoleTextAttribute(h, ColourOnThePurple);
	position.Y = startY + current_item * margin;  // возвращает на первый элемент -> new game
	SetConsoleCursorPosition(h, position);
	cout << menu_items[current_item]; // выводит -> new game

	int code; //перемннная для хранения клавишей, которые мы нажали

	while (true) //пока не выйдем
	{
		code = _getch(); //для нажатия кнопок
		if (code == 224) //для стрелок
			code = _getch(); //повторное присвоение

		SetConsoleTextAttribute(h, Yellow);
		position.Y = startY + current_item * margin;
		SetConsoleCursorPosition(h, position);
		cout << menu_items[current_item];

		if ((code == DOWN || code == RIGHT) && current_item < items_count - 1) // стрелочка вниз
		{
			current_item++;
		}
		else if ((code == UP || code == LEFT) && current_item > 0) // стрелочка вверх
		{
			current_item--;
		}
		else if (code == ENTER) // если пользователь нажал клавишу Enter, тобиж выбрал нужный пункт
		{
			switch (current_item) //какую кнопку выбрал
			{
			case 0: //если 0 (1 элемент массива)
				PlayGame(); // вызываем ф-ию
				break; // для того, чтобы не сделало след. пункт
			case 1: //если 1 (2 элемент массива)
				system("cls");
				HowToPlay();
				break;
			case 2: //если 2 (3 элемент массива)
				AboutAuthor();
				break;
			default:
				exit(0);
				break;
			}
		}

		SetConsoleTextAttribute(h, ColourOnThePurple);
		position.Y = startY + current_item * margin;
		SetConsoleCursorPosition(h, position);
		cout << menu_items[current_item];

	}
}
void PlayGame() //ф-ия для начатия игры
{
	COORD CurrentPosititon;
	Card CurrentCard;
	int bank = 0;
	SetCursor(CurrentPosititon, 3, 25);
	GeneratteDeck(); // инициализация карт
	do
	{
		Sleep(1000);
		system("cls");
		Table(bank); // вывод стола со всей информацией
		ShowBalance(0, bank);
		SetCursor(CurrentPosititon, 3, 36);
		Bets(1, bank); // спрашиваем игрока не хотит ли он взять карту и удвоить ставку
		EndOfGame(0, 0, bank); // завершение игры
		CalculateScore(0, bank);
	} while (AllPlayers[0].Money > 0);



	exit(0);
}
void HowToPlay() //ф-ия для того, чтобы вывсети меню 
{
	system("cls");
	system("title How To Play?");
	system("mode con cols=120 lines=20");
	int count = 0;//количество окон было показано
	WindowsHowToPlay(count); // вывод кусочков с объяснениями

	Sleep(INFINITE);
}
void BackOrNext(COORD& Position, int margin, int count) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	int startX = Position.X;//позиция по иксу
	int startY = Position.Y;// позиция по игрику
	int MarginForX = 10; // для расстояния между кнопками
	const int items_count = 2; //всего кнопок
	string menu_items[items_count] = { "BACK","NEXT" }; //массив кнопок



	for (auto item : menu_items) // ф-ия перебора элементов нашего массива с названиями кнопок
	{
		SetConsoleTextAttribute(h, Yellow);
		SetConsoleCursorPosition(h, Position);
		cout << item; //вывод наших всееех кнопок
		Position.X += MarginForX; //позиция по игрику(строки на нужное кол-во вниз)
	}

	int current_item = 0; //для кнопок, чтоб окрасить в фиол
	SetConsoleTextAttribute(h, Purple);
	Position.X = startX + current_item * MarginForX;  // возвращает на первый элемент -> new game
	SetConsoleCursorPosition(h, Position);
	cout << menu_items[current_item]; // выводит -> new game

	int code; //перемннная для хранения клавишей, которые мы нажали

	while (true) //пока не выйдем
	{
		code = _getch(); //для нажатия кнопок
		if (code == 224) //для стрелок
			code = _getch(); //повторное присвоение

		SetConsoleTextAttribute(h, Yellow);
		Position.X = startX + current_item * MarginForX;
		SetConsoleCursorPosition(h, Position);
		cout << menu_items[current_item];

		if ((code == DOWN || code == RIGHT) && current_item < items_count - 1) // стрелочка вниз
		{
			current_item++;
		}
		else if ((code == UP || code == LEFT) && current_item > 0) // стрелочка вверх
		{
			current_item--;
		}
		else if (code == ENTER) // если пользователь нажал клавишу Enter, тобиж выбрал нужный пункт
		{
			switch (current_item) //какую кнопку выбрал
			{
			case 0: //если 0 (1 элемент массива) если возвращаемся на предыдущее окно
				count--;//чтобы вывелось предыдущее окно с описанем
				WindowsHowToPlay(count); // выводим это окно
				break; // для того, чтобы не сделало след. пункт
			case 1: //если 1 (2 элемент массива) если идем на след окно
				count++;//чтобы вывелось слудуещее окно с описанем
				WindowsHowToPlay(count); // выводим это окно
				break;
			default://если что-то пошло не так ( надеемся такого не будет)
				exit(0);
				break;
			}
		}

		SetConsoleTextAttribute(h, Purple);
		Position.X = startX + current_item * MarginForX;
		SetConsoleCursorPosition(h, Position);
		cout << menu_items[current_item];

	}
	Sleep(INFINITE);
}
void WindowsHowToPlay(int count) {//передаем какое по счету вывести окно
	COORD TextPosition;

	TextPosition.Y = 5; //позиция Y где будет выводится текст
	TextPosition.X = 35; //позиция X где будет выводится текст
	int margin = 2; // расстояние между текстом
	const int current_items = 2;
	string items_for_first[current_items] = { "To start the game you need to press Enter", "The game starts with placing belts" };
	string items_for_second[current_items] = { "After placing belts you will recieve 2 cards ", "Sum up your cards. You need to get more points than dealer, but less than 21" };
	string items_for_third[current_items] = { "You can take additional cards, if you want ", "BUT!!!. If you got more than 21 in this case automatically lose your bets!" };
	string items_for_fourth[current_items] = { "If you choose ""Show cards"" you will see bot's cards and the result of thr game", "Good kuck. And remeber don't take more than 21:))" };
	switch (count) {
	case 0://(до этого не было выводов, но это 1 окно)
		system("cls");
		ShowWindowsHowToPlay(TextPosition, current_items, items_for_first, margin, count);
		break;
	case 1:
		system("cls");
		ShowWindowsHowToPlay(TextPosition, current_items, items_for_second, margin, count);
		break;
	case 2:
		system("cls");

		ShowWindowsHowToPlay(TextPosition, current_items, items_for_third, margin, count);
		break;
	case 3:
		system("cls");

		ShowWindowsHowToPlay(TextPosition, current_items, items_for_fourth, margin, count);
		break;
	default:
		MainMenu();
	}
	Sleep(INFINITE);
}
void ShowWindowsHowToPlay(COORD Position, const int current_item, string(&items)[2], int margin, int count) {
	int sum = 0;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < current_item; i++) {
		SetConsoleTextAttribute(h, Yellow);
		SetConsoleCursorPosition(h, Position);
		cout << items[i]; //вывод наших всееех кнопок
		Position.Y += margin; //позиция по игрику(строки на нужное кол-во вниз)
	}
	if (count == 1) {
		GeneratteDeck();
		SetUpCard();
		for (int i = 0, f = 0; i < 2; i++)
		{

			if (f == 0)
			{
				ShowCard(Position, GetCardStatuses(1, AllPlayers[0].Cards[f]), GetCardStatuses(0, AllPlayers[0].Cards[f]), Position.Y, 0); // вывод карт игрока
				sum += GetCardStatuses(1, AllPlayers[0].Cards[f]);
			}
			else
			{
				ShowCard(Position, GetCardStatuses(0, AllPlayers[0].Cards[f]), GetCardStatuses(0, AllPlayers[0].Cards[f]), Position.Y, 0); // вывод карт игрока
				sum += GetCardStatuses(0, AllPlayers[0].Cards[f]);
			}
			f++;
		}


		SetCursor(Position, Position.X, Position.Y);
		SetConsoleTextAttribute(h, WhiteOnThePurple);
		cout << "Now you have: " << sum;

		Position.X += 10;
		Position.Y += 5;
	}

	SetCursor(Position, Position.X, Position.Y);
	BackOrNext(Position, margin, count);
}
void AboutAuthor()
{
	system("cls");


	const int items_count = 3; //всего кнопок
	string menu_items[items_count] = { "Stepa","Nyuta","Back to main menu" }; //массив кнопок
	int startX = 40; //координата по иксу
	int startY = 5; //координата по игрику
	int margin = 2; //для расстояния
	COORD Position = { startX , startY };
	COORD Hello;
	Hello.Y = 3; // 3
	Hello.X = 30;

	SetConsoleTextAttribute(h, Purple);
	SetConsoleCursorPosition(h, Hello);
	cout << "Hello. Choose one of us: " << char(1);

	for (auto item : menu_items) // ф-ия перебора элементов нашего массива с названиями кнопок
	{
		SetConsoleTextAttribute(h, Yellow);
		SetConsoleCursorPosition(h, Position);
		cout << item; //вывод наших всееех кнопок
		Position.Y += margin; //позиция по игрику(строки на нужное кол-во вниз)
	}

	int current_item = 0; //для кнопок, чтоб окрасить в фиол
	SetConsoleTextAttribute(h, Purple);
	Position.Y = startY + current_item * margin;  // возвращает на первый элемент -> new game
	SetConsoleCursorPosition(h, Position);
	cout << menu_items[current_item]; // выводит -> new game

	int code; //перемннная для хранения клавишей, которые мы нажали

	while (true) //пока не выйдем
	{
		code = _getch(); //для нажатия кнопок
		if (code == 224) //для стрелок
			code = _getch(); //повторное присвоение

		SetConsoleTextAttribute(h, Yellow);
		Position.Y = startY + current_item * margin;
		SetConsoleCursorPosition(h, Position);
		cout << menu_items[current_item];

		if ((code == DOWN || code == RIGHT) && current_item < items_count - 1) // стрелочка вниз
		{
			current_item++;
		}
		else if ((code == UP || code == LEFT) && current_item > 0) // стрелочка вверх
		{
			current_item--;
		}
		else if (code == ENTER) // если пользователь нажал клавишу Enter, тобиж выбрал нужный пункт
		{
			switch (current_item) //какую кнопку выбрал
			{
			case 0: //если 0 (1 элемент массива)
				Stepa();
				break; // для того, чтобы не сделало след. пункт
			case 1: //если 1 (2 элемент массива)
				Nyuta();
				break;
			case 2: //если 2 (3 элемент массива)
				MainMenu(); //возвращаемся в главное меню
				break;
			default:
				exit(0);
				break;
			}
		}

		SetConsoleTextAttribute(h, Purple);
		Position.Y = startY + current_item * margin;
		SetConsoleCursorPosition(h, Position);
		cout << menu_items[current_item];

	}



	margin = 5;
	Position.Y += margin;
	SetConsoleCursorPosition(h, Position);
	cout << "To exit press Enter";


}
void Nyuta() {

	system("cls");
	int code;// для клавиши enter
	COORD position;//позиции текста
	position.X = 30;
	position.Y = 3;
	int margin = 2;
	const int items_count = 3;
	string discript_items[items_count] = { "My name is Nyutka","I'm 17","@nutttelllka_a" }; //массив текста

	for (auto item : discript_items) // ф-ия перебора элементов нашего массива с названиями кнопок
	{
		SetConsoleTextAttribute(h, Yellow);
		SetConsoleCursorPosition(h, position);
		cout << item;
		position.Y += margin;
	}
	position.Y += margin;
	SetConsoleTextAttribute(h, Purple);
	SetConsoleCursorPosition(h, position);
	cout << "To go back press Enter...";
	code = _getch();

	if (code == ENTER) // если пользователь нажал ентер
		AboutAuthor();
	else
		Nyuta();

	Sleep(INFINITE);
}
void Stepa() {

	system("cls");
	int code;// для клавиши enter
	COORD position;//позиции текста
	position.X = 30;
	position.Y = 3;
	int margin = 2;// расстояние между текстом

	const int items_count = 3;
	string discript_items[items_count] = { "My Name is Stepa","I'm 16","I'm a programmer" };//массив текста

	for (auto item : discript_items) // ф-ия перебора элементов нашего массива тобиж строчек текста
	{
		SetConsoleTextAttribute(h, Yellow);
		SetConsoleCursorPosition(h, position);
		cout << item;
		position.Y += margin;
	}
	position.Y += margin;

	SetConsoleTextAttribute(h, Purple);
	SetConsoleCursorPosition(h, position);
	cout << "To go back press Enter...";
	code = _getch();
	if (code == ENTER) // если пользователь нажал ентер
		AboutAuthor();//возвращаемся в меню авторов
	else   // а вот не нажал ентер 
		Stepa();//вызываем саму себя 


	Sleep(INFINITE);
}
void GeneratteDeck() {
	for (int suit = 3, i = 0; suit < 7; suit++, i++)
	{
		for (int value = 2, j = 0; value < 15; value++, j++)
		{
			Deck[i][j].Denomination = value;
			Deck[i][j].Suit = suit;
		}
	}
}
void Bets(bool DoubleDown, int& bank) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //дескриптор на вывод
	COORD TextPosition;

	TextPosition.X = 3;
	TextPosition.Y = 10;
	if (DoubleDown)
	{
		bool answer = 0;
		SetCursor(TextPosition, 10, 18);

		cout << "Would you like to double down?(0 - No, 1 - Yes)";
		SetCursor(TextPosition, 3, 0);
		cout << "                                       ";
		SetCursor(TextPosition, 3, 0);
		cout << "Your answers-> ";
		cin >> answer;
		SetCursor(TextPosition, 10, 18);
		cout << "													";
		
	
		if (answer && AllPlayers[0].Money >= bank / 2)
		{
			AllPlayers[0].Money -= bank / 2;
			AllPlayers[1].Money -= bank / 2;
			bank *= 2;
			AddCard(0, bank);
			CalculateScore(0, bank);
			SetCursor(TextPosition, 3, 0);
			cout << "                        ";
			SetCursor(TextPosition, 3, 0);
			cout << endl << "Your score - " << AllPlayers[0].Score;
			BotTurn(bank);
		}
		else if (!answer)
		{
			do
			{
				SetCursor(TextPosition, 10, 15);

				cout << "0 - show card                                                                                      ";

				SetCursor(TextPosition, 10, 16);

				cout << "1 - take one more card";
				SetCursor(TextPosition, 3, 0);
				cout << "                                       ";
				SetCursor(TextPosition, 3, 0);

				cout << "Your answers-> ";
				cin >> answer;
				if (answer)
				{

					AddCard(0, bank);
					CalculateScore(0, bank);
					TextPosition.Y--;
					SetCursor(TextPosition, 3, 0);
					cout << "                        ";
					SetCursor(TextPosition, 3, 0);
					cout << "Your score - " << AllPlayers[0].Score;
				}
				else
				{
					BotTurn(bank);
				}
			} while (AllPlayers[0].Cards[4] == 0 && answer == true);

		}
		else
		{
			cout << "You haven't more money!";
		}

	}
	else
	{
		int bet = 0;


		SetCursor(TextPosition, 35, 15);


		cout << "Type your bet:";
		SetCursor(TextPosition, 3, 0);
		cout << "                                       ";
		SetCursor(TextPosition, 3, 0);

		cout << "Your answers-> ";
		cin >> bet;

		if (bet > AllPlayers[0].Money && bet > 0)
		{
			do
			{
				SetCursor(TextPosition, 35, 15);


				cout << "Type correct value:";
				SetCursor(TextPosition, 3, 0);

				cin >> bet;
			} while (bet > AllPlayers[0].Money && bet < 0);
		}
		AllPlayers[0].Money -= bet;
		AllPlayers[1].Money -= bet;
		bank += bet * 2;
	}
}
void AddCard(bool bot, int& bank) {
	for (int i = 2; i < 5; i++)
	{
		if (AllPlayers[bot].Cards[i] == 0)
		{
			AllPlayers[bot].Cards[i] = rand() % 48;
			CalculateScore(bot, bank);
			break;
		}
	}


}
void CalculateScore(bool bot, int& bank) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //дескриптор на вывод
	COORD TextPosition;
	AllPlayers[(int)bot].Score = 0;
	for (int q = 0; q < 5; q++)
	{
		int j = 0, i = 0;
		while (j < 48)
		{
			if (j == AllPlayers[(int)bot].Cards[q])
			{
				if (Deck[i][j % 12].Denomination == Jack || Deck[i][j % 12].Denomination == Quen || Deck[i][j % 12].Denomination == King)
					AllPlayers[(int)bot].Score += 10;
				else if (Deck[i][j % 12].Denomination == Ace)
					AllPlayers[(int)bot].Score += 11;
				else
					AllPlayers[(int)bot].Score += Deck[i][j % 12].Denomination;
				break;
			}
			j++;
			i = j / 12;
		}
	}

	if (AllPlayers[bot].Score > 21)
	{
		if (bot)
		{
			/*SetCursor(TextPosition, 35, 52);
			SetConsoleCursorPosition(h, TextPosition);
			cout << endl << "Defeat, you reach more then 21!";*/
			EndOfGame(1, 1, bank);
		}

		else
		{
			/*SetCursor(TextPosition, 35, 52);
			SetConsoleCursorPosition(h, TextPosition);
			cout << endl << "Victory, bot reach more then 21!";*/
			EndOfGame(1, 0, bank);
		}

	}
	Sleep(1000);
}
void BotTurn(int& bank) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //дескриптор на вывод
	COORD PositionBot;

	PositionBot.Y = 3;
	PositionBot.X = 3;
	int BotX = 3;
	int BotY = 3;

	int i = 2;//count
	while (AllPlayers[1].Score < 17)
	{
		AddCard(1, bank);
		i++;
	}
	for (int j = 0, f = 0; j < i; j++, f++)
	{
		if (f == 0)
		{
			ShowBackCard(PositionBot, BotX, BotY, 0);
		}
		else
		{
			ShowBackCard(PositionBot, BotX, BotY, 1);
		}
	}
	BotX = 3;
	BotY = 3;

	SetCursor(PositionBot, BotX, BotY);
	for (int j = 0, f = 0; j < i; j++, f++)
	{
		
		if (f == 0)
		{
			ShowCard(PositionBot, GetCardStatuses(1, AllPlayers[1].Cards[f]), GetCardStatuses(0, AllPlayers[1].Cards[f]), PositionBot.Y, 0);
		}
		else
		{
			ShowCard(PositionBot, GetCardStatuses(0, AllPlayers[1].Cards[f]), GetCardStatuses(0, AllPlayers[1].Cards[f]), PositionBot.Y, 0); // вывод карт игрока
		}
		ShowBalance(1, bank);
	}
}
void EndOfGame(bool defeat, bool bot, int& bank) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //дескриптор на вывод
	COORD TextPosition;

	if (defeat)
	{
		AllPlayers[bot].Money += bank;
		bank = 0;
	}
	else
	{
		if (AllPlayers[0].Score > AllPlayers[1].Score)
		{
			SetCursor(TextPosition, 3, 50);
			SetConsoleCursorPosition(h, TextPosition);
			cout << endl << "You win!";
			AllPlayers[0].Money += bank;
			bank = 0;
		}
		else
		{
			SetCursor(TextPosition, 3, 50);
			SetConsoleCursorPosition(h, TextPosition);
			cout << endl << "You lose!";
			AllPlayers[1].Money += bank;
			bank = 0;
		}

	}
}
void ShowCard(COORD& CardPosition, int value, int suit, int i, bool AddDistanse) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD symbol;
	if (AddDistanse)
		CardPosition.X += card_size + 2; //где будет начинаться рамочка по иксам
	CardPosition.Y = i; //где будет начинаться рамочка по игрикам. Наша позиция вовыда равна игрику 
	SetConsoleTextAttribute(h, Yellow);
	SetConsoleCursorPosition(h, CardPosition); //вывод этих координат
	for (int y = i; y < i + card_size; y++) // цикл идет по строкам
	{
		SetCursor(symbol, CardPosition.X, CardPosition.Y);
		CardPosition.Y++;
		for (int x = 0; x < card_size; x++) // цикл идет по столбцам
		{
			cout << (char)219;
		}
	}
	SetConsoleTextAttribute(h, PurpleOnTheYellow);
	SetCursor(symbol, CardPosition.X + card_size / 2, (CardPosition.Y - card_size / 2) - 1);
	if (value == Cards::Ace) // Выводим достоинство
		cout << "A";
	else if (value == Cards::King)
		cout << "K";
	else if (value == Cards::Quen)
		cout << "Q";
	else if (value == Cards::Jack)
		cout << "J";
	else if (value == Cards::Ten)
		cout << "10";
	else if (value == Cards::Nine)
		cout << "9";
	else if (value == Cards::Eight)
		cout << "8";
	else if (value == Cards::Seven)
		cout << "7";
	else if (value == Cards::Six)
		cout << "6";
	else if (value == Cards::Five)
		cout << "5";
	else if (value == Cards::Four)
		cout << "4";
	else if (value == Cards::Three)
		cout << "3";
	else if (value == Cards::Two)
		cout << "2";
	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			symbol.X = CardPosition.X + card_size - 2; // Определяем серидину карты для размещения масти
			symbol.Y = CardPosition.Y - card_size + 1;
			SetConsoleCursorPosition(h, symbol);
		}
		else
		{
			symbol.X = CardPosition.X + 1; // Определяем серидину карты для размещения масти
			symbol.Y = CardPosition.Y - 2;
			SetConsoleCursorPosition(h, symbol);
		}
		if (suit == Suit::Clubs)
			cout << (char)Suit::Clubs;
		else if (suit == Suit::Hearts)
			cout << (char)Suit::Hearts;
		else if (suit == Suit::Spades)
			cout << (char)Suit::Spades;
		else if (suit == Suit::Dimonds)
			cout << (char)Suit::Dimonds;
	}
	CardPosition.Y = i;
	CardPosition.X += card_size + 2;
	SetConsoleTextAttribute(h, Yellow);
}
void MusicPlay() {

}
void SetCursor(COORD& position, int x, int y) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = x; // координата позиции
	position.Y = y; // координата позиции
	SetConsoleCursorPosition(h, position);
}
void SetUpCard() {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			AllPlayers[i].Cards[j] = rand() % 48;
}
int GetCardStatuses(bool Value, int PosistionInDeck) {
	int j = 0, i = 0;
	while (j < 48)
	{
		if (j == PosistionInDeck)
		{
			if (Value)
				return Deck[i][j % 12].Denomination;
			else
				return Deck[i][j % 12].Suit;
		}
		j++;
		i = j / 12;
	}

}
void Table(int& bank) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //дескриптор на вывод
	int code;
	COORD PositionPlayer;
	COORD PositionBot;
	COORD PositionSentences;
	int XBot = 3;
	int YBot = 3;
	int XPlayer = 3;
	int YPlayer = 22;
	for (int i = 0, f = 0; i < 2; i++, f++)
	{
		if (f == 0)
		{
			ShowBackCard(PositionPlayer, XPlayer, YPlayer, 0);
		}
		else
		{
			ShowBackCard(PositionPlayer, XPlayer, YPlayer, 1);
		}
	}
	for (int i = 0, f = 0; i < 2; i++, f++)
	{
		if (f == 0)
		{
			ShowBackCard(PositionBot, XBot, YBot, 0);
		}
		else
		{
			ShowBackCard(PositionBot, XBot, YBot, 1);
		}
	}
	SetCursor(PositionPlayer, XPlayer, YPlayer);
	code = _getch();


	if (code == ESC) {

		MainMenu();
	}
	if (code == ENTER) {

		SetUpCard();
		CalculateScore(0, bank);
		SetCursor(PositionSentences, 60, 1);
		cout << "Bot's money: " << AllPlayers[1].Money;
		SetCursor(PositionSentences, 60, 20);
		cout << "Your money: " << AllPlayers[1].Money;
		Bets(0, bank);
		for (int i = 0, f = 0; i < 2; i++, f++)
		{
			if (f == 0)
			{
				ShowCard(PositionPlayer, GetCardStatuses(1, AllPlayers[0].Cards[f]), GetCardStatuses(0, AllPlayers[0].Cards[f]), PositionPlayer.Y, 0); // вывод карт игрока
			}
			else
			{
				ShowCard(PositionPlayer, GetCardStatuses(0, AllPlayers[0].Cards[f]), GetCardStatuses(0, AllPlayers[0].Cards[f]), PositionPlayer.Y, 0); // вывод карт игрока
			}
		}


	}
	else {
		Table(bank);
	}


}
void ShowBackCard(COORD& CardPosition, int& X, int& Y, bool AddDistanse) {

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //дескриптор на вывод

	SetConsoleTextAttribute(h, Purple);
	SetConsoleCursorPosition(h, CardPosition);
	CardPosition.Y = Y;
	CardPosition.X = X;
	int i = CardPosition.Y;
	if (AddDistanse)
		CardPosition.X += card_size + 2; //где будет начинаться рамочка по иксам
	CardPosition.Y = i; //где будет начинаться рамочка по игрикам. Наша позиция вовыда равна игрику 

	SetCursor(CardPosition, CardPosition.X, CardPosition.Y);

	for (int y = CardPosition.Y; y < 10 + i; y++) // цикл идет по строкам
	{
		SetCursor(CardPosition, CardPosition.X, CardPosition.Y);

		CardPosition.Y++;

		for (int x = 0; x < 10; x++) // цикл идет по столбцам
		{
			if (y % 2 == 0 && x % 2 == 0) {
				SetConsoleTextAttribute(h, Purple);
				cout << (char)219;
			}
			else if (y % 2 != 0 && x % 2 != 0) {
				SetConsoleTextAttribute(h, Purple);
				cout << (char)219;
			}
			else {
				SetConsoleTextAttribute(h, Yellow);
				cout << (char)219;
			}

		}

	}
	CardPosition.Y = i;
	CardPosition.X += card_size + 2;
}
void ShowBalance(bool bot, int& bank) {
	COORD CurrentPosititon;
	if (bot)
	{
		CalculateScore(1, bank);
		SetCursor(CurrentPosititon, 3, 30);
		cout << "Bot score - " << AllPlayers[1].Score;
	}
	else
	{
		CalculateScore(0, bank);
		SetCursor(CurrentPosititon, 3, 70);
		cout << "\n\n\n\tYour score - " << AllPlayers[0].Score;
	}
}
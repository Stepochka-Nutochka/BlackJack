struct Player
{
	int Cards[5]{};
	int Money = 500; // балланс игрока
	int ModelOfPlaing = 0; // модель поведения ботов
	int Score = 0; // общение количество баллов от карт
};
struct Card
{
	int Denomination = 0; // достоитсво
	int Suit = 0; // масть
	int PositionInDeck = 0; // где находиться в колоде
};

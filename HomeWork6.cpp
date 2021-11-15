#include <iostream>
#include <string>
#include <vector>

////// exercise 3, 4, 5

enum ECardSuit { SPADES, CLUBS, DIAMONDS, HEARTS };
enum ECardValue {
    ACE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 10,
    QUEEN = 10,
    KING = 10
};
class Card {
    ECardSuit suit;
    ECardValue value;
    bool isCoverUp;
public:
    Card(ECardSuit _suit, ECardValue _value) : suit(_suit), value(_value) {
        isCoverUp = true;
    }

    void flip() {
        isCoverUp = !isCoverUp;
    }
    ECardValue getValue() const {
        return value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Card& aCard);
};

std::ostream& operator<<(std::ostream& os, const Card& aCard) {
    const std::string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
    const std::string SUITS[] = { "c", "d", "h", "s" };

    if (aCard.isCoverUp)
    {
        os << RANKS[aCard.value] << SUITS[aCard.suit];
    }
    else
    {
        os << "XX";
    }
    return os;
}

class Hand {
protected:
    int sum;
    std::vector<Card*> m_Cards;
public:
    void Add(Card* pCard) {
        m_Cards.push_back(pCard);
    }
    void Clear() {
        m_Cards.clear();
    }
    int GetTotal() const;
};

int Hand::GetTotal() const {
    if (m_Cards.empty())
    {
        return 0;
    }
    if (m_Cards[0]->getValue() == 0)
    {
        return 0;
    }

    int total = 0;
    std::vector<Card*>::const_iterator iter;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        total += (*iter)->getValue();
    }

    bool containsAce = false;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        if ((*iter)->getValue() == ACE)
        {
            containsAce = true;
        }
    }

    if (containsAce && total <= 11)
    {
        total += 10;
    }
    return total;
}

class GenericPlayer : public Hand {
    friend std::ostream& operator <<(std::ostream& os, const GenericPlayer& aGenericPlayer);
protected:
    std::string m_Name;
public:
    GenericPlayer(const std::string& name = "");
    virtual ~GenericPlayer();
    virtual bool IsHitting() const = 0;
    bool IsBusted() const;
    void Bust() const;
};

GenericPlayer::GenericPlayer(const std::string& name) : m_Name(name) {}
GenericPlayer::~GenericPlayer() {}

bool GenericPlayer::IsBusted() const {
    return (GetTotal() > 21);
}

void GenericPlayer::Bust() const {
    std::cout << m_Name << " busts. \n";
}

std::ostream& operator <<(std::ostream& os, const GenericPlayer& aGenericPlayer) {
    os << aGenericPlayer.m_Name << ":\t";
    std::vector<Card*>::const_iterator pCard;
    if (!aGenericPlayer.m_Cards.empty())
    {
        for (pCard = aGenericPlayer.m_Cards.begin();
            pCard != aGenericPlayer.m_Cards.end();
            ++pCard)
        {
            os << *(*pCard) << "\t";
        }

        if (aGenericPlayer.GetTotal() != 0)
        {
            std::cout << "(" << aGenericPlayer.GetTotal() << ")";
        }
    }
    else
    {
        os << "<empty>";
    }
    return os;
}

class Player : public GenericPlayer {
public:
    Player(const std::string& name = "");
    virtual ~Player();
    virtual bool IsHitting() const;
    void Win() const;
    void Lose() const;
    void Push() const;
};

bool Player::IsHitting() const {
    std::cout << m_Name << ", do you want a hit? (Y/N): ";
    char response;
    std::cin >> response;
    return (response == 'y' || response == 'Y');
}

void Player::Win() const {
    std::cout << m_Name << " wins. \n";
}

void Player::Lose() const {
    std::cout << m_Name << " loses. \n";
}

void Player::Push() const {
    std::cout << m_Name << " pushes. \n";
}

class House : public GenericPlayer {
public:
    House(const std::string& name = "House");

    virtual ~House();
    virtual bool IsHitting() const;
    void FlipFirstCard();
};

bool House::IsHitting() const {
    return (GetTotal() <= 16);
}

void House::FlipFirstCard() {
    if (!(m_Cards.empty()))
    {
        m_Cards[0]->flip();
    }
    else
    {
        std::cout << "No card to flip!\n";
    }
}

class Deck : public Hand {
public:
    void Populate() { }
    void Shuffle() { }
    void Deal(Hand& aHand) { }
    void AddltionalCards(GenericPlayer& aGenericPlayer) { }
};

class Game {
    Deck m_Deck;
    House m_House;
    std::vector<Player> m_Players;
public:
    void Play() {}
};

///////

////// exercise 2

class Endl {
    friend std::ostream& operator<< (std::ostream& out, const Endl &end);
};

std::ostream& operator<< (std::ostream& out, const Endl &end) {
    out << "\n\n";
    fflush(stdout);
    return out;
}

///////////

int main()
{
    /////// exercise 1

    int a;
    std::cout << "Input an integer number: ";
    std::cin >> a;
    while (!std::cin.good())
    {
        std::cout << "Wrong Input try again" << std::endl;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cin >> a;
    }

    ////////

    /////// exercise 2

    Endl endll;
    std::cout << "Hello World!" << endll;

    ////////

    system("pause");
    return 0;
}

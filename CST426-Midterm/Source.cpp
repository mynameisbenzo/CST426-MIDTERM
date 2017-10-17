//Using Strategy Pattern

#include <iostream>
#include <ctype.h>
using namespace std;


// abstract class for all actions
class Action
{
public:
	virtual void do_it() const = 0;
	virtual ~Action() {};
};

////following is list of actions

//default action
class IamAlive : public Action {
public:
	IamAlive() {};
	virtual void do_it() const {
		// ...world?
		cout << "Hello.\n";
	}
	~IamAlive() {};
};

/////////////////forward/left/right/back actions
class WalkForward : public Action
{
public:
	WalkForward() {}
	virtual void do_it() const {
		// Pretty standard.
		cout << "I went forward.\n";
	}
	~WalkForward() {}
}; 

class WalkBackward : public Action
{
public:
	WalkBackward() {}
	virtual void do_it() const {
		// Pretty standard.
		cout << "I went backward.\n";
	}
	~WalkBackward() {}
};

class WalkSideways : public Action {
private:
	int direction;
public:
	WalkSideways(int dir) {
		//left is 0 right is 1
		direction = dir;
	};
	virtual void do_it() const {
		if (direction) {
			cout << "I'm moving right.\n";
			return;
		}
		cout << "I'm moving left.\n";
	}
	~WalkSideways() {};
};

//makes character jump
class Jump : public Action {
public:
	Jump() {};
	virtual void do_it() const {
		// Van Halen would be proud.
		cout << "I'm jumping.\n";
	}
	~Jump() {};
};

//character is now facing behind them
class TurnAround : public Action {
public:
	TurnAround() {};
	virtual void do_it() const {
		// 180 no scope is not as impressive.
		cout << "I turned around.\n";
	}
	~TurnAround() {};
};

//chacter shoots projectiles
class Shoot : public Action {
public:
	Shoot() {};
	virtual void do_it() const {
		// Pew.
		cout << "Pew! Pew!\n";
	}
	~Shoot() {};
};

//the ledge is no match for our character
class ClimbUp : public Action {
public:
	ClimbUp() {};
	virtual void do_it() const {
		// Nothing clever to say.  There's a ledge/ladder that needs climbing.
		cout << "I'm climbing up.\n";
	}
	~ClimbUp() {};
}; 

//character MIGRATES towards the floor
class Duck : public Action {
public:
	Duck() {};
	virtual void do_it() const {
		// Get down!
		cout << "I ducked.\n";
	}
	~Duck() {};
};




// Strategy pattern on character class to switch actions based on input
class Character
{
protected:

	Action* m_action;


public:

	void do_something() const {
		m_action->do_it();
	}

	void setAction(Action* a) {
		delete m_action;
		m_action = a;
	}

};

// Player/You
class Player : public Character {

public:
	Player() {
		m_action = new IamAlive();
	}

	~Player() {
		delete m_action;
	}
};



int main()
{
	Player* p = new Player();

	bool exit = false;					//game loop ender
	bool invalid_action = false;		//dirty flag 
	char input;
	while (!exit) {

		//since screen is cleared at the end, the action is displayed first
		if (!invalid_action) p->do_something();
		else invalid_action = false;

		cout << "Please select an action!\n";
		cout << "W:\t Walk Forward\n";
		cout << "A/D:\t Walk Sideways\n";
		cout << "S:\t Walk Backwards\n";
		cout << "Q:\t Shoot\n";
		cout << "O:\t Turn Around\n";
		cout << "J:\t Jump\n";
		cout << "E:\t Climb Up\n";
		cout << "X:\t Duck\n";
		cout << "1:\t Exit\n\n";
		cin >> input;
		
		if (isalpha(input))
			input = tolower(input);

		//gets input and switches action accordingly
		switch (input) {
		case 'w':
			p->setAction(new WalkForward);
			break;
		case 'a':
			p->setAction(new WalkSideways(0));
			break;
		case 'd':
			p->setAction(new WalkSideways(1));
			break;
		case 's':
			p->setAction(new WalkBackward);
			break;
		case 'q':
			p->setAction(new Shoot);
			break;
		case 'o':
			p->setAction(new TurnAround);
			break;
		case 'j':
			p->setAction(new Jump);
			break;
		case 'e':
			p->setAction(new ClimbUp);
			break;
		case 'x':
			p->setAction(new Duck);
			break;
		case '1':
			exit = true;
			break;
		default:
			invalid_action = true;
			break;
		}

		//looks better when then screen is cleared
		system("cls");
	}

	cout << "Bye!\n\n";
	system("pause");
	delete p;
	return 0;
}
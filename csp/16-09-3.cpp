#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

void vectorTest()
{
	vector<int>a;
	vector<int>::iterator pos2 = a.begin();
	a.insert(pos2, 100);
	/*
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	vector<int>::iterator pos = a.begin();
	pos += 3;
	a.insert(pos, 5);
	*/
	for(int i = 0; i < a.size(); i++)
		printf("%d ", a[i]);
	putchar('\n');
}

struct para {
	int attack, health;
	para(int atk, int heal)
	{
		attack = atk;
		health = heal;
	}
	void attacked(para &attacker)
	{
		health -= attacker.attack;
		attacker.health -= attack;
	}
};

struct player {
	int health;
	vector <para> battleField;
	vector <para>::iterator pos;

	player() {
		health = 30;
	}

	void summon(int p, int atk, int heal)
	{
		pos = battleField.begin() + p - 1;
		battleField.insert(pos, para(atk, heal));
	}

	void attack(int attacker, int defender, player &P)
	{
		attacker--;
		if(defender--) {
			P.battleField[defender].attacked(battleField[attacker]);
			P.checkout(defender);
			checkout(attacker);
		} else {
			P.health -= battleField[attacker].attack;
		}
	}

	void checkout(int i)
	{
		if(battleField[i].health <= 0) {
			pos = battleField.begin() + i;
			battleField.erase(pos);
		}
	}

	void display()
	{
		int siz = battleField.size();
		printf("%d\n%d ", health, siz);
		for(int i = 0; i < siz; i++)
		{
			printf("%d ", battleField[i].health);
		}
		putchar('\n');
	}
}players[2];

int main()
{
	//vectorTest();
	int n, p, a, h, d, now = 0;
	char s[15];
	scanf("%d", &n);
	while(n--)
	{
		scanf("%s", s);
		if(s[0] == 's') {
			scanf("%d%d%d", &p, &a, &h);
			players[now].summon(p, a, h);			
		} else if(s[0] == 'a') {
			scanf("%d%d", &a, &d);
			players[now].attack(a, d, players[!now]);
			if(players[!now].health <= 0) break;
		} else {
			now = !now;
			continue;
		}
	}
	if(players[now].health > 0 && players[!now].health > 0) {
		printf("0\n");
	} else {
		printf("%d\n", now ? -1 : 1);
	}
	players[0].display();
	players[1].display();
	return 0;
}

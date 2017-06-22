#include<string>
#include<vector>

using namespace std;

enum car_type { BUFFET, RESTOURANT, POST, SITTING, GENERAL, KUPE };

class carriage
{
	int num;
	car_type type;
public:
	carriage(int n, car_type t){ num = n; type = t; };
	int get_num(){ return num; };
	car_type get_type() { return type; };
};

class pas_carriage :public carriage
{
	int places;
	int passengers=0;
	int price_per_km;
	bool TV;
	bool telephone;
public:
	pas_carriage(int n, car_type t, int pls, bool tv, bool tel) :carriage(n, t)
	{
		TV = tv; telephone = tel; places = pls;
		price_per_km = 5;
		if (TV) price_per_km += 3;
		if (telephone) price_per_km += 2;
	}
	bool tv() { return TV; }
	bool telephone_() { return telephone; }
	int get_price(){ return price_per_km; }
	bool free_places(){ if (places > passengers) return true; else return false; }
	int buy_ticket() { passengers++; return passengers; }
};
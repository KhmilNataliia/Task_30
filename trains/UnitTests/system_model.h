#include"train.h"

struct ticket
{
	int price;
	int train_num;
	int carriage_num;
	int place_num;
	string departure;
	string arrival;
	time_ dep_time;
	time_ arr_time;
	bool lying;
	bool bed_complect;

};

class system_imitation
{
	vector<station*> stations;
	vector<train*> trains;
public:
	void add_station(string name, int x, int y)
	{
		station* st = new station(name, x, y);
		stations.push_back(st);
	}
	bool add_train(int n, string d, string a, time_ dt, time_ at)
	{
		station* d_st = NULL; station* a_st = NULL;
		for (int i = 0; i < stations.size(); i++)
		{
			if (stations[i]->get_name() == d) d_st = stations[i];
			if (stations[i]->get_name() == a) a_st = stations[i];
		}
		if (d_st && a_st)
		{
			train* tr = new train(n, d_st, a_st, dt, at);
			trains.push_back(tr);
			return true;
		}
		return false;
	}
	void add_serv_car(int tr_n, car_type type)
	{
		for (int i = 0; i < trains.size(); i++)
		{
			if (trains[i]->get_num() == tr_n)
			{
				trains[i]->add_serv_car(new carriage(trains[i]->get_cars_n() + 1, type));
			}
		}
	}
	void add_pas_car(int tr_n, car_type type, int pls, bool tv, bool tel)
	{
		for (int i = 0; i < trains.size(); i++)
		{
			if (trains[i]->get_num() == tr_n)
			{
				trains[i]->add_pas_car(new pas_carriage(trains[i]->get_cars_n() + 1, type, pls, tv, tel));
			}
		}
	}

	ticket* buy_ticket(string departure, string arrival, car_type type, bool rest, bool buffet, bool post, bool lying, bool bed_compl, bool tv, bool tel)
	{
		if (lying)
		{
			if (type != GENERAL && type != KUPE) return NULL;
		}
		if (bed_compl)
		{
			if (type != KUPE || lying!=true) return NULL;
		}
		train* tr = NULL;
		for (int i = 0; i < trains.size(); i++)
		{
			if (trains[i]->get_dep_station()->get_name() == departure && trains[i]->get_arr_station()->get_name() == arrival
				&& (trains[i]->post() == post || !post) && (trains[i]->buffet() == buffet || !buffet) && (trains[i]->restourant() == rest || !rest))
				tr = trains[i];
		}
		pas_carriage* car = NULL;
		if (tr)
		{
			if (tv && tel)
			{
				car = tr->both(type);
			}
			else
			{
				if (tv)
				{
					car = tr->tv(type);
				}
				else
				{
					if (tel)
					{
						car = tr->telephone(type);
					}
					else
					{
						car = tr->find_car(type);
					}
				}
			}

			if (car)
			{
				ticket* tck = new ticket();
				tck->arrival = arrival;
				tck->arr_time = tr->get_arr_time();
				tck->bed_complect = bed_compl;
				tck->carriage_num = car->get_num();
				tck->departure = departure;
				tck->dep_time = tr->get_dep_time();
				tck->lying = lying;
				tck->place_num = car->buy_ticket();
				tck->train_num = tr->get_num();
				tck->price = car->get_price();
				if (bed_compl) tck->price += 1;
				tck->price *= tr->get_kms();
				return tck;
			}
		}
		return NULL;
	}
};
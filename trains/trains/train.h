#include"carriage.h"

struct  time_
{
	int hours;
	int mins;
};

class station
{
	int x, y;
	string name;
public:
	station(string n, int x_, int y_) { name = n; x = x_; y = y_; }
	int get_x() { return x; }
	int get_y() { return y; }
	string get_name() { return name; }
};

class train
{
	vector<carriage*> service_cars;
	vector<pas_carriage*> pas_cars;
	int num;
	int cars;
	int kms;
	station* dep_st; 
	station* arr_st;
	time_ dep_time;
	time_ arr_time;
public:
	train(int n, station* dep, station* arr, time_ d_t, time_ a_t)
	{ 
		num = n; dep_st = dep; arr_st = arr; dep_time = d_t; arr_time = a_t; cars = 0; 
		kms = round(sqrt((dep->get_x() - arr->get_x())*(dep->get_x() - arr->get_x()) + (dep->get_y() - arr->get_y())*(dep->get_y() - arr->get_y())));
	}
	int get_kms() { return kms; }
	void add_serv_car(carriage* car){ service_cars.push_back(car); cars++; }
	void add_pas_car(pas_carriage* car) { pas_cars.push_back(car); cars++; }
	int get_num() { return num; }
	int get_cars_n() { return cars; }
	station* get_dep_station() { return dep_st; }
	station* get_arr_station() { return arr_st; }
	time_ get_dep_time() { return dep_time; }
	time_ get_arr_time() { return arr_time; }
	bool restourant() 
	{
		bool res = false;
		for (int i = 0; i < service_cars.size(); i++)
			if (service_cars[i]->get_type() == RESTOURANT) res = true;
		return res;
	}
	bool post()
	{
		bool res = false;
		for (int i = 0; i < service_cars.size(); i++)
			if (service_cars[i]->get_type() == POST) res = true;
		return res;
	}
	bool buffet()
	{
		bool res = false;
		for (int i = 0; i < service_cars.size(); i++)
			if (service_cars[i]->get_type() == BUFFET) res = true;
		return res;
	}
	pas_carriage* tv(car_type t)
	{
		for (int i = 0; i < pas_cars.size(); i++)
			if (pas_cars[i]->get_type() == t && pas_cars[i]->tv() && pas_cars[i]->free_places()) return pas_cars[i];
		return NULL;
	}
	pas_carriage* telephone(car_type t)
	{
		for (int i = 0; i < pas_cars.size(); i++)
			if (pas_cars[i]->get_type() == t && pas_cars[i]->telephone_() && pas_cars[i]->free_places()) return pas_cars[i];
		return NULL;
	}
	pas_carriage* both(car_type t)
	{
		for (int i = 0; i < pas_cars.size(); i++)
			if (pas_cars[i]->get_type() == t && pas_cars[i]->tv() && pas_cars[i]->telephone_() && pas_cars[i]->free_places()) return pas_cars[i];
		return NULL;
	}
	pas_carriage* find_car(car_type t)
	{
		for (int i = 0; i < pas_cars.size(); i++)
			if (pas_cars[i]->get_type() == t && pas_cars[i]->free_places()) return pas_cars[i];
		return NULL;
	}
};


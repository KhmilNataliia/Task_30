#include "stdafx.h"
#include "CppUnitTest.h"

#include "catch.hpp"
#include "system_model.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CASE("service_cars_types")
	{
		carriage* c1 = new carriage(1, POST);
		carriage* c2 = new carriage(2, BUFFET);
		carriage* c3 = new carriage(3, RESTOURANT);
		REQUIRE(c1->get_type() == POST);
		REQUIRE(c2->get_type() == BUFFET);
		REQUIRE(c3->get_type() == RESTOURANT);
		REQUIRE(c1->get_num() == 1);
		REQUIRE(c2->get_num() == 2);
		REQUIRE(c3->get_num() == 3);
	};
	TEST_CASE("pas_car")
	{
		pas_carriage* pc = new pas_carriage(1, GENERAL, 3, true, true);
		REQUIRE(pc->free_places() == true);
		REQUIRE(pc->get_num() == 1);
		REQUIRE(pc->get_price() == 10);
		REQUIRE(pc->get_type() == GENERAL);
		REQUIRE(pc->telephone_());
		REQUIRE(pc->tv());
		pc->buy_ticket();
		pc->buy_ticket();
		REQUIRE(pc->buy_ticket() == 3);
		REQUIRE(!pc->free_places());
	};
	TEST_CASE("train")
	{
		station* st1 = new station("f", 1, 1);
		station* st2 = new station("c", 5, 4);
		time_ t1, t2; t1.hours = 14; t1.mins = 30; t2.hours = 19; t2.mins = 55;
		train* tr = new train(1, st1, st2, t1, t2);
		carriage* c1 = new carriage(1, POST);
		carriage* c2 = new carriage(2, BUFFET);
		carriage* c3 = new carriage(3, RESTOURANT);
		pas_carriage* pc1 = new pas_carriage(4, GENERAL, 3, true, false);
		pas_carriage* pc2 = new pas_carriage(5, GENERAL, 3, true, true);
		pas_carriage* pc3 = new pas_carriage(6, GENERAL, 3, false, true);
		pas_carriage* pc4 = new pas_carriage(7, GENERAL, 3, false, false);
		tr->add_pas_car(pc1); tr->add_pas_car(pc2); tr->add_pas_car(pc3); tr->add_pas_car(pc4);
		tr->add_serv_car(c1); tr->add_serv_car(c2); tr->add_serv_car(c3);
		REQUIRE(tr->both(GENERAL) != NULL);
		REQUIRE(tr->both(KUPE) == NULL);
		REQUIRE(tr->buffet() == true);
		REQUIRE(tr->find_car(GENERAL) != NULL);
		REQUIRE(tr->find_car(SITTING) == NULL);
		REQUIRE(tr->get_arr_station()->get_name() == "c");
		REQUIRE(tr->get_arr_time().hours==19);
		REQUIRE(tr->get_arr_time().mins == 55);
		REQUIRE(tr->get_cars_n() == 7);
		REQUIRE(tr->get_dep_station()->get_name() == "f");
		REQUIRE(tr->get_dep_time().hours == 14);
		REQUIRE(tr->get_dep_time().mins == 30);
		REQUIRE(tr->get_kms() == 5);
		REQUIRE(tr->get_num() == 1);
		REQUIRE(tr->post() == true);
		REQUIRE(tr->restourant() == true);
		REQUIRE(tr->telephone(GENERAL) != NULL);
		REQUIRE(tr->telephone(KUPE) == NULL);
		REQUIRE(tr->tv(GENERAL) != NULL);
		REQUIRE(tr->tv(SITTING) == NULL);	
	}

	TEST_CASE("system")
	{
		system_imitation* s_i = new system_imitation();
		station* st1 = new station("f", 1, 1);
		station* st2 = new station("c", 5, 4);
		time_ t1, t2; t1.hours = 14; t1.mins = 30; t2.hours = 19; t2.mins = 55;
		train* tr = new train(1, st1, st2, t1, t2);
		carriage* c1 = new carriage(1, POST);
		carriage* c2 = new carriage(2, BUFFET);
		carriage* c3 = new carriage(3, RESTOURANT);
		pas_carriage* pc1 = new pas_carriage(4, GENERAL, 3, true, false);
		pas_carriage* pc2 = new pas_carriage(5, GENERAL, 3, true, true);
		pas_carriage* pc3 = new pas_carriage(6, GENERAL, 3, false, true);
		pas_carriage* pc4 = new pas_carriage(7, GENERAL, 3, false, false);
		tr->add_pas_car(pc1); tr->add_pas_car(pc2); tr->add_pas_car(pc3); tr->add_pas_car(pc4);
		tr->add_serv_car(c1); tr->add_serv_car(c2); tr->add_serv_car(c3);
		s_i->add_station("a", 1, 1);
		s_i->add_station("b", 5, 4);
		s_i->add_station("c", 8, 8);
		s_i->add_train(1, "a", "b", t1, t2);
		s_i->add_train(2, "b", "c", t1, t2);
		s_i->add_train(3, "b", "a", t1, t2);
		s_i->add_serv_car(1, POST);
		s_i->add_serv_car(1, RESTOURANT);
		s_i->add_serv_car(1, BUFFET);
		s_i->add_serv_car(2, RESTOURANT);
		s_i->add_serv_car(2, BUFFET);
		s_i->add_serv_car(3, POST);
		s_i->add_pas_car(1, KUPE, 3, false, false);
		s_i->add_pas_car(1, KUPE, 3, true, true);
		s_i->add_pas_car(1, KUPE, 3, false, true);
		s_i->add_pas_car(1, KUPE, 3, true, false);
		s_i->add_pas_car(2, SITTING, 3, false, true);
		s_i->add_pas_car(2, SITTING, 3, true, false);
		s_i->add_pas_car(2, GENERAL, 3, false, false);
		s_i->add_pas_car(3, SITTING,3, true, true);
		s_i->add_pas_car(3, GENERAL, 3, true, false);
		s_i->add_pas_car(3, GENERAL, 3, false, true);

		ticket* tk1 = s_i->buy_ticket("a", "b", KUPE, true, true, false, true, true, true, true);
		ticket* tk2 = s_i->buy_ticket("b", "c", SITTING, true, false, false, false, false, false, true);
		ticket* tk6 = s_i->buy_ticket("b", "c", SITTING, true, false, false, false, false, true, false);
		ticket* tk3 = s_i->buy_ticket("b", "a", GENERAL, false, false, false, true, false, false, false);
		ticket* tk4 = s_i->buy_ticket("b", "c", SITTING, true, false, false, true, true, false, true);
		ticket* tk5 = s_i->buy_ticket("b", "a", GENERAL, false, false, false, true, true, false, false);
		ticket* tk7 = s_i->buy_ticket("b", "a", KUPE, false, false, false, true, false, false, false);

		REQUIRE(tk1->price == 55);
		REQUIRE(tk2->price == 35);
		REQUIRE(tk3->price == 40);
		REQUIRE(tk6->price == 40);
		REQUIRE(tk4 == NULL);
		REQUIRE(tk5 == NULL);
		REQUIRE(tk7 == NULL);
		REQUIRE(s_i->add_train(7, "d", "h", t1, t2) == false);

		

	}
}
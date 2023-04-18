#include <iostream>
#include <string>
#include "map.hpp"
#include "iterator.hpp"

int main()
{
	stl::map<std::string, int> obj;
	obj.insert("100", 100);
	obj.insert("200", 200);
	obj.insert("300", 300);
	obj.insert("250", 400);
	obj.insert("275", 500);
	obj.insert("225", 600);
	obj.insert("212", 100);
	obj.insert("219", 700);
	obj.insert("206", 800);
	obj.insert("215", 900);
	obj.insert("222", 110);
	obj.insert("203", 120);
	obj.insert("209", 130);
	obj.insert("500", 140);
	obj.insert("150", 150);
	obj.insert("125", 160);
	obj.insert("126", 170);
	obj.insert("127", 180);
	obj.insert("218", 190);
	obj.insert("201", 199);
	obj.insert("216", 190);
	obj.insert("214", 199);
	//next three lines are for testing double insertion of datas already present in collection
	obj.insert("201", 199);
	obj.insert("216", 190);
	obj.insert("214", 199);
	//next four lines test deletion
	obj.Delete("201");
	obj.Delete("118");
	obj.Delete("212");
	obj.Delete("206");

	for (auto i : obj) 
	{
		std::cout << i.first << "\t" << i.second << std::endl;
	}

	return 0;
}

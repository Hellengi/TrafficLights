#include "cl_4.h"
#include "cl_5.h"
#include "cl_7.h"
#include <iostream>
#include <algorithm>

cl_4::cl_4(cl_base* p_head_object, std::string s_object_name) : cl_base(p_head_object, s_object_name) {
	class_set(4);
	std::vector<std::vector<std::string>> line(4, std::vector<std::string>());
	this->line = line;
}

int cl_4::position_get(int x, int y, int road) {
	switch (road) {
	case(1): return (x > 0) ? -x + size : -x + size - 1;
	case(2): return (y > 0) ? -y + size : -y + size - 1;
	case(3): return (x < 0) ? x + size : x + size - 1;
	case(4): return (y < 0) ? y + size : y + size - 1;
	}
}

void cl_4::signal_remove(std::string&) {}

void cl_4::signal_output(std::string&) {}

void cl_4::handler_size(std::string message) {
	size = stoi(message);
	for (int x = 0; x < size * 2; x++) {
		line[0].push_back("");
		line[1].push_back("");
		line[2].push_back("");
		line[3].push_back("");
	}
}

void cl_4::handler_new(std::string message) {
	std::string name = message.substr(0, message.find("_"));
	message = message.substr(message.find("_") + 1);
	int x = stoi(message.substr(0, message.find("_")));
	message = message.substr(message.find("_") + 1);
	int y = stoi(message.substr(0, message.find("_")));
	int road = stoi(message.substr(message.find("_") + 1));
	line[road - 1][position_get(x, y, road)] = name;
}

void cl_4::handler_clear(std::string message) {
	std::string name = message.substr(0, message.find("_"));
	message = message.substr(message.find("_") + 1);
	int x = stoi(message.substr(0, message.find("_")));
	message = message.substr(message.find("_") + 1);
	int y = stoi(message.substr(0, message.find("_")));
	int road = stoi(message.substr(message.find("_") + 1));
	int index = position_get(x, y, road);
	if (index == size * 2 - 1) {
		line[road - 1][index] = "";
		signal_emit(SIGNAL_D(cl_4::signal_remove), name);
		((cl_5*)(object_get("/section/" + name)))->removed_set();
		return;
	}
	if (line[road - 1][index + 1] != "") {
		((cl_5*)(object_get("/section/" + name)))->clear_set(false);
		return;
	}
	swap(line[road - 1][index], line[road - 1][index + 1]);
	((cl_5*)(object_get("/section/" + name)))->clear_set(true);
}

void cl_4::handler_display(std::string message) {
	std::string color = "Traffic light color is " + ((cl_7*)(object_get("/light_control/light")))->color_get();
	signal_emit(SIGNAL_D(cl_4::signal_output), color);
	std::vector<std::string> list;
	for (int x = 0; x < size * 2; x++) {
		if (line[0][x] != "") list.push_back(line[0][x] + " ( " + std::to_string((x < size) ? -x + size : -x + size - 1) + ", 1 )");
		if (line[1][x] != "") list.push_back(line[1][x] + " ( -1, " + std::to_string((x < size) ? -x + size : -x + size - 1) + " )");
		if (line[2][x] != "") list.push_back(line[2][x] + " ( " + std::to_string((x < size) ? x - size : x - size + 1) + ", -1 )");
		if (line[3][x] != "") list.push_back(line[3][x] + " ( 1, " + std::to_string((x < size) ? x - size : x - size + 1) + " )");
	}
	std::sort(list.begin(), list.end());
	for (std::string info : list)signal_emit(SIGNAL_D(cl_4::signal_output), info);
}
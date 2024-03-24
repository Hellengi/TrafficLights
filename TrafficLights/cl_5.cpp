#include "cl_5.h"
#include "cl_7.h"
#include <iostream>

cl_5::cl_5(cl_base* p_head_object, std::string s_object_name) : cl_base(p_head_object, s_object_name) {
	class_set(5);
	name_set(s_object_name.substr(0, s_object_name.find(" ")));
	s_object_name = s_object_name.substr(s_object_name.find(" ") + 1);
	x = stoi(s_object_name.substr(0, s_object_name.find(" ")));
	y = stoi(s_object_name.substr(s_object_name.find(" ") + 1));
	if (y == 1) road = 1;
	else if (x == -1) road = 2;
	else if (y == -1) road = 3;
	else if (x == 1) road = 4;
}

void cl_5::clear_set(bool clear) {
	this->clear = clear;
}

void cl_5::signal_new(std::string& message) {
	message = name_get() + "_" + std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(road);
}

void cl_5::signal_clear(std::string&) {}

void cl_5::signal_output(std::string&) {}

void cl_5::signal_moved(std::string&) {}

void cl_5::handler_moved(std::string) {
	moved = false;
}

void cl_5::handler_info(std::string message) {
	message = message.substr(4);
	if (message == name_get() && this->removed) {
		message = message + " the car left the road section";
		signal_emit(SIGNAL_D(cl_5::signal_output), message);
		return;
	}
	if (message == name_get()) {
		message = "Car " + message + " ( " + std::to_string(x) + ", " + std::to_string(y) + " )";
		signal_emit(SIGNAL_D(cl_5::signal_output), message);
	}
}

void cl_5::handler_move(std::string message) {
	if (moved) return;
	std::string color = ((cl_7*)(object_get("/light_control/light")))->color_get();
	if ((x == 1 && y == -2 || x == -1 && y == 2) && (color == "green" or color == "yellow")) return;
	if ((x == 2 && y == 1 || x == -2 && y == -1) && (color == "red" or color == "yellow")) return;
	message = name_get() + "_" + std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(road);
	signal_emit(SIGNAL_D(cl_5::signal_clear), message);
	if (clear) {
		switch (road) {
		case(1): (x != 1) ? x -= 1 : x -= 2; break;
		case(2): (y != 1) ? y -= 1 : y -= 2; break;
		case(3): (x != -1) ? x += 1 : x += 2; break;
		case(4): (y != -1) ? y += 1 : y += 2; break;
		}
		signal_emit(SIGNAL_D(cl_5::signal_moved), message);
		moved = true;
	}
}

void cl_5::removed_set() {
	removed = true;
}
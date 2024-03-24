#include "cl_3.h"
#include <iostream>

cl_3::cl_3(cl_base* p_head_object, std::string s_object_name) : cl_base(p_head_object, s_object_name) {
	class_set(3);
}

void cl_3::signal_color(std::string& message) {}

void cl_3::handler_switch(std::string message) {
	if (message[25] == 'r') red_step = stoi(message.substr(29));
	if (message[25] == 'g') green_step = stoi(message.substr(31));
}

void cl_3::handler_step(std::string message) {
	if (color == "green" && step == green_step) color = "yellow_g";
	else if (color == "yellow_g" && step == 2) color = "red";
	else if (color == "red" && step == red_step) color = "yellow_r";
	else if (color == "yellow_r" && step == 2) color = "green";
	else {
		step++;
		return;
	}
	step = 1;
	signal_emit(SIGNAL_D(cl_3::signal_color), color);
}
#include "cl_7.h"
#include "cl_application.h"
#include <iostream>

cl_7::cl_7(cl_base* p_head_object, std::string s_object_name) : cl_base(p_head_object, s_object_name) {
	class_set(7);
}

std::string cl_7::color_get() {
	return color;
}

void cl_7::handler_set(std::string message) {
	color = (message[0] == 'y') ? "yellow" : message;
}
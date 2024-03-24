#include "cl_2.h"
#include "cl_application.h"
#include <iostream>

cl_2::cl_2(cl_base* p_head_object, std::string s_object_name) : cl_base(p_head_object, s_object_name) {
	class_set(2);
}

void cl_2::signal(std::string& message) {
	getline(std::cin, message);
}

void cl_2::handler(std::string message) {
	signal_emit(SIGNAL_D(cl_2::signal), message);
}
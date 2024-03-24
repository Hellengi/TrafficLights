#include "cl_6.h"
#include <iostream>

cl_6::cl_6(cl_base* p_head_object, std::string s_object_name) : cl_base(p_head_object, s_object_name) {
	class_set(6);
}

void cl_6::handler(std::string message) {
	if (message == "SHOWTREE") {
		head_get()->tree_output_status();
		return;
	}
	if (message == "Turn off the system") {
		std::cout << "System turned off";
	}
	else std::cout << message << std::endl;
}
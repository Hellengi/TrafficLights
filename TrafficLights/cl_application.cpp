#include "cl_application.h"
#include "cl_2.h"
#include "cl_3.h"
#include "cl_4.h"
#include "cl_5.h"
#include "cl_6.h"
#include "cl_7.h"
#include <iostream>
cl_application::cl_application(cl_base* p_head_object) : cl_base(p_head_object) {}
void cl_application::build_tree_objects() {
	name_set("application");
	status_set(1);
	cl_2* input = new cl_2(this, "input");
	input->status_set(1);
	cl_3* light_control = new cl_3(this, "light_control");
	light_control->status_set(1);
	cl_4* section = new cl_4(this, "section");
	section->status_set(1);
	cl_6* output = new cl_6(this, "output");
	output->status_set(1);
	cl_7* light = new cl_7(light_control, "light");
	light->status_set(1);
	connect_set(SIGNAL_D(cl_application::signal_input), input, HANDLER_D(cl_2::handler));
	input->connect_set(SIGNAL_D(cl_2::signal), this, HANDLER_D(cl_application::handler_input));
	connect_set(SIGNAL_D(cl_application::signal_output), output, HANDLER_D(cl_6::handler));
	info = "Enter the length of the road";
	signal_emit(SIGNAL_D(cl_application::signal_output), info);
	signal_emit(SIGNAL_D(cl_application::signal_input), info);
	connect_set(SIGNAL_D(cl_application::signal_size), section, HANDLER_D(cl_4::handler_size));
	signal_emit(SIGNAL_D(cl_application::signal_size), info);
	info = "Enter the name and coordinates of each car in the format";
	signal_emit(SIGNAL_D(cl_application::signal_output), info);
	info = "\"CarName PositionX PositionY\"";
	signal_emit(SIGNAL_D(cl_application::signal_output), info);
	info = "Type \"End of cars\" at the end";
	signal_emit(SIGNAL_D(cl_application::signal_output), info);
	while (true) {
		signal_emit(SIGNAL_D(cl_application::signal_input), info);
		if (info == "End of cars") break;
		cl_5* car = new cl_5(section, info);
		car->status_set(1);
		connect_set(SIGNAL_D(cl_application::signal_info), car, HANDLER_D(cl_5::handler_info));
		connect_set(SIGNAL_D(cl_application::signal_move), car, HANDLER_D(cl_5::handler_move));
		car->connect_set(SIGNAL_D(cl_5::signal_output), output, HANDLER_D(cl_6::handler));
		car->connect_set(SIGNAL_D(cl_5::signal_clear), section, HANDLER_D(cl_4::handler_clear));
		car->connect_set(SIGNAL_D(cl_5::signal_new), section, HANDLER_D(cl_4::handler_new));
		car->connect_set(SIGNAL_D(cl_5::signal_moved), this, HANDLER_D(cl_application::handler_moved));
		connect_set(SIGNAL_D(cl_application::signal_light), car, HANDLER_D(cl_5::handler_moved));
		car->signal_emit(SIGNAL_D(cl_5::signal_new), info);
	}
	connect_set(SIGNAL_D(cl_application::signal_light), light_control, HANDLER_D(cl_3::handler_step));
	connect_set(SIGNAL_D(cl_application::signal_switch), light_control, HANDLER_D(cl_3::handler_switch));
	connect_set(SIGNAL_D(cl_application::signal_display), section, HANDLER_D(cl_4::handler_display));
	section->connect_set(SIGNAL_D(cl_4::signal_remove), this, HANDLER_D(cl_application::handler_remove));
	section->connect_set(SIGNAL_D(cl_4::signal_output), output, HANDLER_D(cl_6::handler));
	light_control->connect_set(SIGNAL_D(cl_3::signal_color), light, HANDLER_D(cl_7::handler_set));
	info = "Ready to work";
	signal_emit(SIGNAL_D(cl_application::signal_output), info);
}

int cl_application::exec_app() {
	info = "----LIST OF COMMANDS----";
	signal_emit(SIGNAL_D(cl_application::signal_output), info);
	info = "- Display the system status";
	signal_emit(SIGNAL_D(cl_application::signal_output), info);
	info = "- Switching traffic lights [color] [duration]";
	signal_emit(SIGNAL_D(cl_application::signal_output), info);
	info = "- Car [name]";
	signal_emit(SIGNAL_D(cl_application::signal_output), info);
	info = "- Pass";
	signal_emit(SIGNAL_D(cl_application::signal_output), info);
	info = "- Turn off the system";
	signal_emit(SIGNAL_D(cl_application::signal_output), info);
	info = "------------------------";
	signal_emit(SIGNAL_D(cl_application::signal_output), info);
	for (int step = 1; true; step++) {
		signal_emit(SIGNAL_D(cl_application::signal_input), info);
		if (info == "SHOWTREE") {
			signal_emit(SIGNAL_D(cl_application::signal_output), info);
			exit(0);
		}
		if (info.size() > 0) {
			switch (info[0]) {
			case('S'): signal_emit(SIGNAL_D(cl_application::signal_switch), info); break;
			case('C'): signal_emit(SIGNAL_D(cl_application::signal_info), info); break;
			case('D'): signal_emit(SIGNAL_D(cl_application::signal_display), info); break;
			case('T'): signal_emit(SIGNAL_D(cl_application::signal_output), info); exit(0);
			}
		}
		signal_emit(SIGNAL_D(cl_application::signal_light), info);
		while (moved) {
			moved = false;
			signal_emit(SIGNAL_D(cl_application::signal_move), info);
		}
		moved = true;
	}
	return 0;
}

void cl_application::signal_input(std::string& message) {}

void cl_application::signal_output(std::string& message) {}

void cl_application::signal_size(std::string& message) {}

void cl_application::signal_light(std::string& message) {}

void cl_application::signal_move(std::string& message) {}

void cl_application::signal_switch(std::string& message) {}

void cl_application::signal_info(std::string& message) {}

void cl_application::signal_display(std::string& message) {}

void cl_application::handler_input(std::string message) {
	this->info = message;
}

void cl_application::handler_remove(std::string message) {
	cl_5* car = (cl_5*)(object_get("/section/" + message));
	connect_delete(SIGNAL_D(cl_application::signal_move), car, HANDLER_D(cl_5::handler_move));
}

void cl_application::handler_moved(std::string message) {
	moved = true;
}
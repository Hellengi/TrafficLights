#ifndef __CL_APPLICATION__H
#define __CL_APPLICATION__H
#include "cl_base.h"
class cl_application : public cl_base {
private:
	cl_base* current_object = this;
	std::string info = "";
	bool moved = true;
public:
	cl_application(cl_base*);
	void build_tree_objects();
	int exec_app();
	void signal_input(std::string&);
	void signal_output(std::string&);
	void signal_size(std::string&);
	void signal_light(std::string&);
	void signal_move(std::string&);
	void signal_switch(std::string&);
	void signal_info(std::string&);
	void signal_display(std::string&);
	void handler_input(std::string);
	void handler_remove(std::string);
	void handler_moved(std::string);
};
#endif
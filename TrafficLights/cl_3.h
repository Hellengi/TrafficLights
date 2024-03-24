#ifndef __CL_3__H
#define __CL_3__H
#include "cl_base.h"
class cl_3 : public cl_base {
private:
	int step = 0;
	int red_step = 5;
	int green_step = 5;
	std::string color = "green";
public:
	cl_3(cl_base* p_head_object, std::string s_object_name);
	void signal_color(std::string&);
	void handler_switch(std::string);
	void handler_step(std::string);
};
#endif
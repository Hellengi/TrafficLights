#ifndef __CL_7__H
#define __CL_7__H
#include "cl_base.h"
class cl_7 : public cl_base {
private:
	std::string color = "green";
public:
	cl_7(cl_base* p_head_object, std::string s_object_name);
	std::string color_get();
	void handler_set(std::string);
};
#endif
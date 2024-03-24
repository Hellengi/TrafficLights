#ifndef __CL_2__H
#define __CL_2__H
#include "cl_base.h"
class cl_2 : public cl_base {
public:
	cl_2(cl_base* p_head_object, std::string s_object_name);
	void signal(std::string&);
	void handler(std::string);
};
#endif
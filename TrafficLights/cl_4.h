#ifndef __CL_4__H
#define __CL_4__H
#include "cl_base.h"
class cl_4 : public cl_base {
private:
	int size = 0;
	std::vector<std::vector<std::string>> line;
public:
	cl_4(cl_base* p_head_object, std::string s_object_name);
	int position_get(int, int, int);
	void signal_remove(std::string&);
	void signal_output(std::string&);
	void handler_size(std::string);
	void handler_new(std::string);
	void handler_clear(std::string);
	void handler_display(std::string);
};
#endif
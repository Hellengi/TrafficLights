#ifndef __CL_5__H
#define __CL_5__H
#include "cl_base.h"
class cl_5 : public cl_base {
private:
	int x = 0;
	int y = 0;
	int road = 0;
	bool clear = true;
	bool moved = false;
	bool removed = false;
public:
	cl_5(cl_base* p_head_object, std::string s_object_name);
	void clear_set(bool);
	void signal_new(std::string&);
	void signal_clear(std::string&);
	void signal_output(std::string&);
	void signal_moved(std::string&);
	void handler_moved(std::string);
	void handler_info(std::string);
	void handler_move(std::string);
	void removed_set();
};
#endif
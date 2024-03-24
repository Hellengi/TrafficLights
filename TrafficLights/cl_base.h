#ifndef __CL_BASE__H
#define __CL_BASE__H
#include <string>
#include <vector>
#define SIGNAL_D(signal_f) (TYPE_SIGNAL) (&signal_f)
#define HANDLER_D(handler_f) (TYPE_HANDLER) (&handler_f)
class cl_base {
private:
	std::string s_object_name;
	cl_base* p_head_object;
	std::vector <cl_base*> subordinate_objects;
	int class_num = 1, status = 0;
public:
	typedef void (cl_base::* TYPE_SIGNAL)(std::string&); //определение типа данных: указатель на метод сигнала объекта
	typedef void (cl_base::* TYPE_HANDLER)(std::string); //определение типа данных: указатель на метод обработчика объекта
private:
	struct o_sh { // структура задания одной связи
		TYPE_SIGNAL p_signal; // указатель на метод сигнала
		cl_base* p_cl_base; // указатель на целевой объект
		TYPE_HANDLER p_handler; // указатель на метод обработчика
	};
	std::vector <o_sh*> connects;
public:
	cl_base(cl_base*, std::string = "Base_object");
	bool name_set(std::string);
	std::string name_get();
	void class_set(int);
	int class_get();
	cl_base* head_get();
	void tree_print();
	cl_base* subordinate_get(std::string);
	~cl_base();
	int name_amount(std::string);
	cl_base* object_search_current(std::string);
	cl_base* object_search_all(std::string);
	void tree_output();
	void tree_output_status();
	void status_set(int);
	int status_get();
	void object_status_set(std::string, int);
	bool head_set(cl_base*);
	void subordinate_delete(std::string);
	cl_base* object_get(std::string);
	std::string path_get();
	void connect_set(TYPE_SIGNAL, cl_base*, TYPE_HANDLER);
	void connect_delete(TYPE_SIGNAL, cl_base*, TYPE_HANDLER);
	void signal_emit(TYPE_SIGNAL, std::string&);
	int string_to_int(std::string);
};
#endif
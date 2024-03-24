#include "cl_base.h"
#include "cl_application.h"
#include "cl_2.h"
#include "cl_3.h"
#include "cl_4.h"
#include "cl_5.h"
#include "cl_6.h"
#include <iostream>
cl_base::cl_base(cl_base* p_head_object, std::string s_object_name) {
	this->p_head_object = p_head_object;
	this->s_object_name = s_object_name;
	if (p_head_object) {
		p_head_object->subordinate_objects.push_back(this);
	}
}
bool cl_base::name_set(std::string s_object_name) {
	if (p_head_object != nullptr) {
		for (cl_base* parallel_object : p_head_object->subordinate_objects) {
			if (parallel_object->s_object_name == s_object_name) {
				return false;
			}
		}
	}
	this->s_object_name = s_object_name;
	return true;
}

std::string cl_base::name_get() {
	return s_object_name;
}

void cl_base::class_set(int class_num) {
	this->class_num = class_num;
}

int cl_base::class_get() {
	return class_num;
}

cl_base* cl_base::head_get() {
	return p_head_object;
}
void cl_base::tree_print() {
	if (subordinate_objects.size() > 0) {
		std::cout << s_object_name << std::endl;
		for (int x = 0; x < subordinate_objects.size(); x++) {
			std::cout << "  " << subordinate_objects[x]->s_object_name;
		}
		for (cl_base* subordinate_object : subordinate_objects) {
			subordinate_object->tree_print();
		}
	}
}
cl_base* cl_base::subordinate_get(std::string subordinate_name) {
	for (cl_base* subordinate_object : subordinate_objects) {
		if (subordinate_object->s_object_name == subordinate_name) {
			return subordinate_object;
		}
	}
	return nullptr;
}
cl_base::~cl_base() {
	if (p_head_object != nullptr) {
		for (int x = 0; x < p_head_object->subordinate_objects.size(); x++) {
			if (p_head_object->subordinate_objects[x] == this) {
				p_head_object->subordinate_objects.erase(p_head_object->subordinate_objects.begin() + x);
			}
		}
	}
	for (int x = 0; x < subordinate_objects.size(); x++) {
		delete subordinate_objects[x];
	}
}
int cl_base::name_amount(std::string name) {
	int amount = 0;
	if (s_object_name == name) amount++;
	for (cl_base* subordinate_object : subordinate_objects) {
		amount += subordinate_object->name_amount(name);
	}
	return amount;
}
cl_base* cl_base::object_search_current(std::string name) {
	if (name_amount(name) != 1) return nullptr;
	if (s_object_name == name) return this;
	if (subordinate_objects.size() == 0) return nullptr;
	for (cl_base* subordinate_object : subordinate_objects) {
		if (subordinate_object->object_search_current(name) != nullptr) {
			return subordinate_object->object_search_current(name);
		}
	}
	return nullptr;
}
cl_base* cl_base::object_search_all(std::string name) {
	cl_base* root = this;
	while (root->head_get() != nullptr) root = root->head_get();
	return root->object_search_current(name);
}
void cl_base::tree_output() {
	cl_base* root = this;
	while (root->head_get() != nullptr) {
		root = root->head_get();
		std::cout << "    ";
	}
	std::cout << name_get() << std::endl;
	for (cl_base* subordinate_object : subordinate_objects) {
		subordinate_object->tree_output();
	}
}
void cl_base::tree_output_status() {
	cl_base* root = this;
	while (root->head_get() != nullptr) {
		root = root->head_get();
		std::cout << "    ";
	}
	std::cout << name_get();
	if (status != 0) std::cout << " is ready";
	else std::cout << " is not ready";
	std::cout << std::endl;
	for (cl_base* subordinate_object : subordinate_objects) {
		subordinate_object->tree_output_status();
	}
}
void cl_base::status_set(int status) {
	this->status = status;
}
int cl_base::status_get() {
	return status;
}
void cl_base::object_status_set(std::string name, int status) {
	cl_base* root = object_search_all(name);
	if (status != 0) {
		if (root->head_get() == nullptr) root->status_set(status);
		else if (root->head_get()->status != 0) root->status_set(status);
	}
	else {
		root->status_set(0);
		for (cl_base* subordinate_object : root->subordinate_objects) {
			object_status_set(subordinate_object->name_get(), 0);
		}
	}
}
bool cl_base::head_set(cl_base* p_head_object) {
	if (head_get() == nullptr) return false;
	if (p_head_object == nullptr) return false;
	if (p_head_object->subordinate_get(name_get()) != nullptr) return false;
	cl_base* object = p_head_object;
	while (object != nullptr) {
		if (object == this) return false;
		object = object->head_get();
	}
	for (int x = 0; x < this->p_head_object->subordinate_objects.size(); x++) {
		if (this->p_head_object->subordinate_objects[x] == this) {
			this->p_head_object->subordinate_objects.erase(this->p_head_object->subordinate_objects.begin() + x);
		}
	}
	this->p_head_object = p_head_object;
	this->p_head_object->subordinate_objects.push_back(this);
	return true;
}
void cl_base::subordinate_delete(std::string subordinate_name) {
	delete subordinate_get(subordinate_name);
}
cl_base* cl_base::object_get(std::string path) {
	cl_base* root = this;
	std::string object_name = "";
	while (root->head_get() != nullptr) root = root->head_get();
	if (path == "/") return root;
	if (path == ".") return this;
	if (path.substr(0, 2) == "//") return object_search_all(path.substr(2, path.length() - 2));
	if (path[0] == '.') return object_search_current(path.substr(1, path.length() - 1));
	if (path[0] == '/') return root->object_get(path.substr(1, path.length() - 1));
	for (char letter : path) {
		if (letter != '/') object_name += letter;
		else if (subordinate_get(object_name) == nullptr) return nullptr;
		else return subordinate_get(object_name)->object_get(path.substr(object_name.length() + 1, path.length() - object_name.length() - 1));
	}
	return subordinate_get(object_name);
}

std::string cl_base::path_get() {
	std::string path = "";
	cl_base* object = this;
	while (object->head_get() != nullptr) {
		path = "/" + object->name_get() + path;
		object = object->head_get();
	}
	if (path.size() == 0) path = "/";
	return path;
}

void cl_base::connect_set(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_handler) {
	for (int x = 0; x < connects.size(); x++) {
		if (connects[x]->p_signal == p_signal and connects[x]->p_cl_base == p_object and connects[x]->p_handler == p_ob_handler) {
			return;
		}
	}
	o_sh* p_value;
	p_value = new o_sh;
	p_value->p_signal = p_signal;
	p_value->p_cl_base = p_object;
	p_value->p_handler = p_ob_handler;
	connects.push_back(p_value);
}

void cl_base::connect_delete(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_handler) {
	for (int x = 0; x < connects.size(); x++) {
		if (connects[x]->p_signal == p_signal and connects[x]->p_cl_base == p_object and connects[x]->p_handler == p_ob_handler) {
			connects.erase(connects.begin() + x);
			return;
		}
	}
}

void cl_base::signal_emit(TYPE_SIGNAL p_signal, std::string& s_command) {
	TYPE_HANDLER p_handler;
	cl_base* p_object;
	if (status == 0) return;
	(this->*p_signal) (s_command);
	for (int x = 0; x < connects.size(); x++) {
		if (connects[x]->p_signal == p_signal and connects[x]->p_cl_base->status != 0) {
			p_handler = connects[x]->p_handler;
			p_object = connects[x]->p_cl_base;
			(p_object->*p_handler) (s_command);
		}
	}
}
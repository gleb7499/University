#include <iostream>
#include <string>
template <typename T> class List {
	class node {
	public:
		T val;
		node* next, * prev;
		node() : val(T()), next(nullptr), prev(nullptr) {}
	};
	node* head, * tail;
public:
	void push_back(const T& val) {
		object* temp = new object;
		if (!temp) {
			std::cerr << "\a\t***Ошибка выделения динамической памяти!***\n";
			return;
		}
		temp->val = val;
		temp->next = this->tail;
		if (!this->head && !this->tail) {
			this->head = this->tail = temp;
			return;
		}
		this->tail->last = temp;
		this->tail = temp;
	}
	void push_front(const T& val) {
		object* temp = new object;
		if (!temp) {
			std::cerr << "\a\t***Ошибка выделения динамической памяти!***\n";
			return;
		}
		temp->val = val;
		temp->last = this->head;
		if (!this->head && !this->tail) {
			this->head = this->tail = temp;
			return;
		}
		this->head->next = temp;
		this->head = temp;
	}
	T& pop_back() {
		T val = this->tail->val;
		object* temp = tail;
		tail = tail->next;
		tail->last = nullptr;
		delete temp;
		return val;
	}
	T& pop_front() {
		T val = this->head->val;
		object* temp = head;
		head = head->last;
		head->next = nullptr;
		delete temp;
		return val;
	}
	const void print() {
		object* temp = head;
		while (temp) {
			std::cout << temp->val << " ";
			temp = temp->last;
		}
		std::cout << std::endl;
	}
	~List() {
		object* temp;
		while (head) {
			temp = head;
			head = head->last;
			delete temp;
		}
	}
};

int main()
{
	List <std::string> lst_1;
	lst_1.push_back("Hello");
	lst_1.push_back("World");
	lst_1.push_back("!");
	lst_1.print();
	lst_1.pop_front();
	lst_1.print();
	std::cout << std::endl;
	List <int> lst_2;
	lst_2.push_front(123);
	lst_2.push_front(234);
	lst_2.push_front(9876);
	lst_2.print();
	lst_2.pop_back();
	lst_2.print();
	return 0;
}
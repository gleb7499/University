#include <iostream>

template <typename T> class Queue {
	class small {
	public:
		T val;
		small* last;
		small() : val(T()), last(nullptr) {}
	};
	small* head, * tail;
public:
	Queue() : head(nullptr), tail(nullptr) {}
	void push(const T& val) {
		small* temp = new small;
		if (!temp)
		{
			std::cerr << "\a\t***Ошибка выделения динамической памяти\n***";
			return;
		}
		temp->val = val;
		temp->last = nullptr;
		if (this->head == nullptr && this->tail == nullptr)
		{
			this->head = this->tail = temp;
			return;
		}
		this->tail->last = temp;
		this->tail = temp;
	}
	T pop() {
		small* temp = this->head;
		T val = this->head->val;
		this->head = this->head->last;
		delete temp;
		return val;
	}
	void print() {
		if (!this->head) {
			std::cout << "\tСписок пуст\n";
			return;
		}
		small* temp = this->head;
		while (temp) {
			std::cout << temp->val << "  ";
			temp = temp->last;
		}
		std::cout << std::endl;
	}
	~Queue() {
		small* temp = this->head;
		while (head) {
			temp = this->head;
			head = this->head->last;
			delete temp;
		}
	}
};

int main()
{ 
	Queue <int> q;
	q.push(5);
	q.push(8);
	q.push(2);
	q.print();
	q.pop();
	q.print();
	std::cout << std::endl;
	Queue <float> t;
	t.push(23.45);
	t.push(82345.546);
	t.push(2245.4356);
	t.print();
	t.pop();
	t.print(); 
	return 0;
}
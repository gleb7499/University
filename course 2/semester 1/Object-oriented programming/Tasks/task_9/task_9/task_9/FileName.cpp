#include <iostream>
#include <string>
template <typename T> class Stack {
	class small {
	public:
		T val;
		small* last;
		small() : val(T()), last(nullptr) {}
	};
	small* head;
public:
	Stack() : head(nullptr) {}
	void put(const T& val) {
		small* temp = new small;
		if (!temp)
		{
			std::cerr << "\a\t***Ошибка выделения динамической памяти\n***";
			return;
		}
		temp->val = val;
		temp->last = head;
		this->head = temp;
	}
	T& pop() {
		small* temp = this->head;
		T val = this->head->val;
		this->head = this->head->last;
		delete temp;
		return val;
	}
	const void print() {
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
	~Stack() {
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
	Stack <std::string> stack_1;
	stack_1.put("Hello");
	stack_1.put("World");
	stack_1.put("!");
	stack_1.print();
	stack_1.pop();
	stack_1.print();
	std::cout << std::endl;
	Stack <double> stack_2;
	stack_2.put(21.34556);
	stack_2.put(8765.32);
	stack_2.put(0.0002);
	stack_2.print();
	stack_2.pop();
	stack_2.print();
	return 0;
}
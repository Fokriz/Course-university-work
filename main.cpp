/*
Создать класс «Двунаправленный список», элементами которого являются
экземпляры класса «Товар».
Класс «Товар» включает поля:
	номер магазина,
	название товара,
	цена товара.
Определить название магазина, в котором заданный товар самый дешевый.
*/

#include <iostream>
#include <string.h>
#include <ctime>
#include <cstdlib>

using namespace std;

ostream& operator<<(ostream& os, struct Product& product);

struct Product{
	unsigned short numberOfShop;
	//char *productName = (char *) malloc(sizeof(char));
	char productName[32];
	float price;

	Product(){
		numberOfShop = 0;
		price = 0.0;
	}

	Product(unsigned short number, const char* name, float cost){
		numberOfShop = number;
		//productName = (char *) realloc(productName, (strlen(name)+1)*sizeof(char));
		strcpy(productName, name);
		productName[strlen(name)] = '\0';
		price = cost;
	}

	~Product(){
		//free(productName);
	}

	void setData(unsigned short number, const char* name, float cost){
		numberOfShop = number;
		//productName = (char *) realloc(productName, (strlen(name)+1)*sizeof(char));
		strcpy(productName, name);
		productName[strlen(name)] = '\0';
		price = cost;
	}

	void print(){
		cout << *this;
	}
};

template <class T> struct Node {
	T value;
	Node *next, *prev;
};

template <class T> class DoubleLinkedList {
	Node<T> *head, *tail;
	int count;

public:
	DoubleLinkedList();

	DoubleLinkedList(const DoubleLinkedList<T>& list);

	~DoubleLinkedList();

	int get_count();


	bool isEmpty();

	T at(int pos);

	void clear();

	bool erase(int pos);

	bool insert(int pos, T& value);

	void push_back(T& value);

	void push_front(T& value);

	T pop_back();
	T pop_front();


	void print_all();

	void print(int pos);

	DoubleLinkedList<T>& operator=(const DoubleLinkedList<T>& list);

	DoubleLinkedList<T> operator+(const DoubleLinkedList<T>& list);

	bool operator==(const DoubleLinkedList<T>& list);
	bool operator!=(const DoubleLinkedList<T>& list);
};


template <class T> DoubleLinkedList<T>::DoubleLinkedList() {
	head = tail = nullptr;
	count = 0;
}

template <class T> DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T>& list) {
	Node<T> *tmp;

	head = tail = nullptr;
	count = 0;

	tmp = list.head;

	while (tmp != 0) {
		push_back(tmp->value);
		tmp = tmp->next;
	}
}

template <class T> DoubleLinkedList<T>::~DoubleLinkedList() {
	clear();
}

template <class T> void DoubleLinkedList<T>::push_front(T& value) {
	Node<T> *temp = new Node<T>;

	temp->value = value;
	temp->prev = nullptr;
	temp->next = head;

	if (head)
		head->prev = temp;

	if (!count)
		head = tail = temp;
	else
		head = temp;

	count++;
}

template <class T> void DoubleLinkedList<T>::push_back(T& value) {
	Node<T> *temp = new Node<T>;
	temp->next = nullptr;
	temp->value = value;
	temp->prev = tail;

	if (tail)
		tail->next = temp;

	if (!count)
		head = tail = temp;
	else
		tail = temp;

	count++;
}

template <class T> T DoubleLinkedList<T>::pop_back() {
	T value = at(count - 1);
	erase(count - 1);
	return value;
}

template <class T> T DoubleLinkedList<T>::pop_front() {
	T value = at(0);
	erase(0);
	return value;
}

template <class T> bool DoubleLinkedList<T>::insert(int pos, T& value) {
	Node<T> *tmp, *new_node;

	if (pos < 0 || pos > count) {
		return false;
	}

	if (pos == 0) {
		push_front(value);
	}
	else if (pos == count) {
		push_back(value);
	}
	else {
		tmp = head;
		for (int i = 0; i < pos; i++) {
			tmp = tmp->next;
		}

		new_node = new Node<T>;
		new_node->value = value;
		new_node->next = tmp;
		new_node->prev = tmp->prev;

		tmp->prev->next = new_node;
		tmp->prev = new_node;
		count++;
	}

	return true;
}

template <class T> bool DoubleLinkedList<T>::erase(int pos) {
	Node<T> *prev_prod, *next_prod, *tmp;
	int i = 0;

	if (pos < 0 || pos >= count) {
		return false;
	}

	tmp = head;

	while (i < pos) {
		tmp = tmp->next;
		i++;
	}

	prev_prod = tmp->prev;
	next_prod = tmp->next;

	if (prev_prod != 0 && count != 1)
		prev_prod->next = next_prod;

	if (next_prod != 0 && count != 1)
		next_prod->prev = prev_prod;

	if (pos == 0)
		head = next_prod;
	if (pos == count - 1)
		tail = prev_prod;

	delete tmp;

	count--;
	return true;
}

template <class T> void DoubleLinkedList<T>::print(int pos) {
	Node<T> *temp;
	int i = 0;

	if (pos < 0 || pos >= count) {
		return;
	}

	temp = head;

	while (i < pos) {
		temp = temp->next;
		i++;
	}

	cout << pos << " element:\t";
	temp->value.print();
	cout << endl;
}

template <class T> void DoubleLinkedList<T>::print_all() {
	Node<T> *temp;

	if (count) {
		temp = head;

		while (temp->next) {
			temp->value.print();
			cout << "\n\n";
			temp = temp->next;
		}

		temp->value.print();
		cout << endl;
	}
}

template <class T> void DoubleLinkedList<T>::clear() {
	while (count)
		erase(0);
}

template <class T> int DoubleLinkedList<T>::get_count() {
	return count;
}

template <class T> bool DoubleLinkedList<T>::isEmpty() {
	return !get_count();
}

template <class T> T DoubleLinkedList<T>::at(int pos) {
	Node<T> *temp = head;
	int i = 0;

	if (pos < 0 || pos >= count) {
		return Product();
	}

	while (i < pos && temp) {
		temp = temp->next;
		i++;
	}

	if (!temp)
		return Product();
	else
		return temp->value;
}

template <class T> DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList<T>& list) {
	Node<T> * temp = list.head;

	if (this == &list)
		return *this;

	this->~DoubleLinkedList();

	while (temp != 0)
	{
		push_back(temp->value);
		temp = temp->next;
	}

	return *this;
}

template <class T> DoubleLinkedList<T> DoubleLinkedList<T>::operator+(const DoubleLinkedList& list) {
	Node<T> * temp = list.head;

	DoubleLinkedList result_list(*this);
	// List Result = *this;

	while (temp != 0) {
		result_list.push_back(temp->value);
		temp = temp->next;
	}

	return result_list;
}

template <class T> bool DoubleLinkedList<T>::operator==(const DoubleLinkedList<T>& list) {
	Node<T> *t1, *t2;

	if (count != list.count)
		return false;

	t1 = head;
	t2 = list.head;

	while (t1 != 0) {
		if (t1->value != t2->value)
			return false;

		t1 = t1->next;
		t2 = t2->next;
	}

	return true;
}

template <class T> bool DoubleLinkedList<T>::operator!=(const DoubleLinkedList<T>& list) {
	return !(*this == list);
}

ostream& operator<<(ostream& os, struct Product& product) {
	cout << "\tNumber of shop:\t\t" << product.numberOfShop << "\n\tProduct name:\t\t" << product.productName << "\n\tPrice of product:\t" << product.price;
	return os;
}

int main()
{
	DoubleLinkedList<Product> products;
	Product tmpProduct;
	int shopNumber, choose;
	char name[32];
	float productPrice;
	unsigned short temp;
	bool loop = true, flag;

	srand((unsigned int)time(NULL));

	for (int i = 0; i < 10; i++){
		temp = rand() % 27 + 5;
		for(int j = 0; j < temp; j++)
			name[j] = (char) (rand() % 26 + 65);
		name[temp-1] = '\0';
		tmpProduct.setData(rand() % 1000, name, (float) (rand() % 10000));
		products.push_front(tmpProduct);
	}

	while(loop){
		cout << "Menu:\n";
		cout << "1 - print all list\n";
		cout << "2 - find name of product, where this product is cheapest\n";
		cout << "3 - add product to list\n";
		cout << "4 - remove first order from list\n";
		cout << "5 - check if list is empty\n";
		cout << "6 - get list size\n";
		cout << "0 - exit\n";
		cin >> choose;

		switch(choose){
			case 1:
				products.print_all();
				break;
			case 2:
				cout << "\tEnter the product name:\t";
				scanf("%32s", &name);
				temp = products.get_count();
				flag = false;
				for(int i = 0; i < temp; i++){
					tmpProduct = products.at(i);
					if(!strcmp(name, tmpProduct.productName)){
						if(!flag){
							shopNumber = tmpProduct.numberOfShop;
							productPrice = tmpProduct.price;
							flag = true;
							continue;
						}
						if(productPrice > tmpProduct.price){
							shopNumber = tmpProduct.numberOfShop;
							productPrice = tmpProduct.price;
						}
					}
				}
				cout << "\tProduct " << name;
				if(flag) cout << " is the cheapest in shop number " << shopNumber << " and it's price is: " << productPrice << ".\n";
				else cout << " isn't in list.";
				break;
			case 3:
				cout << "\tEnter the number of shop:\t";
				cin >> shopNumber;
				cout << "\tEnter the name of product:\t";
				scanf("%32s", &name);
				cout << "\tEnter the price of product:\t";
				cin >> productPrice;
				tmpProduct.setData(shopNumber, name, productPrice);
				products.push_front(tmpProduct);
				cout << "\tProduct added to the list.\n";
				break;
			case 4:
				if(!products.isEmpty()){
					products.pop_front();
					cout << "\tFirst product deleted from the list.\n";
				}
				else cout << "\tList is empty!\n";
				break;
			case 5:
				cout << "\tList is ";
				if(!products.isEmpty()) cout << "not ";
				cout << "empty.\n";
				break;
			case 6:
				cout << "\tList size: " << products.get_count() << endl;
				break;
			case 0:
				loop = false;
				break;
			default:
				cout << "\tWarning! Enter the number.\n";
		}
	}
	return 0;
}

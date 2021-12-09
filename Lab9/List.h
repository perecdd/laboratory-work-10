#pragma once
#include <ostream>

int NodeCount = 0;
int ListCount = 0;

template <typename T>
struct Node {
	T value_;
	Node* next_ = nullptr;
	Node* prev_ = nullptr;

	Node(T value);
	~Node();
};

template <typename T>
class ListIt {
public:
	ListIt();
	ListIt(Node<T>* node);
	ListIt(const ListIt<T>& it);
	Node<T>* getPointer() const;
	ListIt operator++();
	ListIt operator++(int);
	ListIt operator--();
	ListIt operator--(int);
	T& operator*() const;
	bool operator==(const ListIt& listIt) const;
	bool operator!=(const ListIt& listIt) const;

private:
	bool endIt = false;
	Node<T>* node_ = nullptr;
};

template <typename T>
class List {
public:

	List(ListIt<T> begin, ListIt<T> end);
	List();
	void push_front(T value);
	void push_back(T value);
	Node<T>* find(T value) const;
	void remove(Node<T>* p);
	T pop_back();
	T pop_front();
	int size() const;

	ListIt<T> begin() const;
	ListIt<T> end() const;
	Node<T>* getMiddle() const;

	template <typename U>
	friend std::ostream& operator<<(std::ostream& stream, const List<U>& list);

	~List();

private:
	int size_ = 0;
	Node<T>* head_ = nullptr;
	Node<T>* tail_ = nullptr;
};

template <typename T>
List<T>* merge(List<T>* l1, List<T>* l2) {
	ListIt<T> itl1 = l1->begin();
	ListIt<T> itl2 = l2->begin();
	List<T>* newList = new List<T>;

	while (itl1 != l1->end() || itl2 != l2->end()) {
		if (itl1 != l1->end() && itl2 != l2->end()) {
			if (*itl1 < *itl2) {
				newList->push_back(*itl1++);
			}
			else {
				newList->push_back(*itl2++);
			}
		}
		else {
			if (itl1 != l1->end()) {
				newList->push_back(*itl1++);
			}
			else {
				newList->push_back(*itl2++);
			}
		}
	}
	return newList;
}

template <typename T>
List<T>* mergeSort(List<T>* lst) {
	if (lst->size() <= 1) {
		return new List<T>(lst->begin(), lst->end());
	}
	if (lst->size() == 2) {
		List<T>* newList = new List<T>(lst->begin(), lst->end());
		auto first = newList->begin();
		auto second = newList->begin();
		second++;

		if (*first > *second) {
			T value = std::move(*first);
			*first = std::move(*second);
			*second = std::move(value);
		}
		return newList;
	}
	List<T>* l1 = new List<T>(lst->begin(), ListIt<T>(lst->getMiddle()));
	List<T>* l2 = new List<T>(ListIt<T>(lst->getMiddle()), lst->end());
	l1 = mergeSort(l1);
	l2 = mergeSort(l2);
	return merge(l1, l2);
}

template <typename T>
List<T>::List(ListIt<T> begin, ListIt<T> end) {
	while (begin != end) {
		push_back(*begin++);
	}
}

template <typename T>
ListIt<T>::ListIt() : node_(nullptr), endIt(true)
{
}

template <typename T>
ListIt<T>::ListIt(Node<T>* node) : node_(node)
{
}

template <typename T>
ListIt<T>::ListIt(const ListIt<T>& it) : node_(it.getPointer())
{
	if (it.endIt == true) {
		endIt = true;
	}
}

template <typename T>
Node<T>* ListIt<T>::getPointer() const
{
	return node_;
}

template <typename T>
ListIt<T> ListIt<T>::operator++() {
	if (node_->next_ == nullptr) {
		endIt = true;
	}
	else {
		node_ = node_->next_;
	}
	return *this;
}

template <typename T>
ListIt<T> ListIt<T>::operator++(int) {
	ListIt listIt(node_);

	if (node_->next_ == nullptr) {
		endIt = true;
	}
	else {
		node_ = node_->next_;
	}

	return listIt;
}

template <typename T>
ListIt<T> ListIt<T>::operator--() {
	if (endIt == true) {
		endIt = false;
	}
	else {
		node_ = node_->prev_;
	}
	return *this;
}

template <typename T>
ListIt<T> ListIt<T>::operator--(int) {
	ListIt listIt(node_);

	if (endIt == true) {
		endIt = false;
	}
	else {
		node_ = node_->prev_;
	}
	return listIt;
}

template <typename T>
T& ListIt<T>::operator*() const {
	if (node_ == nullptr) {
		throw std::runtime_error("Specify iterator points to nullptr");
	}
	if (endIt == true) {
		throw std::runtime_error("Attempt to unlock the end iterator");
	}
	return node_->value_;
}

template <typename T>
bool ListIt<T>::operator==(const ListIt& listIt) const {
	return node_ == listIt.node_ && endIt == listIt.endIt;
}

template <typename T>
bool ListIt<T>::operator!=(const ListIt& listIt) const {
	return node_ != listIt.node_ || endIt != listIt.endIt;
}

template <typename U>
inline std::ostream& operator<<(std::ostream& stream, const List<U>& list)
{
	Node<U>* node = list.head_;
	stream << '[';
	while (node != nullptr) {
		stream << node->value_;
		if (node->next_ != nullptr) {
			stream << ", ";
		}
		node = node->next_;
	}
	stream << ']';
	return stream;
}

template <typename T>
Node<T>::Node(T value) : value_(std::move(value))
{
	NodeCount++;
}

template <typename T>
Node<T>::~Node()
{
	NodeCount--;
}

template<typename T>
List<T>::List() : head_(nullptr), tail_(nullptr)
{
	ListCount++;
}

template<typename T>
void List<T>::push_front(T value)
{
	size_++;
	if (head_ != nullptr) {
		head_->prev_ = new Node<T>(std::move(value));
		head_->prev_->next_ = head_;
		head_ = head_->prev_;
	}
	else {
		head_ = new Node<T>(std::move(value));
		tail_ = head_;
	}
}

template<typename T>
void List<T>::push_back(T value)
{
	size_++;
	if (tail_ != nullptr) {
		tail_->next_ = new Node<T>(std::move(value));
		tail_->next_->prev_ = tail_;
		tail_ = tail_->next_;
	}
	else {
		tail_ = new Node<T>(std::move(value));
		head_ = tail_;
	}
}

template<typename T>
Node<T>* List<T>::find(T value) const
{
	Node<T>* node = head_;
	while (node != nullptr && node->value_ != value) {
		node = node->next_;
	}
	return node;
}

template<typename T>
void List<T>::remove(Node<T>* p)
{
	if (p == nullptr) {
		return;
	}

	if (p->next_ != nullptr) {
		p->next_->prev_ = p->prev_;
	}
	if (p->prev_ != nullptr) {
		p->prev_->next_ = p->next_;
	}

	if (p == head_) {
		head_ = p->next_;

		if (head_ != nullptr) {
			head_->prev_ = nullptr;
		}
		else {
			tail_ = nullptr;
		}
	}
	else if (p == tail_) {
		tail_ = p->prev_;

		if (tail_ != nullptr) {
			tail_->next_ = nullptr;
		}
		else {
			head_ = nullptr;
		}
	}
	delete p;
	size_--;
}

template<typename T>
T List<T>::pop_back()
{
	if (tail_ == nullptr) {
		throw std::runtime_error("Empty list");
	}
	T value = std::move(tail_->value_);
	remove(tail_);
	return value;
}

template<typename T>
T List<T>::pop_front()
{
	if (head_ == nullptr) {
		throw std::runtime_error("Empty list");
	}
	T value = std::move(head_->value_);
	remove(head_);
	return value;
}

template<typename T>
inline int List<T>::size() const
{
	return size_;
}

template<typename T>
inline ListIt<T> List<T>::begin() const
{
	if (head_ == nullptr) {
		return ListIt<T>();
	}
	else {
		return ListIt<T>(head_);
	}
}

template<typename T>
inline ListIt<T> List<T>::end() const
{
	if (tail_ == nullptr) {
		return ListIt<T>();
	}
	else {
		return ++ListIt<T>(tail_);
	}
}

template<typename T>
inline Node<T>* List<T>::getMiddle() const
{
	Node<T>* node = head_;
	for (int i = (size_ + 1) / 2; i > 1; --i) {
		node = node->next_;
	}
	return node;
}

template<typename T>
inline List<T>::~List()
{
	while (head_ != nullptr) {
		Node<T>* p = head_;
		head_ = head_->next_;
		delete p;
	}
	ListCount--;
}

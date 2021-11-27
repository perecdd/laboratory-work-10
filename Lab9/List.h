#pragma once
#include <ostream>

template <typename T>
struct Node {
	T value_;
	Node* next_ = nullptr;
	Node* prev_ = nullptr;

	Node(T value);
};

template <typename T>
class List {
public:
	List();
	void push_front(T value);
	void push_back(T value);
	Node<T>* find(T value);
	void remove(Node<T>* p);
	T pop_back();
	T pop_front();

	template <typename U>
	friend std::ostream& operator<<(std::ostream& stream, const List<U>& list);

	~List();

private:
	Node<T>* head_ = nullptr;
	Node<T>* tail_ = nullptr;
};

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
Node<T>::Node(T value) : value_(value)
{
}

template<typename T>
List<T>::List() : head_(nullptr), tail_(nullptr)
{
}

template<typename T>
void List<T>::push_front(T value)
{
	if (head_ != nullptr) {
		head_->prev_ = new Node<T>(value);
		head_->prev_->next_ = head_;
		head_ = head_->prev_;
	}
	else {
		head_ = new Node<T>(value);
		tail_ = head_;
	}
}

template<typename T>
void List<T>::push_back(T value)
{
	if (tail_ != nullptr) {
		tail_->next_ = new Node<T>(value);
		tail_->next_->prev_ = tail_;
		tail_ = tail_->next_;
	}
	else {
		tail_ = new Node<T>(value);
		head_ = tail_;
	}
}

template<typename T>
Node<T>* List<T>::find(T value)
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
inline List<T>::~List()
{
	while (head_ != nullptr) {
		Node<T>* p = head_;
		head_ = head_->next_;
		delete p;
	}
}

template<typename Node>
class IteratorV final {
	Node* _node;
public:
	 IteratorV() :_node(nullptr) {}
	 IteratorV(const IteratorV<Node>& iterator) :_node(iterator._node) {}
	 IteratorV(Node* const node) :_node(node) {}

	IteratorV<Node> operator++() {
		_node++;
		return *this;
	}
	IteratorV<Node> operator--() {
		_node--;
		return *this;
	}
	IteratorV<Node> operator++(int) {
		IteratorV<Node> prev(*this);
		_node++;
		return prev;
	}
	IteratorV<Node> operator--(int) {
		Iterator next(*this);
		_node--;
		return next;
	}

	Node& operator*() {
		return *_node;
	}

	bool operator==(const IteratorV<Node>& iterator)  {
		return _node == iterator._node;
	}
	bool operator!=(const IteratorV<Node>& iterator)  {
		return _node != iterator._node;
	}
	bool operator==(std::nullptr_t null)  {
		return _node == nullptr;
	}
	bool operator!=(std::nullptr_t null)  {
		return !(this == nullptr);
	}

	bool operator<(const IteratorV<Node>& iterator) {
		return _node < iterator._node;
	}
	bool operator>(const IteratorV<Node>& iterator) {
		return !(_node < iterator._node || _node == iterator._node);
	}
};

template<typename Node>
IteratorV<Node> operator+(const IteratorV<Node>& iterator, const int ind) {
	Iterator iter(iterator);
	iter += ind;
	return iter;
}
template<typename Node>
IteratorV<Node> operator+=(const IteratorV<Node>& iterator, const int ind) {
	IteratorV iter(iterator);
	if (!&iterator) return iter;
	for (auto i = 0; i < ind; ++i) {
		iter++;

	}
	return iter;
}


template<typename Node>
class Vector {
	Node* _ptr;
	size_t _size;

public:
	 Vector() :_ptr(nullptr), _size(0) {}
	 Vector( Node* const vector, const int size) :_ptr(vector), _size(size) {}
	 Vector(const int size)  {
		_size = size;
		_ptr = new Node[_size];
	}

	~Vector() {
		delete _ptr;
		_ptr = nullptr;
		_size = 0;
	}

	Vector(const Vector<Node>& vector) :_ptr(new Node[vector._size]), _size(vector._size) {
		for (int i = 0; i < _size; ++i) {
			_ptr[i] = vector._ptr[i];
		}
	}
	Vector<Node>& operator=(const Vector<Node>& vector) {
		if (this == &vector) return *this;
		if (_ptr) delete _ptr;
		_ptr = new Node[vector._size];
		_size = vector._size;
		for (int i = 0; i < _size; ++i) {
			_ptr[i] = vector._ptr[i];
		}
		return *this;
	}

	Vector(Vector<Node>&& tvector) :_ptr(tvector._ptr), _size(tvector._size) {
		tvector._ptr = nullptr;
		tvector._size = 0;
	}
	Vector<Node>& operator=(Vector<Node>&& tvector) {
		if (_ptr) delete _ptr;
		_ptr = tvector._ptr;
		_size = tvector._size;
		tvector._ptr = nullptr;
		tvector._size = 0;
	}



	Node& at(const int ind) {
		if (ind >= _size || ind < 0) throw"Ошибка доступа к элементу";
	}
	Node& at(const int ind)const {
		if (ind >= _size || ind < 0) throw"Ошибка доступа к элементу";
	}

	Node& operator[](const int ind) {
		return _ptr[ind];
	}

	Node& front() {
		return _ptr[0];
	}
	
	
	Node& back() {
		return _ptr[_size - 1];
	}
	

	Node* data() {
		if(_ptr) return &front;
	}



	IteratorV<Node> begin()const noexcept {
		return IteratorV<Node>(_ptr);
	}

	IteratorV<Node> end()const noexcept{
		return IteratorV<Node>(_ptr+_size);
	}



	bool empty() noexcept {
		if (begin() == end()) return true;
		else return false;
	}

	size_t size()noexcept {
		return _size;

	}

	void reserve(const size_t size) {
		if (size < 0) throw"Ошибка определения размера массива";
		_size = size;
	}



	void clear()noexcept {
		delete _ptr;
		_ptr = nullptr;
		_size = 0;
	}

	IteratorV<Node> insert(IteratorV<Node>& iterator, const Node& node) {
		IteratorV<Node>iter(iterator);
		if (iterator > end() || iterator < begin()) throw"Ошибка вставки";
		Vector res(new Node[_size + 1], (int)_size + 1);
		IteratorV<Node> counter = begin();
		int index = 0;
		for(; counter != iter; ++counter)
		{
			++index;
		}

		int counterInt = 0;
		for (auto i = 0; i < _size + 1; ++i) {
			if (i != index) {
				res[i] = _ptr[counterInt];
				counterInt++;
			}
			else
				res[i] = node;
		}
		*this = res;
		iterator = begin() += index;
		return iterator;
	}

	IteratorV<Node> erase(IteratorV<Node>& iterator) {
		if (begin() == end()) throw "Ошибка удаления элемента";
		Vector<Node> res(new Node[_size - 1], (int)_size - 1);
		IteratorV<Node> counter=begin();

		int index = 0;
		for (int i = 0; counter != iterator; ++i)
		{
			++counter;
			++index;
		}

		int counterInt = 0;
		for (auto i = 0; i < _size - 1; ++i) {
			if (counterInt != index) {
				res[i] = _ptr[counterInt];
				counterInt++;
			}
			else
			{
				counterInt++;
				i--;
			}
		}
		*this = res;
		if ((begin() += index) < end())
			iterator = (begin() += index);
		else
			iterator = --(end());
		return iterator;
	}
};

template<typename Node>
bool operator==(const Vector<Node> vector1, const Vector<Node> vector2) {
	if (vector1._size = !vector2._size) return false;
	Iterator iterator1(vector1.begin());
	Iterator iterator2(vector2.begin());
	while (iterator1 != vector1.end()) {
		if (iterator1 != iterator2) return false;
		else {
			iterator1++;
			iterator2++;

		}
	}
	return true;
}

template<typename Node>
bool operator!=(const Vector<Node> vector1, const Vector<Node> vector2) {
	return !(vector1==vector2);
}

template<typename Node>
bool operator>(const Vector<Node> vector1, const Vector<Node> vector2) {
	if (vector1._size > vector2._size) {
		Iterator start(vector1.begin());
		Iterator finish(vector1.end());
	}
	else {
		Iterator start(vector2.begin());
		Iterator finish(vector2.end());
	}
	Iterator iterator1(vector1.begin());
	Iterator iterator2(vector2.begin());
	while (start != finish) {
		if (iterator1 > iterator2) return true;
		iterator1++;
		iterator2++;
	}
	return false;
}

template<typename Node>
bool operator<(const Vector<Node> vector1, const Vector<Node> vector2) {
	return !(vector1 > vector2);
}

template<typename Node>
bool operator>=(const Vector<Node> vector1, const Vector<Node> vector2) {
	return (vector1 > vector2 || vector1 == vector2);
}

template<typename Node>
bool operator<=(const Vector<Node> vector1, const Vector<Node> vector2) {
	return (vector1 < vector2 || vector1 == vector2);
}
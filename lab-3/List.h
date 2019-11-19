template<typename T>
class Node {
public:
	T _data;
	Node* _prev;
	Node* _next;
	Node() :_data(0), _prev(nullptr), _next(nullptr) {}
	Node(T* const data) :_data(*data), _prev(nullptr), _next(nullptr) {}
};

template<typename T>
class IteratorL final {
	Node<T>* _node;
public:
	
	IteratorL() :_node(nullptr) {}
	IteratorL(const IteratorL& iterator) :_node(iterator._node) {}
	IteratorL(Node<T>* const node) :_node(node) {}

	IteratorL& operator++() {
		_node = _node->_next;
		return *this;
	}
	IteratorL& operator--() {
		_node = _node->_prev;
		return *this;
	}

	IteratorL& operator++(int) {
		IteratorL next(*this);
		_node = _node._next;
		return *next;
	}
	IteratorL& operator--(int) {
		IteratorL prev(*this);
		_node = _node._prev;
		return *prev;

	}

	T& operator*()  {
		return _node->_data;
	}

	Node<T>* operator&()  {
		return _node;
	}

	bool operator==( IteratorL<T>& const iterator) {
		return _node == iterator._node;
	}
	bool operator!=(const IteratorL<T>& iterator){
		return _node != iterator._node;
	}
	bool operator<(const IteratorL<T>& iterator) {
		return _node < iterator._node;
	}
	bool operator>(const IteratorL<T>& iterator) {
		return _node > iterator._node;
	}

	bool operator==(std::nullptr_t null) {
		return _node == nullptr;
	}
	bool operator!=(std::nullptr_t null) {
		return _node != nullptr;
	}
};

template<typename T>
IteratorL<T> operator+(IteratorL<T>& iterator, const int num) {
	IteratorL<T> res(iterator);
	return res += num;
}

template<typename T>
IteratorL<T>& operator+=(IteratorL<T>& iterator, const int num) {
	if (iterator == nullptr) {
		return iterator;
	}
	for (auto i = 0; i < num; ++i)
	{
		iterator++;
	}
	return iterator;
}

template<typename T>
class List {
	Node<T>* _ptr;
	size_t _size;
public:

	List<T>() : _ptr(nullptr), _size(0) {}

	List<T>(Node<T>* ptr, size_t size) : _ptr(ptr), _size(size) {
		Node<T>* start = _ptr;
		_ptr = new Node;
		_ptr->_prev = nullptr;
		_ptr->_data = ptr->_data;
		ptr = ptr->next;
		while (ptr)
		{
			_ptr->next = new Node<T>;
			auto tmp = _ptr;
			_ptr = _ptr->_next;
			_ptr->_prev = tmp;
			_ptr->_data = ptr->_data;
			ptr = ptr->_next;
		}
		_ptr->next = nullptr;
		_ptr = start;
	}

	List<T>(std::nullptr_t) : _ptr(nullptr), _size(0) {}

	List<T>(const size_t size) : _size(size) {
		
		_ptr = new Node<T>;
		Node<T>* start = _ptr;
		auto tmp = _ptr;
		_ptr->_prev = nullptr;
		for (auto i = 0; i < size; ++i)
		{
			_ptr->_next = new Node<T>;
			_ptr = _ptr->_next;
			_ptr->_prev = tmp;
			tmp = _ptr;
		}
		_ptr->_next = nullptr;
		_ptr = start;
	}

	~List() {
		if (_ptr) {
			Node<T>* tmp;
			while (_ptr)
			{
				tmp = _ptr->_next;
				delete _ptr;
				_ptr = tmp;
			}

		}

		_ptr = nullptr;
		_size = 0;

	}

	
	List<T>(List& oldList) : _size(oldList._size) {
		IteratorL<T> iterator = oldList.begin();

		if (oldList._size > 1)
		{
			_ptr = new Node<T>;
			Node<T>* start = _ptr;
			_ptr->_data = *iterator;
			_ptr->_data = *iterator;
			_ptr->_prev = nullptr;

			Node<T>* tmp;
			++iterator;
			for (; iterator != oldList.end(); ++iterator)
			{
				tmp = _ptr;
				_ptr->_next = new Node<T>;
				
				_ptr = _ptr->_next;
				_ptr->_data=*iterator;
				_ptr->_data = *iterator;
				_ptr->_prev = tmp;
			}
			_ptr->_next = nullptr;
			_ptr = start;
		}
		else
		{
			if (oldList._size == 1)
			{
				_ptr = new Node<T>;
				_ptr->_data = *iterator;
				_ptr->_data = *iterator;
				_ptr->_prev = nullptr;
				_ptr->_next = nullptr;
			}
			else
				_ptr = nullptr;
		}

	}

	
	List<T>& operator=(const List<T>& list) {
		if (this == list) {
			return *this;
		}

		clear();

		if (list._size >= 1)
		{
			IteratorL<T> iterator = list.begin();

			_ptr = new Node<T>;
			_ptr->_data = *iterator._node->_data;
			_ptr->_prev = nullptr;

			Node<T>* tmp;
			++iterator;
			for (; iterator != list.end(); ++iterator)
			{
				tmp = _ptr;
				_ptr->_next = new Node<T>;
				_ptr = _ptr->_next;
				_ptr->_data = *iterator._node->_data;
				_ptr->_prev = tmp;
			}
			_ptr->_next = nullptr;
		}
		else
		{
			_ptr = nullptr;
		}


		_size = list._size;

		return *this;
	}

	
	List<T>(List<T>&& oldList) noexcept : _ptr(&(oldList.begin())), _size(oldList._size) {
		oldList._ptr = nullptr;
		oldList._size = 0;
	}

	
	List<T>& operator=(List<T>&& list) {
		if (*this == list)
		{
			return *this;
		}
		clear();
		_ptr = &(list.begin());
		_size = list._size;
		list._ptr = nullptr;
		list._size = 0;
		return *this;
	}


	T& front() {
		if (!_ptr) throw"Ошибка, список пуст";
		return _ptr->_data;
	}

	T& back() {
		if (!_ptr) throw"Ошибка, список пуст";	
		auto res = _ptr + _size;
		--res;
		return res->_data;
	}

	IteratorL<T> begin(){
		if (!_ptr) return IteratorL<T>(nullptr);
		return IteratorL<T>(_ptr);
	}
	IteratorL<T> end() {
		if (!_ptr) return IteratorL<T>(nullptr);
		Node<T>* tmp = _ptr;
		while (tmp != nullptr)
		tmp = tmp->_next;
		return IteratorL<T>(tmp);
	}

	bool empty() {
		return end() == begin();
	}

	size_t size() const {
		return _size;
	}

	void clear() noexcept {
		delete this;
	}

	IteratorL<T> insert(IteratorL<T>& const iterator, T& const node) {
		++_size;
		if (!_ptr) {
			_ptr = new Node<T>(&node);
			_ptr->_next = nullptr;
			_ptr->_prev = nullptr;
			return _ptr;
		}
		else {
			IteratorL<T> iter(begin());
			auto res = new Node<T>(&node);
			while (iter != end()) {
				if (iter == iterator) {
					Node<T>* next = &--iterator;
					Node<T>* prev = &++iterator;
					prev->_next = res;
					next->_prev = res;
					res->_prev = prev;
					res->_next = next;
					return IteratorL<T>(res);
				}
				else {
					++iter;
				}
			}
			throw"Ошибка вствки";
		}
	}

	IteratorL<T> erase(IteratorL<T>& const iterator) {
		if (!_ptr) throw"Ошибка удаления элемента";
		--_size;
		if (_ptr->_next == nullptr&&_ptr->_prev == nullptr) {
			delete _ptr;
			return _ptr;
		}
		IteratorL<T> iter(begin());
		Node<T>* tmp;
		while (iter != iterator) {
			if (iter == iterator) {

				Node<T>* next = &--iterator;
				Node<T>* prev = &++iterator;
				prev->_next = next;
				next->_prev = prev;
				return IteratorL<T>(next);
				/*tmp = &iter->_prev;
				auto next = &iter->_next;
				next._prev = tmp;
				tmp._next = next;
				IteratorL<T> res(&next);
				return res;*/
			}
			else {
				++iter;
			}
		}
		throw"Ошибка удаления элемента";
	}
};

template<typename T>
bool operator==(const List<T>& list1, const List<T>& list2) {
	if (list1._size != list2._size) return false;
	else {
		IteratorL count1(list1.begin());
		IteratorL count2(list2.begin())
			while (IteratorL count1(list1.begin()) != list1.end()) {
				if (count1 != count2) return false;
				++count1;
				++count2;
			}
		return true;
	}

}

template<typename T>
bool operator!=(const List<T>& list1, const List<T>& list2) {
	return !(list1 == list2);
}

template<typename T>
bool operator<(const List<T>& list1, const List<T>& list2) {
	if (list1._size > list2._size) {
		IteratorL start(list1.begin());
		IteratorL finish(list1.end());
	}
	else {
		IteratorL start(list2.begin());
		IteratorL finish(list2.end());
	}
	IteratorL count1(list1.begin());
	IteratorL count2(list2.begin())	
		while (start!=finish) {
			if (count1 < count2) return true;
			++count1;
			++count2;
		}
	return false;
	}

template<typename T>
bool operator>(const List<T>& list1, const List<T>& list2) {
	return !(list1==list2||list1>list2);
}

template<typename T>
bool operator<=(const List<T>& list1, const List<T>& list2) {
	return !(list1>list2);
}

template<typename T>
bool operator>=(const List<T>& list1, const List<T>& list2) {
	return !(list1 < list2);
}
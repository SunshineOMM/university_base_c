
template<typename T>
class SharedPtr {
	T* _ptr;
	size_t* _num; 
public:
	SharedPtr() :_ptr(nullptr), _num(new size_t(0)) {}
	explicit SharedPtr(T * const ptr) :_ptr(ptr), _num(new size_t(1)) {}
	~SharedPtr() {
		if (*_num == 1&&_ptr) {
			delete _num;
		}
		(*_num)--;
		_ptr = nullptr;
	}
	SharedPtr(const SharedPtr& sptr) :_ptr(sptr._ptr), _num(sptr._num) {
		(*_num)++;
	}
	SharedPtr& operator=(const SharedPtr& sptr) {
		if (*_num) {
			delete _ptr;
		}
		_ptr = sptr._ptr;
		_num = sptr._num;
		(*_num)++;
		return *this;
	}
	explicit SharedPtr(SharedPtr&& sptr)  noexcept :_ptr(sptr._ptr), _num(sptr._num) {
		sptr._str = nullptr;
	}
	SharedPtr& operator=(SharedPtr&& sptr)noexcept {
		if (*_num) {
			delete _ptr;
		}
		_ptr = sptr._ptr;
		_num = sptr._num;
		sptr._ptr = nullptr;
		return *this;
	}
	explicit constexpr SharedPtr(std::nullptr_t null) : _ptr(nullptr), _count(new size_t(0)) {} 
	SharedPtr& operator=(std::nullptr_t null) noexcept {
		delete _ptr;
		_ptr = nullptr;
		return *this;
	}

	int use_count()const {
		return *_num;
	}
	void reset(const T* ptr = nullptr) {
		if (_ptr != nullptr) {
			delete _ptr;
		}
		_ptr = ptr;
		_num = new int(1);
		//Если на ptr уже кто-то указывал, то неопределённое поведение
	}
	void swap(SharedPtr& sptr) {
		T* bailer = _ptr;
		int* bailerInt = _num;
		_ptr = sptr._ptr;
		sptr._ptr = bailer;
		_num = sptr._num;
		sptr._num = bailerInt;
	}
	T* get()const {
		return _ptr;
	}
	explicit operator bool()const {
		if (_ptr) return true;
		else return false;
	}
	T& operator*() {
		return *_ptr;
	}
	T& operator*() const {
		return *_ptr;
	}
	T* operator->() {
		return _ptr;
	}

};

template<typename T>
bool operator==(const SharedPtr<T>& sptr1, const SharedPtr<T>& sptr2) {
	if (sptr1.get() == sptr2.get()) return true;
	else return false;
}
template<typename T>
bool operator!=(const SharedPtr<T>& sptr1, const SharedPtr<T>& sptr2) {
	return !(sptr1 == sptr2);
}
template<typename T>
bool operator<(const SharedPtr<T>& sptr1, const SharedPtr<T>& sptr2) {
	if (sptr1.get() < sptr2.get()) return true;
	return false;
}
template<typename T>
bool operator>(const SharedPtr<T>& sptr1, const SharedPtr<T>& sptr2) {
	return !(sptr1 < sptr2);
}
template<typename T>
bool operator<=(const SharedPtr<T>& sptr1, const SharedPtr<T>& sptr2) {
	if (sptr1 == sptr2 || sptr1 < sptr2) return true;
	return false;
}
template<typename T>
bool operator>=(const SharedPtr<T>& sptr1, const SharedPtr<T>& sptr2) {
	return !(sptr1 >= sptr2);
}

template<typename T>
bool operator==(std::nullptr_t null, const SharedPtr<T>& sptr) {
	return !sptr;
}
template<typename T>
bool operator==(const SharedPtr<T>& sptr, std::nullptr_t null) {
	return !sptr;
}
template<typename T>
bool operator!=(std::nullptr_t null, const SharedPtr<T>& sptr) {
	return (bool)sptr;
}
template<typename T>
bool operator!=(const SharedPtr<T>& sptr, std::nullptr_t null) {
	return (bool)sptr;
}
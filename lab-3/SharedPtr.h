
template<typename T>
class SharedPtr {
	T* _ptr;
	int* _num;
public:
	SharedPtr():_ptr(nullptr), _num(new int(0)){}
	explicit SharedPtr(T * const ptr):_ptr(ptr),_num(new int (1)) {}
	~SharedPtr() {
		if (*_num == 1) { 
			delete _ptr; 
		}
		 *_num--;
	}
	SharedPtr(const SharedPtr& sptr):_ptr(sptr._ptr), _num(sptr._num) {
		*_num++;
	}
	SharedPtr& operator=(const SharedPtr& sptr){
		if (*_num) {
			delete _ptr;
		}
		_ptr = sptr._ptr;
		_num=sptr._num;
		*_num++;
		return *this;
	}
	SharedPtr(SharedPtr&& sptr)noexcept {
		_ptr = sptr._ptr;
		_num = sptr._num;
		*_num++;

	}
	SharedPtr& operator=(SharedPtr&& sptr)noexcept {
		if (*_num) {
			delete _ptr;
		}
		_ptr = sptr._ptr;
		_num = sptr._num;
		*_num++;
		return *this;

	}

	int use_count() {
		return *_num;

	}
	void reset(T* ptr=nullptr) {
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
	operator bool() {
		if (_ptr) return true;
		else return false;
	}
	T& operator*() {
		return *_ptr;
	}
	T& operator->() {
		return _ptr;
	}

};

template<typename T>
bool operator==(const UniquePtr<T>& uptr1, const UniquePtr<T>& uptr2) {
	if (uptr1.get() == uptr2.get()) return true;
	else return false;
}
template<typename T>
bool operator!=(const UniquePtr<T>& uptr1, const UniquePtr<T>& uptr2) {
	return !(uptr1 == uptr2);
}
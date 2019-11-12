template<typename T>
class UniquePtr {
	T* _ptr;
public:
	UniquePtr() : _ptr(nullptr) {}
	explicit UniquePtr(T* const ptr) : _ptr(ptr) {}
	UniquePtr(const UniquePtr& uptr) = delete;
	UniquePtr& operator =(const UniquePtr& ptr) = delete;
	~UniquePtr() {
		delete _ptr;
		*this = nullptr;
	}
	UniquePtr(UniquePtr&& uptr)noexcept {
		_ptr = uptr._ptr;
		uptr._ptr = nullptr;
	}
	UniquePtr& operator =(UniquePtr&& uptr)noexcept{
		if (this != &uptr) {
			_ptr = uptr._ptr;
			uptr._ptr = nullptr;
		}
		return *this;
	}



	T* release() {
		if (_ptr == nullptr) return nullptr;
		T* res;
		res = _ptr;
		_ptr = nullptr;
		//*this = nullptr;
		return res;
	}
	void reset(T* ptr=nullptr) {
		T* old = _ptr;
		_ptr = ptr;
		if (old != nullptr) {
			delete _ptr;
		}
	}
	void swap(UniquePtr& uptr) {
		T* bailer = _ptr;
		_ptr = uptr._ptr;
		uptr._ptr = bailer;
	}
	T* get() {
		return _ptr;
	}
	operator bool() {
		if (_ptr) return true;
		else return false;

	}
	T& operator*() {
		return _ptr;// убрал *
	}
	T& operator->() {
		return _ptr;
	}
};

bool operator==(const UniquePtr& uptr1,UniquePtr& uptr2) {
	if (uptr1._ptr == uptr2._ptr) return true;
	else return false;
}
bool operator!=(const UniquePtr& uptr1,const UniquePtr& uptr2) {
	return !(uptr1==uptr2);
}
//bool operator<(UniquePtr& uptr1, UniquePtr& uptr2) {
//	if (uptr1._ptr == uptr2._ptr) return true;
//	else return false;
//}
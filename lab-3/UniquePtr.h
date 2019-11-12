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
		//this = nullptr;
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
		if (_ptr != nullptr) {
			delete _ptr;
		}
		_ptr = ptr;
	}
	void swap(UniquePtr& uptr) {
		T* bailer = _ptr;
		_ptr = uptr._ptr;
		uptr._ptr = bailer;
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
bool operator!=(const UniquePtr<T>& uptr1,const UniquePtr<T>& uptr2) {
	return !(uptr1==uptr2);
}
//bool operator<(UniquePtr& uptr1, UniquePtr& uptr2) {
//	if (uptr1._ptr == uptr2._ptr) return true;
//	else return false;
//}
template<typename T>
class UniquePtr {
	T* _ptr;
public:
	UniquePtr() : _ptr(nullptr) {}
	explicit UniquePtr(T* const ptr) : _ptr(ptr) {}
	~UniquePtr() {
		delete _ptr;
		_ptr = nullptr;
	}
	UniquePtr(const UniquePtr& uptr) = delete;
	UniquePtr& operator =(const UniquePtr& ptr) = delete;
	explicit UniquePtr(UniquePtr&& uptr)noexcept :_ptr(uptr._ptr) {
		uptr._ptr = nullptr;
	}
	UniquePtr& operator =(UniquePtr&& uptr)noexcept {
		delete _ptr;
		_ptr = uptr._ptr;
		uptr._ptr = nullptr;
		return *this;
	}
	explicit constexpr UniquePtr(std::nullptr_t null) : _ptr(null) {}
	UniquePtr& operator=(std::nullptr_t null) noexcept { 
		delete _ptr;
		_ptr = null;
		return *this;
	}


	T* release() {
		if (_ptr == nullptr) return nullptr;
		T* res;
		res = _ptr;
		_ptr = nullptr;
		return res;
	}
	void reset(const T* ptr = nullptr) {
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
	//
	explicit operator bool()const {
		if (_ptr) return true;
		else return false;
	}//

	T& operator*() {
		return *_ptr;
	}
	T& operator*()const {
		return *_ptr;
	}
	T* operator->()const {// почему конст
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
template<typename T>
bool operator<(const UniquePtr<T>& uptr1, const UniquePtr<T>& uptr2) {
	if (uptr1.get() < uptr2.get()) return true;
	return false;
}
template<typename T>
bool operator>(const UniquePtr<T>& uptr1, const UniquePtr<T>& uptr2) {
	return !(uptr1 < uptr2);
}
template<typename T>
bool operator<=(const UniquePtr<T>& uptr1, const UniquePtr<T>& uptr2) {
	if (uptr1 == uptr2 || uptr1 < uptr2) return true;
	return false;
}
template<typename T>
bool operator>=(const UniquePtr<T>& uptr1, const UniquePtr<T>& uptr2) {
	return !(uptr1 >= uptr2);
}

template<typename T>
bool operator==(std::nullptr_t null, const UniquePtr<T>& uptr) {
	return !uptr;
}
template<typename T>
bool operator==(const UniquePtr<T>& uptr, std::nullptr_t null) {
	return !uptr;
}
template<typename T>
bool operator!=(std::nullptr_t null, const UniquePtr<T>& uptr) {
	return (bool)uptr;
}
template<typename T>
bool operator!=(const UniquePtr<T>& uptr, std::nullptr_t null) {
	return (bool)uptr;
}
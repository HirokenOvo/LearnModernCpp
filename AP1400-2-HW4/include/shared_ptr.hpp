
#include "shared_ptr.h"

template <typename T>
SharedPtr<T>::SharedPtr()
{
  this->_p = nullptr;
  this->cnt = new int{0};
}

template <typename T>
SharedPtr<T>::SharedPtr(T *_p)
{
  this->_p = _p;
  this->cnt = new int{1};
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &_p) : _p{_p._p}, cnt{_p.cnt}
{
  (*cnt)++;
}

template <typename T>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &_p)
{
  if (this != &_p)
  {
    this->_p = _p._p;
    this->cnt = _p.cnt;
    (*cnt)++;
  }
  return *this;
}
template <typename T>
SharedPtr<T>::~SharedPtr()
{
  (*cnt)--;
  if (!(*cnt))
  {
    delete this->_p;
    this->_p = nullptr;
  }
}

template <typename T>
T *SharedPtr<T>::get() { return _p; }

template <typename T>
T &SharedPtr<T>::operator*() { return *_p; }

template <typename T>
T *SharedPtr<T>::operator->() { return _p; }

template <typename T>
void SharedPtr<T>::reset()
{
  (*cnt)--;
  delete this->_p;
  this->_p = nullptr;
}

template <typename T>
void SharedPtr<T>::reset(T *_p)
{
  delete this->_p;
  this->_p = _p;
  (*cnt) = 1;
}

template <typename T>
int SharedPtr<T>::use_count() { return *cnt; }

template <typename T>
SharedPtr<T>::operator bool() const
{
  return this->_p != nullptr;
}

template <typename T, typename... _Args>
SharedPtr<T> make_shared(_Args &&..._args)
{
  return SharedPtr<T>{new T(std::forward<_Args>(_args)...)};
}
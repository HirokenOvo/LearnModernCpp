
#include "unique_ptr.h"

template <typename T>
UniquePtr<T>::UniquePtr() { this->_p = nullptr; }
template <typename T>
UniquePtr<T>::UniquePtr(T *_p) { this->_p = _p; }

template <typename T>
UniquePtr<T>::~UniquePtr()
{
  if (this->_p)
  {
    delete this->_p;
    this->_p = nullptr;
  }
}

template <typename T>
T *UniquePtr<T>::get() { return _p; }

template <typename T>
T &UniquePtr<T>::operator*() { return *_p; }

template <typename T>
T *UniquePtr<T>::operator->() { return _p; }

template <typename T>
void UniquePtr<T>::reset()
{
  delete this->_p;
  this->_p = nullptr;
}

template <typename T>
void UniquePtr<T>::reset(T *_p)
{
  delete this->_p;
  this->_p = _p;
}

template <typename T>
T *UniquePtr<T>::release()
{
  T *ans{this->_p};
  this->_p = nullptr;
  return ans;
}

template <typename T>
UniquePtr<T>::operator bool() const
{
  return this->_p != nullptr;
}

template <typename T, typename... _Args>
UniquePtr<T> make_unique(_Args &&..._args)
{
  return UniquePtr<T>{new T(std::forward<_Args>(_args)...)};
}
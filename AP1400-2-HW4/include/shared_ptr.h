#ifndef SHARED_PTR
#define SHARED_PTR
#include <memory>
#include <utility>
template <typename T>
class SharedPtr
{
public:
  SharedPtr();
  SharedPtr(T *_p);
  SharedPtr(const SharedPtr<T> &_p);
  SharedPtr<T> &operator=(const SharedPtr<T> &_p);
  ~SharedPtr();

  T *get();
  T &operator*();
  T *operator->();
  void reset();
  void reset(T *_p);
  int use_count();
  operator bool() const;

private:
  T *_p;
  int *cnt;
};

template <typename T, typename... _Args>
SharedPtr<T> make_shared(_Args &&..._args);

#endif // SHARED_PTR
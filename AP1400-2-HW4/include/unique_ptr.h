#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <memory>
#include <utility>

template <typename T>
class UniquePtr
{
public:
  UniquePtr();
  UniquePtr(T *_p);
  UniquePtr(const UniquePtr<T> &_p) = delete;
  UniquePtr<T> &operator=(const UniquePtr<T> &_p) = delete;
  ~UniquePtr();

  T *get();
  T &operator*();
  T *operator->();
  void reset();
  void reset(T *_p);
  T *release();
  operator bool() const;

private:
  T *_p;
};

template <typename T, typename... _Args>
UniquePtr<T> make_unique(_Args &&..._args);

#endif // UNIQUE_PTR
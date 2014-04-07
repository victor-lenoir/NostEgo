#ifndef MEMORY_MANAGER_HH_
# define MEMORY_MANAGER_HH_

# include <string>
# include <map>

template <class T>
class MemoryManager
{
public:
  ~MemoryManager();

  bool isset (const char* path);
  bool get (const char* path, T*& ptr);
  void free (T* element);
private:
  std::map<std::string, std::pair<size_t, T*> > elements;
};

# include "memory_manager.hxx"

#endif

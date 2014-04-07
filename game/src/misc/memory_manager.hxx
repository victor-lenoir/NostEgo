#include <iostream>

template <class T>
bool MemoryManager<T>::isset (const char* path)
{
  return (elements.find (path) != elements.end ());
}

template <class T>
bool MemoryManager<T>::get (const char* path, T*& ptr)
{
  if (isset(path))
    {
      elements.find (path)->second.first++;
      ptr = elements.find (path)->second.second;
      return true;
    }
  else
    {
      ptr = new sf::Image;
      elements.insert (std::pair <std::string, std::pair<size_t, T*> > (path, std::pair <size_t, T*> (1, ptr)));
      return false;
    }
}

template <class T>
MemoryManager<T>::~MemoryManager() {
  typename std::map<std::string, std::pair<size_t, T*> >::iterator it;

  for (it = elements.begin (); it != elements.end (); it++)
  {
    delete it->second.second;
  }
}

template <class T>
void MemoryManager<T>::free (T* element)
{
  typename std::map<std::string, std::pair<size_t, T*> >::iterator it;

  for (it = elements.begin (); it != elements.end (); it++)
    {
      if (element == it->second.second)
	{
	  it->second.first--;
	  if (it->second.first == 0)
	    {
	      delete it->second.second;
	      elements.erase (it);
	      break;
	    }
	}
    }
}

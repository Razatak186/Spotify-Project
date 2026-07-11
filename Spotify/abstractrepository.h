#ifndef ABSTRACTREPOSITORY_H
#define ABSTRACTREPOSITORY_H

#include <optional>
template<typename T>
class AbstractRepository
{
public:
    virtual ~AbstractRepository()=default;

    virtual int save(const T& item)=0;
    virtual bool  remove(int id)=0;
    virtual std::optional<T> search(int id)=0;
};

#endif // ABSTRACTREPOSITORY_H

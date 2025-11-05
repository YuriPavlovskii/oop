#include <iostream>
#include <memory>
class Mystack
{
private:
    /* data */
    unsigned int capacity;
    unsigned int size;
    int *data;
    static inline unsigned count{};
    unsigned num;

public:
    Mystack(unsigned int capacity);
    void toString(/*this*/);
    ~Mystack();

    Mystack(const Mystack &object);
    Mystack &operator=(const Mystack &object);

    Mystack(Mystack &&object);
    Mystack &operator=(Mystack &&object);

    void push(int x);
    int pop();
};

Mystack::Mystack(unsigned int capacity) : capacity(capacity), size(0)
{
    data = new int[capacity];
    if (data == NULL)
        std::cerr << "Memory allocation FAILED!" << std::endl;
    else
        std::cout << "Create stack with capacity " << capacity << std::endl;
    num = Mystack::count++;
}

Mystack::~Mystack()
{
    delete[] data;
    data = nullptr;
    std::cout << "Destroy stack" << std::endl;
}

void Mystack::toString()
{
    std::cout << num << ".Mystack (" << capacity << "," << size << "):" << std::endl;
    for (size_t i = 0; i < size; i++)
    {
        std::cout << "data[" << i << "] = " << data[i] << std::endl;
    }
}

Mystack::Mystack(const Mystack &object) : capacity(object.capacity), size(object.size)
{
    std::cout << "COPY: " << this->num << " <- " << object.num << std::endl;
    data = new int[capacity];
    for (size_t i = 0; i < size; i++)
    {
        data[i] = object.data[i];
    }
}
Mystack &Mystack::operator=(const Mystack &object)
{
    capacity = object.capacity;
    size = object.size;
    std::cout << "COPY(=): " << this->num << " <- " << object.num << std::endl;
    if (this != &object)
    {
        delete[] data;
        data = new int[capacity];
        for (size_t i = 0; i < size; i++)
        {
            data[i] = object.data[i];
        }
    }
    return *this;
}

Mystack::Mystack(Mystack &&object) : capacity(object.capacity), size(object.size)
{
    std::cout << "MOVE: " << this->num << " <- " << object.num << std::endl;
    data = new int[capacity];
    for (size_t i = 0; i < size; i++)
    {
        std::swap(data[i], object.data[i]);
    }
    delete[] object.data;
    object.data = nullptr;
}

Mystack &Mystack::operator=(Mystack &&object)
{
    capacity = object.capacity;
    size = object.size;
    std::cout << "MOVE(=): " << this->num << " <- " << object.num << std::endl;

    if (this != &object)
    {
        delete[] data;
        data = new int[capacity];
        for (size_t i = 0; i < size; i++)
        {
            std::swap(data[i], object.data[i]);
        }
        delete[] object.data;
        object.data = nullptr;
    }
    return *this;
}

void Mystack::push(int x)
{
    if (size == capacity) {
        throw  std::runtime_error("stack is full");
    } else {
        data[size] = x;
        size++;
    }
}

int Mystack::pop()
{
    if (size == 0) {
        throw  std::runtime_error("stack is empty");
    } else {
        size--;
        return data[size];
    }
}

int main()
{
    Mystack stk(64);
    Mystack stk2(32);
    stk.toString();
    stk2.toString();
    stk.push(661);
    stk.push(662);
    stk.push(663);
    stk.push(664);
    stk.push(665);
    stk.push(666);
    stk2 = stk;
    stk.toString();
    stk2.toString();
    int x = stk.pop();
    stk.toString();
    stk2.toString();

    stk2 = std::move(stk);
    stk2.toString();
    for (size_t i = 0; i < 6; i++)
    {
        std::cout << "get x[" << i << "] = " << stk2.pop() << std::endl;
    }
}

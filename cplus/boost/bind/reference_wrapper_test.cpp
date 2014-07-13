template <typename T>
class reference_wrapper
{
public:
    explicit reference_wrapper(T &t):_t(&t)
    {
    }
    operator T& () const
    {
        return *_t;
    }
    T& get() const
    {
        return *_t;
    }
    T* get_pointer() const
    {
        return _t;
    }
private:
    T *_t;
}

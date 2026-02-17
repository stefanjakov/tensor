#include <vector>

template <typename T> class Tensor
{
  private:
    std::vector<T>      _data;
    std::vector<size_t> _shape;

  public:
    Tensor(const std::vector<size_t> &shape) : _shape(shape)
    {
        size_t total = 1;
        for (size_t s : shape)
            total *= s;

        this->_data.resize(total);
    }

    T *raw_data()
    {
        return data.data();
    }
    const std::vector<size_t> &get_shape() const
    {
        return shape;
    }
};
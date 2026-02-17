#pragma once

#include <cstddef>
#include <initializer_list>
#include <vector>

/**
 * @brief A simple dynamically-sized dense tensor.
 *
 * @details
 * Stores data in contiguous row-major layout.
 * The tensor owns its memory via std::vector.
 *
 * Shape is stored as a vector of dimensions:
 *   [x, y, z, ...]
 */
template <typename T> class Tensor
{
  private:
    std::vector<T>      _data;
    std::vector<size_t> _shape;

    /**
     * @brief Computes total number of elements from shape.
     */
    static size_t compute_size(const std::vector<size_t> &shape)
    {
        size_t total = 1;
        for (size_t s : shape)
            total *= s;
        return total;
    }

  public:
    /**
     * @brief Constructs a tensor with the given shape.
     *
     * @details
     * Allocates contiguous storage equal to the product of
     * the shape dimensions and initializes all elements to `value`.
     *
     * @param shape Tensor dimensions in the form [x, y, z, ...].
     * @param value Initial value for all elements (default: T()).
     */
    explicit Tensor(const std::vector<size_t> &shape, const T &value = T())
        : _shape(shape), _data(compute_size(shape), value)
    {
    }

    /**
     * @brief Constructs a tensor using an initializer list for shape.
     *
     * @details
     * Example:
     *     Tensor<float> t({3, 4, 5});
     *
     * All elements are value-initialized.
     *
     * @param shape Tensor dimensions in the form {x, y, z, ...}.
     */
    explicit Tensor(std::initializer_list<size_t> shape)
        : Tensor(std::vector<size_t>(shape))
    {
    }

    /**
     * @brief Returns a mutable raw pointer to the underlying data buffer.
     *
     * @details
     * The memory is contiguous and stored in row-major order.
     * Useful for:
     *  - Interfacing with C APIs
     *  - Passing to CUDA kernels
     *  - Low-level operations
     *
     * @warning Pointer becomes invalid if the tensor is resized or destroyed.
     */
    T *raw_data()
    {
        return _data.data();
    }

    /**
     * @brief Returns a const raw pointer to the underlying data buffer.
     */
    const T *raw_data() const
    {
        return _data.data();
    }

    /**
     * @brief Returns the tensor shape.
     *
     * @return Constant reference to the shape vector.
     */
    const std::vector<size_t> &get_shape() const
    {
        return _shape;
    }

    /**
     * @brief Returns the total number of elements.
     */
    size_t size() const
    {
        return _data.size();
    }

    /**
     * @brief Creates a tensor filled with zeros.
     *
     * @param shape Tensor dimensions in the form [x, y, z, ...].
     * @return Tensor with all elements initialized to zero.
     */
    static Tensor zeros(const std::vector<size_t> &shape)
    {
        return Tensor(shape, T(0));
    }

    /**
     * @brief Creates a tensor filled with zeros using initializer list.
     *
     * Example:
     *     auto t = Tensor<float>::zeros({3, 4});
     */
    static Tensor zeros(std::initializer_list<size_t> shape)
    {
        return Tensor(std::vector<size_t>(shape), T(0));
    }
};

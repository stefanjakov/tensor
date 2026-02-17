#include "../include/tensor.hpp"
#include <gtest/gtest.h>

TEST(TensorTest, SizeConstructor)
{
    const std::vector<size_t> size = {4, 4};

    Tensor<float>             tensor1(size);
    Tensor<float>             tensor2({1, 3, 2});

    ASSERT_EQ(tensor1.get_shape(), size);
    ASSERT_EQ(tensor2.get_shape(), std::vector<size_t>({1, 3, 2}));
}

TEST(TensorTest, ZerosConstructor)
{
    Tensor<float> f = Tensor<float>::zeros({2, 2});
    // using this while I have not impl operator[]
    ASSERT_EQ(f.raw_data()[2], 0);
}
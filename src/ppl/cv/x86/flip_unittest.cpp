#include "ppl/cv/x86/flip.h"
#include "ppl/cv/x86/test.h"
#include <memory>
#include <gtest/gtest.h>
#include "ppl/cv/debug.h"
#include <opencv2/imgproc.hpp>

template <typename T, int32_t nc>
void FlipTest(int32_t height, int32_t width, int32_t flipCode)
{
    std::unique_ptr<T[]> src(new T[width * height * nc]);
    ppl::cv::debug::randomFill<T>(src.get(), width * height * nc, 0, 255);

    std::unique_ptr<T[]> dst(new T[width * height * nc]);

    ppl::cv::x86::Flip<T, nc>(height, width, width * nc, src.get(), width * nc, dst.get(), flipCode);

    std::unique_ptr<T[]> dst_opencv(new T[width * height * nc]);

    cv::Mat iMat(height, width, CV_MAKETYPE(cv::DataType<T>::depth, nc), src.get());
    cv::Mat oMat(height, width, CV_MAKETYPE(cv::DataType<T>::depth, nc), dst_opencv.get());
    cv::flip(iMat, oMat, flipCode);

    checkResult<T, nc>(dst.get(), dst_opencv.get(), height, width, width * nc, width * nc, 1.01f);
}


TEST(FLIP_FP32, x86)
{
    FlipTest<float, 1>(640, 720, 0);
    FlipTest<float, 1>(640, 720, 1);
    FlipTest<float, 1>(640, 720, -1);

    FlipTest<float, 3>(640, 720, 0);
    FlipTest<float, 3>(640, 720, 1);
    FlipTest<float, 3>(640, 720, -1);

    FlipTest<float, 4>(640, 720, 0);
    FlipTest<float, 4>(640, 720, 1);
    FlipTest<float, 4>(640, 720, -1);

    FlipTest<float, 1>(101, 101, 0);
    FlipTest<float, 1>(101, 101, 1);
    FlipTest<float, 1>(101, 101, -1);
    
    FlipTest<float, 3>(101, 101, 0);
    FlipTest<float, 3>(101, 101, 1);
    FlipTest<float, 3>(101, 101, -1);

    FlipTest<float, 4>(101, 101, 0);
    FlipTest<float, 4>(101, 101, 1);
    FlipTest<float, 4>(101, 101, -1);
}

TEST(FLIP_UINT8, x86)
{
    FlipTest<uint8_t, 1>(640, 720, 0);
    FlipTest<uint8_t, 1>(640, 720, 1);
    FlipTest<uint8_t, 1>(640, 720, -1);

    FlipTest<uint8_t, 3>(640, 720, 0);
    FlipTest<uint8_t, 3>(640, 720, 1);
    FlipTest<uint8_t, 3>(640, 720, -1);

    FlipTest<uint8_t, 4>(640, 720, 0);
    FlipTest<uint8_t, 4>(640, 720, 1);
    FlipTest<uint8_t, 4>(640, 720, -1);

    FlipTest<uint8_t, 1>(101, 101, 0);
    FlipTest<uint8_t, 1>(101, 101, 1);
    FlipTest<uint8_t, 1>(101, 101, -1);
    
    FlipTest<uint8_t, 3>(101, 101, 0);
    FlipTest<uint8_t, 3>(101, 101, 1);
    FlipTest<uint8_t, 3>(101, 101, -1);

    FlipTest<uint8_t, 4>(101, 101, 0);
    FlipTest<uint8_t, 4>(101, 101, 1);
    FlipTest<uint8_t, 4>(101, 101, -1);
}

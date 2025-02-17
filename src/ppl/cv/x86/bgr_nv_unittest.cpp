#include "ppl/cv/x86/cvtcolor.h"
#include "ppl/common/retcode.h"
#include "ppl/common/sys.h"
#include "ppl/cv/x86/test.h"
#include <memory>
#include <gtest/gtest.h>
#include "ppl/cv/debug.h"

enum Color2NVMode {RGB2NV12_MODE, RGB2NV21_MODE, BGR2NV12_MODE, BGR2NV21_MODE};
namespace ppl {
namespace cv {
namespace x86 {

template<>
::ppl::common::RetCode I4202NV21<uint8_t>(int32_t height,
               int32_t width,
               int32_t inStrideY,
               const uint8_t* inDataY,
               int32_t inStrideU,
               const uint8_t* inDataU,
               int32_t inStrideV,
               const uint8_t* inDataV,
               int32_t outStrideY,
               uint8_t *outDataY,
               int32_t outStrideVU,
               uint8_t *outDataVU) {
    assert((height % 2) == 0);
    assert((width % 2) == 0);
    assert(height != 0 && width != 0);
    assert(inStrideY != 0 && inStrideV != 0 && inStrideU != 0);
    assert(outStrideY != 0 && outStrideVU != 0);
    assert(inDataY != NULL && inDataU != NULL && inDataV != NULL);
    assert(outDataY != NULL && outDataVU != NULL);

    // memcpy y plane
    for (int32_t i = 0; i < height; ++i) {
        memcpy(outDataY + i * outStrideY, inDataY + i * inStrideY, sizeof(uint8_t) * width);
    }

    // memcpy u,v plane
    for (int32_t i = 0; i < height / 2; ++i) {
        for (int32_t j = 0; j < width / 2; ++j) {
            outDataVU[i * outStrideVU + j * 2] = inDataV[i * inStrideV + j];
            outDataVU[i * outStrideVU + j * 2 + 1] = inDataU[i * inStrideU + j];
        } 
    }
    return ppl::common::RC_SUCCESS;
}

template<>
::ppl::common::RetCode I4202NV12<uint8_t>(int32_t height,
               int32_t width,
               int32_t inStrideY,
               const uint8_t* inDataY,
               int32_t inStrideU,
               const uint8_t* inDataU,
               int32_t inStrideV,
               const uint8_t* inDataV,
               int32_t outStrideY,
               uint8_t *outDataY,
               int32_t outStrideUV,
               uint8_t *outDataUV) {
    assert((height % 2) == 0);
    assert((width % 2) == 0);
    assert(height != 0 && width != 0);
    assert(inStrideY != 0 && inStrideV != 0 && inStrideU != 0);
    assert(outStrideY != 0 && outStrideUV != 0);
    assert(inDataY != NULL && inDataU != NULL && inDataV != NULL);
    assert(outDataY != NULL && outDataUV != NULL);

    // memcpy y plane
    for (int32_t i = 0; i < height; ++i) {
        memcpy(outDataY + i * outStrideY, inDataY + i * inStrideY, sizeof(uint8_t) * width);
    }

    // memcpy u,v plane
    for (int32_t i = 0; i < height / 2; ++i) {
        for (int32_t j = 0; j < width / 2; ++j) {
            outDataUV[i * outStrideUV + j * 2] = inDataU[i * inStrideU + j];
            outDataUV[i * outStrideUV + j * 2 + 1] = inDataV[i * inStrideV + j];
        } 
    }
    return ppl::common::RC_SUCCESS;
}

template<>
::ppl::common::RetCode NV212I420<uint8_t>(int32_t height,
               int32_t width,
               int32_t inStrideY,
               const uint8_t *inDataY,
               int32_t inStrideVU,
               const uint8_t *inDataVU,
               int32_t outStrideY,
               uint8_t* outDataY,
               int32_t outStrideU,
               uint8_t* outDataU,
               int32_t outStrideV,
               uint8_t* outDataV) {
    assert((height % 2) == 0);
    assert((width % 2) == 0);
    assert(height != 0 && width != 0);
    assert(outStrideY != 0 && outStrideV != 0 && outStrideU != 0);
    assert(inStrideY != 0 && inStrideVU != 0);
    assert(outDataY != NULL && outDataU != NULL && outDataV != NULL);
    assert(inDataY != NULL && inDataVU != NULL);

    // memcpy y plane
    for (int32_t i = 0; i < height; ++i) {
        memcpy(outDataY + i * outStrideY, inDataY + i * inStrideY, sizeof(uint8_t) * width);
    }

    // memcpy u,v plane
    for (int32_t i = 0; i < height / 2; ++i) {
        for (int32_t j = 0; j < width / 2; ++j) {
            outDataV[i * outStrideV + j] = inDataVU[i * inStrideVU + 2 * j];
            outDataU[i * outStrideU + j] = inDataVU[i * inStrideVU + 2 * j + 1];
        } 
    }
    return ppl::common::RC_SUCCESS;
}

template<>
::ppl::common::RetCode NV122I420<uint8_t>(int32_t height,
               int32_t width,
               int32_t inStrideY,
               const uint8_t *inDataY,
               int32_t inStrideUV,
               const uint8_t *inDataUV,
               int32_t outStrideY,
               uint8_t* outDataY,
               int32_t outStrideU,
               uint8_t* outDataU,
               int32_t outStrideV,
               uint8_t* outDataV) {
    assert((height % 2) == 0);
    assert((width % 2) == 0);
    assert(height != 0 && width != 0);
    assert(outStrideY != 0 && outStrideV != 0 && outStrideU != 0);
    assert(inStrideY != 0 && inStrideUV != 0);
    assert(outDataY != NULL && outDataU != NULL && outDataV != NULL);
    assert(inDataY != NULL && inDataUV != NULL);

    // memcpy y plane
    for (int32_t i = 0; i < height; ++i) {
        memcpy(outDataY + i * outStrideY, inDataY + i * inStrideY, sizeof(uint8_t) * width);
    }

    // memcpy u,v plane
    for (int32_t i = 0; i < height / 2; ++i) {
        for (int32_t j = 0; j < width / 2; ++j) {
            outDataU[i * outStrideU + j] = inDataUV[i * inStrideUV + 2 * j];
            outDataV[i * outStrideV + j] = inDataUV[i * inStrideUV + 2 * j + 1];
        } 
    }
    return ppl::common::RC_SUCCESS;
}
    
}
}
}

template <Color2NVMode mode>
void Color2NVTest(int32_t height, int32_t width) {
    std::unique_ptr<uint8_t[]> src(new uint8_t[width * height * 3]);
    std::unique_ptr<uint8_t[]> dst_ref(new uint8_t[width * height * 3 / 2]);
    std::unique_ptr<uint8_t[]> dst(new uint8_t[width * height * 3 / 2]);
    ppl::cv::debug::randomFill<uint8_t>(src.get(), width * height * 3, 0, 255);

    cv::Mat srcMat(height, width, CV_MAKETYPE(cv::DataType<uint8_t>::depth, 3), src.get());
    cv::Mat dstMatI420(3 * height / 2, width, CV_MAKETYPE(cv::DataType<uint8_t>::depth, 1));
    uint8_t *i420_ptr = dstMatI420.ptr();
    if (mode == RGB2NV12_MODE) {
        cv::cvtColor(srcMat, dstMatI420, cv::COLOR_RGB2YUV_I420);
        ppl::cv::x86::RGB2NV12<uint8_t>(height, width, width * 3, src.get(),
                                        width, dst.get());
        ppl::cv::x86::I4202NV12<uint8_t>(height, width, width, i420_ptr, width / 2, i420_ptr + height * width, width / 2, i420_ptr + height * width + (height / 2) * (width / 2),
                                                width, dst_ref.get(), width, dst_ref.get() + height * width);
    } else if (mode == RGB2NV21_MODE) {
        cv::cvtColor(srcMat, dstMatI420, cv::COLOR_RGB2YUV_I420);
        ppl::cv::x86::RGB2NV21<uint8_t>(height, width, width * 3, src.get(),
                                        width, dst.get());
        ppl::cv::x86::I4202NV21<uint8_t>(height, width, width, i420_ptr, width / 2, i420_ptr + height * width, width / 2, i420_ptr + height * width + (height / 2) * (width / 2),
                                                width, dst_ref.get(), width, dst_ref.get() + height * width);
    } else if (mode == BGR2NV12_MODE) {
        cv::cvtColor(srcMat, dstMatI420, cv::COLOR_BGR2YUV_I420);
        ppl::cv::x86::BGR2NV12<uint8_t>(height, width, width * 3, src.get(),
                                        width, dst.get());
        ppl::cv::x86::I4202NV12<uint8_t>(height, width, width, i420_ptr, width / 2, i420_ptr + height * width, width / 2, i420_ptr + height * width + (height / 2) * (width / 2),
                                                width, dst_ref.get(), width, dst_ref.get() + height * width);
    } else if (mode == BGR2NV21_MODE) {
        cv::cvtColor(srcMat, dstMatI420, cv::COLOR_BGR2YUV_I420);
        ppl::cv::x86::BGR2NV21<uint8_t>(height, width, width * 3, src.get(),
                                        width, dst.get());
        ppl::cv::x86::I4202NV21<uint8_t>(height, width, width, i420_ptr, width / 2, i420_ptr + height * width, width / 2, i420_ptr + height * width + (height / 2) * (width / 2),
                                                width, dst_ref.get(), width, dst_ref.get() + height * width);
    }
    checkResult<uint8_t, 1>(dst.get(), dst_ref.get(), 3 * height / 2, width, width, width, 1.01f);
}

template <Color2NVMode mode>
void Color2NVMultiPlaneTest(int32_t height, int32_t width) {
    std::unique_ptr<uint8_t[]> src(new uint8_t[width * height * 3]);
    std::unique_ptr<uint8_t[]> dst_ref(new uint8_t[width * height * 3 / 2]);
    std::unique_ptr<uint8_t[]> dst(new uint8_t[width * height * 3 / 2]);
    ppl::cv::debug::randomFill<uint8_t>(src.get(), width * height * 3, 0, 255);

    cv::Mat srcMat(height, width, CV_MAKETYPE(cv::DataType<uint8_t>::depth, 3), src.get());
    cv::Mat dstMatI420(3 * height / 2, width, CV_MAKETYPE(cv::DataType<uint8_t>::depth, 1));
    uint8_t *i420_ptr = dstMatI420.ptr();
    if (mode == RGB2NV12_MODE) {
        cv::cvtColor(srcMat, dstMatI420, cv::COLOR_RGB2YUV_I420);
        ppl::cv::x86::RGB2NV12<uint8_t>(height, width, width * 3, src.get(),
                                        width, dst.get(),
                                        width, dst.get() + height * width);
        ppl::cv::x86::I4202NV12<uint8_t>(height, width, width, i420_ptr, width / 2, i420_ptr + height * width, width / 2, i420_ptr + height * width + (height / 2) * (width / 2),
                                                width, dst_ref.get(), width, dst_ref.get() + height * width);
    } else if (mode == RGB2NV21_MODE) {
        cv::cvtColor(srcMat, dstMatI420, cv::COLOR_RGB2YUV_I420);
        ppl::cv::x86::RGB2NV21<uint8_t>(height, width, width * 3, src.get(),
                                        width, dst.get(),
                                        width, dst.get() + height * width);
        ppl::cv::x86::I4202NV21<uint8_t>(height, width, width, i420_ptr, width / 2, i420_ptr + height * width, width / 2, i420_ptr + height * width + (height / 2) * (width / 2),
                                                width, dst_ref.get(), width, dst_ref.get() + height * width);
    } else if (mode == BGR2NV12_MODE) {
        cv::cvtColor(srcMat, dstMatI420, cv::COLOR_BGR2YUV_I420);
        ppl::cv::x86::BGR2NV12<uint8_t>(height, width, width * 3, src.get(),
                                        width, dst.get(),
                                        width, dst.get() + height * width);
        ppl::cv::x86::I4202NV12<uint8_t>(height, width, width, i420_ptr, width / 2, i420_ptr + height * width, width / 2, i420_ptr + height * width + (height / 2) * (width / 2),
                                                width, dst_ref.get(), width, dst_ref.get() + height * width);
    } else if (mode == BGR2NV21_MODE) {
        cv::cvtColor(srcMat, dstMatI420, cv::COLOR_BGR2YUV_I420);
        ppl::cv::x86::BGR2NV21<uint8_t>(height, width, width * 3, src.get(),
                                        width, dst.get(),
                                        width, dst.get() + height * width);
        ppl::cv::x86::I4202NV21<uint8_t>(height, width, width, i420_ptr, width / 2, i420_ptr + height * width, width / 2, i420_ptr + height * width + (height / 2) * (width / 2),
                                                width, dst_ref.get(), width, dst_ref.get() + height * width);
    }
    checkResult<uint8_t, 1>(dst.get(), dst_ref.get(), 3 * height / 2, width, width, width, 1.01f);
}


enum NV2ColorMode {NV122RGB_MODE, NV122BGR_MODE, NV212RGB_MODE, NV212BGR_MODE};

template <NV2ColorMode mode>
void NV2ColorTest(int32_t height, int32_t width) {
    std::unique_ptr<uint8_t[]> src(new uint8_t[width * height * 3 / 2]);
    std::unique_ptr<uint8_t[]> dst(new uint8_t[width * height * 3]);
    std::unique_ptr<uint8_t[]> dst_ref(new uint8_t[width * height * 3]);

    ppl::cv::debug::randomFill<uint8_t>(src.get(), width * height * 3 / 2, 0, 255);

    cv::Mat srcMat(3 * height / 2, width, CV_MAKETYPE(cv::DataType<uint8_t>::depth, 1), src.get());
    cv::Mat dstMat(height, width, CV_MAKETYPE(cv::DataType<uint8_t>::depth, 3), dst_ref.get());
    if (mode == NV122RGB_MODE) {
        ppl::cv::x86::NV122RGB<uint8_t>(height, width, width, src.get(), 3 * width, dst.get());
        cv::cvtColor(srcMat, dstMat, cv::COLOR_YUV2RGB_NV12);
    } else if (mode == NV122BGR_MODE) {
        ppl::cv::x86::NV122BGR<uint8_t>(height, width, width, src.get(), 3 * width, dst.get());
        cv::cvtColor(srcMat, dstMat, cv::COLOR_YUV2BGR_NV12);
    } else if (mode == NV212RGB_MODE) {
        ppl::cv::x86::NV212RGB<uint8_t>(height, width, width, src.get(), 3 * width, dst.get());
        cv::cvtColor(srcMat, dstMat, cv::COLOR_YUV2RGB_NV21);
    } else if (mode == NV212BGR_MODE) {
        ppl::cv::x86::NV212BGR<uint8_t>(height, width, width, src.get(), 3 * width, dst.get());
        cv::cvtColor(srcMat, dstMat, cv::COLOR_YUV2BGR_NV21);
    }
    checkResult<uint8_t, 3>(dst.get(), dst_ref.get(), height, width, 3 * width, 3 * width, 1.01f);
}


template <NV2ColorMode mode>
void NV2ColorMultiPlaneTest(int32_t height, int32_t width) {
    std::unique_ptr<uint8_t[]> src(new uint8_t[width * height * 3 / 2]);
    std::unique_ptr<uint8_t[]> dst(new uint8_t[width * height * 3]);
    std::unique_ptr<uint8_t[]> dst_ref(new uint8_t[width * height * 3]);

    ppl::cv::debug::randomFill<uint8_t>(src.get(), width * height * 3 / 2, 0, 255);

    cv::Mat srcMat(3 * height / 2, width, CV_MAKETYPE(cv::DataType<uint8_t>::depth, 1), src.get());
    cv::Mat dstMat(height, width, CV_MAKETYPE(cv::DataType<uint8_t>::depth, 3), dst_ref.get());
    if (mode == NV122RGB_MODE) {
        ppl::cv::x86::NV122RGB<uint8_t>(height, width,
                                            width, src.get(),
                                            width, src.get() + height * width,
                                            3 * width, dst.get());
        cv::cvtColor(srcMat, dstMat, cv::COLOR_YUV2RGB_NV12);
    } else if (mode == NV122BGR_MODE) {
        ppl::cv::x86::NV122BGR<uint8_t>(height, width,
                                            width, src.get(),
                                            width, src.get() + height * width,
                                            3 * width, dst.get());
        cv::cvtColor(srcMat, dstMat, cv::COLOR_YUV2BGR_NV12);
    } else if (mode == NV212RGB_MODE) {
        ppl::cv::x86::NV212RGB<uint8_t>(height, width,
                                            width, src.get(),
                                            width, src.get() + height * width,
                                            3 * width, dst.get());
        cv::cvtColor(srcMat, dstMat, cv::COLOR_YUV2RGB_NV21);
    } else if (mode == NV212BGR_MODE) {
        ppl::cv::x86::NV212BGR<uint8_t>(height, width,
                                            width, src.get(),
                                            width, src.get() + height * width,
                                            3 * width, dst.get());
        cv::cvtColor(srcMat, dstMat, cv::COLOR_YUV2BGR_NV21);
    }
    checkResult<uint8_t, 3>(dst.get(), dst_ref.get(), height, width, 3 * width, 3 * width, 1.01f);
}

TEST(NV12_2_RGB, x86)
{
    NV2ColorTest<NV122RGB_MODE>(640, 720);
    NV2ColorTest<NV122RGB_MODE>(720, 1080);
    NV2ColorTest<NV122RGB_MODE>(1080, 1920);
    NV2ColorMultiPlaneTest<NV122RGB_MODE>(640, 720);
    NV2ColorMultiPlaneTest<NV122RGB_MODE>(720, 1080);
    NV2ColorMultiPlaneTest<NV122RGB_MODE>(1080, 1920);
    NV2ColorMultiPlaneTest<NV122RGB_MODE>(642, 722);
    NV2ColorMultiPlaneTest<NV122RGB_MODE>(722, 1082);
    NV2ColorMultiPlaneTest<NV122RGB_MODE>(1082, 1922);
}
TEST(NV21_2_RGB, x86)
{
    NV2ColorTest<NV212RGB_MODE>(640, 720);
    NV2ColorTest<NV212RGB_MODE>(720, 1080);
    NV2ColorTest<NV212RGB_MODE>(1080, 1920);
    NV2ColorMultiPlaneTest<NV212RGB_MODE>(640, 720);
    NV2ColorMultiPlaneTest<NV212RGB_MODE>(720, 1080);
    NV2ColorMultiPlaneTest<NV212RGB_MODE>(1080, 1920);
    NV2ColorMultiPlaneTest<NV212RGB_MODE>(642, 722);
    NV2ColorMultiPlaneTest<NV212RGB_MODE>(722, 1082);
    NV2ColorMultiPlaneTest<NV212RGB_MODE>(1082, 1922);
}
TEST(NV12_2_BGR, x86)
{
    NV2ColorTest<NV122BGR_MODE>(640, 720);
    NV2ColorTest<NV122BGR_MODE>(720, 1080);
    NV2ColorTest<NV122BGR_MODE>(1080, 1920);
    NV2ColorMultiPlaneTest<NV122BGR_MODE>(640, 720);
    NV2ColorMultiPlaneTest<NV122BGR_MODE>(720, 1080);
    NV2ColorMultiPlaneTest<NV122BGR_MODE>(1080, 1920);
}
TEST(NV21_2_BGR, x86)
{
    NV2ColorTest<NV212BGR_MODE>(640, 720);
    NV2ColorTest<NV212BGR_MODE>(720, 1080);
    NV2ColorTest<NV212BGR_MODE>(1080, 1920);
    NV2ColorMultiPlaneTest<NV212BGR_MODE>(640, 720);
    NV2ColorMultiPlaneTest<NV212BGR_MODE>(720, 1080);
    NV2ColorMultiPlaneTest<NV212BGR_MODE>(1080, 1920);
}

TEST(RGB_2_NV12, x86)
{
    Color2NVTest<RGB2NV12_MODE>(640, 720);
    Color2NVTest<RGB2NV12_MODE>(720, 1080);
    Color2NVTest<RGB2NV12_MODE>(1080, 1920);
    Color2NVMultiPlaneTest<RGB2NV12_MODE>(640, 720);
    Color2NVMultiPlaneTest<RGB2NV12_MODE>(720, 1080);
    Color2NVMultiPlaneTest<RGB2NV12_MODE>(1080, 1920);
}
TEST(RGB_2_NV21, x86)
{
    Color2NVTest<RGB2NV21_MODE>(640, 720);
    Color2NVTest<RGB2NV21_MODE>(720, 1080);
    Color2NVTest<RGB2NV21_MODE>(1080, 1920);
    Color2NVMultiPlaneTest<RGB2NV21_MODE>(640, 720);
    Color2NVMultiPlaneTest<RGB2NV21_MODE>(720, 1080);
    Color2NVMultiPlaneTest<RGB2NV21_MODE>(1080, 1920);
}
TEST(BGR_2_NV12, x86)
{
    Color2NVTest<BGR2NV12_MODE>(640, 720);
    Color2NVTest<BGR2NV12_MODE>(720, 1080);
    Color2NVTest<BGR2NV12_MODE>(1080, 1920);
    Color2NVMultiPlaneTest<BGR2NV12_MODE>(640, 720);
    Color2NVMultiPlaneTest<BGR2NV12_MODE>(720, 1080);
    Color2NVMultiPlaneTest<BGR2NV12_MODE>(1080, 1920);
}
TEST(BGR_2_NV21, x86)
{
    Color2NVTest<BGR2NV21_MODE>(640, 720);
    Color2NVTest<BGR2NV21_MODE>(720, 1080);
    Color2NVTest<BGR2NV21_MODE>(1080, 1920);
    Color2NVMultiPlaneTest<BGR2NV21_MODE>(640, 720);
    Color2NVMultiPlaneTest<BGR2NV21_MODE>(720, 1080);
    Color2NVMultiPlaneTest<BGR2NV21_MODE>(1080, 1920);
}

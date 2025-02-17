#ifndef __ST_HPC_PPL_CV_X86_FLIP_H_
#define __ST_HPC_PPL_CV_X86_FLIP_H_

#include "ppl/common/retcode.h"
namespace ppl {
namespace cv {
namespace x86 {

/**
* @brief Flips a 2D array around vertical, horizontal, or both axes.
* @tparam T The data type of input and output image, currently only \a uint8_t and \a float are supported.
* @tparam channels The number of channels of input image and output image, 1, 3 and 4 are supported.
* @param height            input image's height
* @param width             input image's width
* @param inWidthStride     input image's width stride, usually it equals to `width * channels`
* @param inData            input image data
* @param outWidthStride    output image's width stride, usually it equals to `width * channels`
* @param outData           output image data
* @param flipCode          0 means flipping around the x-axis and positive value (for example, 1) means flipping around y-axis. Negative value (for example, -1) means flipping around both axes.
* @warning All input parameters must be valid, or undefined behaviour may occur.
* @remark The fllowing table show which data type and channels are supported.
* <table>
* <tr><th>Data type(T)<th>channels
* <tr><td>float<td>1
* <tr><td>float<td>3
* <tr><td>float<td>4
* <tr><td>uint8_t<td>1
* <tr><td>uint8_t<td>3
* <tr><td>uint8_t<td>4
* </table>
* <table>
* <caption align="left">Requirements</caption>
* <tr><td>x86 platforms supported<td> All
* <tr><td>Header files<td> #include &lt;ppl/cv/x86/flip.h&gt;
* <tr><td>Project<td> ppl.cv
* @since ppl.cv-v1.0.0
* ###Example
* @code{.cpp}
* #include <ppl/cv/x86/flip.h>
* int32_t main(int32_t argc, char** argv) {
*     const int32_t W = 640;
*     const int32_t H = 480;
*     const int32_t C = 3;
*     float* dev_iImage = (float*)malloc(W * H * C * sizeof(float));
*     float* dev_oImage = (float*)malloc(W * H * C * sizeof(float));
*     int32_t flipCode = 0;
*
*     ppl::cv::x86::Flip<float, 3>(H, W, W * C, dev_iImage, W * C, dev_oImage, flipCode);
*
*     free(dev_iImage);
*     free(dev_oImage);
*     return 0;
* }
* @endcode
***************************************************************************************************/

template <typename T, int32_t nc>
::ppl::common::RetCode Flip(
    int32_t height,
    int32_t width,
    int32_t inWidthStride,
    const T *inData,
    int32_t outWidthStride,
    T *outData,
    int32_t flipCode);

} //! namespace x86
} //! namespace cv
} //! namespace ppl

#endif //!__ST_HPC_PPL3_CV_X86_FLIP_H_


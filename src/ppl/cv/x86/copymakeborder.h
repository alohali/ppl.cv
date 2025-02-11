#ifndef __ST_HPC_PPL_CV_X86_COPYMAKEBORDER_H_
#define __ST_HPC_PPL_CV_X86_COPYMAKEBORDER_H_
#include <ppl/cv/types.h>
#include "ppl/common/retcode.h"

namespace ppl {
namespace cv {
namespace x86 {
/**
 * @brief Copy the source image into the middle of dest image, and make border pixels according to specific border type.
 * @tparam T The data type of input image, currently \a float and \a uint8_t are supported.
 * @tparam channels The number of channels of input image, 1, 3 and 4 are supported.
 * @param srcHeight         input image's height
 * @param srcWidth          input image's width need to be processed
 * @param srcWidthStride    input image's width stride, usually it equals to `width * channels`
 * @param src               input image data
 * @param dstHeight         output image's height
 * @param dstWidth          output image's width
 * @param dstWidthStride    the width stride of output image, usually it equals to `width * channels`
 * @param dst               output image data
 * @param border_type       ways to deal with border. BORDER_TYPE_REFLECT_101 ,BORDER_TYPE_REFLECT, BORDER_TYPE_CONSTANT and BORDER_TYPE_REPLICATE are supported
 * @param border_value      padding value when border_type is BORDER_TYPE_CONSTANT
 * @warning All input parameters must be valid, or undefined behaviour may occur.
 * @remark The fllowing table show which data type and channels are supported.
 * <table>
 * <tr><th>Data type(T)<th>channels
 * <tr><td>uint8_t(uint8_t)<td>1
 * <tr><td>uint8_t(uint8_t)<td>3
 * <tr><td>uint8_t(uint8_t)<td>4
 * </table>
 * <table>
 * <caption align="left">Requirements</caption>
 * <tr><td>X86 platforms supported<td> All
 * <tr><td>Header files<td> #include &lt;ppl/cv/x86/copymakeborder.h&gt;
 * <tr><td>Project<td> ppl.cv
 * 
 * @since ppl.cv-v1.0.0
 * ###Example 
 * 
 * @code{.cpp}
 * #include <ppl/cv/x86/copymakeborder.h>
 * int32_t main(int32_t argc, char** argv) {
 *     const int32_t srcW = 640;
 *     const int32_t srcH = 480;
 *     const int32_t C = 3;
 *     const int32_t dstW = 644;
 *     const int32_t dstH = 484;
 *     const uint8_t border_value = 0;          
 *     uint8_t* dev_iImage = (uint8_t*)malloc(srcW * srcH * C * sizeof(uint8_t));
 *     uint8_t* dev_oImage = (uint8_t*)malloc(dstW * dstH * C * sizeof(uint8_t));
 * 
 *     ppl::cv::x86::CopyMakeBorder<uint8_t, 3>(srcH, srcW, srcW * C, dev_iImage, dstH, dstW, dstW * C, dev_oImage, 
 *                                                  ppl::cv::BORDER_TYPE_REFLECT_101, border_value);
 *               
 *     return 0;
 * }
 * @endcode
 ***************************************************************************************************/
template<typename T, int32_t channels>
::ppl::common::RetCode CopyMakeBorder(
    int32_t srcHeight, 
    int32_t srcWidth, 
    int32_t srcWidthStride, 
    const T* src,
    int32_t dstHeight,
    int32_t dstWidth, 
    int32_t dstWidthStride,
    T* dst,  
    BorderType border_type, 
    T border_value = 0);

} //! namespace x86
} //! namespace cv
} //! namespace ppl
#endif //! PPL3_CV_X86_COPYMAKEBORDER_H_
#ifndef __ST_HPC_PPL_CV_X86_GET_ROTATION_MATRIX2D_H_
#define __ST_HPC_PPL_CV_X86_GET_ROTATION_MATRIX2D_H_

#include "ppl/cv/types.h"
#include "ppl/common/retcode.h"

namespace ppl {
namespace cv {
namespace x86 {

/**
* @brief Calculates an affine matrix of 2D rotation.
* @param center_y               Center y of the rotation in the source image.
* @param center_x               Center x of the rotation in the source image.
* @param angle                  Rotation angle in degrees. Positive values mean counter-clockwise rotation.
* @param scale                  Isotropic scale factor.
* @param out_data               transform matrix, 2x3 matrix. can be nullptr.
* @warning All input parameters must be valid, or undefined behaviour may occur.
* <caption align="left">Requirements</caption>
* <tr><td>x86 platforms supported<td> All
* <tr><td>Header files<td> #include &lt;ppl/cv/x86/get_rotation_matrix2d.h&gt;
* <tr><td>Project<td> ppl.cv
* @since ppl.cv-v1.0.0
* ###Example
* @code{.cpp}
* #include <ppl/cv/x86/get_rotation_matrix2d.h>
* int32_t main(int32_t argc, char** argv) {
*     float center_y = 0;
*     float center_x = 0;
*     double angle = 30;
*     double scale = 1;
*     ppl::cv::x86::GetRotationMatrix2D(center_y, center_x, angle, scale, dst.get());
*     return 0;
* }
* @endcode
***************************************************************************************************/

::ppl::common::RetCode GetRotationMatrix2D(
    float center_y,
    float center_x,
    double angle,
    double scale,
    double* out_data);

} //! namespace x86
} //! namespace cv
} //! namespace ppl

#endif //! __ST_HPC_PPL3_CV_X86_GET_ROTATION_MATRIX2D_H_

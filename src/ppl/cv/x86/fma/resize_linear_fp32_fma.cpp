#include <immintrin.h>
#include <math.h>
#include "internal_fma.hpp"
#include "ppl/common/sys.h"

namespace ppl {
namespace cv {
namespace x86 {
namespace fma {

int32_t resize_linear_twoline_fp32_fma(
    int32_t max_length,
    int32_t channels,
    const float *in_data_0,
    const float *in_data_1,
    const int32_t *w_offset,
    const float *w_coeff,
    float h_coeff,
    float *row_0,
    float *row_1,
    float *out_data)
{
    bool bSupportFMA = ppl::common::CpuSupports(ppl::common::ISA_X86_FMA);
    if (!bSupportFMA) {
        return 0;
    }

    __m256 m_h_coeff_0 = _mm256_set1_ps(h_coeff);
    __m256 m_h_coeff_1 = _mm256_set1_ps(1.0f - h_coeff);
    __m256 m_one       = _mm256_set1_ps(1.0f);

    int32_t i = 0;
    for (; i <= max_length - 8; i += 8) {
        __m256 m_data_0 = _mm256_set_ps(in_data_0[w_offset[i + 7]],
                                        in_data_0[w_offset[i + 6]],
                                        in_data_0[w_offset[i + 5]],
                                        in_data_0[w_offset[i + 4]],
                                        in_data_0[w_offset[i + 3]],
                                        in_data_0[w_offset[i + 2]],
                                        in_data_0[w_offset[i + 1]],
                                        in_data_0[w_offset[i + 0]]);
        __m256 m_data_1 = _mm256_set_ps(in_data_0[w_offset[i + 7] + channels],
                                        in_data_0[w_offset[i + 6] + channels],
                                        in_data_0[w_offset[i + 5] + channels],
                                        in_data_0[w_offset[i + 4] + channels],
                                        in_data_0[w_offset[i + 3] + channels],
                                        in_data_0[w_offset[i + 2] + channels],
                                        in_data_0[w_offset[i + 1] + channels],
                                        in_data_0[w_offset[i + 0] + channels]);
        __m256 m_data_2 = _mm256_set_ps(in_data_1[w_offset[i + 7]],
                                        in_data_1[w_offset[i + 6]],
                                        in_data_1[w_offset[i + 5]],
                                        in_data_1[w_offset[i + 4]],
                                        in_data_1[w_offset[i + 3]],
                                        in_data_1[w_offset[i + 2]],
                                        in_data_1[w_offset[i + 1]],
                                        in_data_1[w_offset[i + 0]]);
        __m256 m_data_3 = _mm256_set_ps(in_data_1[w_offset[i + 7] + channels],
                                        in_data_1[w_offset[i + 6] + channels],
                                        in_data_1[w_offset[i + 5] + channels],
                                        in_data_1[w_offset[i + 4] + channels],
                                        in_data_1[w_offset[i + 3] + channels],
                                        in_data_1[w_offset[i + 2] + channels],
                                        in_data_1[w_offset[i + 1] + channels],
                                        in_data_1[w_offset[i + 0] + channels]);

        __m256 m_w_coeff_0 = _mm256_load_ps(w_coeff + i);
        __m256 m_w_coeff_1 = _mm256_sub_ps(m_one, m_w_coeff_0);

        __m256 m_rst_row_0 = _mm256_fmadd_ps(m_data_0, m_w_coeff_0, _mm256_mul_ps(m_data_1, m_w_coeff_1));
        __m256 m_rst_row_1 = _mm256_fmadd_ps(m_data_2, m_w_coeff_0, _mm256_mul_ps(m_data_3, m_w_coeff_1));

        __m256 m_rst = _mm256_fmadd_ps(m_rst_row_0, m_h_coeff_0, _mm256_mul_ps(m_rst_row_1, m_h_coeff_1));

        _mm256_store_ps(row_0 + i, m_rst_row_0);
        _mm256_store_ps(row_1 + i, m_rst_row_1);
        _mm256_storeu_ps(out_data + i, m_rst);
    }
    return i;
}

}
}
}
} // namespace ppl::cv::x86::fma

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of qtjack_bpm_tab                                    //
//    Copyright (C) 2022 <majorx234@googlemail.com>                          //
//                                                                           //
//    qtjack_bpm_tab is free software: you can redistribute it and/or modify //
//    it under the terms of the GNU General Public License as published by   //
//    the Free Software Foundation, either version 3 of the License, or      //
//    (at your option) any later version.                                    //
//                                                                           //
//    qtjack_bpm_tab is distributed in the hope that it will be useful,      //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of         //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                           //
//                                                                           //
//    You should have received a copy of the GNU General Public License      //
//    along with qtjack_bpm_tab. If not, see <http://www.gnu.org/licenses/>. //
//                                                                           //
//    It is possible to obtain a closed-source license of QtJack.            //
//    If you're interested, contact me at: majorx234@gmail.com               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "beatthis/combfilter.hpp"

Combfilter::Combfilter(size_t samples,
                   unsigned int sample_rate){
  signal_ = fftw_alloc_complex(samples);
  result_ = fftw_alloc_complex(samples);
  freqdomain_signal_ = fftw_alloc_complex(samples);
  timedomain_result_ = fftw_alloc_complex(samples);
  plan_forward_ = fftw_plan_dft_1d(samples, signal_, result_, 
                                   FFTW_FORWARD, FFTW_ESTIMATE);
  plan_backward_ = fftw_plan_dft_1d(samples, freqdomain_signal_, timedomain_result_,
                                    FFTW_BACKWARD, FFTW_ESTIMATE);

}

Combfilter::~Combfilter() {
  fftw_free(signal_);
  fftw_free(result_);
  fftw_free(freqdomain_signal_);
  fftw_free(timedomain_result_);
  fftw_destroy_plan(plan_forward_);
  fftw_destroy_plan(plan_backward_);
}
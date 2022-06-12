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

#ifndef ENVELOPE_EXTRACTOR_HPP_
#define ENVELOPE_EXTRACTOR_HPP_

#include <fftw3.h>

class EnvelopeExtractor
{
public:
  EnvelopeExtractor(size_t samples,
                   unsigned int sample_rate);
  ~EnvelopeExtractor();
  void calculate_hann_window_fct(unsigned int window_length,
                                 unsigned int max_freq);
  float** extract_envelope(double**);
private:
  size_t samples_;
  unsigned int sample_rate_;

  double* hann_window_;
};

#endif // ENVELOPE_EXTRACTOR_HPP_
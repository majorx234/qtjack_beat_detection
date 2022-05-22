#ifndef BUFFRING_UTILS_HPP_
#define BUFFRING_UTILS_HPP_

#include <vector>
#include <functional>

// This is used for downmixing a stereo buffer into mono and framing it into
// overlapping windows as is typically necessary when taking a short-time
// Fourier transform.
class DownmixAndOverlapHelper {
 public:
  DownmixAndOverlapHelper() = default;

  typedef std::function<bool(double* pBuffer, size_t frames)>
      WindowReadyCallback;

  bool initialize(
        size_t windowSize,
        size_t stepSize,
        const WindowReadyCallback& callback);

  bool processStereoSamples(
        const float* pInput,
        size_t inputStereoSamples);

  bool finalize();

 private:
  bool processInner(const float* pInput, size_t numInputFrames);

  std::vector<double> m_buffer;
  // The window size in frames.
  size_t m_windowSize = 0;
  // The number of frames to step the window forward on each output.
  size_t m_stepSize = 0;
  size_t m_bufferWritePosition = 0;
  WindowReadyCallback m_callback;
};

#endif //BUFFRING_UTILS_HPP_

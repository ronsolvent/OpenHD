//
// Created by consti10 on 06.12.22.
//

#ifndef OPENHD_OPENHD_OHD_COMMON_OPENHD_VIDEO_FRAME_H_
#define OPENHD_OPENHD_OHD_COMMON_OPENHD_VIDEO_FRAME_H_

#include <vector>
#include <memory>
#include <chrono>

namespace openhd{

// R.n this is the best name i can come up with
// This is not required to be exactly one frame, but should be
// already packetized into rtp fragments
// R.n it is always either h264,h265 or mjpeg fragmented using the RTP protocol
struct FragmentedVideoFrame{
  std::vector<std::shared_ptr<std::vector<uint8_t>>> frame_fragments;
  // Time point of when this frame was produced, as early as possible.
  // ideally, this would be the time point when the frame was generated by the CMOS - but r.n
  // no platform supports measurements this deep.
  std::chrono::steady_clock::time_point creation_time=std::chrono::steady_clock::now();
  // OpenHD WB supprts changing encryption on the fly - and r.n no other implementation exists.
  // For the future: This hints that the link implementation should encrypt the data as secure as possible
  // even though that might result in higher CPU load.
  bool enable_ultra_secure_encryption= false;
};

}
#endif  // OPENHD_OPENHD_OHD_COMMON_OPENHD_VIDEO_FRAME_H_

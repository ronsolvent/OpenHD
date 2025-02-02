//
// Created by consti10 on 10.01.24.
//

#include "openhd_action_handler.h"

openhd::ArmingStateHelper &openhd::ArmingStateHelper::instance() {
  static openhd::ArmingStateHelper instance;
  return instance;
}

void openhd::ArmingStateHelper::register_listener(
    const std::string &tag, openhd::ArmingStateHelper::STATE_CHANGED_CB cb) {
  assert(m_cbs.find(tag) == m_cbs.end());
  m_cbs[tag] = std::move(cb);
}

void openhd::ArmingStateHelper::unregister_listener(const std::string &tag) {
  auto element = m_cbs.find(tag);
  if (element == m_cbs.end()) {
    openhd::log::get_default()->warn("Cannot unregister arming listener {}",
                                     tag);
    return;
  }
  m_cbs.erase(element);
}

void openhd::ArmingStateHelper::update_arming_state_if_changed(bool armed) {
  if (m_is_armed == armed) return;
  m_is_armed = armed;
  m_console->debug("MAV armed:{}, calling listeners.",
                   OHDUtil::yes_or_no(armed));
  for (auto &element : m_cbs) {
    // m_console->debug("Calling {},begin",element.first);
    element.second(armed);
    // m_console->debug("Calling {},end",element.first);
  }
  m_console->debug("Done calling listeners.");
}

openhd::FCRcChannelsHelper &openhd::FCRcChannelsHelper::instance() {
  static openhd::FCRcChannelsHelper instance;
  return instance;
}

void openhd::FCRcChannelsHelper::update_rc_channels(
    const std::array<int, 18> &rc_channels) {
  auto tmp = m_action_rc_channel;
  if (tmp) {
    ACTION_ON_ANY_RC_CHANNEL_CB cb = *tmp;
    cb(rc_channels);
  }
}

void openhd::FCRcChannelsHelper::action_on_any_rc_channel_register(
    openhd::FCRcChannelsHelper::ACTION_ON_ANY_RC_CHANNEL_CB cb) {
  if (cb == nullptr) {
    m_action_rc_channel = nullptr;
    return;
  }
  m_action_rc_channel = std::make_shared<ACTION_ON_ANY_RC_CHANNEL_CB>(cb);
}

openhd::LinkActionHandler &openhd::LinkActionHandler::instance() {
  static openhd::LinkActionHandler instance;
  return instance;
}

openhd::TerminateHelper &openhd::TerminateHelper::instance() {
  static TerminateHelper instance;
  return instance;
}

#pragma once

#include "esphome/core/helpers.h"
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"

#include <string>
#include <vector>
#include <map>

#ifdef USE_TIME
#include "esphome/components/time/real_time_clock.h"
#include "esphome/core/time.h"
#endif

namespace esphome {
namespace duco {

class DucoDevice;

class DucoMessage {
 public:
  DucoMessage() {}

  uint8_t function;
  uint8_t id;
  std::vector<uint8_t> data;
  uint16_t crc;

  std::vector<uint8_t> get_message() {
    std::vector<uint8_t> message;
    message.push_back(data.size() + 2);
    message.push_back(function);
    message.push_back(id);
    message.insert(message.end(), data.begin(), data.end());

    auto crc = crc16(message.data(), message.size());

    message.push_back(crc & 0xFF);
    message.push_back((crc >> 8) & 0xFF);

    return message;
  }

  std::string to_string() const {
    std::string res;

    char buf[5];

    size_t len = data.size();

    sprintf(buf, "%02X", len + 2);
    res += buf;
    res += "  ";

    sprintf(buf, "%02X", function);
    res += buf;
    res += " ";

    sprintf(buf, "%02X", id);
    res += buf;
    res += " ";

    for (size_t i = 0; i < len; i++) {
      res += " ";
      sprintf(buf, "%02X", data[i]);
      res += buf;
    }

    return res;
  }
};

class Duco : public uart::UARTDevice, public Component {
 public:
  Duco() { this->last_id_ = 10; };

  void setup() override;

  void loop() override;

  void dump_config() override;

  float get_setup_priority() const override;

  void send(DucoMessage message, DucoDevice *device);
  void set_send_wait_time(uint16_t time_in_ms) { send_wait_time_ = time_in_ms; }
  void set_disable_crc(bool disable_crc) { disable_crc_ = disable_crc; }

  std::map<uint8_t, DucoDevice *> waiting_for_response;
  void stop_waiting(uint8_t message_id);

 protected:
  uint8_t last_id_ = 0;
  uint8_t next_id_();

  bool parse_byte_(uint8_t byte);
  void finalize_message_();
  uint16_t send_wait_time_{250};
  bool disable_crc_;
  std::vector<uint8_t> rx_buffer_;
  uint32_t last_byte_{0};
  uint32_t last_send_{0};
  bool removed_last_ = false;

  void debug_hex_(std::vector<uint8_t> bytes, uint8_t separator);
};

class DucoDevice : public Parented<Duco> {
 public:
  virtual void receive_response(const DucoMessage &message) {}
};

class DucoDiscovery : public DucoDevice, public PollingComponent {
 public:
  void loop() override;
  void update() override;

  void receive_response(const DucoMessage &message) override;

  static const std::string NODE_TYPE_UNKNOWN;
  static const std::string NODE_TYPE_DTWV;
  static const std::string NODE_TYPE_UCBAT;
  static const std::string NODE_TYPE_UC;
  static const std::string NODE_TYPE_UCRH;
  static const std::string NODE_TYPE_UCCO2;
  static const std::string NODE_TYPE_VLV;
  static const std::string NODE_TYPE_VLVRH;
  static const std::string NODE_TYPE_VLVCO2;
  static const std::string NODE_TYPE_BOX;
  static const std::string NODE_TYPE_SWITCH;
  static const std::string NODE_TYPE_IAV;
  static const std::string NODE_TYPE_IAV_RH;
  static const std::string NODE_TYPE_IAV_CO2;
  static const std::string NODE_TYPE_CTRL_UNIT;
  static const std::string NODE_TYPE_CO2_RH_VLV;
  static const std::string NODE_TYPE_UC_SUN;
  static const std::string NODE_TYPE_UC_VC;
  static const std::string NODE_TYPE_MULTI_ZONE;
  static const std::string NODE_TYPE_BOX_RH;
  static const std::string NODE_TYPE_BOX_CO2;
  static const std::string NODE_TYPE_RELAY;
  static const std::string NODE_TYPE_WEATHER;
  static const std::string NODE_TYPE_MOTOR_MODBUS;
  static const std::string NODE_TYPE_DIGITAL_IN;
  static const std::string NODE_TYPE_DIGITAL_OUT;
  static const std::string NODE_TYPE_RELAY_MODBUS;
  static const std::string NODE_TYPE_PERILEX;
  static const std::string NODE_TYPE_RELAY_OUT;

  static const uint8_t NODE_TYPE_CODE_DTWV = 7;
  static const uint8_t NODE_TYPE_CODE_UCBAT = 8;
  static const uint8_t NODE_TYPE_CODE_UC = 9;
  static const uint8_t NODE_TYPE_CODE_UCRH = 10;
  static const uint8_t NODE_TYPE_CODE_UCCO2 = 12;
  static const uint8_t NODE_TYPE_CODE_VLV = 13;
  static const uint8_t NODE_TYPE_CODE_VLVRH = 14;
  static const uint8_t NODE_TYPE_CODE_VLVC02 = 16;
  static const uint8_t NODE_TYPE_CODE_BOX = 17;
  static const uint8_t NODE_TYPE_CODE_SWITCH = 18;
  static const uint8_t NODE_TYPE_CODE_IAV = 22;
  static const uint8_t NODE_TYPE_CODE_IAV_RH = 23;
  static const uint8_t NODE_TYPE_CODE_IAV_CO2 = 25;
  static const uint8_t NODE_TYPE_CODE_CTRL_UNIT = 27;
  static const uint8_t NODE_TYPE_CODE_CO2_RH_VLV = 28;
  static const uint8_t NODE_TYPE_CODE_UC_SUN = 29;
  static const uint8_t NODE_TYPE_CODE_UC_VC = 30;
  static const uint8_t NODE_TYPE_CODE_MULTI_ZONE = 31;
  static const uint8_t NODE_TYPE_CODE_BOX_RH = 35;
  static const uint8_t NODE_TYPE_CODE_BOX_CO2 = 37;
  static const uint8_t NODE_TYPE_CODE_RELAY = 38;
  static const uint8_t NODE_TYPE_CODE_WEATHER = 39;
  static const uint8_t NODE_TYPE_CODE_MOTOR_MODBUS = 40;
  static const uint8_t NODE_TYPE_CODE_DIGITAL_IN = 41;
  static const uint8_t NODE_TYPE_CODE_DIGITAL_OUT = 42;
  static const uint8_t NODE_TYPE_CODE_RELAY_MODBUS = 44;
  static const uint8_t NODE_TYPE_CODE_PERILEX = 45;
  static const uint8_t NODE_TYPE_CODE_RELAY_OUT = 46;


 protected:
  // start with a delay of 1000 loops
  uint32_t delay_{1000};
  uint8_t next_node_{0};
  bool waiting_for_response_ = false;

  std::vector<std::tuple<uint8_t, uint8_t>> nodes_;
};

#ifdef USE_TIME
class DucoTime : public DucoDevice, public PollingComponent {
 public:
  void setup() override;
  void update() override;

  void set_time_id(time::RealTimeClock *time_id) { this->time_id_ = time_id; }

  void receive_response(const DucoMessage &message) override;

 protected:
  time::RealTimeClock *time_id_{nullptr};
};
#endif

}  // namespace duco
}  // namespace esphome

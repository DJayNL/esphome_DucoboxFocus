#pragma once

#include "esphome/core/log.h"
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "../duco.h"

namespace esphome {
namespace duco {

class DucoCo2Sensor : public DucoDevice, public PollingComponent, public sensor::Sensor {
 public:
  void setup() override;
  void update() override;

  float get_setup_priority() const override;

  void receive_response(const DucoMessage &message) override;

  void set_address(uint8_t address);

 protected:
  uint8_t address_;
};

class DucoHumiditySensor : public DucoDevice, public PollingComponent, public sensor::Sensor {
 public:
  void setup() override;
  void update() override;

  float get_setup_priority() const override;

  void receive_response(const DucoMessage &message) override;

  void set_address(uint8_t address);

 protected:
  uint8_t address_;
};

class DucoTemperatureSensor : public DucoDevice, public PollingComponent, public sensor::Sensor {
 public:
  void setup() override;
  void update() override;

  float get_setup_priority() const override;

  void receive_response(const DucoMessage &message) override;

  void set_address(uint8_t address);

 protected:
  uint8_t address_;
};

class DucoFlowLevelValve1Sensor : public DucoDevice, public PollingComponent, public sensor::Sensor {
 public:
  void setup() override;
  void update() override;

  float get_setup_priority() const override;

  void receive_response(const DucoMessage &message) override;

  void set_address(uint8_t address);

 protected:
  uint8_t address_;
};

class DucoFlowLevelValve2Sensor : public DucoDevice, public PollingComponent, public sensor::Sensor {
 public:
  void setup() override;
  void update() override;

  float get_setup_priority() const override;

  void receive_response(const DucoMessage &message) override;

  void set_address(uint8_t address);

 protected:
  uint8_t address_;

};
class DucoBoxTemperatureSensor : public DucoDevice, public PollingComponent, public sensor::Sensor {
 public:
  void setup() override;
  void update() override;

  float get_setup_priority() const override;

  void receive_response(const DucoMessage &message) override;

  void set_type(uint8_t type);

 protected:
  uint8_t address_;
  uint8_t type_;
};

class DucoBypassSensor : public DucoDevice, public PollingComponent, public sensor::Sensor {
 public:
  void setup() override;
  void update() override;

  float get_setup_priority() const override;

  void receive_response(const DucoMessage &message) override;
};

class DucoFilterRemainingSensor : public DucoDevice, public PollingComponent, public sensor::Sensor {
 public:
  void setup() override;
  void update() override;

  float get_setup_priority() const override;

  void receive_response(const DucoMessage &message) override;
};

class DucoFlowLevelSensor : public DucoDevice, public PollingComponent, public sensor::Sensor {
 public:
  void setup() override;
  void update() override;

  float get_setup_priority() const override;

  void receive_response(const DucoMessage &message) override;
};

class DucoStateTimeRemainingSensor : public DucoDevice, public PollingComponent, public sensor::Sensor {
 public:
  void setup() override;
  void update() override;

  float get_setup_priority() const override;

  void receive_response(const DucoMessage &message) override;
};

class DucoScannerSensor : public DucoDevice, public PollingComponent, public sensor::Sensor {
 public:
  void setup() override {}
  void update() override;
  float get_setup_priority() const override;
  void receive_response(const DucoMessage &message) override;

  void set_address(uint8_t address);

 protected:
  uint8_t address_;

  uint8_t reg_start_ = 0x48;
  uint8_t reg_end_   = 0x4C;
  uint8_t current_reg_ = 0x48;

  uint8_t sub_index_ = 0x01;  // we’ll alternate 0x01 / 0x02
};

}  // namespace duco
}  // namespace esphome

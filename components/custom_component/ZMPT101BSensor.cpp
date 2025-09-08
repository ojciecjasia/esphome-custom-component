#include "esphome.h"
#include <Arduino.h>

#define FREQUENCY 50
#define CALIBRATE_READ 130

class ZMPT101BSensor : public PollingComponent, public Sensor {
  public:
    static ZMPT101BSensor *instance;   // global pointer

    ZMPT101BSensor(float reference_voltage) : PollingComponent(1000) {
      this->reference_voltage = reference_voltage;
      instance = this;  // store pointer to the one and only instance
    }

    void set_scale(float new_scale) {
      this->scale = new_scale;
    }

    float get_setup_priority() const override { return esphome::setup_priority::HARDWARE; }

    void setup() override {
      long sum = 0;
      const int samples = 500;
      for (int i = 0; i < samples; i++) {
        sum += analogRead(A0);
        delayMicroseconds(50);
      }
      zero_vac = sum / samples;

      // Initial scale (rough, updated later via calibration)
      scale = reference_voltage / CALIBRATE_READ;
    }

    void update() override {
      const int cycles = 5;
      float Vrms_sum = 0;

      for (int c = 0; c < cycles; c++) {
        uint32_t period = 1000000 / FREQUENCY;
        uint32_t t_start = micros();
        uint32_t Vsum = 0, measurements_count = 0;
        int32_t Vnow;

        while (micros() - t_start < period) {
          Vnow = analogRead(A0) - zero_vac;
          Vsum += Vnow * Vnow;
          measurements_count++;
        }

        Vrms_sum += sqrt(Vsum / measurements_count);
      }

      float Vrms_avg = Vrms_sum / cycles;
      float Vrms = Vrms_avg * scale;

      publish_state(Vrms);
    }

  private:
    float reference_voltage;
    float scale = 1.0;
    int zero_vac;
};

// define the static instance pointer
ZMPT101BSensor* ZMPT101BSensor::instance = nullptr;

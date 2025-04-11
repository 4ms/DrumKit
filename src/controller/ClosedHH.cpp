#include "ClosedHH.hpp"

#include <cstring>

ClosedHHModule::ClosedHHModule( ) {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

  auto numSamples = 14;
  auto defaultSample = 7;
  setupWidgetNames(numSamples, defaultSample);

  numModules = 2;

  setupSamples();
}

uint8_t ClosedHHModule::sampleId(uint8_t which) {
  float sample = paramValue(DRUM_PARAM + which, DRUM_CV + which, 0, 14);
  if (sample >= numSamples || sample < 0) {
    return 0;
  }

  return (uint8_t) sample;
}

void ClosedHHModule::setupSamples() {
  numSamples = 15;
  char name[32];

  for (uint8_t i = 0; i < numSamples; i++) {
    snprintf(name, sizeof name, "closedhh-%02d", i + 1);
    samples[i] = sampleManager->selectSample(name);
  }
}

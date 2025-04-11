#include "CR78.hpp"

#include <cstring>

CR78Module::CR78Module( ) {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

  auto numSamples = 6;
  auto defaultSample = 3;
  setupWidgetNames(numSamples, defaultSample);

  numModules = 2;

  setupSamples();
}

uint8_t CR78Module::sampleId(uint8_t which) {
  float sample = paramValue(DRUM_PARAM + which, DRUM_CV + which, 0, 15);
  if (sample >= numSamples || sample < 0) {
    return 0;
  }

  return (uint8_t) sample;
}

void CR78Module::setupSamples() {
  numSamples = 7;
  char name[32];

  for (uint8_t i = 0; i < numSamples; i++) {
    snprintf(name, sizeof name, "cr78-%02d", i + 1);
    samples[i] = sampleManager->selectSample(name);
  }
}

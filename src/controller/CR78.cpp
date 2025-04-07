#include "CR78.hpp"

#include <cstring>

CR78Module::CR78Module( ) {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  configParam(DRUM_PARAM, 0.0, 6.0, 3.0, "Sample Select Ch. 1");
  configParam(TUNE_PARAM, 0.2, 1.8, 1, "Playback Speed Ch. 1", "x");
  configInput(DRUM_CV, "Select CV Ch. 1");
  configInput(GATE_INPUT, "Gate Input Ch. 1");
  configInput(TUNE_CV, "Speed CV Ch. 1");
  configOutput(AUDIO_OUTPUT, "Ch. 1");

  configParam(DRUM_PARAM + 1, 0.0, 6.0, 3.0, "Sample Select Ch. 2");
  configParam(TUNE_PARAM + 1, 0.2, 1.8, 1, "Playback Speed Ch. 2", "x");
  configInput(DRUM_CV + 1, "Select CV Ch. 2");
  configInput(GATE_INPUT + 1, "Gate Input Ch. 2");
  configInput(TUNE_CV + 1, "Speed CV Ch. 2");
  configOutput(AUDIO_OUTPUT + 1, "Ch. 2");

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

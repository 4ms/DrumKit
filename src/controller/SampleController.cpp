#include "SampleController.hpp"

SampleController::SampleController( ) {
  for (uint8_t i = 0; i < MAX_MODULES; i++) {
    cv[i] = new SynthDevKit::CV(0.5f);
  }

  numSamples = 0;
  numModules = 0;
}

SampleController::~SampleController() {
  for (uint8_t i = 0; i < MAX_MODULES; i++)
    delete cv[i];
}

void SampleController::setupWidgetNames(unsigned numSamples, unsigned defaultSample) {
  for (int i = 0; i < 2; i++) {
	  auto chan = "Ch. " + std::to_string(i + 1);
	  configParam(DRUM_PARAM + i, 0.0, numSamples, defaultSample, "Select " + chan);
	  configParam(TUNE_PARAM + i, 0.2, 1.8, 1, "Playback Speed " + chan, "x");
	  configInput(DRUM_CV + i, "Sample Select CV " + chan);
	  configInput(GATE_INPUT + i, "Gate " + chan);
	  configInput(TUNE_CV + i, "Tune CV " + chan);
	  configOutput(AUDIO_OUTPUT + i, "Out " + chan);
  }

}

float SampleController::paramValue (uint16_t param, uint16_t input, float low, float high) {
  float current = params[param].getValue();

  if (inputs[input].isConnected()) {
    // high - low, divided by one tenth input voltage, plus the current value
    current += ((inputs[input].getVoltage() / 10) * (high - low));
  }

  return clamp(current, low, high);
}

DrumKit::Sample *SampleController::getSample(uint8_t current) {
  if (numSamples == 0) {
    return nullptr;
  }
  if (current < 1 || current >= numSamples) {
    return samples[ 0 ];
  }
  return samples[ current - 1 ];
}

void SampleController::process(const ProcessArgs &args) {
  for (uint8_t i = 0; i < numModules; i++) {
    if (inputs[GATE_INPUT + i].isConnected()) {
      float input = inputs[GATE_INPUT + i].getVoltage();

      cv[i]->update(input);
      if (cv[i]->newTrigger()) {
        ctx[i].reset();
      }
    }

    if (outputs[AUDIO_OUTPUT + i].isConnected()) {
      uint8_t which = sampleId(i);
      ctx[i].sample = getSample(which);
      float tune = clamp(params[TUNE_PARAM + i].getValue() + (inputs[TUNE_CV + i].isConnected() ? inputs[TUNE_CV + i].getVoltage() : 0.0f), 0.2, 1.8);
      float output = sampleManager->step(&ctx[i], tune, args.sampleRate);
      outputs[AUDIO_OUTPUT + i].setVoltage(output);
    }
  }
}

void SampleController::setupSamples( ) { }
uint8_t SampleController::sampleId(uint8_t which) { return 0; }
float SampleController::getTune(uint8_t which) { return 1.0f; }

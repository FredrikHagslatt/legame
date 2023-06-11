#ifndef EFFECTVECTOR_H
#define EFFECTVECTOR_H

#include <string>
#include <vector>

struct Effect // This is not the component
{
  std::string type;
  float duration;
  float intensity;

  Effect(const std::string &effectType, float effectDuration, float effectIntensity)
      : type(effectType),
        duration(effectDuration),
        intensity(effectIntensity) {}
};

struct EffectVector // This is the component that stores one or multiple effects
{
  std::vector<Effect> effects;

  EffectVector() {}

  void AddEffect(const Effect &effect)
  {
    effects.push_back(effect);
  }
};

#endif
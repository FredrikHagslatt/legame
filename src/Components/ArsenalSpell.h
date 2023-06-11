#ifndef SPELLSPECS_H
#define SPELLSPECS_H

#include <string>

struct ArsenalSpell
{
	std::string name;
	float castingTime;
	float cooldownTotal;
	float cooldownRemaining;
	std::string animationName;
	std::string soundName;

	ArsenalSpell(const std::string &spellName, float castingTime, float cooldownTotal, const std::string &animationName, const std::string &soundName)
		: name(spellName),
		  castingTime(castingTime),
		  cooldownTotal(cooldownTotal),
		  cooldownRemaining(0.0f),
		  animationName(animationName),
		  soundName(soundName) {}
};

#endif
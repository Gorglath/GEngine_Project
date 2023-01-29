#include "Vector3.h"

const GEngine::GVector3 GEngine::GVector3::zeroVector{ 0,0,0 };
const GEngine::GVector3 GEngine::GVector3::oneVector{ 1,1,1 };
const GEngine::GVector3 GEngine::GVector3::upVector{ 0,1,0 };
const GEngine::GVector3 GEngine::GVector3::downVector{ 0,-1,0 };
const GEngine::GVector3 GEngine::GVector3::rightVector{ 1,0,0 };
const GEngine::GVector3 GEngine::GVector3::leftVector{ -1,0,0 };
const GEngine::GVector3 GEngine::GVector3::forwardVector{ 0,0,1 };
const GEngine::GVector3 GEngine::GVector3::backVector{ 0,0,-1 };
const GEngine::GVector3 GEngine::GVector3::negativeInfinityVector{ std::numeric_limits<float>::min() };
const GEngine::GVector3 GEngine::GVector3::positiveInfinityVector{ std::numeric_limits<float>::max() };
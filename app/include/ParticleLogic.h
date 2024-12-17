#ifndef __PARTICLELOGIC_H__
#define __PARTICLELOGIC_H__

struct ParticleCanvas;

class ParticleLogic
{
public:
    static void Water(ParticleCanvas& canvas, int index, int x, int y);
    static void Sand(ParticleCanvas& canvas, int index, int x, int y);
};

#endif // __PARTICLELOGIC_H__
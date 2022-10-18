using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SimpleNoiseFilter : INoiseFilter {
    SimplexNoise noise = new SimplexNoise();
    NoiseSettings settings;

    public SimpleNoiseFilter(NoiseSettings settings) {
        this.settings = settings;
    }

    public float Evaluate(Vector3 point) {
        float noiseValue = 0;
        float frequency = settings.baseRoughness;
        float amplitude = 1;

        for (int i = 0; i < settings.octaves; i++) {
            float value = (noise.Evaluate(point / settings.scale  * frequency + settings.offset) + 1f) * 0.5f * amplitude;
            
            noiseValue += value;

            frequency *= settings.roughness;
            amplitude *= settings.persistance;
        }

        noiseValue = noiseValue - settings.minValue;
        noiseValue = settings.strength * noiseValue;

        return noiseValue;
    }
}
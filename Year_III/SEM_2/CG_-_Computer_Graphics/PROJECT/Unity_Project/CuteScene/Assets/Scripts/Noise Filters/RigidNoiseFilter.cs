using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RigidNoiseFilter : INoiseFilter {
    SimplexNoise noise = new SimplexNoise();
    NoiseSettings settings;

    public RigidNoiseFilter(NoiseSettings settings) {
        this.settings = settings;
    }

    public float Evaluate(Vector3 point) {
        float noiseValue = 0;
        float frequency = settings.baseRoughness;
        float amplitude = 1;
        float weight = 1;

        for (int i = 0; i < settings.octaves; i++) {
            float value = 1 - Mathf.Abs(noise.Evaluate(point / settings.scale * frequency + settings.offset));
            value *= value;
            value *= weight;
            weight = value;

            noiseValue += value * amplitude;

            frequency *= settings.roughness;
            amplitude *= settings.persistance;
        }

        noiseValue = noiseValue - settings.minValue;
        noiseValue = settings.strength * noiseValue;

        return noiseValue;
    }
}
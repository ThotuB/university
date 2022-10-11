using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PerlinNoiseFilter : INoiseFilter {
    NoiseSettings settings;

    public PerlinNoiseFilter(NoiseSettings settings) {
        this.settings = settings;
    }

    public float Evaluate(Vector3 point) {
        float noiseValue = 0;

        float frequency = settings.baseRoughness;
        float amplitude = 1;

        for (int i = 0; i < settings.octaves; i++) {
            // float value = 1 - Mathf.Abs(noise.Evaluate(point / settings.scale * frequency + settings.offset));

            // noiseValue += value * amplitude;

            frequency *= settings.roughness;
            amplitude *= settings.persistance;
        }

        noiseValue = noiseValue - settings.minValue;
        noiseValue = settings.strength * noiseValue;

        return noiseValue;
    }
}

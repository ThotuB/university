using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapShapeGenerator
{
    MapShapeSettings settings;
    INoiseFilter[] noiseFilters;
    public MinMax elevationMinMax;

    public void UpdateSettings(MapShapeSettings settings) {
        this.settings = settings;
        this.noiseFilters = new INoiseFilter[settings.noiseLayers.Length];

        for (int i = 0; i < noiseFilters.Length; i++) {
            noiseFilters[i] = NoiseFilterFactory.CreateNoiseFilter(settings.noiseLayers[i].settings);
        }

        elevationMinMax = new MinMax();
    }

    public float GetUnscaledElevation(Vector3 pointOnUnitSphere) {
        float elevation = 0;

        for (int i = 0; i < noiseFilters.Length; i++) {
            if (!settings.noiseLayers[i].enabled) continue;

            elevation += noiseFilters[i].Evaluate(pointOnUnitSphere);
        }
        elevationMinMax.Push(elevation);

        return elevation;
    }

    public float GetScaledElevation(float unscaledElevation) {
        return settings.heightCurve.Evaluate(Mathf.InverseLerp(elevationMinMax.Min, elevationMinMax.Max, unscaledElevation));
    }

    public float GetTimeDif() {
        return (Mathf.Sin(settings.time / 10f) - 1f) * 5f;
    }
}

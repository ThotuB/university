using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShapeGenerator
{
    PlanetShapeSettings settings;
    INoiseFilter[] noiseFilters;
    public MinMax elevationMinMax;

    public void UpdateSettings(PlanetShapeSettings settings)
    {
        this.settings = settings;
        this.noiseFilters = new INoiseFilter[settings.noiseLayers.Length];

        for (int i = 0; i < noiseFilters.Length; i++)
        {
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
        float elevation = Mathf.Max(0, unscaledElevation);
        elevation = settings.radius * (1 + elevation);
        return elevation;
    }
}

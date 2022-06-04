using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlanetColorGenerator {
    PlanetColorSettings settings;
    Texture2D texture;
    const int textureResolution = 50;
    INoiseFilter biomeNoiseFilter;

    public void UpdateSettings(PlanetColorSettings settings) {
        this.settings = settings;

        if (texture == null || texture.height != settings.biomeColorSettings.biomes.Length) {
            texture = new Texture2D(textureResolution * 2, settings.biomeColorSettings.biomes.Length, TextureFormat.RGBA32, false);
        }
        this.biomeNoiseFilter = NoiseFilterFactory.CreateNoiseFilter(settings.biomeColorSettings.noise);
    }

    public void UpdateElevation(MinMax elevationMinMax) {
        settings.planetMaterial.SetVector("_elevationMinMax", new Vector4(elevationMinMax.Min, elevationMinMax.Max));
    }

    public float BiomePercent(Vector3 point) {
        float heightPercent = (point.y + 1) / 2f;
        heightPercent += (biomeNoiseFilter.Evaluate(point) - settings.biomeColorSettings.noiseOffset) * settings.biomeColorSettings.noiseStrength;
        float biomeIndex = 0;
        int numBiomes = settings.biomeColorSettings.biomes.Length;
        float blendRange = settings.biomeColorSettings.blend / 2f + 0.001f;

        for (int i = 0; i < numBiomes; i++) {
            float dist = heightPercent - settings.biomeColorSettings.biomes[i].startHeight;
            float weight = Mathf.InverseLerp(-blendRange, blendRange, dist);

            biomeIndex *= (1 - weight);
            biomeIndex += i * weight;
        }

        return biomeIndex / Mathf.Max(1, numBiomes - 1);
    }

    public void UpdateColors() {
        Color[] colors = new Color[texture.width * texture.height];
        int colorIndex = 0;
        foreach (var biome in settings.biomeColorSettings.biomes) {
            for (int i = 0; i < textureResolution * 2; i++) {
                Color gradientColor;
                if ( i < textureResolution) {
                    gradientColor = settings.oceanColor.Evaluate(i / (textureResolution - 1f));
                }
                else {
                    gradientColor = biome.gradient.Evaluate((i - textureResolution) / (textureResolution - 1f));
                }
                Color tintColor = biome.tint;

                colors[colorIndex] = gradientColor * (1 - biome.tintAlpha) + tintColor * biome.tintAlpha;
                colorIndex++;
            }
        }
        
        texture.SetPixels(colors);
        texture.Apply();
        settings.planetMaterial.SetTexture("_texture", texture);
    }
}
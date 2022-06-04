using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapColorGenerator {
    MapColorSettings settings;
    Texture2D texture;
    const int textureResolution = 50;

    public void UpdateSettings(MapColorSettings settings) {
        this.settings = settings;

        if (texture == null ) {
            texture = new Texture2D(textureResolution, 1);
        }
    }
    
    public void UpdateElevation(MinMax elevationMinMax) {
        settings.mapMaterial.SetVector("_mapMinMax", new Vector4(elevationMinMax.Min, elevationMinMax.Max));
    }

    public void UpdateColors() {
        Color[] colors = new Color[textureResolution];

        for (int i = 0; i < textureResolution; i++) {
            if ( i < textureResolution / 2) {
                colors[i] = settings.gradientLand.Evaluate(2f * i / (textureResolution));
            } else {
                colors[i] = settings.gradientWater.Evaluate(2f * (i - textureResolution / 2) / (textureResolution));
            }
        }
        
        texture.SetPixels(colors);
        texture.Apply();
        settings.mapMaterial.SetTexture("_textureMap", texture);
    }
}
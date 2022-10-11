using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu()]
public class PlanetShapeSettings : ScriptableObject {
    public float radius;
    public NoiseLayer[] noiseLayers;

    [System.Serializable]
    public class NoiseLayer {
        public bool enabled = true;
        public NoiseSettings settings;
    }
}

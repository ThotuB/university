using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu()]
public class MapShapeSettings : ScriptableObject {
    public AnimationCurve heightCurve;
    public float time;
    public NoiseLayer[] noiseLayers;

    [System.Serializable]
    public class NoiseLayer {
        public bool enabled = true;
        public NoiseSettings settings;
    }
}

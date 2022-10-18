using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu()]
public class MapColorSettings : ScriptableObject {
    public Material mapMaterial;
    public Gradient gradientLand;
    public Gradient gradientWater;
}
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class NoiseSettings {
    public enum FilterType {
        Simple,
        Rigid
        // Perlin
    }
    public FilterType filterType;
    public float scale;

    public float strength = 1;
    public float baseRoughness = 1;
    public float roughness = 2;
    public Vector3 offset;

    [Range(1, 10)]
    public int octaves = 3;
    [Range(0, 5)]
    public float persistance = 0.5f; 

    public float minValue;
}
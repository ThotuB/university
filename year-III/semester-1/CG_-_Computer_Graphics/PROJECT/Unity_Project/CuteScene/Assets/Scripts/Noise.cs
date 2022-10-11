using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class Noise {

    public static float[,] GenereateNoiseMap(int mapWidth, int mapHeight, float scale, int seed, int octaves, float persistance, float lacunarity, Vector2 offset) {
        float[,] noiseMap = new float[mapWidth, mapHeight];

        System.Random prng = new System.Random(seed);
        Vector2[] octaveOffsets = new Vector2[octaves];

        for (int i = 0; i < octaves; i++) {
            float offsetX = prng.Next(-100000, 100000) + offset.x;
            float offsetY = prng.Next(-100000, 100000) + offset.y;

            octaveOffsets[i] = new Vector2(offsetX, offsetY);
        }

        float maxNoiseValue = float.MinValue;
        float minNoiseValue = float.MaxValue;

        float halfWidth = mapWidth / 2f;
        float halfHeight = mapHeight / 2f;
        
        for (int y = 0; y < mapHeight; y++) {
            for (int x = 0; x < mapWidth; x++) {
                float amplitude = 1;
                float frequency = 1;
                
                float noiseValue = 0;

                for (int i = 0; i < octaves; i++) {
                    float sampleX = (x - halfWidth) / scale * frequency + octaveOffsets[i].x;
                    float sampleY = (y - halfHeight) / scale * frequency + octaveOffsets[i].y;

                    float perlinValue = Mathf.PerlinNoise(sampleX, sampleY) * 2 - 1;
                    noiseValue += perlinValue * amplitude;

                    amplitude *= persistance;
                    frequency *= lacunarity;
                }

                if (noiseValue > maxNoiseValue) {
                    maxNoiseValue = noiseValue;
                } else if (noiseValue < minNoiseValue) {
                    minNoiseValue = noiseValue;
                }

                noiseMap[x, y] = noiseValue;
            }
        }

        for (int y = 0; y < mapHeight; y++) {
            for (int x = 0; x < mapWidth; x++) {
                noiseMap[x, y] = Mathf.InverseLerp(minNoiseValue, maxNoiseValue, noiseMap[x, y]);
            }
        }

        return noiseMap;
    }

    public static bool[,] GenerateRandomMap(int mapWidth, int mapHeight, int seed, float threshold) {
        bool[,] randomMap = new bool[mapWidth, mapHeight];

        System.Random prng = new System.Random(seed);

        for (int y = 0; y < mapHeight; y++) {
            for (int x = 0; x < mapWidth; x++) {
                randomMap[x, y] = prng.Next(0, 100) < threshold;
            }
        }

        return randomMap;
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapMesh {
    MapShapeGenerator shapeGenerator;
    Mesh mesh;
    int resolution;
    float size;

    float[] unscaledHeights;
    float[] scaledHeights;

    public MapMesh(MapShapeGenerator shapeGenerator, Mesh mesh, int resolution, float size) {
        this.shapeGenerator = shapeGenerator;
        this.mesh = mesh;
        this.resolution = resolution;
        this.size = size;

        this.unscaledHeights = new float[resolution * resolution];
        this.scaledHeights = new float[resolution * resolution];
    }

    public void ConstructMesh() {
        Vector3[] vertices = new Vector3[resolution * resolution];
        int[] triangles = new int[(resolution - 1) * (resolution - 1) * 6];
        int triIndex = 0;
        Vector2[] uv = (mesh.uv.Length == vertices.Length) ? mesh.uv : new Vector2[vertices.Length];

        float scale = size / resolution;

        float dif = shapeGenerator.GetTimeDif();
        for (int y = 0; y < resolution; y++) {
            for (int x = 0; x < resolution; x++) {
                int i = x + y * resolution;
                Vector3 point = new Vector3(x * scale, y * scale, scale);

                unscaledHeights[i] = shapeGenerator.GetUnscaledElevation(point);
                scaledHeights[i] = shapeGenerator.GetScaledElevation(unscaledHeights[i]);
                
                if ( scaledHeights[i] < 0.5f ) {
                    uv[i].x = unscaledHeights[i] + dif;
                }
                else {
                    uv[i].x = unscaledHeights[i] - dif;
                }

                vertices[i] = new Vector3(x * scale, scaledHeights[i], -y * scale);

                if (x != resolution - 1 && y != resolution - 1) {
                    triangles[triIndex] = i;
                    triangles[triIndex + 1] = i + resolution + 1;
                    triangles[triIndex + 2] = i + resolution;

                    triangles[triIndex + 3] = i;
                    triangles[triIndex + 4] = i + 1;
                    triangles[triIndex + 5] = i + resolution + 1;
                    triIndex += 6;
                }
            }
        }

        mesh.Clear();
        mesh.vertices = vertices;
        mesh.triangles = triangles;
        mesh.RecalculateNormals();
        mesh.uv = uv;
    }

    public void UpdateUVs() {
        Vector2[] uv = mesh.uv;
        float dif = shapeGenerator.GetTimeDif();
        for (int y = 0; y < resolution; y++) {
            for (int x = 0; x < resolution; x++) {
                int i = x + y * resolution;
                
                if ( scaledHeights[i] < 0.5f ) {
                    uv[i].x = unscaledHeights[i] + dif;
                }
                else {
                    uv[i].x = unscaledHeights[i] - dif;
                }
            }
        }

        mesh.uv = uv;
    }
}
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Planet : MonoBehaviour {

    [Range(2,256)]
    public int resolution = 10;
    public bool autoUpdate = true;

    public Vector3 orbitPoint;
    public float orbitSpeed;
    public float rotationSpeed;

    public PlanetShapeSettings shapeSettings;
    public PlanetColorSettings colorSettings;

    [HideInInspector]
    public bool shapeSettingsFoldout;
    [HideInInspector]
    public bool colorSettingsFoldout;

    PlanetShapeGenerator shapeGenerator = new PlanetShapeGenerator();
    PlanetColorGenerator colorGenerator = new PlanetColorGenerator();

    [SerializeField, HideInInspector]
    MeshFilter[] meshFilters;
    PlanetFace[] terrainFaces;

    void Start() {
        GeneratePlanet();
    }

    void Update() {
        transform.RotateAround(orbitPoint, Vector3.forward, orbitSpeed);
        transform.Rotate(Vector3.left, rotationSpeed);
    }

	void Initialize() {
        shapeGenerator.UpdateSettings(shapeSettings);
        colorGenerator.UpdateSettings(colorSettings);

        if (meshFilters == null || meshFilters.Length == 0) {
            meshFilters = new MeshFilter[6];
        }
        terrainFaces = new PlanetFace[6];

        Vector3[] directions = { Vector3.up, Vector3.down, Vector3.left, Vector3.right, Vector3.forward, Vector3.back };

        for (int i = 0; i < 6; i++) {
            if (meshFilters[i] == null) {
                GameObject meshObj = new GameObject("mesh");
                meshObj.transform.parent = transform;

                meshObj.AddComponent<MeshRenderer>();
                meshFilters[i] = meshObj.AddComponent<MeshFilter>();
                meshFilters[i].sharedMesh = new Mesh();
            }
            meshFilters[i].GetComponent<MeshRenderer>().sharedMaterial = colorSettings.planetMaterial;

            terrainFaces[i] = new PlanetFace(shapeGenerator, meshFilters[i].sharedMesh, resolution, directions[i]);
        }
    }

    public void GeneratePlanet() {
        Initialize();
        GenerateMesh();
        GenerateColours();
    }

    public void OnShapeSettingsUpdated() {
        if (autoUpdate) {
            Initialize();
            GenerateMesh();
        }
    }

    public void OnColourSettingsUpdated() {
        if (autoUpdate) {
            Initialize();
            GenerateColours();
        }
    }

    void GenerateMesh() {
        foreach (PlanetFace face in terrainFaces) {
            face.ConstructMesh();
        }

        colorGenerator.UpdateElevation(shapeGenerator.elevationMinMax);
    }

    void GenerateColours() {
        colorGenerator.UpdateColors();
        foreach (PlanetFace face in terrainFaces) {
            face.UpdateUVs(colorGenerator);
        }
    }
}
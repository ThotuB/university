using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Map : MonoBehaviour {
    [Range(2,256)]
    public int resolution = 10;
    public float size = 10f;
    public bool autoUpdate = true;

    public MapShapeSettings shapeSettings;
    public MapColorSettings colorSettings;

    [HideInInspector]
    public bool shapeSettingsFoldout;
    [HideInInspector]
    public bool colorSettingsFoldout;

    MapShapeGenerator shapeGenerator = new MapShapeGenerator();
    MapColorGenerator colorGenerator = new MapColorGenerator();

    [SerializeField, HideInInspector]
    MeshFilter meshFilter;
    MapMesh mapMesh;

    void Start() {
        GenerateMap();
    }

    float lastfired;

    bool fire() {
        if (Time.time - lastfired > 0.1f) {
            lastfired = Time.time;
            return true;
        }
        return false;
    }
    
    void Update ()
    {
        bool updated = false;
        if (fire()) {
            shapeSettings.time += 0.2f;
            if (Input.GetKey("w") || Input.GetKey("up")) {
                shapeSettings.noiseLayers[1].settings.offset.y -= 0.01f;
                updated = true;
            }
            if (Input.GetKey("s") || Input.GetKey("down")) {
                shapeSettings.noiseLayers[1].settings.offset.y += 0.01f;
                updated = true;
            }
            if (Input.GetKey("a") || Input.GetKey("left")) {
                shapeSettings.noiseLayers[1].settings.offset.x -= 0.01f;
                updated = true;
            }
            if (Input.GetKey("d") || Input.GetKey("right")) {
                shapeSettings.noiseLayers[1].settings.offset.x += 0.01f;
                updated = true;
            }
            if (Input.GetKey("q")) {
                shapeSettings.noiseLayers[1].settings.offset.z += 0.01f;
                updated = true;
            }
            if (Input.GetKey("e")) {
                shapeSettings.noiseLayers[1].settings.offset.z -= 0.01f;
                updated = true;
            }

            if (Input.GetAxis("Mouse ScrollWheel") > 0f) {
                shapeSettings.time += 1f;
            }
            if (Input.GetAxis("Mouse ScrollWheel") < 0f) {
                shapeSettings.time -= 1f;
            }

            if ( updated ) {
                OnShapeSettingsUpdated();
            }
            mapMesh.UpdateUVs();
        }   
    }

    void Initialize() {
        shapeGenerator.UpdateSettings(shapeSettings);
        colorGenerator.UpdateSettings(colorSettings);

        if (meshFilter == null) {
            meshFilter = new MeshFilter();
        }

        if (meshFilter == null) {
            GameObject meshObj = new GameObject("mesh");
            meshObj.transform.parent = transform;

            meshObj.AddComponent<MeshRenderer>();
            meshFilter = meshObj.AddComponent<MeshFilter>();
            meshFilter.sharedMesh = new Mesh();
        }

        meshFilter.GetComponent<MeshRenderer>().sharedMaterial = colorSettings.mapMaterial;

        mapMesh = new MapMesh(shapeGenerator, meshFilter.sharedMesh, resolution, size);
    }

    public void GenerateMap() {
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
        mapMesh.ConstructMesh();

        colorGenerator.UpdateElevation(shapeGenerator.elevationMinMax);
    }

    void GenerateColours() {
        colorGenerator.UpdateColors();
    }
}
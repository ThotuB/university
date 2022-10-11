using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

[CustomEditor(typeof(Map))]
public class MapEditor : Editor
{
    Map map;
    Editor shapeEditor;
    Editor colorEditor;

	public override void OnInspectorGUI()
	{
        using (var check = new EditorGUI.ChangeCheckScope())
        {
            base.OnInspectorGUI();
            if (check.changed)
            {
                map.GenerateMap();
            }
        }

        if (GUILayout.Button("Generate Map"))
        {
            map.GenerateMap();
        }

        DrawSettingsEditor(map.shapeSettings, map.OnShapeSettingsUpdated, ref map.shapeSettingsFoldout, ref shapeEditor);
        DrawSettingsEditor(map.colorSettings, map.OnColourSettingsUpdated, ref map.colorSettingsFoldout, ref colorEditor);
	}

    void DrawSettingsEditor(Object settings, System.Action onSettingsUpdated, ref bool foldout, ref Editor editor)
    {
        if (settings is null) return;
        
        foldout = EditorGUILayout.InspectorTitlebar(foldout, settings);
        using (var check = new EditorGUI.ChangeCheckScope())
        {
            if (!foldout) return;
            
            CreateCachedEditor(settings, null, ref editor);
            editor.OnInspectorGUI();

            if (check.changed)
            {
                if (onSettingsUpdated is null) return;
                
                onSettingsUpdated();
            }
        }
    }

	private void OnEnable()
	{
        map = (Map)target;
	}
}

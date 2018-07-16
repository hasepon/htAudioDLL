using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

/// <summary>
/// https://www.urablog.xyz/entry/2017/10/22/183331
/// ここを拝借しました
/// </summary>
public class htArcDraw : MonoBehaviour
{
    private static readonly int TRIANGLE_COUNT = 12;
    private static readonly Color INNER_MESH_COLOR = new Color(1.0f, 0.0f, 0.0f, 0.9f);
    private static readonly Color OUTER_MESH_COLOR = new Color(0.0f, 0.5f, 0.0f, 0.3f);

    [DrawGizmo(GizmoType.NonSelected | GizmoType.Selected)]
    private static void DrawPointGizmos(htArcInfo i_object, GizmoType i_gizmoType)
    {
        if (i_object.Length <= 0.0f)
        {
            return;
        }

        Transform transform = i_object.transform;
        Vector3 pos = transform.position + Vector3.up * 0.01f; // 0.01fは地面と高さだと見づらいので調整用。
        Quaternion rot = transform.rotation;
        Vector3 scale = Vector3.one * i_object.Length;

        // InnerAngle
        if (i_object.InnerAngle > 0.0f)
        {
            Gizmos.color = INNER_MESH_COLOR;
            Mesh fanMesh = CreateFanMesh(i_object.InnerAngle, TRIANGLE_COUNT);

            Gizmos.DrawMesh(fanMesh, pos, rot * Quaternion.AngleAxis(90.0f, Vector3.forward), scale);
            Gizmos.DrawMesh(fanMesh, pos, rot * Quaternion.AngleAxis(270.0f, Vector3.forward), scale);
        }

        if (i_object.InnerAngle > 0.0f)
        {
            Gizmos.color = INNER_MESH_COLOR;
            Mesh fanMesh = CreateFanMesh(i_object.InnerAngle, TRIANGLE_COUNT);

            Gizmos.DrawMesh(fanMesh, pos, rot, scale);
            Gizmos.DrawMesh(fanMesh, pos, rot * Quaternion.AngleAxis(180.0f, Vector3.forward), scale);
        }


        // OuterAngle
        if (i_object.OuterAngle > 0.0f)
        {
            Gizmos.color = OUTER_MESH_COLOR;
            Mesh fanMesh = CreateFanMesh(i_object.OuterAngle, TRIANGLE_COUNT);

            Gizmos.DrawMesh(fanMesh, pos, rot * Quaternion.AngleAxis(90.0f, Vector3.forward), scale);
            Gizmos.DrawMesh(fanMesh, pos, rot * Quaternion.AngleAxis(270.0f, Vector3.forward), scale);
        }

        if (i_object.OuterAngle > 0.0f)
        {
            Gizmos.color = OUTER_MESH_COLOR;
            Mesh fanMesh = CreateFanMesh(i_object.OuterAngle, TRIANGLE_COUNT);

            Gizmos.DrawMesh(fanMesh, pos, rot, scale);
            Gizmos.DrawMesh(fanMesh, pos, rot * Quaternion.AngleAxis(180.0f, Vector3.forward), scale);
        }

    }

    private static Mesh CreatFunMesh(float i_angle, int i_triangleCount)
    {
        var mesh = new Mesh();

        mesh.vertices = null;
        mesh.triangles = null;

        mesh.RecalculateNormals();

        return mesh;
    }

    private static Vector3[] CreateFanVertices(float i_angle, int i_triangleCount)
    {
        if (i_angle <= 0.0f)
        {
            throw new System.ArgumentException(string.Format("角度がおかしい！ i_angle={0}", i_angle));
        }

        if (i_triangleCount <= 0)
        {
            throw new System.ArgumentException(string.Format("数がおかしい！ i_triangleCount={0}", i_triangleCount));
        }

        i_angle = Mathf.Min(i_angle, 360.0f);

        var vertices = new List<Vector3>(i_triangleCount + 2);

        // 始点
        vertices.Add(Vector3.zero);

        // Mathf.Sin()とMathf.Cos()で使用するのは角度ではなくラジアンなので変換しておく。
        float radian = i_angle * Mathf.Deg2Rad;
        float startRad = -radian / 2;
        float incRad = radian / i_triangleCount;

        for (int i = 0; i < i_triangleCount + 1; ++i)
        {
            float currentRad = startRad + (incRad * i);

            Vector3 vertex = new Vector3(Mathf.Sin(currentRad), 0.0f, Mathf.Cos(currentRad));
            vertices.Add(vertex);
        }

        return vertices.ToArray();
    }

    private static Mesh CreateFanMesh(float i_angle, int i_triangleCount)
    {
        var mesh = new Mesh();

        var vertices = CreateFanVertices(i_angle, i_triangleCount);

        var triangleIndexes = new List<int>(i_triangleCount * 3);

        for (int i = 0; i < i_triangleCount; ++i)
        {
            triangleIndexes.Add(0);
            triangleIndexes.Add(i + 1);
            triangleIndexes.Add(i + 2);
        }

        mesh.vertices = vertices;
        mesh.triangles = triangleIndexes.ToArray();

        mesh.RecalculateNormals();

        return mesh;
    }

}

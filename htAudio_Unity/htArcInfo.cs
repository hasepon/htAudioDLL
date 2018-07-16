using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class htArcInfo : MonoBehaviour {

    [SerializeField, Range(0.0f, 360.0f)]
    private float m_InnerAngle = 0.0f;
    [SerializeField, Range(0.0f, 360.0f)]
    private float m_OuterAngle = 0.0f;
    [SerializeField, Range(0.0f, 15.0f)]
    private float m_length = 0.0f;

    public float InnerAngle { get { return m_InnerAngle; } }
    public float OuterAngle { get { return m_OuterAngle; } }
    public float Length { get { return m_length; } set { m_length = value; } }

    htSpeaker Speaker;

    private void Start()
    {
        Speaker = gameObject.GetComponent<htSpeaker>();
        m_InnerAngle = Speaker.InnerAngle;
        m_OuterAngle = Speaker.OuterAngle;
    }

    private void Update()
    {
        Speaker.SetInnerAngle(m_InnerAngle);
        Speaker.SetOuterAngle(m_OuterAngle);
    }

}

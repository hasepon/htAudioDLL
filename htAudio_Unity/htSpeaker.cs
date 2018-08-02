using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;

public class htSpeaker : MonoBehaviour {

    [DllImport("OpenAL_Engine", CharSet = CharSet.Unicode)]
    public static extern IntPtr htaSpeakerCreateName([MarshalAs(UnmanagedType.LPWStr)]string filepath, [MarshalAs(UnmanagedType.LPWStr)]string soundname);
    [DllImport("OpenAL_Engine")]
    public static extern void htaSpeakerDelete(IntPtr instance);
    [DllImport("OpenAL_Engine")]
    public static extern bool Formatflag(IntPtr instance);
    [DllImport("OpenAL_Engine")]
    public static extern bool Play(IntPtr instance);
    [DllImport("OpenAL_Engine")]
    public static extern bool Update(IntPtr instance);
    [DllImport("OpenAL_Engine")]
    public static extern void htaSpeakerPosition(IntPtr instance, float x, float y, float z);
    [DllImport("OpenAL_Engine")]
    public static extern void htaSpeakerVelocity(IntPtr instance, float x, float y, float z);
    [DllImport("OpenAL_Engine")]
    public static extern void htaSpeakerDirection(IntPtr instance,float x, float y, float z);

    [DllImport("OpenAL_Engine")]
    public static extern void htaSpeakerSetConeOuterGain(IntPtr instance,float val);
    [DllImport("OpenAL_Engine")]
    public static extern void htaSpeakerSetConeInnerAngle(IntPtr instance, float val);
    [DllImport("OpenAL_Engine")]
    public static extern void htaSpeakerSetConeOuterAngle(IntPtr instance, float val);

    [DllImport("OpenAL_Engine")]
    public static extern float htaSpeakerGetConeOuterGain(IntPtr instance);
    [DllImport("OpenAL_Engine")]
    public static extern float htaSpeakerGetConeInnerAngle(IntPtr instance);
    [DllImport("OpenAL_Engine")]
    public static extern float htaSpeakerGetConeOuterAngle(IntPtr instance);

    IntPtr SpeakerPtr;

    float OuterGain;
    float innerAngle;
    float outerAngle;

    public float InnerAngle { get { return innerAngle; } }
    public float OuterAngle { get { return outerAngle; } }

    public string path;
    public string testname;

    htArcInfo arcinfo;

    // Use this for initialization
    void Start ()
    {
        SpeakerPtr = htaSpeakerCreateName(path, testname);

        bool clear = Formatflag(SpeakerPtr);

        Debug.Log(clear);

        Play(SpeakerPtr);

        arcinfo = gameObject.AddComponent<htArcInfo>();

        arcinfo.Length = 3;

    }
	
	// Update is called once per frame
	void FixedUpdate ()
    {
        // アングル設定
        htaSpeakerSetConeInnerAngle(SpeakerPtr,innerAngle);
        htaSpeakerSetConeOuterAngle(SpeakerPtr,outerAngle);
        htaSpeakerSetConeOuterGain(SpeakerPtr, 1);
        
        htaSpeakerPosition(SpeakerPtr,transform.position.x, transform.position.y, transform.position.z);
        //htaSpeakerDirection(SpeakerPtr, transform.forward.x, transform.forward.y, transform.forward.z);

    }

    private void OnApplicationQuit()
    {
        if (SpeakerPtr != IntPtr.Zero)
        {
            htaSpeakerDelete(SpeakerPtr);
            SpeakerPtr = IntPtr.Zero;
        }
    }

    private void OnDisable()
    {
        if (SpeakerPtr != IntPtr.Zero)
        {
            htaSpeakerDelete(SpeakerPtr);
            SpeakerPtr = IntPtr.Zero;
        }
    }

    private void OnDestroy()
    {
        if (SpeakerPtr != null)
        {
            htaSpeakerDelete(SpeakerPtr);
            SpeakerPtr = IntPtr.Zero;
        }
    }

    public void SetOuterAngle( float angle)
    {
        htaSpeakerSetConeOuterAngle(SpeakerPtr, angle);
    }

    public void SetInnerAngle(float angle)
    {
        htaSpeakerSetConeInnerAngle(SpeakerPtr, angle);
    }

}

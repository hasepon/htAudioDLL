using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;

public class htListener : MonoBehaviour {

    [DllImport("OpenAL_Engine")]
    public static extern IntPtr htaListenerCreate();
    [DllImport("OpenAL_Engine")]
    public static extern void htaListenerDelete(IntPtr intPtr);

    [DllImport("OpenAL_Engine")]
    public static extern void htaListenerPosition(IntPtr intPtr, float x, float y, float z);
    [DllImport("OpenAL_Engine")]
    public static extern void htaListenerPositionArray(IntPtr intPtr, float[] Pos);
    [DllImport("OpenAL_Engine")]
    public static extern void htaListenerVelocity(IntPtr intPtr, float x, float y, float z);
    [DllImport("OpenAL_Engine")]
    public static extern void htaListenerVelocityArray(IntPtr intPtr, float[] Pos);
    [DllImport("OpenAL_Engine")]
    public static extern void htaListenerOrientation(IntPtr intPtr, float[] AtVec, float[] UpVec);
    [DllImport("OpenAL_Engine")]
    public static extern void htaListenerOrientationArray(IntPtr intPtr, float[] AtOrient);

    IntPtr ListenerPtr;

    // Use this for initialization
    void Start () {
        ListenerPtr = htaListenerCreate();
    }
	
	// Update is called once per frame
	void FixedUpdate() {

        float[] vec =  new float[3] { 0, 0, 0 };
        float[] At = new float[3] { transform.forward.x, transform.forward.y, transform.forward.z };
        float[] Up = new float[3] { transform.up.x, transform.up.y, transform.up.z };

        htaListenerOrientation(ListenerPtr, At,Up);
        htaListenerVelocityArray(ListenerPtr, vec);
        htaListenerPosition(ListenerPtr,transform.position.x,transform.position.y, transform.position.z);
    }

    private void OnDestroy()
    {
        htaListenerDelete(ListenerPtr);
    }

}

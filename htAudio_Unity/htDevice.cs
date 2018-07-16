using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;

public class htDevice : MonoBehaviour {


    [DllImport("OpenAL_Engine")]
    public static extern bool htaCreate(ref IntPtr instance);

    [DllImport("OpenAL_Engine")]
    public static extern void htaDelete(IntPtr intPtr);

    IntPtr OpenalPtr;

    // Use this for initialization
    void Awake () {
        htaCreate(ref OpenalPtr);
    }
	
	// Update is called once per frame
	void OnApplicationQuit()
    {
        htaDelete(OpenalPtr);
    }
}

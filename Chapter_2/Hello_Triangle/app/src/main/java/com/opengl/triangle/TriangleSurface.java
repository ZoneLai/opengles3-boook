package com.opengl.triangle;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;


public class TriangleSurface extends GLSurfaceView {

    private static final String TAG = "TriangleSurface";
    private Context mContext;
    private TriangleRenderer triangleRenderer;

    public TriangleSurface(Context context) {
        this(context, null);
    }

    public TriangleSurface(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        if (detectOpenGLES30()) {
            // Tell the surface view we want to create an OpenGL ES 3.0-compatible
            // context, and set an OpenGL ES 3.0-compatible renderer.
            setEGLContextClientVersion(3);
            triangleRenderer = new TriangleRenderer(context);
            setRenderer(triangleRenderer);
        } else {
            Log.e(TAG, "OpenGL ES 3.0 not supported on device.  Exiting...");
        }
    }

    private boolean detectOpenGLES30() {
        ActivityManager am = (ActivityManager) mContext.getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo info = am.getDeviceConfigurationInfo();
        return (info.reqGlEsVersion >= 0x30000);
    }

    @Override
    public void onResume() {
        super.onResume();
        setRenderMode(RENDERMODE_WHEN_DIRTY);
        triangleRenderer.onResume();
    }

    @Override
    public void onPause() {
        super.onPause();
        triangleRenderer.onPause();
    }

    public void onStop() {
        triangleRenderer.onStop();
    }

    public void onDestroy() {
        triangleRenderer.onDestroy();
    }
}

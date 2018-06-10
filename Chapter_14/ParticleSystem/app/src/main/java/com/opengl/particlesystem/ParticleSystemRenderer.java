package com.opengl.particlesystem;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class ParticleSystemRenderer implements GLSurfaceView.Renderer {

    static {
        System.loadLibrary("opengl-lib");
    }

    private Context mContext;

    public ParticleSystemRenderer(Context context) {
        mContext = context;
        nativeOnCreate();
    }

    @Override
    public void onSurfaceCreated(GL10 glUnused, EGLConfig config) {
        nativeInitGL(mContext.getAssets(), "smoke.png");
    }

    @Override
    public void onSurfaceChanged(GL10 glUnused, int width, int height) {
        nativeOnSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 glUnused) {
        nativeDrawFrame();
    }

    public void onResume() {
        nativeOnResume();
    }

    public void onPause() {
        nativeOnPause();
    }

    public void onStop() {
        nativeOnStop();
    }

    public void onDestroy() {
        nativeOnDestroy();
    }

    private static native void nativeOnCreate();

    private static native void nativeInitGL(AssetManager assetManager, String fileName);

    private static native void nativeOnResume();

    private static native void nativeOnPause();

    private static native void nativeOnStop();

    private static native void nativeOnDestroy();

    private static native void nativeDrawFrame();

    private static native void nativeOnSurfaceChanged(int width, int height);
}

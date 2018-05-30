package com.opengl.vbo;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;


public class CenterSurfaceView extends GLSurfaceView {

    private VboRenderer mVboRenderer;

    public CenterSurfaceView(Context context) {
        super(context);
    }

    public CenterSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextClientVersion(3);
        mVboRenderer = new VboRenderer(context);
        setRenderer(mVboRenderer);
    }

    @Override
    public void onResume() {
        super.onResume();
        setRenderMode(RENDERMODE_WHEN_DIRTY);
        mVboRenderer.onResume();
    }

    @Override
    public void onPause() {
        super.onPause();
        mVboRenderer.onPause();
    }
}

package com.opengl.vao;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;


public class CenterSurfaceView extends GLSurfaceView {

    private VaoRenderer mVaoRenderer;

    public CenterSurfaceView(Context context) {
        super(context);
    }

    public CenterSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextClientVersion(3);
        mVaoRenderer = new VaoRenderer(context);
        setRenderer(mVaoRenderer);
    }

    @Override
    public void onResume() {
        super.onResume();
        setRenderMode(RENDERMODE_WHEN_DIRTY);
        mVaoRenderer.onResume();
    }

    @Override
    public void onPause() {
        super.onPause();
        mVaoRenderer.onPause();
    }
}

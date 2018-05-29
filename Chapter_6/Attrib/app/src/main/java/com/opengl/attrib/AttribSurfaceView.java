package com.opengl.attrib;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;


public class AttribSurfaceView extends GLSurfaceView {

    private AttribRenderer mAttribRenderer;

    public AttribSurfaceView(Context context) {
        super(context);
    }

    public AttribSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextClientVersion(3);
        mAttribRenderer = new AttribRenderer(context);
        setRenderer(mAttribRenderer);
    }

    @Override
    public void onResume() {
        super.onResume();
        setRenderMode(RENDERMODE_WHEN_DIRTY);
        mAttribRenderer.onResume();
    }

    @Override
    public void onPause() {
        super.onPause();
        mAttribRenderer.onPause();
    }
}

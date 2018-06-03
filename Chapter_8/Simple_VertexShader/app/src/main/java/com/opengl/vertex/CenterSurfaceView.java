package com.opengl.vertex;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;


public class CenterSurfaceView extends GLSurfaceView {

    private VertexRenderer mVertexRenderer;

    public CenterSurfaceView(Context context) {
        super(context);
    }

    public CenterSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextClientVersion(3);
        mVertexRenderer = new VertexRenderer(context);
        setRenderer(mVertexRenderer);
    }

    @Override
    public void onResume() {
        super.onResume();
        //setRenderMode(RENDERMODE_WHEN_DIRTY);
        mVertexRenderer.onResume();
    }

    @Override
    public void onPause() {
        super.onPause();
        mVertexRenderer.onPause();
    }
}

package com.opengl.triangle;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;


public class TriangleSurface extends GLSurfaceView {

    private TriangleRenderer triangleRenderer;

    public TriangleSurface(Context context) {
        this(context, null);
    }

    public TriangleSurface(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextClientVersion(3);
        triangleRenderer = new TriangleRenderer(context);
        setRenderer(triangleRenderer);
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

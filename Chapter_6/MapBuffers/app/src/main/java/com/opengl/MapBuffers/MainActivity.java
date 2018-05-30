package com.opengl.MapBuffers;

import android.app.Activity;
import android.os.Bundle;

/**
 * Activity class for example program that detects OpenGL ES 3.0.
 **/
public class MainActivity extends Activity {

    private CenterSurfaceView mCenterSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.avtivity_main);
        mCenterSurfaceView = findViewById(R.id.sv_triangle);
    }

    @Override
    protected void onResume() {
        super.onResume();
        mCenterSurfaceView.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        mCenterSurfaceView.onPause();
    }
}

package com.github.seanstone.ndkexample;

import android.app.Activity;
import android.widget.TextView;
import android.os.Bundle;

public class JniConsole extends Activity
{
    TextView textview;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        textview = new TextView(this);
        setContentView(textview);

        String str = stringFromJNI();
        textview.setText(str);
    }

    public void print(String string)
    {
        textview.setText(string);
    }

    public native String stringFromJNI();

    static
    {
        System.loadLibrary("NDKExample");
    }
}

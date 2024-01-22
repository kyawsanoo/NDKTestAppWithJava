package kso.android.ndktestapp;

public class Helper {
    // Used to load the 'ndkappjava' library on application startup.
    static {
        System.loadLibrary("ndktest-lib");
    }
    public native String greetingFromJNI();
}

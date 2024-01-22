package kso.android.ndktestapp;

import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

import kso.android.ndktestapp.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'ndktest-lib' library on application startup.
    static {
        System.loadLibrary("ndktest-lib");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        Helper test = new Helper();
        binding.sampleText1.setText(stringFromJNI() + ", " + test.greetingFromJNI());
        int sum = add(1, 2);
        binding.sampleText2.setText("1+2=" + sum);
        int stringLength = getStrLen("HelloWorld");
        binding.sampleText3.setText("length of 'HelloWorld' = " + stringLength);
        int sumOfArray = addArray(new int[]{0,1,2,3});
        binding.sampleText4.setText("add Array[0, 1, 2, 3] = " + sumOfArray);
        saveArray(new int[]{0,1,2,3});
        int sumOfSaveArray = addSavedArray();
        binding.sampleText5.setText("addSavedArray = " + sumOfSaveArray);
        Employee employee = getEmployeeFromJNI();
        binding.sampleText6.setText("employee name = " + employee.getName());
        String message = getInfo();
        binding.sampleText7.setText("Info = " + message);
    }

    private String getMessage(){ //fun call by JNI
        showLog();
        return "Kotlin";
    }
    private void showLog(){
        Log.e("MainActivity", "Calling kotlin function from JNI");
    }


    /**
     * A native method that is implemented by the 'ndkappjava' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int add(int a, int b);

    public native int getStrLen(String s);

    public native int addArray(int[] intArr);

    public native void saveArray(int[] intArr);

    public native int addSavedArray();

    public native Employee getEmployeeFromJNI();

    public native String getInfo();

}
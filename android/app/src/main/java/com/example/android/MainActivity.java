package com.example.android;

import androidx.appcompat.app.AppCompatActivity;

import android.animation.ObjectAnimator;
import android.animation.PropertyValuesHolder;
import android.app.Dialog;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Bundle;
import android.text.Editable;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;


public class MainActivity extends AppCompatActivity {
    private String Ip;
    private int port;
    private int fan=0;
    private int light=0;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        SharedPreferences sharedPreferences = getSharedPreferences("server", MODE_PRIVATE);
        this.Ip = sharedPreferences.getString("IP", "");
        this.port= sharedPreferences.getInt("Port", 0);
        EditText txtIp = (EditText)findViewById(R.id.txtIp);
        EditText txtPort = (EditText)findViewById(R.id.txtPort);
        txtIp.setText(Ip);
        txtPort.setText(Integer.toString(port));


    }
    public void fan(View v){
        ImageView btnFan = (ImageView) findViewById(R.id.btnfan);
        ImageView btnLight = (ImageView) findViewById(R.id.btnlight);
        EditText txtSend = (EditText) findViewById(R.id.txtSend);
        Button  btnSend = (Button)findViewById(R.id.btnSend);
        btnFan.setColorFilter(Color.argb(100, 0, 255, 0));
        if (fan == 1){
            txtSend.setText("fanOn");
            send("fanOn");
            fan=fan-1;
            btnFan.setColorFilter(Color.argb(100, 255, 0, 0));


        }else {
            txtSend.setText("fanOff");
            send("fanOff");
            fan=fan+1;
            btnFan.setColorFilter(Color.argb(100, 0, 0, 255));
        }
    }
    public void light(View v){
        ImageView btnFan = (ImageView) findViewById(R.id.btnfan);
        ImageView btnLight = (ImageView) findViewById(R.id.btnlight);
        EditText txtSend = (EditText) findViewById(R.id.txtSend);
        Button  btnSend = (Button)findViewById(R.id.btnSend);
        if(light==1) {
            txtSend.setText("lightOn");
            send("lightOn");
            light=light-1;
            btnLight.setColorFilter(Color.argb(100, 255, 0, 0));
        }else{
            txtSend.setText("lightOff");
            send("lightOff");
            light=light+1;
            btnLight.setColorFilter(Color.argb(100, 0, 0, 255));
        }
    }
    public void save(View v){
        SharedPreferences sharedPreferences = getSharedPreferences("server", MODE_PRIVATE);
        EditText txtIp = (EditText)findViewById(R.id.txtIp);
        EditText txtPort = (EditText)findViewById(R.id.txtPort);
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.clear();
        editor.putString("IP",txtIp.getText().toString());
        editor.putInt("Port",Integer.parseInt(txtPort.getText().toString()));
        editor.apply();
    }
    public void custon(View v){
        EditText txtSend = (EditText) findViewById(R.id.txtSend);
        send(txtSend.getText().toString());
    }
    public void send(String message){
        Server server=new Server(Ip,port,message);
        Thread thread=new Thread(server);
        thread.start();
        try {
            thread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        /*String result = server.getReply();
        EditText txtSend = (EditText) findViewById(R.id.txtSend);
        txtSend.setText(result);
        server.setReply();*/
    }
    public void inbuiltlight(View v){
        EditText txtSend = (EditText) findViewById(R.id.txtSend);
        txtSend.setText("blueoff");
        send("blueoff");
    }
    public void showbox(View v){
        Dialog myDialog = new Dialog(this);
        myDialog.setContentView(R.layout.server_box);
        myDialog.show();
        Button myButton = myDialog.findViewById(R.id.btnOk);

        myButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                SharedPreferences sharedPreferences = getSharedPreferences("server", MODE_PRIVATE);
                EditText etIp = (EditText) myDialog.findViewById(R.id.etIp);
                EditText etPort = (EditText) myDialog.findViewById(R.id.etPort);
                if (etIp.getText().toString().trim().isEmpty()) {
                    etIp.setError("IP can not be empty"); // Set an error message for the empty field
                    etIp.requestFocus();
                } else if (etPort.getText().toString().trim().isEmpty()) {
                    etPort.setError("Port?"); // Set an error message for the empty field
                    etPort.requestFocus();
                } else if (etIp.getText().toString().trim().isEmpty() && etPort.getText().toString().trim().isEmpty()) {
                    etIp.setError("IP can not be empty"); // Set an error message for the empty field
                    etPort.setError("Port?"); // Set an error message for the empty field
                    etIp.requestFocus();

                } else {
                    SharedPreferences.Editor editor = sharedPreferences.edit();
                    editor.clear();
                    editor.putString("IP", etIp.getText().toString());
                    editor.putInt("Port", Integer.parseInt(etPort.getText().toString()));
                    editor.apply();
                    MainActivity.this.Ip = sharedPreferences.getString("IP", "");
                    MainActivity.this.port = sharedPreferences.getInt("Port", 0);
                    EditText txtIp = (EditText) findViewById(R.id.txtIp);
                    EditText txtPort = (EditText) findViewById(R.id.txtPort);
                    txtIp.setText(Ip);
                    txtPort.setText(String.valueOf(port));
                    myDialog.dismiss(); // Dismiss the dialog to close the pop-up

                }
            }
        });
    }

}
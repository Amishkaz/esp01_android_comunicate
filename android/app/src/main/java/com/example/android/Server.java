package com.example.android;

import android.util.Log;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class Server implements Runnable{
    private static final String TAG = "TestClient";
    private Socket socket;
    private DataInputStream dataInputStream;
    private DataOutputStream dataOutputStream;
    String reply;
    String ipAddress;
    int portNumber;
    String message;
    public Server(String ipAddress, int portNumber , String message) {
        this.ipAddress = ipAddress;
        this.portNumber = portNumber;
        this.message=message;
    }

    @Override
    public void run() {
        try {
            // create new socket and connect to the server
            this.socket = new Socket(ipAddress,portNumber);
        } catch (IOException e) {
            Log.e(TAG, "failed to create socket", e);
            return;
        }

        Log.d(TAG, "connected");

        try {
            this.dataInputStream = new DataInputStream(new BufferedInputStream(this.socket.getInputStream()));
            this.dataOutputStream = new DataOutputStream(new BufferedOutputStream(this.socket.getOutputStream()));
            dataOutputStream.writeBytes(message+"\n");
            dataOutputStream.flush(); // make sure the message is sent immediately
            BufferedReader reader = new BufferedReader(new InputStreamReader(dataInputStream));
            this.reply = reader.readLine();
            socket.close();
        } catch (IOException e) {
            Log.e(TAG, "failed to create streams", e);
            return;
        }


    }
    public String getReply(){
        return this.reply;
    }
    public void setReply(){
        this.reply=null;
    }
}
package com.mrwxb.dongcheng;

import android.Manifest;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

public class SplashActivity extends AppCompatActivity {
    public Handler mHandler=new Handler(){
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            if(msg.what==107){
                startActivity(new Intent(SplashActivity.this,MyMainActivity.class));
                //startActivity(new Intent(SplashActivity.this,Test.class));
                finish();
            }

        }
    };
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
         super.onCreate(savedInstanceState);
         setContentView(R.layout.activity_splash);
         SharedPreferences.Editor editor=getSharedPreferences("data",MODE_PRIVATE).edit();
         editor.putString("APPID","709595400f7046818cbd48a61942a3ae");
         editor.putString("APPSECRET","673e371033384f26bf1ae6ba9634b5e7");
         editor.putString("PRODUCTKEY","01e0fe474fec4b1e94fda97f45977af6");
         editor.putString("PRODUCTSECRET","62844d53834b4e4d941f20de606e5c61");
         editor.apply();
         chekAndroidPermissiong();
    }

    private void chekAndroidPermissiong() {
        //如果系统高于或等于6.0，需要动态授权
        if(Build.VERSION.SDK_INT>=23){ requestRunPermissions(new String[]{Manifest.permission.READ_EXTERNAL_STORAGE ,
                Manifest.permission.WRITE_EXTERNAL_STORAGE,
                Manifest.permission.ACCESS_FINE_LOCATION,
                Manifest.permission.ACCESS_WIFI_STATE,
                Manifest.permission.READ_PHONE_STATE,
                Manifest.permission.ACCESS_COARSE_LOCATION});//打开精准定位后，在开启GPS，6.0以上才能查到SSID，否则显示unknown ssid
        }
        else {
            mHandler.sendEmptyMessageDelayed(107,1000);

        }
    }
    private void requestRunPermissions(String[] strings) {
        int status=0;
        for(String permisson:strings){
            if(ContextCompat.checkSelfPermission(this,permisson)!=PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(this, strings, 108);
            }
            else{
            status++;
            }
        }
        if(status==6){
            mHandler.sendEmptyMessageDelayed(107,1000);

        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
      switch (requestCode){
          case 108:
              if(grantResults.length>0){
                  List<String> deniodePermission =new ArrayList<>();
                  for(int i=0;i<grantResults.length;i++){
                      int grantPerminssin=grantResults[i];
                      String permission=permissions[i];
                      if(grantPerminssin!=PackageManager.PERMISSION_GRANTED){
                          deniodePermission.add(permission);
                      }
                      if(deniodePermission.isEmpty()){
                       mHandler.sendEmptyMessage(107);

                      }
                      else {
                          Toast.makeText(this, "拒绝了部分授权", Toast.LENGTH_SHORT).show();
                          mHandler.sendEmptyMessageDelayed(107,1000);
                      }
                  }


              }

      }

    }



}

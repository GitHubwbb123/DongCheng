package com.mrwxb.dongcheng;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.annotation.Nullable;
import android.text.InputType;
import android.util.Log;
import android.view.View;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.gizwits.gizwifisdk.enumration.GizWifiErrorCode;
import com.qmuiteam.qmui.widget.dialog.QMUIDialog;
import com.qmuiteam.qmui.widget.dialog.QMUIDialogAction;
import com.wxb.mygizlib.ui.BaseDeviceControlActivity;

import java.util.concurrent.ConcurrentHashMap;

//子类
public class DeviceControlActivity extends BaseDeviceControlActivity implements View.OnClickListener {
    private  String LED1NAME="";
    private  String LED2NAME="";
    private  String LED3NAME="";
    private  String LED4NAME="";
    private  String LED5NAME="";
    private  String LED6NAME="";
    private  String LED7NAME="";
    private  String LED8NAME="";
    private  String IN1NAME="";
    private  String IN2NAME="";
    private  String IN3NAME="";
    private  String IN4NAME="";
    private Switch mLED1;
    private Switch mLED2;
    private Switch mLED3;
    private Switch mLED4;
    private Switch mLED5;
    private Switch mLED6;
    private Switch mLED7;
    private Switch mLED8;
    private TextView mWD1;
    private TextView mWD2;
    private Switch mIN1;
    private Switch mIN2;
    private Switch mIN3;
    private Switch mIN4;
    private  static final String LED_1="LED1";
    private  static final String LED_2="LED2";
    private  static final String LED_3="LED3";
    private  static final String LED_4="LED4";
    private  static final String LED_5="LED5";
    private  static final String LED_6="LED6";
    private  static final String LED_7="LED7";
    private  static final String LED_8="LED8";
    private  static final String TEM_1="TEM1";
    private  static final String TEM_2="TEM2";
    private  static final String IN_1="IN1";
    private  static final String IN_2="IN2";
    private  static final String IN_3="IN3";
    private  static final String IN_4="IN4";
    // End Of Content View Elements
    private boolean  led1Switch=false;
    private boolean  led2Switch=false;
    private boolean  led3Switch=false;
    private boolean  led4Switch=false;
    private boolean  led5Switch=false;
    private boolean  led6Switch=false;
    private boolean  led7Switch=false;
    private boolean  led8Switch=false;
    private static double data_TEM1;
    private static double data_TEM2;
    private boolean  in1Switch=false;
    private boolean  in2Switch=false;
    private boolean  in3Switch=false;
    private boolean  in4Switch=false;

    private void bindViews() {
        mLED1 = (Switch) findViewById(R.id.Led1);
        mLED2 = (Switch) findViewById(R.id.Led2);
        mLED3 = (Switch) findViewById(R.id.Led3);
        mLED4 = (Switch) findViewById(R.id.Led4);
        mLED5 = (Switch) findViewById(R.id.Led5);
        mLED6 = (Switch) findViewById(R.id.Led6);
        mLED7 = (Switch) findViewById(R.id.Led7);
        mLED8 = (Switch) findViewById(R.id.Led8);
        mWD1  = (TextView) findViewById(R.id.Wd1);
        mWD2  = (TextView) findViewById(R.id.Wd2);
        mIN1 = (Switch) findViewById(R.id.In1);
        mIN2 = (Switch) findViewById(R.id.In2);
        mIN3 = (Switch) findViewById(R.id.In3);
        mIN4 = (Switch) findViewById(R.id.In4);

        mLED1.setOnClickListener(this);
        mLED2.setOnClickListener(this);
        mLED3.setOnClickListener(this);
        mLED4.setOnClickListener(this);
        mLED5.setOnClickListener(this);
        mLED6.setOnClickListener(this);
        mLED7.setOnClickListener(this);
        mLED8.setOnClickListener(this);


    }
    private Handler mHandler =new Handler(){
        @Override
        public void dispatchMessage(Message msg) {
            super.dispatchMessage(msg);

            if(msg.what==108){
                updateUI();

            }
        }
    };

    private void updateUI() {
     mWD1.setText("温度"+data_TEM1+"℃");
     mWD2.setText("湿度"+data_TEM1+"%");
     mLED1.setChecked(led1Switch);
     mLED2.setChecked(led2Switch);
     mLED3.setChecked(led3Switch);
     mLED4.setChecked(led4Switch);
     mLED5.setChecked(led5Switch);
     mLED6.setChecked(led6Switch);
     mLED7.setChecked(led7Switch);
     mLED8.setChecked(led8Switch);
     mIN1.setChecked(in1Switch);
     mIN2.setChecked(in2Switch);
     mIN3.setChecked(in3Switch);
     mIN4.setChecked(in4Switch);
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_device_control);
        initView();
    }

    private void initView() {
        mTopBar=findViewById(R.id.topBarCon);
        mTopBar.addLeftImageButton(com.wxb.mygizlib.R.mipmap.ic_back,com.wxb.mygizlib.R.id.topbar_left_icon).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });
        mTopBar.addRightTextButton("编辑节点名称",com.wxb.mygizlib.R.id.text).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                showReNamePointDialogClick();

            }
        });
        //判断名字改过没有，如果改过，就同步新的名字
        String tempTitle=mDevice.getAlias().isEmpty() ? mDevice.getProductName():mDevice.getAlias();
        mTopBar.setTitle(tempTitle);
        bindViews();
        pointNameInit();
    }
private  void pointNameInit(){
    SharedPreferences editor=getSharedPreferences("data",MODE_PRIVATE);
    //节点名字获取
    LED1NAME=editor.getString("LED1NAME","");
    LED2NAME=editor.getString("LED2NAME","");
    LED3NAME=editor.getString("LED3NAME","");
    LED4NAME=editor.getString("LED4NAME","");
    LED5NAME=editor.getString("LED5NAME","");
    LED6NAME=editor.getString("LED6NAME","");
    LED7NAME=editor.getString("LED7NAME","");
    LED8NAME=editor.getString("LED8NAME","");
    IN1NAME=editor.getString("IN1NAME","");
    IN2NAME=editor.getString("IN2NAME","");
    IN3NAME=editor.getString("IN3NAME","");
    IN4NAME=editor.getString("IN4NAME","");
    mLED1.setText(LED1NAME);
    mLED2.setText(LED2NAME);
    mLED3.setText(LED3NAME);
    mLED4.setText(LED4NAME);
    mLED5.setText(LED5NAME);
    mLED6.setText(LED6NAME);
    mLED7.setText(LED7NAME);
    mLED8.setText(LED8NAME);
    mIN1.setText(IN1NAME);
    mIN2.setText(IN2NAME);
    mIN3.setText(IN3NAME);
    mIN4.setText(IN4NAME);
}


    /******
     * 弹出节点名字修改选择对话框，选择节点
     */
    private void showReNamePointDialogClick() {
        //显示弹窗
        String[] items=new String[]{mLED1.getText().toString(),mLED2.getText().toString(),mLED3.getText().toString(),mLED4.getText().toString(),mLED5.getText().toString(),mLED6.getText().toString(),mLED7.getText().toString(),mLED8.getText().toString(),mIN1.getText().toString(),mIN2.getText().toString(),mIN3.getText().toString(),mIN4.getText().toString()};

        new QMUIDialog.MenuDialogBuilder(this).addItems(items, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                switch (i){
                    case 0:
                        showReNamePointDialog(mLED1);
                        break;
                    case 1:
                        showReNamePointDialog(mLED2);
                        break;
                    case 2:
                        showReNamePointDialog(mLED3);
                        break;
                    case 3:
                        showReNamePointDialog(mLED4);
                        break;
                    case 4:
                        showReNamePointDialog(mLED5);
                        break;
                    case 5:
                        showReNamePointDialog(mLED6);
                        break;
                    case 6:
                        showReNamePointDialog(mLED7);
                        break;
                    case 7:
                        showReNamePointDialog(mLED8);
                        break;
                  /* case 8:
                     //   showReNamePointDialog(mWD1);
                      //  break;
                    //case 9:
                      //  showReNamePointDialog(mWD2);
                      //  break;*/
                    case 8:
                        showReNamePointDialog(mIN1);
                        break;
                    case 9:
                       showReNamePointDialog(mIN2);
                        break;
                     case 10:
                        showReNamePointDialog(mIN3);
                        break;
                    case 11:
                        showReNamePointDialog(mIN4);
                        break;

                }
                dialogInterface.dismiss();
            }
        }).show();

    }
    //重命名节点
    private void showReNamePointDialog(final  Switch switchId) {
        final QMUIDialog.EditTextDialogBuilder builder=new QMUIDialog.EditTextDialogBuilder(this);
        builder.setTitle("重命名")
                .setInputType(InputType.TYPE_CLASS_TEXT)
                .setPlaceholder("在此输入新名称")
                .addAction("取消", new QMUIDialogAction.ActionListener() {
                    @Override
                    public void onClick(QMUIDialog dialog, int index) {
                        dialog.dismiss();
                    }
                })
                .addAction("确认", new QMUIDialogAction.ActionListener() {
                    @Override
                    public void onClick(QMUIDialog dialog, int index) {
                        String newName= builder.getEditText().getText().toString().trim();
                        if(newName.isEmpty()){
                            Toast.makeText(DeviceControlActivity.this,"输入为空",Toast.LENGTH_SHORT).show();

                        }
                        else{
                            switchId.setText(newName);
                            SharedPreferences.Editor editor=getSharedPreferences("data",MODE_PRIVATE).edit();
                            switch (switchId.getId()){
                                case R.id.Led1:
                                    editor.putString("LED1NAME",newName);
                                    break;
                                case R.id.Led2:
                                    editor.putString("LED2NAME",newName);
                                    break;
                                case R.id.Led3:
                                    editor.putString("LED3NAME",newName);
                                    break;
                                case R.id.Led4:
                                    editor.putString("LED4NAME",newName);
                                    break;
                              case R.id.Led5:
                                    editor.putString("LED5NAME",newName);
                                    break;
                                case R.id.Led6:
                                    editor.putString("LED6NAME",newName);
                                    break;
                                case R.id.Led7:
                                    editor.putString("LED7NAME",newName);
                                    break;
                                case R.id.Led8:
                                    editor.putString("LED8NAME",newName);
                                    break;
                                case R.id.In1:
                                    editor.putString("IN1NAME",newName);
                                    break;
                                case R.id.In2:
                                    editor.putString("IN2NAME",newName);
                                    break;
                                case R.id.In3:
                                    editor.putString("IN3NAME",newName);
                                    break;
                                case R.id.In4:
                                    editor.putString("IN4NAME",newName);
                                    break;

                            }
                            editor.apply();

                        }
                        dialog.dismiss();

                    }
                })
                .show();
    }

    @Override
    protected void receiveCloudData(GizWifiErrorCode result, ConcurrentHashMap<String, Object> dataMap) {
        super.receiveCloudData(result, dataMap);
        Log.e("ZNJJ","子类界面"+dataMap);
        if(result==GizWifiErrorCode.GIZ_SDK_SUCCESS){
            if(dataMap!=null){

                parseReceiveData(dataMap);
            }

        }
    }
//解析数据
    private void parseReceiveData(ConcurrentHashMap<String, Object> dataMap) {
        if(dataMap.get("data")!=null){
            ConcurrentHashMap<String, Object> tempperDataMap= ( ConcurrentHashMap<String, Object>)dataMap.get("data");
                for(String dataKey:tempperDataMap.keySet()){
                    //温度
                    //通过云端定义的标识符来同步数据如LED1
                    if(dataKey.equals(LED_1)){
                        led1Switch= (boolean) tempperDataMap.get(LED_1);
                    }
                    if(dataKey.equals(LED_2)){
                        led2Switch= (boolean) tempperDataMap.get(LED_2);
                    }
                    if(dataKey.equals(LED_3)){
                        led3Switch= (boolean) tempperDataMap.get(LED_3);
                    }
                    if(dataKey.equals(LED_4)){
                        led4Switch= (boolean) tempperDataMap.get(LED_4);
                    }
                   if(dataKey.equals(LED_5)){
                        led5Switch= (boolean) tempperDataMap.get(LED_5);
                    }
                    if(dataKey.equals(LED_6)){
                        led6Switch= (boolean) tempperDataMap.get(LED_6);
                    }
                    if(dataKey.equals(LED_7)){
                        led7Switch= (boolean) tempperDataMap.get(LED_7);
                    }
                    if(dataKey.equals(LED_8)){
                        led8Switch= (boolean) tempperDataMap.get(LED_8);
                    }

                    if(dataKey.equals(TEM_1)){
                        if (tempperDataMap.get(dataKey) instanceof Integer) {
                            data_TEM1 = (Integer) tempperDataMap.get(dataKey);
                        } else {
                            data_TEM1 = (Double) tempperDataMap.get(dataKey);
                        }
                    }
                    if(dataKey.equals(TEM_2)){
                        if (tempperDataMap.get(dataKey) instanceof Integer) {
                            data_TEM2 = (Integer) tempperDataMap.get(dataKey);
                        } else {
                            data_TEM2 = (Double) tempperDataMap.get(dataKey);
                        }
                    }

                    if(dataKey.equals(IN_1)){
                        in1Switch= (boolean) tempperDataMap.get(IN_1);

                    }
                    if(dataKey.equals(IN_2)){
                        in2Switch= (boolean) tempperDataMap.get(IN_2);

                    }
                    if(dataKey.equals(IN_3)){
                        in3Switch= (boolean) tempperDataMap.get(IN_3);
                    }
                    if(dataKey.equals(IN_4)){
                        in4Switch= (boolean) tempperDataMap.get(IN_4);

                    }



                }
                mHandler.sendEmptyMessage(108);
        }

    }

    //按钮回调
    @Override
    public void onClick(View view) {
      if(view.getId()== R.id.Led1) {
          sendCommand(LED_1, mLED1.isChecked());
      }
      else if(view.getId()== R.id.Led2){
              sendCommand(LED_2,mLED2.isChecked());
      }
      else if(view.getId()== R.id.Led3){
          sendCommand(LED_3,mLED3.isChecked());
      }
      else if(view.getId()== R.id.Led4){
          sendCommand(LED_4,mLED4.isChecked());
      }
      else if(view.getId()== R.id.Led5){
          sendCommand(LED_5,mLED5.isChecked());
      }
      else if(view.getId()== R.id.Led6){
          sendCommand(LED_6,mLED6.isChecked());
      }
      else if(view.getId()== R.id.Led7){
          sendCommand(LED_7,mLED7.isChecked());
      }
      else if(view.getId()== R.id.Led8){
          sendCommand(LED_8,mLED8.isChecked());
      }
    }
}

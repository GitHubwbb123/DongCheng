/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related       hardware initialization 
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/

#include <stdio.h>
#include <string.h>
#include "hal_uart.h"
#include "gizwits_product.h"
#include "common.h"
#include "Hal_key.h"
static uint32_t timerMsCount;

/** User area the current device state structure*/
extern dataPoint_t currentDataPoint;

/**@} */
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
  uint8_t i = 0;
  dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
  protocolTime_t *ptime = (protocolTime_t *)gizdata;
  
#if MODULE_TYPE
  gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
  moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

  if((NULL == info) || (NULL == gizdata))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
    switch(info->event[i])
    {
      case EVENT_LED1:
        currentDataPoint.valueLED1 = dataPointPtr->valueLED1;
        GIZWITS_LOG("Evt: EVENT_LED1 %d \n", currentDataPoint.valueLED1);
        if(0x01 == currentDataPoint.valueLED1)
        {
          //user handle
          P2DIR|=BIT0;
          P2OUT&=~BIT0;
        }
        else
        {
          //user handle  
          P2DIR|=BIT0;
          P2OUT|=BIT0;
        }
        break;
      case EVENT_LED2:
        currentDataPoint.valueLED2 = dataPointPtr->valueLED2;
        GIZWITS_LOG("Evt: EVENT_LED2 %d \n", currentDataPoint.valueLED2);
        if(0x01 == currentDataPoint.valueLED2)
        {
          //user handle
          P2DIR|=BIT1;
          P2OUT&=~BIT1;
        }
        else
        {
          //user handle    
          P2DIR|=BIT1;
          P2OUT|=BIT1;
        }
        break;
      case EVENT_LED3:
        currentDataPoint.valueLED3 = dataPointPtr->valueLED3;
        GIZWITS_LOG("Evt: EVENT_LED3 %d \n", currentDataPoint.valueLED3);
        if(0x01 == currentDataPoint.valueLED3)
        {
          //user handle
          P2DIR|=BIT2;
          P2OUT&=~BIT2;
        }
        else
        {
          //user handle   
          P2DIR|=BIT2;
          P2OUT|=BIT2;
        }
        break;
      case EVENT_LED4:
        currentDataPoint.valueLED4 = dataPointPtr->valueLED4;
        GIZWITS_LOG("Evt: EVENT_LED4 %d \n", currentDataPoint.valueLED4);
        if(0x01 == currentDataPoint.valueLED4)
        {
          //user handle
          P2DIR|=BIT3;
          P2OUT&=~BIT3;
        }
        else
        {
          //user handle  
          P2DIR|=BIT3;
          P2OUT|=BIT3;
        }
        break;
      case EVENT_LED5:
        currentDataPoint.valueLED5 = dataPointPtr->valueLED5;
        GIZWITS_LOG("Evt: EVENT_LED5 %d \n", currentDataPoint.valueLED5);
        if(0x01 == currentDataPoint.valueLED5)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_LED6:
        currentDataPoint.valueLED6 = dataPointPtr->valueLED6;
        GIZWITS_LOG("Evt: EVENT_LED6 %d \n", currentDataPoint.valueLED6);
        if(0x01 == currentDataPoint.valueLED6)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_LED7:
        currentDataPoint.valueLED7 = dataPointPtr->valueLED7;
        GIZWITS_LOG("Evt: EVENT_LED7 %d \n", currentDataPoint.valueLED7);
        if(0x01 == currentDataPoint.valueLED7)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_LED8:
        currentDataPoint.valueLED8 = dataPointPtr->valueLED8;
        GIZWITS_LOG("Evt: EVENT_LED8 %d \n", currentDataPoint.valueLED8);
        if(0x01 == currentDataPoint.valueLED8)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;




      case WIFI_SOFTAP:
        break;
      case WIFI_AIRLINK:
        break;
      case WIFI_STATION:
        break;
      case WIFI_CON_ROUTER:
 
        break;
      case WIFI_DISCON_ROUTER:
 
        break;
      case WIFI_CON_M2M:
 
        break;
      case WIFI_DISCON_M2M:
        break;
      case WIFI_RSSI:
        GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
        break;
      case TRANSPARENT_DATA:
        GIZWITS_LOG("TRANSPARENT_DATA \n");
        //user handle , Fetch data from [data] , size is [len]
        break;
      case WIFI_NTP:
        GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
        break;
      case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
      #if MODULE_TYPE
            GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
      #else
            GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
      #endif
    break;
      default:
        break;
    }
  }

  return 0;
}

/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void userHandle(void)
{
 
    currentDataPoint.valueIN1 =BUTTON_S2 ;//Add Sensor Data Collection
    currentDataPoint.valueIN2 = 0;//Add Sensor Data Collection
    currentDataPoint.valueIN3 =P1IN&BIT2 ;//Add Sensor Data Collection
    currentDataPoint.valueIN4 = P1IN&BIT2;//Add Sensor Data Collection
    currentDataPoint.valueTEM1 =80 ;//Add Sensor Data Collection
    currentDataPoint.valueTEM2 = 100;//Add Sensor Data Collection

    
    
}

/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    
    /** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
    /*
      currentDataPoint.valueLED1 = ;
      currentDataPoint.valueLED2 = ;
      currentDataPoint.valueLED3 = ;
      currentDataPoint.valueLED4 = ;
      currentDataPoint.valueLED5 = ;
      currentDataPoint.valueLED6 = ;
      currentDataPoint.valueLED7 = ;
      currentDataPoint.valueLED8 = ;
      currentDataPoint.valueIN1 = ;
      currentDataPoint.valueIN2 = ;
      currentDataPoint.valueIN3 = ;
      currentDataPoint.valueIN4 = ;
      currentDataPoint.valueTEM1 = ;
      currentDataPoint.valueTEM2 = ;
    */

}


/**
* @brief Millisecond timing maintenance function, milliseconds increment, overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief Read millisecond count

* @param none
* @return millisecond count
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}


/**
* @brief MCU reset function

* @param none
* @return none
*/
void mcuRestart(void)
{
         ((void (*)())0xFFFE)();
}

/**@} */

/**


/**
* @brief Serial port write operation, send data to WiFi module
*
* @param buf      : buf address
* @param len      : buf length
*
* @return : Return effective data length;-1，return failure
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
    uint32_t i = 0;
    
    if(NULL == buf)
    {
        return -1;
    }

#ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%4d:%4d]: ", gizGetTimerCount(), len);
    for(i=0; i<len; i++)
    {
        GIZWITS_LOG("%02x ", buf[i]);

        if(i >=2 && buf[i] == 0xFF)
        {
            GIZWITS_LOG("%02x ", 0x55);
        }
    }

    GIZWITS_LOG("\n");
#endif
    
    for(i=0; i<len; i++)
    {
        uart1_byte(buf[i]);
        if(i >=2 && buf[i] == 0xFF)
        {
          uart1_byte(0x55);
        }
    }
        
    return len;
}
